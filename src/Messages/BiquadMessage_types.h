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
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */


#include <asplib/Biquads/apslib_BiquadFactory.h>
#include <kodi_adsp_types.h>
#include "template/ADSPHelpers.h"
#include <vector>

typedef enum
{
  BIQUAD_DESIGN_UNKOWN = -1,
  BIQUAD_CONST_Q_EQ,
  BIQUAD_NON_CONST_Q_EQ,
  BIQUAD_BUTTERWORTH_LOW_PASS,
  BIQUAD_BUTTERWORTH_HIGH_PASS,
  BIQUAD_DESIGN_MAX
}BiquadDesignMethod;

typedef struct
{
  BiquadDesignMethod    DesignMethod;     // Stores the Biquad Design method. For details see BiquadDesignMethod
  AE_DSP_CHANNEL        AudioChannel;     // Stores the requested AudioChannel
  AE_DSP_CHANNEL_FLAGS  ChannelFlag;      // Stores the requested AudioChannelFlag
  uint32_t              SampleFrequency;  // Stores the used sample frequency by the Biquad.
  uint32_t              Quantity;         // Stores the amount of used Biquads
  ASPLIB_BIQUAD_HANDLE  *BiquadHandle;    // store the Biquad Filter and the used optimization module
}ADSP_Biquad;

struct BIQUAD_INFOS
{
  uint32_t SampleFrequency;
  uint32_t BiquadAmount;
  BIQUAD_INFOS() { SampleFrequency=0; BiquadAmount=0; };
};

struct  BIQUAD_COEFFICIENTS
{
  ASPLIB_BIQUAD_COEFFICIENTS coefficients;
  float d0;
  float c0;
  uint32_t biquadIndex;
  BIQUAD_COEFFICIENTS()
  {
    coefficients.a0 = 0.0f; coefficients.a1 = 0.0f; coefficients.a2 = 0.0f;
    coefficients.b1 = 0.0f; coefficients.b2 = 0.0f;
    d0 = 0.0f; c0 = 0.0f; biquadIndex = 0;
  };
};

typedef std::vector<BIQUAD_COEFFICIENTS> BIQUAD_COEFFICIENTS_VECTOR;
