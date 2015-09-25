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



#include <map>
#include <list>
#include <string>
#include <template/include/client.h>

#include "TSettingsElement.h"

// Settings typedefs
typedef TSettingsElement<std::string>   CStringSetting;
typedef TSettingsElement<unsigned int>  CUnsignedIntSetting;
typedef TSettingsElement<int>           CIntSetting;
typedef TSettingsElement<float>         CFloatSetting;
typedef TSettingsElement<double>        CDoubleSetting;
typedef TSettingsElement<bool>          CBoolSetting;
typedef std::list<ISettingsElement*>    CSettingsList;

// Settings macro helpers
#define STRING_SETTINGS(X)        dynamic_cast<CStringSetting*>(X)
#define UNSIGNED_INT_SETTINGS(X)  dynamic_cast<CUnsignedIntSetting*>(X)
#define INT_SETTINGS(X)           dynamic_cast<CIntSetting*>(X)
#define FLOAT_SETTINGS(X)         dynamic_cast<CFloatSetting*>(X)
#define DOUBLE_SETTINGS(X)        dynamic_cast<CDoubleSetting*>(X)
#define BOOL_SETTINGS(X)          dynamic_cast<CBoolSetting*>(X)

#define SETTINGS_SEPERATOR_STR "::"

typedef std::map<std::string, CSettingsList> SettingsMap;

class CSettingsManager
{
  public:
    CSettingsManager(std::string XMLFilename, std::string Path=g_strUserPath);
    ~CSettingsManager();
    // This method loads settings from an XML-File, this method can only called once during the lifetime of this object
    void Init();
    // This method can create or override settings elements
    bool add_Setting( std::string MainCategory, std::string SubCategory,
                      std::string GroupName, std::string Key,
                      ISettingsElement::SettingsTypes Type, void *Value);
    void destroy_Setting(std::string MainCategory, std::string SubCategory, std::string GroupName, std::string Key);
    ISettingsElement *find_Setting(std::string MainCategory, std::string SubCategory, std::string GroupName, std::string Key);

    // This method writes settings into the XML-File
    void write_SettingsXML();
        
  protected:
    ISettingsElement *CreateElement(std::string Key, ISettingsElement::SettingsTypes Type, void *Value);
    bool              SetNewElementValue(ISettingsElement *Element, void *Value);
    void destroy();
    //SettingsMap m_Settings;
    SettingsMap m_Settings;
    std::string m_XMLFilename;
    std::string m_Path;

    // This method reads settings from the XML-File
    void read_SettingsXML();

  private:
    bool m_IsSettingsXMLLoaded;
    
};
