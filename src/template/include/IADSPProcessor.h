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

#include <kodi_adsp_types.h>
#include "../configuration/templateConfiguration.h"

//!	This is the interface class and you must derive your processing class from this interface.
/*! 
 * All processing modes can be enabled or disabled in the templateConfiguration.h.
 */
class IADSPProcessor
{
public:
	IADSPProcessor();
	virtual ~IADSPProcessor();

#ifdef ADSP_ADDON_USE_INPUTPROCESS
	//! If you define ADSP_ADDON_USE_INPUTPROCESS in templateConfiguration.h 
	//! then your derived processing class must implement 
	//! CDSPProcessor::InputProcess(float **Array_in, unsigned int Samples).
	/*!
	 * Can be used to have unchanged stream.
	 * @param Array_in Pointer to data memory
	 * @param Samples Amount of samples inside Array_in
	 * @return true if work was OK
	 * @remarks All ADSP add-ons allowed to-do this. This Mode is optional and can be enabled if you define ADSP_ADDON_USE_INPUTPROCESS in templateConfiguration.h.
	 */
	virtual bool InputProcess(const float **Array_in, unsigned int Samples) = 0;
#endif
#ifdef ADSP_ADDON_USE_INPUTRESAMPLE
	//! If you define ADSP_ADDON_USE_INPUTPROCESS in templateConfiguration.h 
	//! then your derived processing class must implement
	//! CDSPProcessor::InputProcess(float **Array_in, unsigned int Samples).
	/*!
	 * This mode is processed before a mastermode and can be used to have a high quality resample.
	 * @param Array_in Pointer to input data memory
	 * @param Array_out Pointer to output data memory
	 * @param Samples Amount of samples inside Array_in
	 * @return Amount of samples processed
	 * @remarks Only one ADSP add-on is allowed to-do this! This Mode is optional and can be enabled if you define ADSP_ADDON_USE_INPUTRESAMPLE in templateConfiguration.h.
	 */
	virtual unsigned int InputResampleProcess(float **Array_in, float **Array_out, unsigned int Samples) = 0;
#endif
#ifdef ADSP_ADDON_USE_PREPROCESSING
	//! If you define ADSP_ADDON_USE_INPUTPROCESS in templateConfiguration.h 
	//! then your derived processing class must implement 
	//! CDSPProcessor::PreProcess(unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples).
	/*!
	 * @param Mode_id The mode inside add-on which must be performed on call. 
	 * Id is set from add-on and can be modified templateConfiguration.cpp by editing adspPreModeNum array.
	 * Best practise is to use a global enum to have only a mode id once. 
	 * For example see adspProcessingModeIDs in templateConfiguration.h
	 * @param Array_in Pointer to input data memory
	 * @param Array_out Pointer to output data memory
	 * @param Samples Amount of samples inside Array_in
	 * @return Amount of samples processed
	 * @remarks All ADSP add-ons allowed to-do this. This Mode is optional and can be enabled if you define ADSP_ADDON_USE_PREPROCESSING in templateConfiguration.h.
	 */
	virtual unsigned int PreProcess(unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples) = 0;
#endif
#ifdef ADSP_ADDON_USE_MASTERPROCESS
	//! If you define ADSP_ADDON_USE_INPUTPROCESS in templateConfiguration.h 
	//! then your derived processing class must implement 
	//! CDSPProcessor::MasterProcess(float **Array_in, float **Array_out, unsigned int Samples).
	/*!
	 * Master processing becomes performed with it Here a channel up-mix/down-mix 
	 * for stereo surround sound can be performed. Only one master mode can be selected
	 * in listening mode.
	 * @param Array_in Pointer to input data memory
	 * @param Array_out Pointer to output data memory
	 * @param Samples Amount of samples inside Array_in
	 * @return Amount of samples processed
	 * @remarks Optional. Is set by AE_DSP_ADDON_CAPABILITIES and asked with GetAddonCapabilities
	 */
	virtual unsigned int MasterProcess(float **Array_in, float **Array_out, unsigned int Samples) = 0;
#endif
#ifdef ADSP_ADDON_USE_POSTPROCESS
	//! If you define ADSP_ADDON_USE_INPUTPROCESS in templateConfiguration.h 
	//! then your derived processing class must implement 
	//! CDSPProcessor::PostProcess(unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples).
	/*!
	 * DSP post processing <br>
	 * On the post processing can be things performed with additional channel upmix like 6.1 to 7.1
	 * or frequency/volume corrections, speaker distance handling, equalizer... .
	 * All DSP add-ons allowed to-do this.
	 * @param Mode_id The mode inside add-on which must be performed on call. 
	 * Id is set from add-on and can be modified templateConfiguration.cpp by editing adspPreModeNum array.
	 * Best practise is to use a global enum to have only a mode id once. 
	 * For example see adspProcessingModeIDs in templateConfiguration.h
	 * @param Array_in Pointer to input data memory
	 * @param Array_out Pointer to output data memory
	 * @param Samples Amount of samples inside Array_in
	 * @return Amount of samples processed
	 * @remarks Optional. Is set by AE_DSP_ADDON_CAPABILITIES and asked with GetAddonCapabilities
	 */
	virtual unsigned int PostProcess(unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples) = 0;
#endif
#ifdef ADSP_ADDON_USE_INPUTPROCESS
	//! If you define ADSP_ADDON_USE_INPUTPROCESS in templateConfiguration.h 
	//! then your derived processing class must implement
	//! CDSPProcessor::OutputResampleProcess(float **Array_in, float **Array_out, unsigned int Samples).
	/*!
	 * DSP post processing <br>
	 * On the post processing can be things performed with additional channel 
	 * upmix like 6.1 to 7.1 or frequency/volume corrections, speaker distance handling,
	 * equalizer... . All ADSP add-ons allowed to-do this.
	 * @param Array_in Pointer to input data memory
	 * @param Array_out Pointer to output data memory
	 * @param Samples Amount of samples inside Array_in
	 * @return Amount of samples processed
	 * @remarks Optional. Is set by AE_DSP_ADDON_CAPABILITIES and asked with GetAddonCapabilities
	 */
	virtual unsigned int OutputResampleProcess(float **Array_in, float **Array_out, unsigned int Samples) = 0;
#endif

