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

#ifndef ADSP_PROCESSOR_CLASS_NAME
#error ADSP_PROCESSOR_CLASS_NAME was not defined! Please define the name of your class in <Your Directory>/template/configuration/templateConfiguration.h
#endif

#ifndef ADSP_PROCESSOR_HEADER_FILE
#error "ADSP_PROCESSOR_HEADER_FILE was not defined! Please define the name of your include file in <Your Directory>/template/configuration/templateConfiguration.h"
#endif

#ifndef ADSP_ADDON_NAME
#error "ADSP_ADDON_NAME was not defined! Please define the the addon name in <Your Directory>/template/configuration/templateConfiguration.h"
#endif

#ifdef ADSP_ADDON_USE_MASTERPROCESS
#ifndef ADSP_MAX_MASTER_MODES
#error "Please define ADSP_MAX_MASTER_MODES with the number of used master processes!"
#endif
#endif