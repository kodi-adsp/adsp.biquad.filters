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


//! Example process class method implementations.
/*!
 * \file DSPProcessor.cpp
 * ToDo: detailed description!
 */
#include <string.h>
#include <template/include/client.h>

#include "DSPProcessor.h"
#include "template/ADSPHelpers.h"
using namespace asplib;

#include "BiquadFiltersSettings.h"

// set addon properties here
CDSPProcessor::CDSPProcessor()
{
  m_MaxFreqBands = 10;
  m_MaxProcessingChannels = 0;
  m_Biquads = NULL;
  m_TempBiquad = NULL;
  m_PostGain = NULL;
  m_MessageArrayElements = 0;
  m_MessagePtr = NULL;
  m_NewMessage = false;
}

// delete your buffers here
CDSPProcessor::~CDSPProcessor()
{
  if(m_NewMessage)
  {
    process_NewMessage();
    m_NewMessage = false;
  }
  
  if(m_Biquads)
  {
    for(int ii = 0; ii < m_MaxProcessingChannels; ii++)
    {
      ASPLIB_ERR err = CBiquadFactory::destroy_Biquads(&m_Biquads[ii].BiquadHandle);
      if(err != ASPLIB_ERR_NO_ERROR)
      {
        // ToDo: show some error message!
      }
    }
    delete[] m_Biquads;
    m_Biquads = NULL;
  } 

  if(m_PostGain)
  {
    delete [] m_PostGain;
    m_PostGain = NULL;
  }
}

AE_DSP_ERROR CDSPProcessor::Create()
{
  m_MaxProcessingChannels = m_StreamSettings.iOutChannels;
  m_Biquads = new ADSP_Biquad[m_MaxProcessingChannels];
  if(!m_Biquads)
  {
    KODI->Log(ADDON::LOG_ERROR, "%s line %i: Biquads not created! Not enough free memory?", __func__, __LINE__);
    return AE_DSP_ERROR_FAILED;
  }

  m_PostGain = new float[m_MaxProcessingChannels];
  if(!m_PostGain)
  {
    KODI->Log(ADDON::LOG_ERROR, "%s line %i: Post gain array not created! Not enough free memory?", __func__, __LINE__);
    return AE_DSP_ERROR_FAILED;
  }

  CBiquadFiltersSettings &settingsManager = CBiquadFiltersSettings::Get();

  // ToDo: bypass audio channel LFE!
  int lastAudioChannel = 0;
  for(int ch = 0; ch < m_MaxProcessingChannels; ch++)
  {
    // map next channel to biquad filter
    unsigned long tempChannelFlag = 1<<lastAudioChannel;
    m_Biquads[ch].AudioChannel = CADSPHelpers::GetNextChID(m_StreamSettings.lOutChannelPresentFlags,
                                                           CADSPHelpers::Translate_ChFlag_TO_ChID((AE_DSP_CHANNEL_PRESENT)tempChannelFlag));
    m_Biquads[ch].ChannelFlag = CADSPHelpers::Translate_ChID_TO_ChFlag((AE_DSP_CHANNEL)m_Biquads[ch].AudioChannel);
    if(m_Biquads[ch].AudioChannel == AE_DSP_CH_INVALID)
    {
      KODI->Log(ADDON::LOG_ERROR, "%s line %i: No audio channel is available!", __func__, __LINE__);
      return AE_DSP_ERROR_FAILED;
    }
    lastAudioChannel = m_Biquads[ch].AudioChannel +1;

    // create biquad for requested audio channel
    // ToDo: add functions for opt modules
    m_Biquads[ch].DesignMethod = BIQUAD_CONST_Q_EQ;
    m_Biquads[ch].Quantity = 10;
    m_Biquads[ch].SampleFrequency = m_StreamSettings.iProcessSamplerate;
    m_Biquads[ch].BiquadHandle = CBiquadFactory::get_Biquads(m_MaxFreqBands, (float)m_Biquads[ch].SampleFrequency, ASPLIB_OPT_NATIVE);
    if(!m_Biquads[ch].BiquadHandle)
    {
      KODI->Log(ADDON::LOG_ERROR, "%s line %i: Biquad for audio channel %s not created! Not enough free memory?", __func__, __LINE__, CADSPHelpers::Translate_ChID_TO_String(m_Biquads[ch].AudioChannel).c_str());
      return AE_DSP_ERROR_FAILED;
    }

    // set gain values
    for(uint32_t idx = 0; idx < m_MaxFreqBands; idx++)
    {
      float gain = 0.0f;
      if(!settingsManager.get_Parametric10BandEQGain(m_Biquads[ch].AudioChannel, (CBiquadFiltersSettings::PARAMETRIC_10BAND_EQ_BANDS)idx, &gain))
      {
        KODI->Log(ADDON::LOG_NOTICE, "Biquad filter settings manager returned invalid gain for biquad audio channel \"%s\" with biquad index %i. Setting gain to 0dB.", CADSPHelpers::Translate_ChID_TO_String(m_Biquads[ch].AudioChannel).c_str(), idx);
        gain = 0.0f;
      }

      CBiquadFactory::set_constQPeakingParams(m_Biquads[ch].BiquadHandle, gain, idx);
    }

    // set post gain value
    if(settingsManager.get_Parametric10BandEQGain(m_Biquads[ch].AudioChannel, CBiquadFiltersSettings::EQ_10BAND_POST, &m_PostGain[ch]))
    {
      m_PostGain[ch] = CADSPHelpers::Convert_dB_TO_Value(m_PostGain[ch]);
    }
    else
    {
      KODI->Log(ADDON::LOG_NOTICE, "Biquad filter settings manager returned invalid gain for for post gain on audio channel \"%s\". Setting gain to 0dB.", CADSPHelpers::Translate_ChID_TO_String(m_Biquads[ch].AudioChannel).c_str());
      m_PostGain[ch] = 1.0f;
    }
  }

  return AE_DSP_ERROR_NO_ERROR;
}

