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



#include <string>
// reserved for future implementation
//#include <exception>
#include <kodi_adsp_types.h>
#include "AddonHelpers.h"

typedef unsigned long AE_DSP_CHANNEL_FLAGS;

class CADSPHelpers
{
public:
  static AE_DSP_CHANNEL         Translate_ChFlag_TO_ChID(AE_DSP_CHANNEL_PRESENT ChFlag);
  static AE_DSP_CHANNEL_PRESENT Translate_ChID_TO_ChFlag(AE_DSP_CHANNEL ChID);
  static std::string            Translate_ChFlag_TO_String(AE_DSP_CHANNEL_PRESENT ChFlag);
  static std::string            Translate_ChID_TO_String(AE_DSP_CHANNEL ChID);
  static bool                   IsChannelFlag_Present(AE_DSP_CHANNEL_FLAGS AvailableFlags, AE_DSP_CHANNEL_PRESENT ChFlag);
  static bool                   IsChannelID_Present(AE_DSP_CHANNEL_FLAGS AvailableFlags, AE_DSP_CHANNEL ChID);
  static AE_DSP_CHANNEL_PRESENT GetNextChFlag(AE_DSP_CHANNEL_FLAGS AvailableFlags, AE_DSP_CHANNEL_PRESENT ChFlag);
  static AE_DSP_CHANNEL         GetNextChID(AE_DSP_CHANNEL_FLAGS AvailableFlags, AE_DSP_CHANNEL ChID);
  static float                  Convert_dB_TO_Value(float dB);
  static float                  Convert_Value_TO_dB(float Scale);

  // reserved for future implementation
  //static std::string            GetAddonHomePath();
  //static std::string            GetAddonSettingsFile();
};

// reserved for future implementation
//class CADSPException : public CAddonException
//{
//
//};
