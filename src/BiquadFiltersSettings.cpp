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



#include <template/ADSPHelpers.h>
#include "BiquadFiltersSettings.h"

using namespace std;

static string stat_str10BandEQGains[] =
{
  "gain_32Hz",
  "gain_64Hz",
  "gain_125Hz",
  "gain_250Hz",
  "gain_500Hz",
  "gain_1kHz",
  "gain_2kHz",
  "gain_4kHz",
  "gain_8kHz",
  "gain_16kHz",
  "gain_post"
};

CBiquadFiltersSettings::CBiquadFiltersSettings()
{
  Init_Parametric10BandEQSettings();
}

CBiquadFiltersSettings::~CBiquadFiltersSettings()
{
  if(m_10BandEQSettings)
  {
    delete m_10BandEQSettings;
    m_10BandEQSettings = NULL;
  }
}

CBiquadFiltersSettings &CBiquadFiltersSettings::Get()
{
  static CBiquadFiltersSettings sSettings;
  return sSettings;
}

// returns saved gain in dB for a 10 Band EQ
// returns true --> valid value
// returns false --> invalid value
bool CBiquadFiltersSettings::get_Parametric10BandEQGain(AE_DSP_CHANNEL AudioChannel, PARAMETRIC_10BAND_EQ_BANDS Band, float *Gain)
{
  if(Band <= EQ_10BAND_UNKNOWN || Band >= EQ_10BAND_MAX || !Gain)
  {
    return false;
  }
  
  ISettingsElement *setting = m_10BandEQSettings->find_Setting( "parametric_eq_settings", "gain_10_bands", 
                                                                CADSPHelpers::Translate_ChID_TO_String(AudioChannel), stat_str10BandEQGains[Band]);
  if(!setting)
  {
    return false;
  }
  *Gain = FLOAT_SETTINGS(setting)->get_Setting();
  
  return true;
}

bool CBiquadFiltersSettings::set_Parametric10BandEQGain(AE_DSP_CHANNEL AudioChannel, PARAMETRIC_10BAND_EQ_BANDS Band, float Gain)
{
  return m_10BandEQSettings->add_Setting( "parametric_eq_settings", "gain_10_bands",
                                          CADSPHelpers::Translate_ChID_TO_String(AudioChannel), stat_str10BandEQGains[Band], 
                                          ISettingsElement::FLOAT_SETTING, &Gain);
}

void CBiquadFiltersSettings::save_Parametric10BandEQSettings()
{
  m_10BandEQSettings->write_SettingsXML();
}

void CBiquadFiltersSettings::Init_Parametric10BandEQSettings()
{
  m_10BandEQSettings = new CSettingsManager("parametricEQSettings.xml");
  if(!m_10BandEQSettings)
  {
    // ToDo: throw some exception!
    KODI->Log(ADDON::LOG_ERROR, "CBiquadFiltersSettings: Couldn't create CSettingsManager class! Not enough free memory?");
    return;
  }

  // set default values
  for(int ii = AE_DSP_CH_FL; ii < AE_DSP_CH_MAX; ii++)
  {
    float gainVal = 0.0f;
    for(int gainSet = 0; gainSet < EQ_10BAND_MAX; gainSet++)
    {
      if(!m_10BandEQSettings->add_Setting("parametric_eq_settings", "gain_10_bands",
                                          CADSPHelpers::Translate_ChID_TO_String((AE_DSP_CHANNEL)ii),
                                          stat_str10BandEQGains[gainSet], ISettingsElement::FLOAT_SETTING, &gainVal))
      {
        // ToDo: throw some exception!
        return;
      }
    }
  }

  // If XML-File is present initialize with user settings
  m_10BandEQSettings->Init();
}