unsigned int CDSPProcessor::PostProcess(unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples)
{
  if(m_NewMessage)
  {
    process_NewMessage();
    m_NewMessage = false;
    m_MessageAudioChannel = AE_DSP_CH_INVALID;
  }

  for(uint32_t ch = 0; ch < (uint32_t)m_MaxProcessingChannels; ch++)
  {
    ASPLIB_ERR err = ASPLIB_ERR_NO_ERROR;
    if(m_Biquads[ch].AudioChannel != AE_DSP_CH_LFE)
    {
      err = CBiquadFactory::calc_BiquadSamples( m_Biquads[ch].BiquadHandle, Array_in[m_Biquads[ch].AudioChannel], Array_out[m_Biquads[ch].AudioChannel], Samples);
      if(err != ASPLIB_ERR_NO_ERROR)
      {
        KODI->Log(ADDON::LOG_ERROR, "Biquad sample calculation on audio channel \"%s\" failed!", CADSPHelpers::Translate_ChID_TO_String(m_Biquads[ch].AudioChannel).c_str());
        return 0;
      }

      if(m_PostGain[ch] != 1.0f)
      {
        for(uint32_t ii = 0; ii < Samples; ii++)
        {
          Array_out[m_Biquads[ch].AudioChannel][ii] *= m_PostGain[ch];
        }
      }
    }
    else
    { // we do net process LFE, this should be done by a other processing mode
      memcpy(Array_out[m_Biquads[ch].AudioChannel], Array_in[m_Biquads[ch].AudioChannel], sizeof(float)*Samples);
    }
  }
  return Samples;
}

