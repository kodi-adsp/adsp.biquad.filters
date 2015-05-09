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



#include <string>
#include "IAddonException.h"

template<class T>
class TAddonException : public IAddonException<T>
{
  public:
    TAddonException(T Exception, std::string Function="", std::string Filename="", int Line=-1, std::string Module="")
      : IAddonException<T>(Function, Filename, Line, Module)
    {
      IAddonException<T>::m_Exception = Exception;
    }

    virtual ~TAddonException() {}

    virtual T &what() { return IAddonException<T>::m_Exception; }
};

// type definitions
typedef TAddonException<std::string> CAddonStringException;

#if defined (TARGET_WINDOWS)
  #ifndef __func__
    #define __func__ __FUNCTION__
  #endif
#endif

#define ADDON_STRING_EXCEPTION_HANDLER(ErrorStr)  CAddonStringException(ErrorStr, __func__, __FILE__, __LINE__)
#define ADDON_STRING_MODULE_EXCEPTION_HANDLER(ErrorStr, Module)  CAddonStringException(ErrorStr, __func__, __FILE__, __LINE__, Module)
