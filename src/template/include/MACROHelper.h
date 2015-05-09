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
#include "typedefs.h"
#include "../configuration/templateConfiguration.h"

#define USE_ADDONOPTIONAL	defined(ADSP_ADDON_USE_SETTINGS) || defined(ADSP_ADDON_USE_READSETTINGS) || \
							defined(ADSP_ADDON_USE_GETSETTINGS) || defined(ADSP_ADDON_USE_STOP) || \
							defined(ADSP_ADDON_USE_FREESETTINGS) || defined(ADSP_ADDON_USE_ANNOUNCE) || \
							defined(ADSP_ADDON_USE_MENUHOOK)

#define SIZE_OF_ARRAY(X, Y) sizeof(X)/sizeof(Y)

#define STRINGIFY_(x) #x
#define STRINGIFY(x) STRINGIFY_(x)

#ifdef ADSP_ADDON_USE_INPUTRESAMPLE
	extern ADSP_INRESMOD_UNIQUEDBID adspInResampleUniqueDdId;
	extern ADSP_INRESMOD_STR_NAMES adspInResampleStrNames[AE_DSP_ADDON_STRING_LENGTH];

	extern ADSP_INRESMOD_MODE_NUM adspInResampleModeNum;
	extern ADSP_INRESMOD_TYPE_FLAGS adspInResampleTypeFlags;
	extern ADSP_INRESMOD_SETTINGS_DIALOG adspInResampleSettings;
	extern ADSP_INRESMOD_DISABLED adspInResampleDisabled;

	extern ADSP_INRESMOD_NAME adspInResampleName;
	extern ADSP_INRESMOD_SETUP_NAME adspInResampleSetupName;
	extern ADSP_INRESMOD_DESCRIPTION adspInResampleDescription;
	extern ADSP_INRESMOD_HELP adspInResampleHelp;

	extern ADSP_INRESMOD_OWN_IMAGE adspInResampleOwnImage[AE_DSP_ADDON_STRING_LENGTH];
	extern ADSP_INRESMOD_OVERRIDE_IMAGE adspInResampleOverrideImage[AE_DSP_ADDON_STRING_LENGTH];
#endif

#ifdef ADSP_ADDON_USE_PREPROCESSING
	extern ADSP_PREMOD_UNIQUEDBID adspPreUniqueDbId[ADSP_MAX_PRE_MODES];
	extern ADSP_PREMOD_STR_NAMES adspPreStrNames[ADSP_MAX_PRE_MODES][AE_DSP_ADDON_STRING_LENGTH];

	extern ADSP_PREMOD_MODE_NUM adspPreModeNum[ADSP_MAX_PRE_MODES];
	extern ADSP_PREMOD_TYPE_FLAGS adspPreTypeFlags[ADSP_MAX_PRE_MODES];
	extern ADSP_PREMOD_SETTINGS_DIALOG adspPreSettings[ADSP_MAX_PRE_MODES];
	extern ADSP_PREMOD_DISABLED adspPreDisabled[ADSP_MAX_PRE_MODES];

	extern ADSP_PREMOD_NAME adspPreName[ADSP_MAX_PRE_MODES];
	extern ADSP_PREMOD_SETUP_NAME adspPreSetupName[ADSP_MAX_PRE_MODES];
	extern ADSP_PREMOD_DESCRIPTION adspPreDescription[ADSP_MAX_PRE_MODES];
	extern ADSP_PREMOD_HELP adspPreHelp[ADSP_MAX_PRE_MODES];

	extern ADSP_PREMOD_OWN_IMAGE adspPreOwnImage[ADSP_MAX_PRE_MODES][AE_DSP_ADDON_STRING_LENGTH];
	extern ADSP_PREMOD_OVERRIDE_IMAGE adspPreOverrideImage[ADSP_MAX_PRE_MODES][AE_DSP_ADDON_STRING_LENGTH];
#endif


