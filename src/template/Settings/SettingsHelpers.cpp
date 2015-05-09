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



#include "SettingsHelpers.h"

using namespace std;


CSettingsHelpers::CSettingsHelpers()
{
}

CSettingsHelpers::~CSettingsHelpers()
{
}

string CSettingsHelpers::TranslateTypeEnumToStr(ISettingsElement::SettingsTypes eType)
{
  string type = "Unknown";

  switch(eType)
  {
    case ISettingsElement::STRING_SETTING:
      type = "string";
    break;

    case ISettingsElement::UNSIGNED_INT_SETTING:
      type = "unsigned int";
    break;

    case ISettingsElement::INT_SETTING:
      type = "int";
    break;

    case ISettingsElement::FLOAT_SETTING:
      type = "float";
    break;

    case ISettingsElement::DOUBLE_SETTING:
      type = "double";
    break;

    case ISettingsElement::BOOL_SETTING:
      type = "bool";
    break;

    default:
      type = "Unknown";
    break;
  }

  return type;
}

ISettingsElement::SettingsTypes CSettingsHelpers::TranslateTypeStrToEnum(string strType)
{
  ISettingsElement::SettingsTypes eType = ISettingsElement::UNKNOWN_SETTING;

  if(strType == "string")
  {
    eType = ISettingsElement::STRING_SETTING;
  }
  else if(strType == "unsigned int")
  {
    eType = ISettingsElement::UNSIGNED_INT_SETTING;
  }
  else if(strType == "int")
  {
    eType = ISettingsElement::INT_SETTING;
  }
  else if(strType == "float")
  {
    eType = ISettingsElement::FLOAT_SETTING;
  }
  else if(strType == "double")
  {
    eType = ISettingsElement::DOUBLE_SETTING;
  }
  else if(strType == "bool")
  {
    eType = ISettingsElement::BOOL_SETTING;
  }

  return eType;
}
