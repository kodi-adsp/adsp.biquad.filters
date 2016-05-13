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



#include <iterator>
#include <tinyxml.h>
#include "utils/stdStringUtils.h"
#include "SettingsHelpers.h"
#include "SettingsManager.h"
#include "../AddonExceptions/TAddonException.h"
#include "libXBMC_addon.h"
#include "exception"

using namespace ADDON;
using namespace std;

// helpers for XML-Files
#include <string>
#include <list>
typedef std::pair<std::string, std::string> ATTRIBUTE_PAIR;
typedef std::list<ATTRIBUTE_PAIR> ATTRIBUTES_LIST;

int getAttributesAsList(TiXmlElement* pElement, ATTRIBUTES_LIST &AttributesList);


CSettingsManager::CSettingsManager(string XMLFilename, string Path)
{
  if(XMLFilename == "" || XMLFilename.empty())
  {
    throw ADDON_STRING_EXCEPTION_HANDLER("Invalid XML filename!");
  }
  m_Path = Path;
  m_XMLFilename = generateFilePath(m_Path, XMLFilename);
  KODI->Log(LOG_DEBUG, "CSettingsManager will save it's XML file to: %s", m_XMLFilename.c_str());

  m_IsSettingsXMLLoaded = false;

  m_Settings.clear();
}

CSettingsManager::~CSettingsManager()
{
  destroy();
}

void CSettingsManager::Init()
{
  if(!m_IsSettingsXMLLoaded)
  {
    m_IsSettingsXMLLoaded = true;
    read_SettingsXML();
  }
}

void CSettingsManager::destroy()
{
  write_SettingsXML();

  // delete settings map and its elements
  for(SettingsMap::iterator mapIter = m_Settings.begin(); mapIter != m_Settings.end(); mapIter++)
  {
    for(CSettingsList::iterator listIter = mapIter->second.begin(); listIter != mapIter->second.end(); listIter++)
    {
      ISettingsElement *settingsElement = *listIter;
      if(settingsElement)
      {
        delete settingsElement;
        *listIter = NULL;
      }
    }
  }

  // all dynamic memory is deallocated, so we can delete the settings map
  m_Settings.clear();
}

void CSettingsManager::write_SettingsXML()
{
  try
  {
    if(m_Settings.size() > 0)
    {
      TiXmlDocument doc;
      // ToDo: check all TiXml* generations!
      TiXmlDeclaration *declaration = new TiXmlDeclaration("1.0", "", "");
      doc.LinkEndChild(declaration);
      TiXmlComment *autoGenComment = new TiXmlComment();
      autoGenComment->SetValue(" THIS IS A AUTO GENERTATED FILE. DO NOT EDIT! ");
      doc.LinkEndChild(autoGenComment);

      for(SettingsMap::iterator mapIter = m_Settings.begin(); mapIter != m_Settings.end(); mapIter++)
      {
        vector<string> tokens;
        strTokenizer(mapIter->first, SETTINGS_SEPERATOR_STR, tokens);
        if(tokens.size() != 3)
        {
          doc.Clear();
          KODI->Log(LOG_ERROR, "Line: %i func: %s, Saving XML-File failed! Wrong SettingsMap string! Please call contact Addon author!\n", __LINE__, __func__, m_XMLFilename.c_str());
          return;
        }

        TiXmlElement *mainCategory = NULL;
        // check if this main category is already available
        for(TiXmlNode *element = doc.FirstChild(); element && !mainCategory; element = element->NextSiblingElement())
        {
          if(element->Value() == tokens[0])
          {
            mainCategory = static_cast<TiXmlElement*>(element);
          }
        }

        if(!mainCategory)
        { // create new main category
          mainCategory = new TiXmlElement(tokens[0]);
          doc.LinkEndChild(mainCategory);
        }

        TiXmlElement *settingsGroup = new TiXmlElement("settings_group");
        settingsGroup->SetAttribute("sub_category", tokens[1].c_str());
        settingsGroup->SetAttribute("group_name", tokens[2].c_str());
        mainCategory->LinkEndChild(settingsGroup);

        for(CSettingsList::iterator setIter=mapIter->second.begin(); setIter != mapIter->second.end(); setIter++)
        {
          if(!*setIter)
          {
            KODI->Log(LOG_ERROR, "Line: %i func: %s, invalid settings element! Please call contact Addon author!\n", __LINE__, __func__);
            return;
          }
          TiXmlElement *setting = new TiXmlElement("setting");
          setting->SetAttribute("key", (*setIter)->get_Key().c_str());

          switch((*setIter)->get_Type())
          {
            case ISettingsElement::STRING_SETTING:
              setting->SetAttribute("string", STRING_SETTINGS(*setIter)->get_Setting().c_str());
            break;

            case ISettingsElement::UNSIGNED_INT_SETTING:
              setting->SetAttribute("unsigned_int", toString(UNSIGNED_INT_SETTINGS(*setIter)->get_Setting()).c_str());
            break;

            case ISettingsElement::INT_SETTING:
              setting->SetAttribute("int", INT_SETTINGS(*setIter)->get_Setting());
            break;

            case ISettingsElement::FLOAT_SETTING:
              setting->SetDoubleAttribute("float", (double)FLOAT_SETTINGS(*setIter)->get_Setting());
            break;

            case ISettingsElement::DOUBLE_SETTING:
              setting->SetDoubleAttribute("double", DOUBLE_SETTINGS(*setIter)->get_Setting());
            break;

            case ISettingsElement::BOOL_SETTING:
              if(BOOL_SETTINGS(*setIter)->get_Setting())
              {
                setting->SetAttribute("bool", "true");
              }
              else
              {
                setting->SetAttribute("bool", "false");
              }
            break;

            default:
              KODI->Log(LOG_ERROR, "Line: %i func: %s, invalid settings type! Please call contact Addon author!\n", __LINE__, __func__);
              return;
            break;
          }

          settingsGroup->LinkEndChild(setting);
        }
      }

      if(!doc.SaveFile(m_XMLFilename.c_str()))
      {
        KODI->Log(LOG_ERROR, "Couldn't save XML settings to file %s", m_XMLFilename.c_str());
      }
    }
  }
  catch(bad_alloc &e)
  {
    KODI->Log(LOG_ERROR, "In function: %s a invalid memory allocation accured! Not enough free memory? Exception message: %s\n", __func__, e.what());
  }
}