#ifdef ADSP_ADDON_USE_MASTERPROCESS
	extern ADSP_MAMOD_UNIQUEDBID adspMaUniqueDdId[ADSP_MAX_MASTER_MODES];
	extern ADSP_MAMOD_STR_NAMES adspMaStrNames[ADSP_MAX_MASTER_MODES][AE_DSP_ADDON_STRING_LENGTH];

	extern ADSP_MAMOD_MODE_NUM adspMaModeNum[ADSP_MAX_MASTER_MODES];
	extern ADSP_MAMOD_TYPE_FLAGS adspMaTypeFlags[ADSP_MAX_MASTER_MODES];
	extern ADSP_MAMOD_SETTINGS_DIALOG adspMasterSettings[ADSP_MAX_MASTER_MODES];
	extern ADSP_MAMOD_DISABLED adspMaDisabled[ADSP_MAX_MASTER_MODES];

	extern ADSP_MAMOD_NAME adspMaName[ADSP_MAX_MASTER_MODES];
	extern ADSP_MAMOD_SETUP_NAME adspMaSetupName[ADSP_MAX_MASTER_MODES];
	extern ADSP_MAMOD_DESCRIPTION adspMaDescription[ADSP_MAX_MASTER_MODES];
	extern ADSP_MAMOD_HELP adspMaHelp[ADSP_MAX_MASTER_MODES];

	extern ADSP_MAMOD_OWN_IMAGE adspMaOwnImage[ADSP_MAX_MASTER_MODES][AE_DSP_ADDON_STRING_LENGTH];
	extern ADSP_MAMOD_OVERRIDE_IMAGE adspMaOverrideImage[ADSP_MAX_MASTER_MODES][AE_DSP_ADDON_STRING_LENGTH];
#endif


#ifdef ADSP_ADDON_USE_POSTPROCESS
	extern ADSP_POSTMOD_UNIQUEDBID adspPostUniqueDbId[ADSP_MAX_POST_MODES];
	extern ADSP_POSTMOD_STR_NAMES adspPostStrNames[ADSP_MAX_POST_MODES][AE_DSP_ADDON_STRING_LENGTH];

	extern ADSP_POSTMOD_MODE_NUM adspPostModeNum[ADSP_MAX_POST_MODES];
	extern ADSP_POSTMOD_TYPE_FLAGS adspPostTypeFlags[ADSP_MAX_POST_MODES];
	extern ADSP_POSTMOD_SETTINGS_DIALOG adspPostSettings[ADSP_MAX_POST_MODES];
	extern ADSP_POSTMOD_DISABLED adspPostDisabled[ADSP_MAX_POST_MODES];

	extern ADSP_POSTMOD_NAME adspPostName[ADSP_MAX_POST_MODES];
	extern ADSP_POSTMOD_SETUP_NAME adspPostSetupName[ADSP_MAX_POST_MODES];
	extern ADSP_POSTMOD_DESCRIPTION adspPostDescription[ADSP_MAX_POST_MODES];
	extern ADSP_POSTMOD_HELP adspPostHelp[ADSP_MAX_POST_MODES];

	extern ADSP_POSTMOD_OWN_IMAGE adspPostOwnImage[ADSP_MAX_POST_MODES][AE_DSP_ADDON_STRING_LENGTH];
	extern ADSP_POSTMOD_OVERRIDE_IMAGE adspPostOverrideImage[ADSP_MAX_POST_MODES][AE_DSP_ADDON_STRING_LENGTH];
#endif

#ifdef ADSP_ADDON_USE_OUTPUTRESAMPLE
	extern ADSP_OUTRESMOD_UNIQUEDBID adspOutResampleUniqueDdId;
	extern ADSP_OUTRESMOD_STR_NAMES adspOutResampleStrNames[AE_DSP_ADDON_STRING_LENGTH];

	extern ADSP_OUTRESMOD_MODE_NUM adspOutResampleModeNum;
	extern ADSP_OUTRESMOD_TYPE_FLAGS adspOutResampleTypeFlags;
	extern ADSP_OUTRESMOD_SETTINGS_DIALOG adspOutResampleSettings;
	extern ADS_OUTRESMOD_DISABLED adspOutResampleDisabled;

	extern ADSP_OUTRESMOD_NAME adspOutResampleName;
	extern ADSP_OUTRESMOD_SETUP_NAME adspOutResampleSetupName;
	extern ADSP_OUTRESMOD_DESCRIPTION adspOutResampleDescription;
	extern ADSP_OUTRESMOD_HELP adspOutResampleHelp;

	extern ADSP_OUTRESMOD_OWN_IMAGE adspOutResampleOwnImage[AE_DSP_ADDON_STRING_LENGTH];
	extern ADSP_OUTRESMOD_OVERRIDE_IMAGE adspOutResampleOverrideImage[AE_DSP_ADDON_STRING_LENGTH];
#endif