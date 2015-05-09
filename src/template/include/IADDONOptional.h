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

#include "client.h"
#include <string>
#include "../configuration/templateConfiguration.h"

class IADDONOptional
{
public:
	IADDONOptional();
	virtual ~IADDONOptional();

#ifdef ADSP_ADDON_USE_SETTINGS
	virtual ADDON_STATUS SetSetting(std::string SettingName, const void *SettingValue) = 0;
#endif
#ifdef ADSP_ADDON_USE_GETSETTINGS
	virtual unsigned int GetSettings(ADDON_StructSetting ***sSet) = 0;
#endif
#ifdef ADSP_ADDON_USE_STOP
	virtual void Stop() = 0;
#endif
#ifdef ADSP_ADDON_USE_FREESETTINGS
	virtual void FreeSettings() = 0;
#endif
#ifdef ADSP_ADDON_USE_ANNOUNCE
	virtual void Announce(std::string Flag, std::string Sender, std::string Message, const void *Data) = 0;
#endif
#ifdef	ADSP_ADDON_USE_READSETTINGS
	virtual void ReadSettings(void) = 0;
#endif
#ifdef ADSP_ADDON_USE_MENUHOOK
	virtual AE_DSP_ERROR CallMenuHook(const AE_DSP_MENUHOOK& Menuhook, const AE_DSP_MENUHOOK_DATA &Item) = 0;
#endif
#ifdef ADSP_ADDON_USE_OPTIONAL_INIT
	virtual bool OptionalInit() = 0;
#endif
};