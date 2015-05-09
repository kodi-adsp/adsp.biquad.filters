//! Example array mode settings.
/*!
 * \file templateConfiguration.cpp
 * This file configures the adsp.template for the adsp.biquad.filters addon
 */

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
#include "../include/typedefs.h"
#include "../include/client.h"
#include "../configuration/templateConfiguration.h"
#include <string>

// image user path
std::string adspImageUserPath = "resources//skins//media";

//// configuration for input resample
//ADSP_INRESMOD_UNIQUEDBID adspInResampleUniqueDdId = -1;
//ADSP_INRESMOD_STR_NAMES adspInResampleStrNames[AE_DSP_ADDON_STRING_LENGTH] = {"Input Resample Mode 1"};
//
//ADSP_INRESMOD_MODE_NUM adspInResampleModeNum = INPUT_RESAMPLE_MODE_ID;
//ADSP_INRESMOD_TYPE_FLAGS adspInResampleTypeFlags = {	AE_DSP_PRSNT_ASTREAM_BASIC | AE_DSP_PRSNT_ASTREAM_MUSIC | AE_DSP_PRSNT_ASTREAM_MOVIE | AE_DSP_PRSNT_ASTREAM_GAME | AE_DSP_PRSNT_ASTREAM_APP | AE_DSP_PRSNT_ASTREAM_MESSAGE | AE_DSP_PRSNT_ASTREAM_PHONE};
//ADSP_INRESMOD_SETTINGS_DIALOG adspInResampleSettings = {true};
//ADSP_INRESMOD_DISABLED adspInResampleDisabled = {true};
//
//ADSP_INRESMOD_NAME adspInResampleName = {30000};
//ADSP_INRESMOD_SETUP_NAME adspInResampleSetupName = {30001};
//ADSP_INRESMOD_DESCRIPTION adspInResampleDescription = {30002};
//ADSP_INRESMOD_HELP adspInResampleHelp = {30003};
//
//ADSP_INRESMOD_OWN_IMAGE adspInResampleOwnImage[AE_DSP_ADDON_STRING_LENGTH] = {""};
////ADSP_INRESMOD_OVERRIDE_IMAGE adspInResampleOverrideImage[ADSP_MAX_INRES_MODES][AE_DSP_ADDON_STRING_LENGTH] = {""};


//// configuration for preprocessing modes
//ADSP_PREMOD_UNIQUEDBID adspPreUniqueDbId[ADSP_MAX_PRE_MODES] = {-1};
//ADSP_PREMOD_STR_NAMES adspPreStrNames[ADSP_MAX_PRE_MODES][AE_DSP_ADDON_STRING_LENGTH] = {"Preprocess Mode 1"};
//
//ADSP_PREMOD_MODE_NUM adspPreModeNum[ADSP_MAX_PRE_MODES] = {PRE_MODE1_ID};
//ADSP_PREMOD_TYPE_FLAGS adspPreTypeFlags[ADSP_MAX_PRE_MODES] = {	AE_DSP_PRSNT_ASTREAM_BASIC | AE_DSP_PRSNT_ASTREAM_MUSIC | AE_DSP_PRSNT_ASTREAM_MOVIE | AE_DSP_PRSNT_ASTREAM_GAME | AE_DSP_PRSNT_ASTREAM_APP | AE_DSP_PRSNT_ASTREAM_MESSAGE | AE_DSP_PRSNT_ASTREAM_PHONE};
//ADSP_PREMOD_SETTINGS_DIALOG adspPreSettings[ADSP_MAX_PRE_MODES] = {true};
//ADSP_PREMOD_DISABLED adspPreDisabled[ADSP_MAX_PRE_MODES] = {true};
//
//ADSP_PREMOD_NAME adspPreName[ADSP_MAX_PRE_MODES] = {30004};
//ADSP_PREMOD_SETUP_NAME adspPreSetupName[ADSP_MAX_PRE_MODES] = {30005};
//ADSP_PREMOD_DESCRIPTION adspPreDescription[ADSP_MAX_PRE_MODES] = {30006};
//ADSP_PREMOD_HELP adspPreHelp[ADSP_MAX_PRE_MODES] = {30007};
//
//ADSP_PREMOD_OWN_IMAGE adspPreOwnImage[ADSP_MAX_PRE_MODES][AE_DSP_ADDON_STRING_LENGTH] = {""};
////ADSP_PREMOD_OVERRIDE_IMAGE adspPreOverrideImage[ADSP_MAX_PRE_MODES][AE_DSP_ADDON_STRING_LENGTH] = {""};


