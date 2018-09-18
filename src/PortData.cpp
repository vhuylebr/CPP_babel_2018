//
// EPITECH PROJECT, 2018
// CPP_babel_2018
// File description:
// PortData FILE CPP 
//

#include "../include/PortAudio.hpp"

void    Audio::PortData::setData(paTestData &data)
{
    data = data;
}

void    Audio::PortData::setMaxFrameData(paTestData &data, int maxFrameIndex)
{
    data.maxFrameIndex = maxFrameIndex;
}

void    Audio::PortData::setFrameData(paTestData &data, int frameIndex)
{
    data.frameIndex = frameIndex;
}

void    Audio::PortData::setRecordedData(paTestData &data, SAMPLE *recordedSamples)
{
    data.recordedSamples = recordedSamples;
}

int    Audio::PortData::getFrameIndex()
{
    return data.frameIndex;
}

SAMPLE  *Audio::PortData::getRecordedData()
{
    return data.recordedSamples;
}

paTestData    Audio::PortData::getData()
{
    return data;
}

