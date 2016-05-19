#pragma once
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



#include <kodi_adsp_types.h>

// typedefs
typedef unsigned char uint8_t;

class CADSPModeMessage
{
  public:
    CADSPModeMessage();
    ~CADSPModeMessage();

    // ToDo: Description
    unsigned int  get_ProcessingModeId();
    // ToDo: Description
    AE_DSP_ERROR  set_ProcessingModeId(unsigned int ModeId);

    // ToDo: Description
    unsigned int  get_StreamId();
    // Sets the stream id of the message
    // if StreamId is AE_DSP_STREAM_MAX_STREAMS then the message 
    // will be sent to all active audio streams
    AE_DSP_ERROR  set_StreamId(unsigned int StreamId);

    // ToDo: Description
    unsigned int  get_MessageType();
    // ToDo: Description
    AE_DSP_ERROR  set_MessageType(unsigned int Type);

    // ToDo: Description
    AE_DSP_CHANNEL  get_AudioChannel();
    // Sets the audio channel. If AudioChannel is AE_DSP_CH_MAX then this message
    // will be sent to all active audio channels.
    AE_DSP_ERROR    set_AudioChannel(AE_DSP_CHANNEL AudioChannel);

    // ToDo: Description
    AE_DSP_ERROR  get_MessageData(void *Data);
    // ToDo: Description
    AE_DSP_ERROR  get_MessageDataPtr(void *&Ptr);
    // ToDo: Description
    AE_DSP_ERROR  set_MessageData(void *Data, size_t DataSize=0);

    // ToDo: Description
    size_t        get_MessageDataSize();
    // ToDo: Description
    AE_DSP_ERROR  set_MessageDataSize(size_t DataSize);

  private:
    unsigned int    m_ProcessingModeId;
    unsigned int    m_StreamId;
    unsigned int    m_MessageType;
    AE_DSP_CHANNEL  m_AudioChannel;
    size_t          m_MessageDataSize;
    uint8_t        *m_MessageData;
};