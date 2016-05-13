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

#include <vector>
#include <string>

// include template configuration header files
#include "configuration/templateConfiguration.h"
#include "../template/include/MACROHelper.h"
#include "include/checkTemplateConfig.h"

// include kodi platform header files
#include <kodi_adsp_dll.h>
#include <p8-platform/util/util.h>

// include adsp template specific header files
#include "include/client.h"
#include "include/ADSPProcessorHandle.h"
#include "include/ADSPAddonHandler.h"

// includes your DSP Processor class
#include ADSP_PROCESSOR_HEADER_FILE

using namespace std;
using namespace ADDON;

#ifdef TARGET_WINDOWS
#define snprintf _snprintf
#endif

int            m_iStreamsPresent  = 0;
bool           m_bCreated         = false;
ADDON_STATUS   m_CurStatus        = ADDON_STATUS_UNKNOWN;

/* User adjustable settings are saved here.
 * Default values are defined inside client.h
 * and exported to the other source files.
 */
std::string   g_strUserPath       = "";
std::string   g_strAddonPath      = "";


CHelper_libXBMC_addon   *KODI       = NULL;
CHelper_libKODI_adsp    *ADSP       = NULL;
CHelper_libKODI_guilib  *GUI        = NULL;

/*
 *	ADSP Addon handling class
 */
CADSPAddonHandler g_AddonHandler;

