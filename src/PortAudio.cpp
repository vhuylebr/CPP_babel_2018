//
// EPITECH PROJECT, 2018
// CPP_babel_2018
// File description:
// PortAudio FILE CPP 
//

#include "../include/PortAudio.hpp"

Audio::PortAudio::PortAudio()
{

}

Audio::PortAudio::~PortAudio(){}

PaError Audio::PortAudio::StartStream(PaStream *stream)
{
    return Pa_StartStream(stream);
}

PaError Audio::PortAudio::OpenStream(PaStream **stream, const PaStreamParameters *inputParameters, const PaStreamParameters *outputParameters, 
									double sampleRate, unsigned long framesPerBuffer, PaStreamFlags streamFlags, PaStreamCallback *streamCallback, void *userData)
{
    return Pa_OpenStream(stream, inputParameters, outputParameters, sampleRate, framesPerBuffer, streamFlags, streamCallback, userData);
}

PaError Audio::PortAudio::IsStreamActive(PaStream *stream)
{
    return Pa_IsStreamActive(stream);
}

PaError Audio::PortAudio::CloseStream(PaStream *stream)
{
    return Pa_CloseStream(stream);
}

PaError Audio::PortAudio::Terminate()
{
    return Pa_Terminate();
}

PaError Audio::PortAudio::Initialize()
{
    std::cout << "Initiliazing" << std::endl;
    return Pa_Initialize();
}

void    Audio::PortAudio::Sleep(long msec)
{
    return Pa_Sleep(msec);
}

const char *Audio::PortAudio::GetErrorText(PaError errorCode)
{
    return Pa_GetErrorText(errorCode);
}

const PaDeviceInfo *Audio::PortAudio::GetDeviceInfo(PaDeviceIndex device)
{
    return Pa_GetDeviceInfo(device);
}

PaDeviceIndex   Audio::PortAudio::GetDefaultInputDevice()
{
    return Pa_GetDefaultInputDevice();
}

PaDeviceIndex   Audio::PortAudio::GetDefaultOutputDevice()
{
    return Pa_GetDefaultOutputDevice();
}