AE_DSP_ERROR CDSPProcessor::send_Message(CADSPModeMessage &Message)
{
  if(Message.get_ProcessingModeId() != POST_MODE_PARAMETRIC_EQ_ID)
  {
    return AE_DSP_ERROR_REJECTED;
  }

  // wait for old message;
  while(m_NewMessage);

  switch(Message.get_MessageType())
  {
// ----- Biquad coefficients index message -------------------------------------------------
    case EQ_MESSAGE_BIQUAD_IDX_COEFFICIENTS:
    {
      BIQUAD_COEFFICIENTS sCoe;
      if(Message.get_MessageDataSize() != sizeof(BIQUAD_COEFFICIENTS) || Message.get_AudioChannel() < AE_DSP_CH_FL || Message.get_AudioChannel() > AE_DSP_CH_MAX)
      {
        KODI->Log(ADDON::LOG_ERROR, "%s line %i: ModeMessage has not the correct DataSize! On AudioChannel: %s, MessageSize: %i, MessageType: %i, ProcessingModeId: %i, StreamId: %i", 
                  __func__, __LINE__, CADSPHelpers::Translate_ChID_TO_String(Message.get_AudioChannel()).c_str(),
                  Message.get_MessageDataSize(), Message.get_MessageType(), Message.get_ProcessingModeId(), Message.get_StreamId());
        return AE_DSP_ERROR_INVALID_PARAMETERS;
      }

      AE_DSP_ERROR err = Message.get_MessageData((void*)&sCoe);
      if(err != AE_DSP_ERROR_NO_ERROR)
      {
        return err;
      }

      // create temporary Message Data
      m_MessagePtr = (void*)&sCoe;
      m_MessageAudioChannel = Message.get_AudioChannel();
      m_MessageType = Message.get_MessageType();
      m_NewMessage = true;

      // wait until the message is processed
      while(m_NewMessage);
    }
    break;
// -------------------------------------------------------------------------

// ----- Biquad coefficients list message -------------------------------------------------    
    case EQ_MESSAGE_BIQUAD_COEFFICIENTS_LIST:
    {
      BIQUAD_COEFFICIENTS *coefficients;
      if(Message.get_MessageDataSize() < sizeof(BIQUAD_COEFFICIENTS) || Message.get_AudioChannel() < AE_DSP_CH_FL || Message.get_AudioChannel() > AE_DSP_CH_MAX)
      {
        KODI->Log(ADDON::LOG_ERROR, "%s line %i: ModeMessage has not the correct DataSize! On AudioChannel: %s, MessageSize: %i, MessageType: %i, ProcessingModeId: %i, StreamId: %i",
                  __func__, __LINE__, CADSPHelpers::Translate_ChID_TO_String(Message.get_AudioChannel()).c_str(),
                  Message.get_MessageDataSize(), Message.get_MessageType(), Message.get_ProcessingModeId(), Message.get_StreamId());
        return AE_DSP_ERROR_INVALID_PARAMETERS;
      }

      AE_DSP_ERROR err = Message.get_MessageDataPtr((void*&)coefficients);
      if(err != AE_DSP_ERROR_NO_ERROR)
      {
        return err;
      }

      // create temporary Message Data
      m_MessagePtr = (void*)coefficients;
      m_MessageAudioChannel = Message.get_AudioChannel();
      m_MessageType = Message.get_MessageType();
      m_MessageArrayElements = Message.get_MessageDataSize() / sizeof(BIQUAD_COEFFICIENTS);
      m_NewMessage = true;

      // wait until the message is processed
      while(m_NewMessage);
    }
    break;
// -------------------------------------------------------------------------

// ----- Post gain message -------------------------------------------------        
    case EQ_MESSAGE_POST_GAIN:
    {
      if(Message.get_MessageDataSize() != sizeof(float) || Message.get_AudioChannel() < AE_DSP_CH_FL || Message.get_AudioChannel() > AE_DSP_CH_MAX)
      {
        KODI->Log(ADDON::LOG_ERROR, "%s line %i: ModeMessage has not the correct DataSize! On AudioChannel: %s, MessageSize: %i, MessageType: %i, ProcessingModeId: %i, StreamId: %i", 
                  __func__, __LINE__, CADSPHelpers::Translate_ChID_TO_String(Message.get_AudioChannel()).c_str(),
                  Message.get_MessageDataSize(), Message.get_MessageType(), Message.get_ProcessingModeId(), Message.get_StreamId());
        return AE_DSP_ERROR_INVALID_PARAMETERS;
      }

      float tempGain = 0.0f;
      AE_DSP_ERROR err = Message.get_MessageData((void*)&tempGain);
      if(err != AE_DSP_ERROR_NO_ERROR)
      {
        return err;
      }
      tempGain = CADSPHelpers::Convert_dB_TO_Value(tempGain);

      // create temporary Message Data
      m_MessagePtr = (void*)&tempGain;
      m_MessageAudioChannel = Message.get_AudioChannel();
      m_MessageType = Message.get_MessageType();
      m_NewMessage = true;

      // wait until the message is processed
      while(m_NewMessage);
      
    }
    break;
// -------------------------------------------------------------------------
    
    default:
      return AE_DSP_ERROR_UNKNOWN;
    break;
  }

  return AE_DSP_ERROR_NO_ERROR;
}

