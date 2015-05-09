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


//! Example optional class method implementations.
/*!
 * \file ADDONOptional.cpp
 * ToDo: detailed description!
 */
#include "template/include/client.h"
using namespace ADDON;

#include "BiquadFiltersSettings.h"
#include "ADDONOptional.h"
#include "Dialogs/GUIDialogPostProcess.h"
#include "BiquadFiltersSettings.h"

CADDONOptional::CADDONOptional()
{
}

CADDONOptional::~CADDONOptional()
{
}


ADDON_STATUS CADDONOptional::SetSetting(std::string SettingName, const void *SettingValue)
{
	return ADDON_STATUS_OK;
}

unsigned int CADDONOptional::GetSettings(ADDON_StructSetting ***sSet)
{
	return 0;
}

void CADDONOptional::Stop()
{
  
}

void CADDONOptional::FreeSettings()
{
}

void CADDONOptional::Announce(std::string Flag, std::string Sender, std::string Message, const void *Data)
{
}

void CADDONOptional::ReadSettings(void)
{
}

AE_DSP_ERROR CADDONOptional::CallMenuHook(const AE_DSP_MENUHOOK& Menuhook, const AE_DSP_MENUHOOK_DATA &Item)
{
	switch(Menuhook.iHookId)
	{
	  case ID_MENU_POST_PROCESS_PARAMETRIC_EQ:
		{
			CGUIDialogPostProcess menu;
			menu.DoModal();
		}
	  break;

	  default:
		  KODI->Log(LOG_ERROR, "called unknown menu hook!" );
		  return AE_DSP_ERROR_FAILED;
	  break;
	};

	return AE_DSP_ERROR_NO_ERROR;
}

bool CADDONOptional::OptionalInit()
{
	// now we register out menu hooks
	AE_DSP_MENUHOOK hook;

	// register menu hook for the post process parametric eq
  hook.iHookId              = ID_MENU_POST_PROCESS_PARAMETRIC_EQ;
  hook.category             = AE_DSP_MENUHOOK_POST_PROCESS;
  hook.iLocalizedStringId   = 30000;
  hook.iRelevantModeId      = POST_MODE_PARAMETRIC_EQ_ID;
  hook.bNeedPlayback        = false;
  ADSP->AddMenuHook(&hook);

  // Create Biquad Filter Settings
  CBiquadFiltersSettings::Get();

	return true;
}