void CSettingsManager::read_SettingsXML()
{
  TiXmlDocument xmlDoc;
  if(!xmlDoc.LoadFile(m_XMLFilename))
  {
    KODI->Log(LOG_NOTICE, "No initial settings XML file found.");
    return;
  }

  TiXmlElement *pRootElement = xmlDoc.RootElement();
  if(!pRootElement)
  {
    KODI->Log(LOG_NOTICE, "Settings XML file is empty.");
    return;
  }

  string mainCategory = pRootElement->Value();
  for(TiXmlNode *pGroupNode = pRootElement->FirstChild(); pGroupNode != NULL; pGroupNode = pRootElement->IterateChildren(pGroupNode))
  {
    if(pGroupNode->ValueStr() == "settings_group")
    {
      ATTRIBUTES_LIST groupAttributesList;
      if(pGroupNode && pGroupNode->Type() == TiXmlNode::TINYXML_ELEMENT)
      {
        getAttributesAsList(pGroupNode->ToElement(), groupAttributesList);
      }

      if(pGroupNode && pGroupNode->Type() == TiXmlNode::TINYXML_ELEMENT && groupAttributesList.size() == 2 && pGroupNode->ValueStr() == "settings_group")
      {
        string subCategory = "";
        string groupName = "";
        for(ATTRIBUTES_LIST::iterator iter = groupAttributesList.begin(); iter != groupAttributesList.end(); iter++)
        {
          if(iter->first == "sub_category")
          {
            subCategory = iter->second;
          }

          if(iter->first == "group_name")
          {
            groupName = iter->second;
          }
        }

        for(TiXmlNode *pKeyNode = pGroupNode->FirstChild(); pKeyNode != NULL; pKeyNode = pGroupNode->IterateChildren(pKeyNode))
        {
          if(pKeyNode && pKeyNode->Type() == TiXmlNode::TINYXML_ELEMENT && pKeyNode->ValueStr() == "setting")
          {
            ATTRIBUTES_LIST settingAttributesList;
            if(getAttributesAsList(pKeyNode->ToElement(), settingAttributesList) == 2)
            {
              string key = "";
              ISettingsElement::SettingsTypes type = ISettingsElement::UNKNOWN_SETTING;
              string value = "";
              for(ATTRIBUTES_LIST::iterator iter = settingAttributesList.begin(); iter != settingAttributesList.end(); iter++)
              {
                if(iter->first == "key")
                {
                  key = iter->second;
                }
                else
                {
                  type = CSettingsHelpers::TranslateTypeStrToEnum(iter->first);
                  value = iter->second;
                }
              }

              ISettingsElement *setting = find_Setting(mainCategory, subCategory, groupName, key);
              if(setting && setting->get_Type() == type)
              {
                switch(type)
                  {
                    case ISettingsElement::STRING_SETTING:
                      STRING_SETTINGS(setting)->set_Setting(value);
                    break;

                    case ISettingsElement::UNSIGNED_INT_SETTING:
                      {
                        unsigned int val = stringToVal<unsigned int>(value);
                        UNSIGNED_INT_SETTINGS(setting)->set_Setting(val);
                      }
                    break;

                    case ISettingsElement::INT_SETTING:
                      {
                        int val = stringToVal<int>(value);
                        INT_SETTINGS(setting)->set_Setting(val);
                      }
                    break;

                    case ISettingsElement::FLOAT_SETTING:
                      {
                        float val = stringToVal<float>(value);
                        FLOAT_SETTINGS(setting)->set_Setting(val);
                      }
                    break;

                    case ISettingsElement::DOUBLE_SETTING:
                      {
                        double val = stringToVal<double>(value);
                        DOUBLE_SETTINGS(setting)->set_Setting(val);
                      }
                    break;

                    case ISettingsElement::BOOL_SETTING:
                      if(value == "true" || value == "TRUE" || value == "True")
                      {
                        bool val = true;
                        BOOL_SETTINGS(setting)->set_Setting(val);
                      }
                      else if(value == "false" || value == "FALSE" || value == "False")
                      {
                        bool val = false;
                        BOOL_SETTINGS(setting)->set_Setting(val);
                      }
                      else
                      {
                        KODI->Log(LOG_ERROR, "CSettingsManager: Failed reading bool setting");
                      }
                    break;

                    default:
                      KODI->Log(LOG_ERROR, "CSettingsManager: Unknown settings type!");
                    break;
                  }
              }
              else
              {
                KODI->Log(LOG_ERROR, "CSettingsManager: Read settings element does not match the created settings element type!");
              }
            }
          }
        }
      }
    }
  }
}

