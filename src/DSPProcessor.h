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


//! Example header file for a processing class.
/*!
 * \file DSPProcessor.h
 * ToDo: detailed description!
 */
#include <string>
#include "template/include/IADSPProcessor.h"
#include <asplib/Biquads/apslib_BiquadFactory.h>
#include "template/include/ADSPModeMessage.h"
#include "Messages/BiquadMessage_types.h"

//!	In this class you can define your processing modes.
/*! 
 * All processing modes can be enabled or disabled in the templateConfiguration.h.
 */
class CDSPProcessor : public IADSPProcessor
{
public:
  typedef enum
  {
    EQ_MESSAGE_UNKNOWN = 0,
    EQ_MESSAGE_BIQUAD_IDX_COEFFICIENTS,
    EQ_MESSAGE_BIQUAD_COEFFICIENTS_LIST,
    EQ_MESSAGE_POST_GAIN,
    EQ_MESSAGE_MAX
  }EQ_MESSAGES;
  //! Here for example you can create global buffers of your Addon
  CDSPProcessor();

  //! Here for example you can delete global buffers from your Addon
  ~CDSPProcessor();

  /*!
	 * @brief DSP post processing
	 * On the post processing can be things performed with additional channel upmix like 6.1 to 7.1
	 * or frequency/volume corrections, speaker distance handling, equalizer... .
	 * All DSP add-ons allowed to-do this.
	 * @param mode_id The mode inside add-on which must be performed on call. Id is set from add-on by iModeNumber on AE_DSP_MODE structure during RegisterMode callback,
	 * and can be defined from add-on as a structure pointer or anything else what is needed to find it.
	 * @param array_in Pointer to input data memory
	 * @param array_out Pointer to output data memory
	 * @param samples Amount of samples inside array_in
	 * @return Amount of samples processed
	 * @remarks Optional. Is set by AE_DSP_ADDON_CAPABILITIES and asked with GetAddonCapabilities
	 */
  virtual unsigned int PostProcess(unsigned int Mode_id, float **Array_in, float **Array_out, unsigned int Samples);

  virtual AE_DSP_ERROR Create();

  AE_DSP_ERROR send_Message(CADSPModeMessage &Message);

private:
  void process_NewMessage();

  ADSP_Biquad                  *m_Biquads;
  ADSP_Biquad                  *m_TempBiquad;
  float                        *m_PostGain;
  volatile bool                 m_NewMessage;
  int                           m_MaxProcessingChannels;
  uint32_t                      m_MaxFreqBands;
  int                           m_MessageType;
  void                         *m_MessagePtr;
  int                           m_MessageArrayElements;
  int                           m_MessageAudioChannel;
};