extern "C" {

void ADDON_ReadSettings(void)
{
#ifdef ADSP_ADDON_USE_READSETTINGS
	g_AddonHandler.ReadSettings();
#endif
}

ADDON_STATUS ADDON_Create(void* hdl, void* props)
{
	if (!hdl || !props)
	{
		return ADDON_STATUS_UNKNOWN;
	}

	AE_DSP_PROPERTIES* adspprops = (AE_DSP_PROPERTIES*)props;

	KODI = new CHelper_libXBMC_addon;
	if (!KODI->RegisterMe(hdl))
	{
		SAFE_DELETE(KODI);
		return ADDON_STATUS_PERMANENT_FAILURE;
	}

	GUI = new CHelper_libKODI_guilib;
	if (!GUI->RegisterMe(hdl))
	{
		SAFE_DELETE(GUI);
		SAFE_DELETE(KODI);
		return ADDON_STATUS_PERMANENT_FAILURE;
	}

	ADSP = new CHelper_libKODI_adsp;
	if (!ADSP->RegisterMe(hdl))
	{
		SAFE_DELETE(ADSP);
		SAFE_DELETE(GUI);
		SAFE_DELETE(KODI);
		return ADDON_STATUS_PERMANENT_FAILURE;
	}
	KODI->Log(LOG_DEBUG, "%s - Creating the Audio DSP add-on template", __FUNCTION__);

	m_CurStatus     = ADDON_STATUS_UNKNOWN;
	g_strUserPath   = adspprops->strUserPath;
	g_strAddonPath  = adspprops->strAddonPath;

	ADDON_ReadSettings();

	if(!g_AddonHandler.Init())
	{
		return m_CurStatus;
	}

	m_CurStatus = ADDON_STATUS_OK;
	m_bCreated = true;
	m_iStreamsPresent = 0;
	return m_CurStatus;
}

ADDON_STATUS ADDON_GetStatus()
{
  return m_CurStatus;
}

void ADDON_Destroy()
{
	m_bCreated = false;
  m_iStreamsPresent = 0;

  g_AddonHandler.Destroy();

  SAFE_DELETE(ADSP);
  SAFE_DELETE(GUI);
  SAFE_DELETE(KODI);

  m_CurStatus = ADDON_STATUS_UNKNOWN;
}

bool ADDON_HasSettings()
{
#ifdef ADSP_ADDON_USE_SETTINGS
  return true;
#else
	return false;
#endif
}

unsigned int ADDON_GetSettings(ADDON_StructSetting ***sSet)
{
#ifdef ADSP_ADDON_USE_GETSETTINGS
	return g_AddonHandler.GetSettings(sSet);
#else
	(void) sSet; // Remove compiler warning
	return 0;
#endif
}

ADDON_STATUS ADDON_SetSetting(const char *SettingName, const void *SettingValue)
{
	string settingName(SettingName);
	if(!SettingValue)
	{
		return ADDON_STATUS_PERMANENT_FAILURE;
	}

#ifdef ADSP_ADDON_USE_SETTINGS
	return g_AddonHandler.SetSetting( string(SettingName), SettingValue );
#else
	return ADDON_STATUS_OK;
#endif
}

void ADDON_Stop()
{
#ifdef ADSP_ADDON_USE_STOP
	g_AddonHandler.Stop();
#endif
}

void ADDON_FreeSettings()
{
#ifdef ADSP_ADDON_USE_FREESETTINGS
	g_AddonHandler.FreeSettings();
#endif
}

void ADDON_Announce(const char *Flag, const char *Sender, const char *Message, const void *Data)
{
#ifdef ADSP_ADDON_USE_ANNOUNCE
	g_AddonHandler.Announce( string(Flag), string(Sender), string(Message), Data );
#else
	// Remove compiler warnings
	(void) Flag;
	(void) Sender; 
	(void) Message; 
	(void) Data;
#endif
}


/***********************************************************
 * Audio DSP Client AddOn specific public library functions
 ***********************************************************/
const char* GetAudioDSPAPIVersion(void)
{
  return KODI_AE_DSP_API_VERSION;
}

const char* GetMinimumAudioDSPAPIVersion(void)
{
  return KODI_AE_DSP_MIN_API_VERSION;
}

const char* GetGUIAPIVersion(void)
{
  return KODI_GUILIB_API_VERSION;
}

const char* GetMinimumGUIAPIVersion(void)
{
  return KODI_GUILIB_MIN_API_VERSION;
}

AE_DSP_ERROR GetAddonCapabilities(AE_DSP_ADDON_CAPABILITIES* pCapabilities)
{
	if(pCapabilities == NULL)
	{
		return AE_DSP_ERROR_FAILED;
	}

	pCapabilities->bSupportsInputProcess    = g_AddonHandler.SupportsInputProcess();
	pCapabilities->bSupportsPreProcess      = g_AddonHandler.SupportsPreProcess();
	pCapabilities->bSupportsMasterProcess   = g_AddonHandler.SupportsMasterProcess();
	pCapabilities->bSupportsPostProcess     = g_AddonHandler.SupportsPostProcess();
	pCapabilities->bSupportsInputResample   = g_AddonHandler.SupportsInputResample();
	pCapabilities->bSupportsOutputResample  = g_AddonHandler.SupportsOutputResample();

	return AE_DSP_ERROR_NO_ERROR;
}

const char* GetDSPName(void)
{
  return ADSP_ADDON_NAME;
}

const char* GetDSPVersion(void)
{
  return ADSP_ADDON_VERSION;
}

AE_DSP_ERROR CallMenuHook(const AE_DSP_MENUHOOK& Menuhook, const AE_DSP_MENUHOOK_DATA &Item)
{
#ifdef ADSP_ADDON_USE_MENUHOOK
	return g_AddonHandler.CallMenuHook(Menuhook, Item);
#else
	return AE_DSP_ERROR_NOT_IMPLEMENTED;
#endif
}


/*!
 * Control function for start and stop of dsp processing.
 */
AE_DSP_ERROR StreamCreate(const AE_DSP_SETTINGS *AddonSettings, const AE_DSP_STREAM_PROPERTIES* pProperties, ADDON_HANDLE handle)
{
	return g_AddonHandler.StreamCreate( AddonSettings, pProperties, handle );
}

AE_DSP_ERROR StreamDestroy(const ADDON_HANDLE handle)
{
	return g_AddonHandler.StreamDestroy(handle->dataIdentifier);
}

AE_DSP_ERROR StreamInitialize(const ADDON_HANDLE handle, const AE_DSP_SETTINGS *AddonSettings)
{
	if( !AddonSettings )
	{
		KODI->Log(LOG_ERROR, "Null pointer were given!");
		return AE_DSP_ERROR_UNKNOWN;
	}

	return g_AddonHandler.StreamInitialize(handle, AddonSettings);
}


/*!
 * Pre processing related functions
 */
unsigned int PreProcessNeededSamplesize(const ADDON_HANDLE handle, unsigned int Mode_id)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->PreProcessNeededSamplesize(Mode_id);
	}
	else
	{
		KODI->Log(LOG_ERROR, "PreProcessNeededSamplesize(...): uninitialized Stream was requested!");
		return 0;
	}
}

