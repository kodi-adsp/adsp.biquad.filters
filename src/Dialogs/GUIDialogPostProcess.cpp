/*
 *      Copyright (C) 2005-2014 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */



#include "GUIDialogPostProcess.h"
#include "utils/stdStringUtils.h"
#include "BiquadFiltersSettings.h"
#include "Messages/BiquadMessage_types.h"
#include "template/include/ADSPAddonHandler.h"
#include "DSPProcessor.h"
#include <asplib/Biquads/apslib_BiquadFactory.h>
#include <math.h>

using namespace asplib;
using namespace std;

#define BUTTON_OK             10050
#define BUTTON_CANCEL         10051
#define BUTTON_DEFAULT        10052
#define SLIDER_PREAMP         8000
#define SLIDER_PREAMP_LABEL   8100
#define SLIDER_PREAMP_VALUE   8200
#define SLIDER_32Hz           8001
#define SLIDER_32Hz_LABEL     8101
#define SLIDER_32Hz_VALUE     8201
#define SLIDER_64Hz           8002
#define SLIDER_64Hz_LABEL     8102
#define SLIDER_64Hz_VALUE     8202
#define SLIDER_125Hz          8003
#define SLIDER_125Hz_LABEL    8103
#define SLIDER_125Hz_VALUE    8203
#define SLIDER_250Hz          8004
#define SLIDER_250Hz_LABEL    8104
#define SLIDER_250Hz_VALUE    8204
#define SLIDER_500Hz          8005
#define SLIDER_500Hz_LABEL    8105
#define SLIDER_500Hz_VALUE    8205
#define SLIDER_1kHz           8006
#define SLIDER_1kHz_LABEL     8106
#define SLIDER_1kHz_VALUE     8206
#define SLIDER_2kHz           8007
#define SLIDER_2kHz_LABEL     8107
#define SLIDER_2kHz_VALUE     8207
#define SLIDER_4kHz           8008
#define SLIDER_4kHz_LABEL     8108
#define SLIDER_4kHz_VALUE     8208
#define SLIDER_8kHz           8009
#define SLIDER_8kHz_LABEL     8109
#define SLIDER_8kHz_VALUE     8209
#define SLIDER_16kHz          8010
#define SLIDER_16kHz_LABEL    8110
#define SLIDER_16kHz_VALUE    8210

std::string float_dB_toString(float dB);

CGUIDialogPostProcess::CGUIDialogPostProcess() :
	CGUIDialogBase(	"DialogParametricEQ.xml", false, true )
{
  for(int band = 0; band < MAX_FREQ_BANDS +1; band++)
  {
    m_Sliders[band] = NULL;
    for(int ch = AE_DSP_CH_FL; ch < AE_DSP_CH_MAX; ch++)
    {
      m_Gains[ch][band] = 0.0f;
      m_InitialGains[ch][band] = 0.0f;
    }
  }
}

CGUIDialogPostProcess::~CGUIDialogPostProcess()
{
}

bool CGUIDialogPostProcess::OnInit()
{
  // get current gain settings from BiquadFiltersSettings Manager
  for(int band = 0; band < MAX_FREQ_BANDS +1; band++)
  {
    m_Sliders[band] = GUI->Control_getSlider(m_window, SLIDER_PREAMP + band);
    if(!m_Sliders[band])
    {
      KODI->Log(ADDON::LOG_ERROR, "Slider with ID: %i (%s) not found!", SLIDER_PREAMP + band, KODI->GetLocalizedString(30150 + band));
      return false;
    }

    for(int ch = AE_DSP_CH_FL; ch < AE_DSP_CH_MAX; ch++)
    {
      if(!CBiquadFiltersSettings::Get().get_Parametric10BandEQGain((AE_DSP_CHANNEL)ch, (CBiquadFiltersSettings::PARAMETRIC_10BAND_EQ_BANDS)band, &m_InitialGains[ch][band]))
      {
        m_InitialGains[ch][band] = 0.0f;
      }

      // clamp value
      if(m_InitialGains[ch][band] > ABS_MAX_GAIN)
      {
        m_InitialGains[ch][band] = ABS_MAX_GAIN;
      }
      else if(m_InitialGains[ch][band] < -ABS_MAX_GAIN)
      {
        m_InitialGains[ch][band] = -ABS_MAX_GAIN;
      }

      m_Gains[ch][band] = m_InitialGains[AE_DSP_CH_FL][band];
    }

    m_Sliders[band]->SetFloatRange(-ABS_MAX_GAIN, ABS_MAX_GAIN);
    m_Sliders[band]->SetFloatValue(m_InitialGains[AE_DSP_CH_FL][band]);
    m_window->SetControlLabel(SLIDER_PREAMP_LABEL + band, KODI->GetLocalizedString(30150 + band));
    m_window->SetControlLabel(SLIDER_PREAMP_VALUE + band, float_dB_toString(m_InitialGains[AE_DSP_CH_FL][band]).c_str());
  }

	return true;
}