bool CSettingsManager::add_Setting( string MainCategory, string SubCategory,
                                    string GroupName, string Key,
                                    ISettingsElement::SettingsTypes Type, void *Value)
{
  if(!Value)
  {
    KODI->Log(LOG_ERROR, "CSettingsManager: Invalid input for %s", __FUNCTION__);
    return false;
  }

  string settingsStr = MainCategory + SETTINGS_SEPERATOR_STR + SubCategory + SETTINGS_SEPERATOR_STR + GroupName;
  SettingsMap::iterator mapIter = m_Settings.find(settingsStr);
  if(mapIter != m_Settings.end())
  { // first we have to search, if the settings element is present in the founded Main- and Subcategory
    CSettingsList::iterator settingsIter = mapIter->second.begin();
    while(settingsIter != mapIter->second.end() && (*settingsIter)->get_Key() != Key)
    {
      settingsIter++;
    }

    if(settingsIter != mapIter->second.end() && (*settingsIter)->get_Key() == Key && Type == (*settingsIter)->get_Type())
    { // if the Type and Key are the same, we override the current setting with the new value
      return SetNewElementValue(*settingsIter, Value);
    }
  }

  // No element with the requested Main- and Subcategory and Type exists
  // so we create a new one
  ISettingsElement *settingsElement = CSettingsManager::CreateElement(Key, Type, Value);
  if(!settingsElement)
  {
    KODI->Log(LOG_ERROR, "CSettingsManager: Couldn't create settings element!");
    return false;
  }

  if(mapIter != m_Settings.end())
  {
    mapIter->second.push_back(settingsElement);
  }
  else
  {
    CSettingsList settingsList;
    settingsList.push_back(settingsElement);
    m_Settings[settingsStr] = settingsList;
  }

  return true;
}