float PreProcessGetDelay(const ADDON_HANDLE handle, unsigned int Mode_id)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->PreProcessGetDelay(Mode_id);
	}
	else
	{
		KODI->Log(LOG_ERROR, "PreProcessGetDelay(...): uninitialized Stream was requested!");
		return 0.0f;
	}
}

/*!
 * Resampling related functions before master processing.
 * only one dsp addon is allowed to do this
 */
unsigned int InputResampleProcessNeededSamplesize(const ADDON_HANDLE handle)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->InputResampleProcessNeededSamplesize();
	}
	else
	{
		KODI->Log(LOG_ERROR, "InputResampleProcessNeededSamplesize(...): uninitialized Stream was requested!");
		return 0;
	}
}

int InputResampleSampleRate(const ADDON_HANDLE handle)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->InputResampleSampleRate();
	}
	else
	{
		KODI->Log(LOG_ERROR, "InputResampleSampleRate(...): uninitialized Stream was requested!");
		return 0;
	}
}
  
float InputResampleGetDelay(const ADDON_HANDLE handle)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->InputResampleGetDelay();
	}
	else
	{
		KODI->Log(LOG_ERROR, "InputResampleGetDelay(...): uninitialized Stream was requested!");
		return 0;
	}
}

/*!
 * Master processing functions
 * only one during playback selectable dsp addon is allowed to do this
 */
AE_DSP_ERROR MasterProcessSetMode(const ADDON_HANDLE handle, AE_DSP_STREAMTYPE Type, unsigned int Mode_id, int Unique_db_mode_id)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return  p->MasterProcessSetMode(Type, Mode_id, Unique_db_mode_id);
	}
	else
	{
		KODI->Log(LOG_ERROR, "MasterProcessSetMode(...): uninitialized Stream was requested!");
		return AE_DSP_ERROR_UNKNOWN;
	}
}

unsigned int MasterProcessNeededSamplesize(const ADDON_HANDLE handle)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->MasterProcessNeededSamplesize();
	}
	else
	{
		KODI->Log(LOG_ERROR, "MasterProcessNeededSamplesize(...): uninitialized Stream was requested!");
		return 0;
	}
}

float MasterProcessGetDelay(const ADDON_HANDLE handle)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->MasterProcessGetDelay();
	}
	else
	{
		KODI->Log(LOG_ERROR, "MasterProcessGetDelay(...): uninitialized Stream was requested!");
		return 0.0f;
	}
}

int MasterProcessGetOutChannels(const ADDON_HANDLE handle, unsigned long &Out_channel_present_flags)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->MasterProcessGetOutChannels(Out_channel_present_flags);
	}
	else
	{
		KODI->Log(LOG_ERROR, "MasterProcessGetOutChannels(...): uninitialized Stream was requested!");
		return 0;
	}
}

const char *MasterProcessGetStreamInfoString(const ADDON_HANDLE handle)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->MasterProcessGetStreamInfoString();
	}
	else
	{
		KODI->Log(LOG_ERROR, "MasterProcessGetStreamInfoString(...): uninitialized Stream was requested!");
		return "";
	}
}


/*!
 * Post processing related functions
 * all enabled addons allowed todo this
 */
unsigned int PostProcessNeededSamplesize(const ADDON_HANDLE handle, unsigned int Mode_id)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return  p->PostProcessNeededSamplesize(Mode_id);
	}
	else
	{
		KODI->Log(LOG_ERROR, "PostProcessNeededSamplesize(...): uninitialized Stream was requested!");
		return 0;
	}
}

float PostProcessGetDelay(const ADDON_HANDLE handle, unsigned int Mode_id)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->PostProcessGetDelay(Mode_id);
	}
	else
	{
		KODI->Log(LOG_ERROR, "PostProcessGetDelay(...): uninitialized Stream was requested!");
		return 0.0f;
	}
}

/*!
 * Resampling related functions after final processing.
 * only one dsp addon is allowed to do this
 */