//// configuration for master modes
//ADSP_MAMOD_UNIQUEDBID adspMaUniqueDdId[ADSP_MAX_MASTER_MODES] = {-1};
//ADSP_MAMOD_STR_NAMES adspMaStrNames[ADSP_MAX_MASTER_MODES][AE_DSP_ADDON_STRING_LENGTH] = {"Master Mode 1"};
//
//ADSP_MAMOD_MODE_NUM adspMaModeNum[ADSP_MAX_MASTER_MODES] = {MA_MODE1_ID};
//ADSP_MAMOD_TYPE_FLAGS adspMaTypeFlags[ADSP_MAX_MASTER_MODES] = {	AE_DSP_PRSNT_ASTREAM_BASIC | AE_DSP_PRSNT_ASTREAM_MUSIC | AE_DSP_PRSNT_ASTREAM_MOVIE | AE_DSP_PRSNT_ASTREAM_GAME | AE_DSP_PRSNT_ASTREAM_APP | AE_DSP_PRSNT_ASTREAM_MESSAGE | AE_DSP_PRSNT_ASTREAM_PHONE};
//ADSP_MAMOD_SETTINGS_DIALOG adspMasterSettings[ADSP_MAX_MASTER_MODES] = {true};
//ADSP_MAMOD_DISABLED adspMaDisabled[ADSP_MAX_MASTER_MODES] = {true};
//
//ADSP_MAMOD_NAME adspMaName[ADSP_MAX_MASTER_MODES] = {30008};
//ADSP_MAMOD_SETUP_NAME adspMaSetupName[ADSP_MAX_MASTER_MODES] = {30009};
//ADSP_MAMOD_DESCRIPTION adspMaDescription[ADSP_MAX_MASTER_MODES] = {30010};
//ADSP_MAMOD_HELP adspMaHelp[ADSP_MAX_MASTER_MODES] = {30011};
//
//ADSP_MAMOD_OWN_IMAGE adspMaOwnImage[ADSP_MAX_MASTER_MODES][AE_DSP_ADDON_STRING_LENGTH] = {""};
//ADSP_MAMOD_OVERRIDE_IMAGE adspMaOverrideImage[ADSP_MAX_MASTER_MODES][AE_DSP_ADDON_STRING_LENGTH] = {""};


// configuration for postprocess modes
ADSP_POSTMOD_UNIQUEDBID adspPostUniqueDbId[ADSP_MAX_POST_MODES] = {-1};
ADSP_POSTMOD_STR_NAMES adspPostStrNames[ADSP_MAX_POST_MODES][AE_DSP_ADDON_STRING_LENGTH] = {"parametric EQ"};

ADSP_POSTMOD_MODE_NUM adspPostModeNum[ADSP_MAX_POST_MODES] = {POST_MODE_PARAMETRIC_EQ_ID};
ADSP_POSTMOD_TYPE_FLAGS adspPostTypeFlags[ADSP_MAX_POST_MODES] = {AE_DSP_PRSNT_ASTREAM_BASIC | AE_DSP_PRSNT_ASTREAM_MUSIC | AE_DSP_PRSNT_ASTREAM_MOVIE | AE_DSP_PRSNT_ASTREAM_GAME | AE_DSP_PRSNT_ASTREAM_APP | AE_DSP_PRSNT_ASTREAM_MESSAGE | AE_DSP_PRSNT_ASTREAM_PHONE};
ADSP_POSTMOD_SETTINGS_DIALOG adspPostSettings[ADSP_MAX_POST_MODES] = {true};
ADSP_POSTMOD_DISABLED adspPostDisabled[ADSP_MAX_POST_MODES] = {true};

ADSP_POSTMOD_NAME adspPostName[ADSP_MAX_POST_MODES] = {30000};
ADSP_POSTMOD_SETUP_NAME adspPostSetupName[ADSP_MAX_POST_MODES] = {30001};
ADSP_POSTMOD_DESCRIPTION adspPostDescription[ADSP_MAX_POST_MODES] = {30002};
ADSP_POSTMOD_HELP adspPostHelp[ADSP_MAX_POST_MODES] = {30003};

ADSP_POSTMOD_OWN_IMAGE adspPostOwnImage[ADSP_MAX_POST_MODES][AE_DSP_ADDON_STRING_LENGTH] = {"adsp.parametric.eq_modeLogo.png"};
ADSP_POSTMOD_OVERRIDE_IMAGE adspPostOverrideImage[ADSP_MAX_POST_MODES][AE_DSP_ADDON_STRING_LENGTH] = {""};


//// configuration for output resample
//ADSP_OUTRESMOD_UNIQUEDBID adspOutResampleUniqueDdId = -1;//[ADSP_MAX_OUTRES_MODES] = {-1};
//ADSP_OUTRESMOD_STR_NAMES adspOutResampleStrNames[AE_DSP_ADDON_STRING_LENGTH] = {"Output Resample Mode 1"};
//
//ADSP_OUTRESMOD_MODE_NUM adspOutResampleModeNum = OUTPUT_RESAMPLE_MODE_ID;
//ADSP_OUTRESMOD_TYPE_FLAGS adspOutResampleTypeFlags = {	AE_DSP_PRSNT_ASTREAM_BASIC | AE_DSP_PRSNT_ASTREAM_MUSIC | AE_DSP_PRSNT_ASTREAM_MOVIE | AE_DSP_PRSNT_ASTREAM_GAME | AE_DSP_PRSNT_ASTREAM_APP | AE_DSP_PRSNT_ASTREAM_MESSAGE | AE_DSP_PRSNT_ASTREAM_PHONE};
//ADSP_OUTRESMOD_SETTINGS_DIALOG adspOutResampleSettings = {true};
//ADS_OUTRESMOD_DISABLED adspOutResampleDisabled = {true};
//
//ADSP_OUTRESMOD_NAME adspOutResampleName = {30016};
//ADSP_OUTRESMOD_SETUP_NAME adspOutResampleSetupName = {30017};
//ADSP_OUTRESMOD_DESCRIPTION adspOutResampleDescription = {30018};
//ADSP_OUTRESMOD_HELP adspOutResampleHelp = {30019};
//
//ADSP_OUTRESMOD_OWN_IMAGE adspOutResampleOwnImage[AE_DSP_ADDON_STRING_LENGTH] = {""};
//ADSP_OUTRESMOD_OVERRIDE_IMAGE adspOutResampleOverrideImage[ADSP_MAX_OUTRES_MODES][AE_DSP_ADDON_STRING_LENGTH] = {""};