bool CGUIDialogPostProcess::OnClick(int controlId)
{
  switch(controlId)
  {
    case BUTTON_OK:
    {
      CBiquadFiltersSettings &settingsManager = CBiquadFiltersSettings::Get();
      for(int ch = AE_DSP_CH_FL; ch < AE_DSP_CH_MAX; ch++)
      {
        for(int band = 0; band < MAX_FREQ_BANDS +1; band++)
        {
          if(m_Gains[ch][band] != m_InitialGains[ch][band])
          {
            settingsManager.set_Parametric10BandEQGain((AE_DSP_CHANNEL)ch, (CBiquadFiltersSettings::PARAMETRIC_10BAND_EQ_BANDS)band, m_Gains[ch][band]);
          }
        }
      }
      settingsManager.save_Parametric10BandEQSettings();
      this->Close();
    }
    break;

    case BUTTON_CANCEL:
    {
      // set frequency bands to 0dB
      CADSPModeMessage message;
      message.set_AudioChannel(AE_DSP_CH_MAX);
      message.set_ProcessingModeId(POST_MODE_PARAMETRIC_EQ_ID);
      message.set_MessageType(CDSPProcessor::EQ_MESSAGE_BIQUAD_COEFFICIENTS_LIST);
      BIQUAD_COEFFICIENTS_VECTOR coefficientsVector;
      for(AE_DSP_STREAM_ID id = 0; id < AE_DSP_STREAM_MAX_STREAMS; id++)
      {
        AE_DSP_SETTINGS streamSettings;
        AE_DSP_STREAM_PROPERTIES streamProperties;
        BIQUAD_INFOS BiquadInfos;
        coefficientsVector.clear();
        if(g_AddonHandler.GetStreamInfos(id, &streamSettings, &streamProperties, (void*)&BiquadInfos) == AE_DSP_ERROR_NO_ERROR)
        { // send new gain values to the biquad filter
          for(uint32_t band = 0; band < MAX_FREQ_BANDS; band++)
          {
            BIQUAD_COEFFICIENTS coefficients;
            ASPLIB_ERR err = CBiquadFactory::get_constQPeakingBiquadCoes(streamSettings.iProcessSamplerate, MAX_FREQ_BANDS, m_InitialGains[AE_DSP_CH_FL][band +1], band, &coefficients.coefficients);
            if(err == ASPLIB_ERR_NO_ERROR)
            {
              coefficients.biquadIndex = band;
              coefficients.c0 = 1.0f;
              coefficients.d0 = 0.0f;
              coefficientsVector.push_back(coefficients);
            }
            else
            {
              KODI->Log(ADDON::LOG_ERROR, "%s line %i: Failed getting const Q Peaking biquad coefficients from asplin!", __func__, __LINE__);
            }
          }

          if(coefficientsVector.size() > 0)
          {
            message.set_StreamId(id);
            message.set_MessageDataSize(sizeof(BIQUAD_COEFFICIENTS)*coefficientsVector.size());
            message.set_MessageData((void*)coefficientsVector.data());

            // send message to AddonHandler
            g_AddonHandler.SendMessageToStream(message);
          }
          else
          {
            KODI->Log(ADDON::LOG_ERROR, "%s line %i: Invalid coefficient list!", __func__, __LINE__);
          }
        }
        else
        {
          KODI->Log(ADDON::LOG_ERROR, "%s line %i: Failed getting audio stream infos!", __func__, __LINE__);
        }
      }
      this->Close();
    }
    break;

    case BUTTON_DEFAULT:
    {
      for(int band = 0; band < MAX_FREQ_BANDS +1; band++)
      {
        for(int ch = AE_DSP_CH_FL; ch < AE_DSP_CH_MAX; ch++)
        {
          m_Gains[ch][band] = 0.0f;
        }
        m_Sliders[band]->SetFloatValue(m_Gains[AE_DSP_CH_FL][band]);
        m_window->SetControlLabel(SLIDER_PREAMP_VALUE + band, float_dB_toString(m_Gains[AE_DSP_CH_FL][band]).c_str());
      }

      // set post gain to 0dB
      CADSPModeMessage message;
      message.set_AudioChannel(AE_DSP_CH_MAX);
      message.set_ProcessingModeId(POST_MODE_PARAMETRIC_EQ_ID);
      message.set_MessageData((void*)&m_Gains[AE_DSP_CH_FL][0], sizeof(float));
      message.set_MessageType(CDSPProcessor::EQ_MESSAGE_POST_GAIN);
      for(AE_DSP_STREAM_ID id = 0; id < AE_DSP_STREAM_MAX_STREAMS; id++)
      {
        AE_DSP_SETTINGS streamSettings;
        AE_DSP_STREAM_PROPERTIES streamProperties;
        BIQUAD_INFOS BiquadInfos;
        if(g_AddonHandler.GetStreamInfos(id, &streamSettings, &streamProperties, (void*)&BiquadInfos) == AE_DSP_ERROR_NO_ERROR)
        {
          message.set_StreamId(id);

          // send mesage to AddonHandler
          g_AddonHandler.SendMessageToStream(message);
        }
        else
        {
          KODI->Log(ADDON::LOG_ERROR, "%s line %i: Failed getting audio stream infos!", __func__, __LINE__);
        }
      }

      // set frequency bands to 0dB
      message.set_AudioChannel(AE_DSP_CH_MAX);
      message.set_ProcessingModeId(POST_MODE_PARAMETRIC_EQ_ID);
      message.set_MessageType(CDSPProcessor::EQ_MESSAGE_BIQUAD_COEFFICIENTS_LIST);
      BIQUAD_COEFFICIENTS_VECTOR coefficientsVector;
      for(AE_DSP_STREAM_ID id = 0; id < AE_DSP_STREAM_MAX_STREAMS; id++)
      {
        AE_DSP_SETTINGS streamSettings;
        AE_DSP_STREAM_PROPERTIES streamProperties;
        BIQUAD_INFOS BiquadInfos;
        coefficientsVector.clear();
        if(g_AddonHandler.GetStreamInfos(id, &streamSettings, &streamProperties, (void*)&BiquadInfos) == AE_DSP_ERROR_NO_ERROR)
        { // send new gain values to the biquad filter
          for(uint32_t band = 0; band < MAX_FREQ_BANDS; band++)
          {
            BIQUAD_COEFFICIENTS coefficients;
            ASPLIB_ERR err = CBiquadFactory::get_constQPeakingBiquadCoes(streamSettings.iProcessSamplerate, MAX_FREQ_BANDS, m_Gains[AE_DSP_CH_FL][band +1], band, &coefficients.coefficients);
            if(err == ASPLIB_ERR_NO_ERROR)
            {
              coefficients.biquadIndex = band;
              coefficients.c0 = 1.0f;
              coefficients.d0 = 0.0f;
              coefficientsVector.push_back(coefficients);
            }
            else
            {
              KODI->Log(ADDON::LOG_ERROR, "%s line %i: Failed getting const Q Peaking biquad coefficients from asplin!", __func__, __LINE__);
            }
          }

          if(coefficientsVector.size() > 0)
          {
            message.set_MessageDataSize(coefficientsVector.size()*sizeof(BIQUAD_COEFFICIENTS));
            message.set_StreamId(id);
            message.set_MessageData((void*)coefficientsVector.data());

            // send message to AddonHandler
            g_AddonHandler.SendMessageToStream(message);
          }
          else
          {
            KODI->Log(ADDON::LOG_ERROR, "%s line %i: Invalid coefficient list!", __func__, __LINE__);
          }
        }
        else
        {
          KODI->Log(ADDON::LOG_ERROR, "%s line %i: Failed getting audio stream infos!", __func__, __LINE__);
        }
      }
    }
    break;

    case SLIDER_PREAMP:
    {
      // ToDo: Add spin control to control each audio channel
      m_Gains[AE_DSP_CH_FL][0] = m_Sliders[0]->GetFloatValue();
      for(int ch = AE_DSP_CH_FR; ch < AE_DSP_CH_MAX; ch++)
      {
        m_Gains[ch][0] = m_Gains[AE_DSP_CH_FL][0];
      }
      m_window->SetControlLabel(controlId + 200, float_dB_toString(m_Gains[AE_DSP_CH_FL][0]).c_str());
      
      CADSPModeMessage message;
      message.set_AudioChannel(AE_DSP_CH_MAX);
      message.set_ProcessingModeId(POST_MODE_PARAMETRIC_EQ_ID);
      message.set_MessageData((void*)&m_Gains[AE_DSP_CH_FL][0], sizeof(float));
      message.set_MessageType(CDSPProcessor::EQ_MESSAGE_POST_GAIN);
      for(AE_DSP_STREAM_ID id = 0; id < AE_DSP_STREAM_MAX_STREAMS; id++)
      {
        AE_DSP_SETTINGS streamSettings;
        AE_DSP_STREAM_PROPERTIES streamProperties;
        BIQUAD_INFOS BiquadInfos;
        if(g_AddonHandler.GetStreamInfos(id, &streamSettings, &streamProperties, (void*)&BiquadInfos) == AE_DSP_ERROR_NO_ERROR)
        {
          message.set_StreamId(id);
          
          // send mesage to AddonHandler
          g_AddonHandler.SendMessageToStream(message);
        }
        else
        {
          KODI->Log(ADDON::LOG_ERROR, "%s line %i: Failed getting audio stream infos!", __func__, __LINE__);
        }
      } 
    }
    break;

    case SLIDER_32Hz:
    case SLIDER_64Hz:
    case SLIDER_125Hz:
    case SLIDER_250Hz:
    case SLIDER_500Hz:
    case SLIDER_1kHz:
    case SLIDER_2kHz:
    case SLIDER_4kHz:
    case SLIDER_8kHz:
    case SLIDER_16kHz:
    {
      // ToDo: Add spin control to control each audio channel
      uint32_t freqBand = controlId - SLIDER_PREAMP;
      m_Gains[AE_DSP_CH_FL][freqBand] = m_Sliders[freqBand]->GetFloatValue();
      for(int ch = AE_DSP_CH_FR; ch < AE_DSP_CH_MAX; ch++)
      {
        m_Gains[ch][freqBand] = m_Gains[AE_DSP_CH_FL][freqBand];
      }
      m_window->SetControlLabel(controlId + 200, float_dB_toString(m_Gains[AE_DSP_CH_FL][freqBand]).c_str());

      CADSPModeMessage message;
      message.set_AudioChannel(AE_DSP_CH_MAX);
      message.set_ProcessingModeId(POST_MODE_PARAMETRIC_EQ_ID);
      message.set_MessageDataSize(sizeof(BIQUAD_COEFFICIENTS));
      message.set_MessageType(CDSPProcessor::EQ_MESSAGE_BIQUAD_IDX_COEFFICIENTS);
      BIQUAD_COEFFICIENTS coefficients;
      for(AE_DSP_STREAM_ID id = 0; id < AE_DSP_STREAM_MAX_STREAMS; id++)
      {
        AE_DSP_SETTINGS streamSettings;
        AE_DSP_STREAM_PROPERTIES streamProperties;
        BIQUAD_INFOS BiquadInfos;
        if(g_AddonHandler.GetStreamInfos(id, &streamSettings, &streamProperties, (void*)&BiquadInfos) == AE_DSP_ERROR_NO_ERROR)
        { // send new gain values to the biquad filter
          ASPLIB_ERR err = CBiquadFactory::get_constQPeakingBiquadCoes(streamSettings.iProcessSamplerate, MAX_FREQ_BANDS, m_Gains[AE_DSP_CH_FL][freqBand], freqBand -1, &coefficients.coefficients);
          if(err == ASPLIB_ERR_NO_ERROR)
          {
            coefficients.biquadIndex = freqBand -1;
            coefficients.c0 = 1.0f;
            coefficients.d0 = 0.0f;
            message.set_StreamId(id);
            message.set_MessageData((void*)&coefficients);

            // send message to AddonHandler
            g_AddonHandler.SendMessageToStream(message);
          }
        }
      }
    } 
    break;

    default:
      return false;
    break;
  }

	return true;
}

bool CGUIDialogPostProcess::OnFocus(int controlId)
{
  return true;
}

bool CGUIDialogPostProcess::OnAction(int actionId)
{
  if(actionId == ADDON_ACTION_CLOSE_DIALOG ||
     actionId == ADDON_ACTION_PREVIOUS_MENU ||
     actionId == ADDON_ACTION_NAV_BACK)
  {
    return OnClick(BUTTON_CANCEL);
  }
  else
  {
    return false;
  }
}

void CGUIDialogPostProcess::OnClose()
{
  for(int band = 0; band < MAX_FREQ_BANDS +1; band++)
  {
    if(m_Sliders[band])
    {
      GUI->Control_releaseSlider(m_Sliders[band]);
      m_Sliders[band] = NULL;
    }
  }
}

std::string float_dB_toString(float dB)
{
  std::string str = toString(roundf(dB*10.0f)/10.0f);
  float val10 = (float)((int)fabsf(roundf(dB*10.0f)));
  int fraction = (int)(val10 - ((int)(val10/10.0f)*10.0f));

  if(fraction == 0 || dB == 0.0f)
  {
    str += ".0";
  }

  str += "dB";
  
  return str;
}