	//!	This method returns the needed output array size for the preprocessing mode.
	/*!
	 * If the addon operate with buffered arrays and the output size can be higher as the input
	 * it becomes asked about needed size before any PreProcess call.
	 * @param Mode_id The mode inside add-on which must be performed on call. 
	 * Id is set from add-on and can be modified templateConfiguration.cpp by editing adspPreModeNum array.
	 * Best practise is to use a global enum to have only a mode id once. 
	 * For example see adspProcessingModeIDs in templateConfiguration.h
	 * @return The needed size of output array or 0 if no changes within it. 
	 * The default implementation always returns 0.
	 * @remarks This method can be overloaded within your processing class 
	 * if you wanna process other output array sizes.
	 */
	virtual unsigned int PreProcessNeededSamplesize(unsigned int Mode_id);
	
	//! This method is used to get the needed input resample buffer size.
	/*!
	 * If the add-on operate with buffered arrays and the output size 
	 * can be higher as the input it becomes asked about needed size before
	 * any OutputResampleProcess call.
	 * @return The needed size of output array or 0 if no changes within it
	 * @remarks This method always returns 0. If you wanna return a other buffer size
	 * then you have to overload this method in your processing class.
	 */
	virtual unsigned int InputResampleProcessNeededSamplesize();

	//! This method is used to return the sample rate before master process.
	/*!
	 * Returns the re-sampling generated new sample rate used before the master process
	 * @return The default input sample rate from \ref m_StreamSettings.
	 * @remarks This method always returns the stream process sample rate. 
	 * If you wanna return a other sample rate then you have to overload this 
	 * method in your processing class.
	 */
	virtual int InputResampleSampleRate();
	
	//! Set the active master process mode.
	/*!
	 * @param Type Requested stream type for the selected master mode.
	 * @param Mode_id The mode inside add-on which must be performed on call. 
	 * Id is set from add-on and can be modified templateConfiguration.cpp by 
	 * editing adspPreModeNum array. Best practise is to use a global enum to 
	 * have only a mode id once. For example see adspProcessingModeIDs in 
	 * templateConfiguration.h
	 * @param Unique_db_mode_id The Mode unique id generated from DSP database.
	 * @return AE_DSP_ERROR_NO_ERROR if the setup was successful
	 * @remarks If you wanna support more than one master modes you have to overload this
	 * method and manage your active master mode by your self. By default this method does
	 * nothing.
	 */
	virtual AE_DSP_ERROR MasterProcessSetMode(AE_DSP_STREAMTYPE Type, unsigned int Mode_id, int Unique_db_mode_id);

	//!	This method returns the needed output array size for the master processing mode. 
	/*!
	 * @brief If the add-on operate with buffered arrays and the output size can be higher as the input
	 * it becomes asked about needed size before any MasterProcess call.
	 * @return The needed size of output array or 0 if no changes within it.
	 * @remarks This method always returns 0. If you wanna return a 
	 * buffer sizes then you have to overload this method in your processing class.
	 */
	virtual unsigned int MasterProcessNeededSamplesize();

	//! This method returns the performed channel alignment. 
	/*!
	 * If you wanna use this function then you have to overload it and
	 * set your own channel flags.
	 * @retval	Out_channel_present_flags the exact channel present flags after performed up-/downmix 
	 *			for availible flags see AE_DSP_CHANNEL_PRESENT in xbmc_adsp_types.h
	 * @return	The amount channels, when no up- or downmix should be performed always return -1. 
	 *			This method returns always -1 by default.
	 * @remarks Optional. Must be used and set if a channel up- or downmix is processed from the active master mode
	 */
	virtual int MasterProcessGetOutChannels(unsigned long &Out_channel_present_flags);

