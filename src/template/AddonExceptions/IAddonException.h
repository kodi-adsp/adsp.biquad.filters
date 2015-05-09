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

template<typename T>
class IAddonException
{
  public:
    IAddonException(std::string Function="", std::string Filename="", int Line=-1, std::string Module="")
    {
      m_Function    = Function;
      m_Filename    = Filename;
      m_Line        = Line;
      m_Module      = Module;
      m_Line        = Line;
    }

    virtual ~IAddonException() {}

    virtual T &what() = 0;

  protected:
    T m_Exception;
    std::string m_Function;
    std::string m_Filename;
    std::string m_Module;
    int         m_Line;
};
