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
#include "template/include/MACROHelper.h"
#include ADSP_PROCESSOR_HEADER_FILE

class CADSPProcessorHandle : public ADSP_PROCESSOR_CLASS_NAME
{
public:
	CADSPProcessorHandle(const AE_DSP_SETTINGS *settings, const AE_DSP_STREAM_PROPERTIES *pProperties);
	~CADSPProcessorHandle();

	AE_DSP_ERROR StreamInitialize(const AE_DSP_SETTINGS *settings);

	float OutputResampleGetDelay();
	float PostProcessGetDelay(unsigned int Mode_id);
	float MasterProcessGetDelay();
	float PreProcessGetDelay(unsigned int Mode_id);
	float InputResampleGetDelay();
};
