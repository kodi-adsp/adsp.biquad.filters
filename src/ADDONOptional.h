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


//! Example optional header file.
/*!
 * \file ADDONOptional.h
 * ToDo: detailed description!
 */
#include "template/include/client.h"
#include "template/configuration/templateConfiguration.h"
#include "template/include/IADDONOptional.h"

class CADDONOptional : public IADDONOptional
{
public:
	CADDONOptional();
	~CADDONOptional();

	virtual ADDON_STATUS SetSetting(std::string SettingName, const void *SettingValue);
	virtual unsigned int GetSettings(ADDON_StructSetting ***sSet);
	virtual void Stop();
	virtual void FreeSettings();
	virtual void Announce(std::string Flag, std::string Sender, std::string Message, const void *Data);
	virtual void ReadSettings(void);
	virtual AE_DSP_ERROR CallMenuHook(const AE_DSP_MENUHOOK& Menuhook, const AE_DSP_MENUHOOK_DATA &Item);
	virtual bool OptionalInit();
};