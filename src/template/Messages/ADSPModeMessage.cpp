/*
 *      Copyright (C) 2014-2015 Team KODI
 *      http://kodi.tv
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 */



#include "template/include/client.h"
#include "template/include/ADSPModeMessage.h"
#include "template/AddonExceptions/TAddonException.h"

CADSPModeMessage::CADSPModeMessage()
{
  m_ProcessingModeId = 0;
  m_StreamId = AE_DSP_STREAM_MAX_STREAMS;
  m_MessageType = 0;
  m_AudioChannel = AE_DSP_CH_MAX;
  m_MessageDataSize = 0;
  m_MessageData = NULL;
}

CADSPModeMessage::~CADSPModeMessage()
{
  if(m_MessageData)
  {
    delete m_MessageData;
    m_MessageData = NULL;
  }
}

unsigned int CADSPModeMessage::get_ProcessingModeId()
{
  return m_ProcessingModeId;
}

AE_DSP_ERROR CADSPModeMessage::set_ProcessingModeId(unsigned int ModeId)
{
  if(!ModeId)
  {
    return AE_DSP_ERROR_INVALID_PARAMETERS;
  }
  m_ProcessingModeId = ModeId;

  return AE_DSP_ERROR_NO_ERROR;
}

unsigned int CADSPModeMessage::get_StreamId()
{
  return m_StreamId;
}

AE_DSP_ERROR CADSPModeMessage::set_StreamId(unsigned int StreamId)
{
  if(StreamId >= AE_DSP_STREAM_MAX_STREAMS)
  {
    return AE_DSP_ERROR_INVALID_PARAMETERS;
  }
  m_StreamId = StreamId;

  return AE_DSP_ERROR_NO_ERROR;
}

unsigned int CADSPModeMessage::get_MessageType()
{
  return m_MessageType;
}

AE_DSP_ERROR CADSPModeMessage::set_MessageType(unsigned int Type)
{
  if(!Type)
  {
    return AE_DSP_ERROR_INVALID_PARAMETERS;
  }
  m_MessageType = Type;

  return AE_DSP_ERROR_NO_ERROR;
}

AE_DSP_CHANNEL CADSPModeMessage::get_AudioChannel()
{
  return m_AudioChannel;
}

AE_DSP_ERROR CADSPModeMessage::set_AudioChannel(AE_DSP_CHANNEL AudioChannel)
{
  if(AudioChannel <= AE_DSP_CH_INVALID || AudioChannel >= AE_DSP_CH_MAX)
  {
    return AE_DSP_ERROR_INVALID_PARAMETERS;
  }
  m_AudioChannel = AudioChannel;

  return AE_DSP_ERROR_NO_ERROR;
}

AE_DSP_ERROR CADSPModeMessage::get_MessageData(void *Data)
{
  if(!Data)
  {
    return AE_DSP_ERROR_INVALID_PARAMETERS;
  }

  if(!m_MessageData || !m_MessageDataSize)
  {
    KODI->Log(ADDON::LOG_ERROR, "%s line %i: Invalid internal MessageData pointer! Not enough free dynamic memory available?", __func__, __LINE__);
    return AE_DSP_ERROR_FAILED;
  }

  memcpy(Data, m_MessageData, m_MessageDataSize);

  return AE_DSP_ERROR_NO_ERROR;
}

AE_DSP_ERROR  CADSPModeMessage::get_MessageDataPtr(void *&Ptr)
{
  if (!m_MessageData || !m_MessageDataSize)
  {
    KODI->Log(ADDON::LOG_ERROR, "%s line %i: Invalid internal MessageData pointer! Not enough free dynamic memory available?", __func__, __LINE__);
    return AE_DSP_ERROR_FAILED;
  }

  Ptr = (void*)m_MessageData;

  return AE_DSP_ERROR_NO_ERROR;
}

AE_DSP_ERROR CADSPModeMessage::set_MessageData(void *Data, size_t DataSize)
{
  if(!Data)
  {
    return AE_DSP_ERROR_INVALID_PARAMETERS;
  }

  if(DataSize > 0)
  {
    if(DataSize > m_MessageDataSize)
    {
      if(m_MessageData)
      {
        delete [] m_MessageData;
      }

      m_MessageDataSize = DataSize;
      m_MessageData = new uint8_t[m_MessageDataSize];
    }

    if(!m_MessageData)
    {
      KODI->Log(ADDON::LOG_ERROR, "%s line %i: Invalid internal MessageData pointer! Not enough free dynamic memory available?", __func__, __LINE__);
      m_MessageDataSize = 0;
      return AE_DSP_ERROR_FAILED;
    }
  }

  memcpy(m_MessageData, Data, m_MessageDataSize);
  return AE_DSP_ERROR_NO_ERROR;
}

size_t CADSPModeMessage::get_MessageDataSize()
{
  return m_MessageDataSize;
}

AE_DSP_ERROR CADSPModeMessage::set_MessageDataSize(size_t DataSize)
{
  if(DataSize <= 0)
  {
    return AE_DSP_ERROR_INVALID_PARAMETERS;
  }

  if(m_MessageDataSize == DataSize)
  { // delete old data
    memset(m_MessageData, 0, m_MessageDataSize);
    return AE_DSP_ERROR_NO_ERROR;
  }

  if(m_MessageData)
  {
    delete [] m_MessageData;
    m_MessageData = NULL;
  }

  m_MessageDataSize = DataSize;
  m_MessageData = new uint8_t[m_MessageDataSize];
  if(!m_MessageData)
  {
    KODI->Log(ADDON::LOG_ERROR, "%s line %i: Invalid internal MessageData pointer! Not enough free dynamic memory available?", __func__, __LINE__);
    return AE_DSP_ERROR_FAILED;
  }
  memset(m_MessageData, 0, m_MessageDataSize);

  return AE_DSP_ERROR_NO_ERROR;
}