void CDSPProcessor::process_NewMessage()
{
  switch(m_MessageType)
  {

// ----- Biquad coefficients index message -------------------------------------------------    
    case EQ_MESSAGE_BIQUAD_IDX_COEFFICIENTS:
    {
      BIQUAD_COEFFICIENTS *p = (BIQUAD_COEFFICIENTS*)m_MessagePtr;
      if(m_MessageAudioChannel == AE_DSP_CH_MAX)
      {
        for(int audioCh = AE_DSP_CH_FL; audioCh < AE_DSP_CH_MAX; audioCh++)
        {
          for(int biquadCh = 0; biquadCh < m_MaxProcessingChannels; biquadCh++)
          { // Search the requested audio channel
            if(m_Biquads[biquadCh].AudioChannel == audioCh)
            {
              // ToDo: check for errors
              ASPLIB_ERR err = CBiquadFactory::set_BiquadCoefficients(m_Biquads[biquadCh].BiquadHandle, &(p->coefficients), p->biquadIndex, p->c0, p->d0);
            }
          }
        }
      }
      else
      {
        ADSP_Biquad *pBiquad = NULL;
        for(int ch = 0; ch < m_MaxProcessingChannels && !pBiquad; ch++)
        { // Search the requested audio channel
          if(m_Biquads[ch].AudioChannel == m_MessageAudioChannel)
          {
            pBiquad = &m_Biquads[ch];
          }
        }

        if(pBiquad)
        {
          // ToDo: check for errors
          ASPLIB_ERR err = CBiquadFactory::set_BiquadCoefficients(pBiquad->BiquadHandle, &(p->coefficients), p->biquadIndex, p->c0, p->d0);
        }
        else
        {
          // ToDo: check for errors
        }
      }
    }
    break;
// -------------------------------------------------------------------------

// ----- Biquad coefficients list message -------------------------------------------------    
    case EQ_MESSAGE_BIQUAD_COEFFICIENTS_LIST:
    {
      BIQUAD_COEFFICIENTS *p = (BIQUAD_COEFFICIENTS*)(m_MessagePtr);
      if(m_MessageAudioChannel == AE_DSP_CH_MAX)
      {
        for(int audioCh = AE_DSP_CH_FL; audioCh < AE_DSP_CH_MAX; audioCh++)
        {
          for(int biquadCh = 0; biquadCh < m_MaxProcessingChannels; biquadCh++)
          { // Search the requested audio channel
            if(m_Biquads[biquadCh].AudioChannel == audioCh)
            {
              for(unsigned int ii = 0; ii < m_MessageArrayElements; ii++)
              {
                ASPLIB_ERR err = CBiquadFactory::set_BiquadCoefficients(m_Biquads[biquadCh].BiquadHandle, &(p[ii].coefficients), p[ii].biquadIndex, p[ii].c0, p[ii].d0);
              }
            }
          }
        }
      }
      else
      {
        // TODO: Implementation for specific audio channels?
      }
    }
    break;
// -------------------------------------------------------------------------

// ----- POST Gain Message -------------------------------------------------    
    case EQ_MESSAGE_POST_GAIN:
    {
      float tempGain = *((float*)m_MessagePtr);

      if(m_MessageAudioChannel == AE_DSP_CH_MAX)
      {
        for(int ch = 0; ch < m_MaxProcessingChannels; ch++)
        { // Search the requested audio channel
          m_PostGain[ch] = tempGain;
        }
      }
      else
      {
        for(int ch = 0; ch < m_MaxProcessingChannels && m_Biquads[ch].AudioChannel != m_MessageAudioChannel; ch++)
        { // Search the requested audio channel
          if(m_Biquads[ch].AudioChannel == m_MessageAudioChannel)
          {
            m_PostGain[ch] = tempGain;
          }
        }
      }
    }
    break;
// -------------------------------------------------------------------------
  }
}
