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

//! In this file you can configure the hole template.
/*!
 * \file templateConfiguration.h
 * This file configures the adsp.template for the adsp.biquad.filters addon
 */
#include "../include/typedefs.h"

//! Here you mus define the name of your processing class.
#define ADSP_PROCESSOR_CLASS_NAME   CDSPProcessor
//! Here you must define the name of the header file from your processing class.
#define ADSP_PROCESSOR_HEADER_FILE  "DSPProcessor.h"
//! Here you must define the name of your ADSP addon.
#define ADSP_ADDON_NAME             "Biquad Filters"
//! Here you must define the version of your ADSP addon.
#define ADSP_ADDON_VERSION          "0.0.1"
//#define ADSP_ADDON_ID

//optional calling methods
//! Here you can define the name of the header file for optional ADSP addon functions.
//! If you define this, then your ADSP addon can use optional functions for example 
//! a settings GUI.
#define	ADSP_ADDON_OPTIONAL_HEADER_FILE "ADDONOptional.h"
//! If have defined a optional header file, then you must define the name of your 
//! optional class.
#define ADSP_ADDON_OPTIONAL_CLASS_NAME  CADDONOptional
//! If you define this, then your ADSP addon can use settings.
#define ADSP_ADDON_USE_SETTINGS
//! This is optional and can be used to have configuration file.
#define ADSP_SETTINGS_FILE              "adsp.biquad.filters__GlobalSettings.xml"
//! If you define this, then your ADSP addon can read the saved settings.
#define ADSP_ADDON_USE_READSETTINGS
//! If you define this, then your ADSP addon can get settings from xbmc.
#define ADSP_ADDON_USE_GETSETTINGS
//! Use stop function
#define ADSP_ADDON_USE_STOP
//! Use free settings function
#define ADSP_ADDON_USE_FREESETTINGS
//! Use addon announce function
#define ADSP_ADDON_USE_ANNOUNCE
//! If you define this, then your ADSP addon can have a settings GUI for processing modes.
#define ADSP_ADDON_USE_MENUHOOK
//! If you define this, then your ADSP addon can use a optional init method and 
//! xbmc will call it when your ADSP is loaded the first time.
#define ADSP_ADDON_USE_OPTIONAL_INIT



//--------------processing methods--------------------------------------------
//! Define this if you wish to use input process mode within your ADSP addon. 
/*!
 * If you define this, then your processing class must implement 
 * CDSPProcessor::InputProcess(float **Array_in, unsigned int Samples)
 * in your processing class. For details see CDSPProcessor.
 */
//#define ADSP_ADDON_USE_INPUTPROCESS

//! Define this if you wish to use input resample mode within your ADSP addon.
/*!
 * If you define this, then your processing class must implement 
 * CDSPProcessor::InputResampleProcess(float **Array_in, float **Array_out, unsigned int Samples) 
 * in your processing class. For details see CDSPProcessor.
 */
//#define ADSP_ADDON_USE_INPUTRESAMPLE

//! Define this if you wish to use preprocessing mode within your ADSP addon.
/*!
 * If you define this, then your processing class must implement 
 * CDSPProcessor::PreProcess(unsigned int Mode_id, float **Array_in, 
 * float **Array_out, unsigned int Samples) 
 * in your processing class. For details see CDSPProcessor.
 */
//#define ADSP_ADDON_USE_PREPROCESSING

//! Define this if you wish to use master mode within your ADSP addon.
/*!
 * If you define this, then your processing class must implement 
 * CDSPProcessor::MasterProcess(float **Array_in, float **Array_out, unsigned int Samples)
 * in your processing class. For details see CDSPProcessor.
 */
//#define ADSP_ADDON_USE_MASTERPROCESS

//! Define this if you wish to use postprocess mode within your ADSP addon.
/*!
 * If you define this, then your processing class must implement 
 * CDSPProcessor::PostProcess(unsigned int Mode_id, float **Array_in, float **Array_out, 
 * unsigned int Samples) in your processing class. For details see CDSPProcessor.
 */
#define ADSP_ADDON_USE_POSTPROCESS

//! Define this if you wish to use output resample mode within your ADSP addon.
/*!
 * If you define this, then your processing class must implement 
 * CDSPProcessor::OutputResampleProcess(float **Array_in, float **Array_out, 
 * unsigned int Samples) in your processing class. For details see CDSPProcessor.
 */
//#define ADSP_ADDON_USE_OUTPUTRESAMPLE

// max processing methods
//#define ADSP_MAX_INRES_MODES  1
//! If you have defined ADSP_ADDON_USE_MASTERPROCESS, then you must define the amount 
//! of available masterprocess modes of your ADSP addon.
//#define ADSP_MAX_MASTER_MODES 1
//! If you have defined ADSP_ADDON_USE_MASTERPROCESS, then you must define the amount 
//! of available preprocess modes of your ADSP addon.
//#define ADSP_MAX_PRE_MODES    1
//! If you have defined ADSP_ADDON_USE_POSTPROCESS, then you must define the amount 
//! of available postprocess modes of your ADSP addon.
#define ADSP_MAX_POST_MODES     1
//#define ADSP_MAX_OUTRES_MODES 1

//--------------general settings--------------------------------------------
/**
 * @brief Here you can define mode ids. The best practise is to use this enum,
 * because a mode id should only use once in the whole ADSP addon.
 */
typedef enum
{
  ADSP_MODE_ID_UNKNOWN = 0,
  POST_MODE_PARAMETRIC_EQ_ID,
  ADSP_MODE_ID_MAX
}adspProcessingModeIDs;

typedef enum 
{
  ID_MENU_UNKNOWN = 0,
  ID_MENU_POST_PROCESS_PARAMETRIC_EQ,
  ID_MENU_MAX
}adspMENUIDs;