ISettingsElement *CSettingsManager::CreateElement(string Key, ISettingsElement::SettingsTypes Type, void *Value)
{
  if(!Value)
  {
    KODI->Log(LOG_ERROR, "CSettingsManager: Invalid input for %s", __FUNCTION__);
    return NULL;
  }

  ISettingsElement *element = NULL;
  switch(Type)
  {
    case ISettingsElement::STRING_SETTING:
    {
      string *pVal = static_cast<string*>(Value);
      CStringSetting *p = new CStringSetting(*pVal, Key, Type);

      if(pVal && p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
      else
      {
        if(p)
        {
          delete p;
          p = NULL;
        }
      }
    }
    break;

    case ISettingsElement::UNSIGNED_INT_SETTING:
    {
      unsigned int *pVal = (unsigned int*)(Value);
      CUnsignedIntSetting *p = new CUnsignedIntSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    case ISettingsElement::INT_SETTING:
    {
      int *pVal = (int*)(Value);
      CIntSetting *p = new CIntSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    case ISettingsElement::FLOAT_SETTING:
    {
      float *pVal = (float*)(Value);
      CFloatSetting *p = new CFloatSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    case ISettingsElement::DOUBLE_SETTING:
    {
      double *pVal = (double*)(Value);
      CDoubleSetting *p = new CDoubleSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    case ISettingsElement::BOOL_SETTING:
    {
      bool *pVal = (bool*)(Value);
      CBoolSetting *p = new CBoolSetting(*pVal, Key, Type);

      if(p)
      {
        element = dynamic_cast<ISettingsElement*>(p);
      }
    }
    break;

    default:
      element = NULL;
    break;
  }

  return element;
}

bool CSettingsManager::SetNewElementValue(ISettingsElement *Element, void *Value)
{
  if(!Element || !Value)
  {
    KODI->Log(LOG_ERROR, "CSettingsManager: Invalid input for %s", __FUNCTION__);
    return false;
  }

  switch(Element->get_Type())
  {
    case ISettingsElement::STRING_SETTING:
      STRING_SETTINGS(Element)->set_Setting(*static_cast<string*>(Value));
    break;

    case ISettingsElement::UNSIGNED_INT_SETTING:
      UNSIGNED_INT_SETTINGS(Element)->set_Setting(*((unsigned int*)Value));
    break;

    case ISettingsElement::INT_SETTING:
      INT_SETTINGS(Element)->set_Setting(*((int*)Value));
    break;

    case ISettingsElement::FLOAT_SETTING:
      FLOAT_SETTINGS(Element)->set_Setting(*((float*)Value));
    break;

    case ISettingsElement::DOUBLE_SETTING:
      DOUBLE_SETTINGS(Element)->set_Setting(*((double*)Value));
    break;

    case ISettingsElement::BOOL_SETTING:
      BOOL_SETTINGS(Element)->set_Setting(*((bool*)Value));
    break;

    default:
      return false;
    break;
  }

  return true;
}

void CSettingsManager::destroy_Setting(string MainCategory, string SubCategory, string GroupName, string Key)
{
  string settingsStr = MainCategory + SETTINGS_SEPERATOR_STR + SubCategory + SETTINGS_SEPERATOR_STR + GroupName;
  SettingsMap::iterator mapIter = m_Settings.find(settingsStr);
  if(mapIter != m_Settings.end())
  {
    CSettingsList::iterator listIter = mapIter->second.begin();

    // search for the correct key
    while(listIter != mapIter->second.end() && (*listIter)->get_Key() != Key)
    {
      listIter++;
    }

    // if the key was found, delete this setting
    if(listIter != mapIter->second.end() && (*listIter)->get_Key() != Key)
    {
      if(*listIter)
      {
        delete *listIter;
        *listIter = NULL;
      }

      // erase this setting from the list
      mapIter->second.erase(listIter);
    }

    // check if there are other settings, else delete this Main- and Subcategory
    if(mapIter->second.size() <= 0)
    {
      m_Settings.erase(mapIter);
    }

    if(listIter == mapIter->second.end())
    {
      KODI->Log(LOG_NOTICE, "CSettingsManager: Requested settings element \"%s\" in method \"%s\" not found!", settingsStr.c_str(), __FUNCTION__);
    }
  }
  else
  {
    KODI->Log(LOG_NOTICE, "CSettingsManager: Requested settings element \"%s\" in method \"%s\" not found!", settingsStr.c_str(), __FUNCTION__);
  }
}

ISettingsElement *CSettingsManager::find_Setting(string MainCategory, string SubCategory, string GroupName, string Key)
{
  string settingsStr = MainCategory + SETTINGS_SEPERATOR_STR + SubCategory + SETTINGS_SEPERATOR_STR + GroupName;
  SettingsMap::iterator mapIter = m_Settings.end();
  if(m_Settings.size() > 0)
  {
    mapIter = m_Settings.find(settingsStr);
  }
  if(mapIter != m_Settings.end())
  {
    CSettingsList::iterator listIter = mapIter->second.begin();

    // search for the correct key
    while(listIter != mapIter->second.end() && (*listIter)->get_Key() != Key)
    {
      listIter++;
    }

    if(listIter != mapIter->second.end() && (*listIter)->get_Key() == Key)
    {
      return *listIter;
    }
  }

  KODI->Log(LOG_NOTICE, "CSettingsManager: Couldn't find requested settings element \"%s\" in method \"%s\" not found!", settingsStr.c_str(), __FUNCTION__);
  return NULL;
}


// Helper functions for XML-Files
int getAttributesAsList(TiXmlElement* pElement, ATTRIBUTES_LIST &AttributesList)
{
  if ( !pElement ) return -1;

  for(TiXmlAttribute *pAttrib = pElement->FirstAttribute(); pAttrib != NULL; pAttrib = pAttrib->Next())
  {
    AttributesList.push_back(ATTRIBUTE_PAIR(pAttrib->Name(), pAttrib->Value()));
  }

  return AttributesList.size();
}
