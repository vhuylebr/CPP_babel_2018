//
// EPITECH PROJECT, 2018
// CPP_babel_2018
// File description:
// InputParams FILE CPP 
//

#include "../include/PortAudio.hpp"

void    Audio::InputParams::setIParams(PaStreamParameters &input)
{
    input = input;
}

void    Audio::InputParams::setIDeviceParams(PaStreamParameters &input, PaDeviceIndex device)
{
    input.device = device;
}

void    Audio::InputParams::setIChannelParams(PaStreamParameters &input, int channelCount)
{
    input.channelCount = channelCount;
}

void    Audio::InputParams::setISampleParams(PaStreamParameters &input, PaSampleFormat sampleFormat)
{
    input.sampleFormat = sampleFormat;
}

void    Audio::InputParams::setILatencyParams(PaStreamParameters &input, PaTime suggestedLatency)
{
    input.suggestedLatency = suggestedLatency;
}

void    Audio::InputParams::setIHostParams(PaStreamParameters &input, void *hostApiSpecificStreamInfo)
{
    input.hostApiSpecificStreamInfo = hostApiSpecificStreamInfo;
}

PaDeviceIndex   &Audio::InputParams::getIDeviceParams()
{
    return iParams.device;
}

PaStreamParameters    &Audio::InputParams::getIParams()
{
        return iParams;
}
