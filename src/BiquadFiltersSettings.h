#pragma once
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

#include <template/Settings/SettingsManager.h>

class CBiquadFiltersSettings
{
public:
  typedef enum
  {
    MANAGER_UNKNOWN = -1,
    MANAGER_PARAMETRIC_EQ,
    MANAGER_MAX
  }SETTINGS_MANAGERS;

  typedef enum
  {
    EQ_10BAND_UNKNOWN = -1,
    EQ_10BAND_32Hz,
    EQ_10BAND_64Hz,
    EQ_10BAND_125Hz,
    EQ_10BAND_250Hz,
    EQ_10BAND_500Hz,
    EQ_10BAND_1kHz,
    EQ_10BAND_2kHz,
    EQ_10BAND_4kHz,
    EQ_10BAND_8kHz,
    EQ_10BAND_16kHz,
    EQ_10BAND_POST,
    EQ_10BAND_MAX
  }PARAMETRIC_10BAND_EQ_BANDS;

  CBiquadFiltersSettings();
  ~CBiquadFiltersSettings();
  static CBiquadFiltersSettings &Get();
  // returns saved gain in dB for a 10 Band EQ
  // returns true --> valid value
  // returns false --> invalid value
  bool get_Parametric10BandEQGain(AE_DSP_CHANNEL AudioChannel, PARAMETRIC_10BAND_EQ_BANDS Band, float *Gain);
  bool set_Parametric10BandEQGain(AE_DSP_CHANNEL AudioChannel, PARAMETRIC_10BAND_EQ_BANDS Band, float Gain);
  void save_Parametric10BandEQSettings();
  
  protected:
    CSettingsManager *m_10BandEQSettings;

  private:
    void Init_Parametric10BandEQSettings();
};