unsigned int OutputResampleProcessNeededSamplesize(const ADDON_HANDLE handle)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->OutputResampleProcessNeededSamplesize();
	}
	else
	{
		KODI->Log(LOG_ERROR, "OutputResampleProcessNeededSamplesize(...): uninitialized Stream was requested!");
		return 0;
	}
}

int OutputResampleSampleRate(const ADDON_HANDLE handle)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->OutputResampleSampleRate();
	}
	else
	{
		KODI->Log(LOG_ERROR, "OutputResampleSampleRate(...): uninitialized Stream was requested!");
		return 0;
	}
}

float OutputResampleGetDelay(const ADDON_HANDLE handle)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->OutputResampleGetDelay();
	}
	else
	{
		KODI->Log(LOG_ERROR, "OutputResampleGetDelay(...): uninitialized Stream was requested!");
		return 0.0f;
	}
}

/*!
 *	Addon Processing functions
 */
bool InputProcess(const ADDON_HANDLE handle, const float **Array_in, unsigned int Samples)
{
#ifdef ADSP_ADDON_USE_INPUTPROCESS
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->InputProcess(Array_in, Samples);
	}
	else
	{
		KODI->Log(LOG_ERROR, "InputProcess(...): uninitialized Stream was requested!");
		return false;
	}
#else
	return true;
#endif
}

unsigned int InputResampleProcess(const ADDON_HANDLE handle, float **Array_in, float **Array_out, unsigned int Samples)
{
#ifdef ADSP_ADDON_USE_INPUTRESAMPLE
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->InputResampleProcess(Array_in, Array_out, Samples);
	}
	else
	{
		KODI->Log(LOG_ERROR, "InputResampleProcess(...): uninitialized Stream was requested!");
		return 0;
	}
#else
	return 0;
#endif
}

unsigned int PreProcess(const ADDON_HANDLE handle, unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples)
{
#ifdef ADSP_ADDON_USE_PREPROCESSING
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->PreProcess(Mode_id, Array_in, Array_out, Samples);
	}
	else
	{
		KODI->Log(LOG_ERROR, "PreProcess(...): uninitialized Stream was requested!");
		return 0;
	}
#else
	return 0;
#endif
}

unsigned int MasterProcess(const ADDON_HANDLE handle, float **Array_in, float **Array_out, unsigned int Samples)
{
#ifdef ADSP_ADDON_USE_MASTERPROCESS
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->MasterProcess(Array_in, Array_out, Samples);
	}
	else
	{
		KODI->Log(LOG_ERROR, "MasterProcess(...): uninitialized Stream was requested!");
		return 0;
	}
#else
	return 0;
#endif
}

unsigned int PostProcess(const ADDON_HANDLE handle, unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples)
{
#ifdef ADSP_ADDON_USE_POSTPROCESS
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->PostProcess(Mode_id, Array_in, Array_out, Samples);
	}
	else
	{
		KODI->Log(LOG_ERROR, "PostProcess(...): uninitialized Stream was requested!");
		return 0;
	}
#else
	return 0;
#endif
}

unsigned int OutputResampleProcess(const ADDON_HANDLE handle, float **array_in, float **array_out, unsigned int samples)
{
#ifdef ADSP_ADDON_USE_OUTPUTRESAMPLE
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->OutputResampleProcess(array_in,  array_out, samples);
	}
	else
	{
		KODI->Log(LOG_ERROR, "OutputResampleProcess(...): uninitialized Stream was requested!");
		return 0;
	}
#else
	return 0;
#endif
}

AE_DSP_ERROR StreamIsModeSupported(const ADDON_HANDLE handle, AE_DSP_MODE_TYPE Type, unsigned int Mode_id, int Unique_db_mode_id)
{
	CADSPProcessorHandle *p = g_AddonHandler.GetStream(handle->dataIdentifier);
	if(p)
	{
		return p->StreamIsModeSupported(Type, Mode_id, Unique_db_mode_id);
	}
	else
	{
		KODI->Log(LOG_ERROR, "StreamIsModeSupported(...): uninitialized Stream was requested!");
		return AE_DSP_ERROR_UNKNOWN;
	}
}

}