	//!	Used to get a information string about the processed work to show on skin.
	/*!
	 * @return A string to show. This method always returns a empty string.
	 * @remarks If you wanna return a custom string, then you must overload this method
	 * in your processing class.
	 */
	virtual const char *MasterProcessGetStreamInfoString();

	//!	This method returns the needed output array size for the postprocessing mode. 
	/*!
	 * If the add-on operate with buffered arrays and the output size can be higher as 
	 * the input it becomes asked about needed size before any PostProcess call.
	 * @param Mode_id The mode inside add-on which must be performed on call. 
	 * Id is set from add-on and can be modified templateConfiguration.cpp by 
	 * editing adspPreModeNum array. Best practise is to use a global enum to 
	 * have only a mode id once. For example see adspProcessingModeIDs in 
	 * templateConfiguration.h
	 * @return The needed size of output array or 0 if no changes within it
	 * @remarks This method always returns 0. If you wanna return a 
	 * buffer sizes then you have to overload this method in your processing class.
	 */
	virtual unsigned int PostProcessNeededSamplesize(unsigned int Mode_id);
	
	//! This method is used to get the needed output resample buffer size.
	/*!
	 * If the add-on operate with buffered arrays and the output size 
	 * can be higher as the input it becomes asked about needed size before
	 * any OutputResampleProcess call.
	 * @return The needed size of output array or 0 if no changes within it
	 * @remarks This method always returns 0. If you wanna return a other buffer size
	 * then you have to overload this method in your processing class.
	 */
	virtual unsigned int OutputResampleProcessNeededSamplesize();

	//! This method is used to return the sample rate after master process.
	/*!
	 * Returns the re-sampling generated new sample rate used after the master process
	 * @return The default output sample rate from \ref m_StreamSettings.
	 * @remarks This method always returns the stream process sample rate. 
	 * If you wanna return a other sample rate then you have to overload this 
	 * method in your processing class.
	 */
	virtual int OutputResampleSampleRate();

	//! This method checks the input stream and can filter processing mode types.
	/*!
	 * Ask the add-on about a requested processing mode that it is supported on the current
	 * stream. Is called about every add-on mode after successed StreamCreate.
	 * @param Type The processing mode type, see AE_DSP_MODE_TYPE for definitions
	 * @param Mode_id The mode inside add-on which must be performed on call. 
	 * Id is set from add-on and can be modified templateConfiguration.cpp by 
	 * editing adspPreModeNum array. Best practise is to use a global enum to 
	 * have only a mode id once. For example see adspProcessingModeIDs in 
	 * templateConfiguration.h
	 * @param Unique_db_mode_id The Mode unique id generated from dsp database.
	 * @return AE_DSP_ERROR_NO_ERROR if the properties were fetched successfully. 
	 * If the stream is not supported the ADSP addon must return AE_DSP_ERROR_IGNORE_ME.
	 * @remarks By default this method accept all processing types. 
	 * If you wanna filter processing mode types then you have to overload this method in
	 * your processing class.
	 */
	virtual AE_DSP_ERROR StreamIsModeSupported(AE_DSP_MODE_TYPE Type, unsigned int Mode_id, int Unique_db_mode_id);

  //! ToDo: description.
  /*!
   * Returns ToDo!
   * @return ToDo!
   * @remarks ToDo!
   */
  virtual AE_DSP_ERROR Create() = 0;
  
  //!	This gets the current stream settings and properties. 
  /*!
   * Get stream settings and properties. For details see  and AE_DSP_STREAM_PROPERTIES structures.
   * If the add-on operate with buffered arrays and the output size can be higher as 
   * the input it becomes asked about needed size before any PostProcess call.
   * @param pSettings Stream settings for details see AE_DSP_SETTINGS.
   * @param pProperties Stream properties for details see AE_DSP_STREAM_PROPERTIES.
   * @return AE_DSP_ERROR_INVALID_PARAMETERS: if your input parameters were invalid.
   * AE_DSP_ERROR_NO_ERROR: if all was ok.
   */
  AE_DSP_ERROR GetStreamInfos(const AE_DSP_SETTINGS *pSettings, const AE_DSP_STREAM_PROPERTIES* pProperties, void *CustomStreamInfos=NULL);


protected:
  //! ToDo: description.
  /*!
   * Returns ToDo!
   * @return ToDo!
   * @remarks ToDo!
   */
  virtual AE_DSP_ERROR GetCustomStreamInfos(void *CustomStreamSettings);

	//! Used stream settings for details see AE_DSP_SETTINGS.
	AE_DSP_SETTINGS m_StreamSettings;
	//! Used stream properties for details see AE_DSP_STREAM_PROPERTIES.
	AE_DSP_STREAM_PROPERTIES m_StreamProperties;
};
