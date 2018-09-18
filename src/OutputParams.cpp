//
// EPITECH PROJECT, 2018
// CPP_babel_2018
// File description:
// InputParams FILE CPP 
//

#include "../include/PortAudio.hpp"

void    Audio::OutputParams::setOParams(PaStreamParameters &output)
{
    output = output;
}

void    Audio::OutputParams::setODeviceParams(PaStreamParameters &output, PaDeviceIndex device)
{
    output.device = device;
}

void    Audio::OutputParams::setOChannelParams(PaStreamParameters &output, int channelCount)
{
    output.channelCount = channelCount;
}

void    Audio::OutputParams::setOSampleParams(PaStreamParameters &output, PaSampleFormat sampleFormat)
{
    output.sampleFormat = sampleFormat;
}

void    Audio::OutputParams::setOLatencyParams(PaStreamParameters &output, PaTime suggestedLatency)
{
    output.suggestedLatency = suggestedLatency;
}

void    Audio::OutputParams::setOHostParams(PaStreamParameters &output, void *hostApiSpecificStreamInfo)
{
    output.hostApiSpecificStreamInfo = hostApiSpecificStreamInfo;
}

PaStreamParameters    Audio::OutputParams::getOParams()
{
    return oParams;
}