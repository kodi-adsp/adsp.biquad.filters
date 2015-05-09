#include "include/ADSPProcessorHandle.h"
#include <string.h>

CADSPProcessorHandle::CADSPProcessorHandle(const AE_DSP_SETTINGS *Settings, const AE_DSP_STREAM_PROPERTIES *pProperties)
{
	memcpy(&m_StreamSettings, Settings, sizeof(AE_DSP_SETTINGS));
	memcpy(&m_StreamProperties, pProperties, sizeof(AE_DSP_SETTINGS));
}

CADSPProcessorHandle::~CADSPProcessorHandle()
{
}

AE_DSP_ERROR CADSPProcessorHandle::StreamInitialize(const AE_DSP_SETTINGS *Settings)
{
	memcpy(&m_StreamSettings, Settings, sizeof(AE_DSP_SETTINGS));

	return AE_DSP_ERROR_NO_ERROR;
}

float CADSPProcessorHandle::OutputResampleGetDelay()
{
	return (float)m_StreamSettings.iInFrames / (float)m_StreamSettings.iInSamplerate;
}

float CADSPProcessorHandle::PostProcessGetDelay(unsigned int Mode_id)
{
	return (float)m_StreamSettings.iInFrames / (float)m_StreamSettings.iInSamplerate;
}

float CADSPProcessorHandle::MasterProcessGetDelay()
{
	return (float)m_StreamSettings.iInFrames / (float)m_StreamSettings.iInSamplerate;
}

float CADSPProcessorHandle::PreProcessGetDelay(unsigned int Mode_id)
{
	return (float)m_StreamSettings.iInFrames / (float)m_StreamSettings.iInSamplerate;
}

float CADSPProcessorHandle::InputResampleGetDelay()
{
	return (float)m_StreamSettings.iInFrames / (float)m_StreamSettings.iInSamplerate;
}
