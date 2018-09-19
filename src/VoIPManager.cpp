//
// EPITECH PROJECT, 2018
// CPP_babel_2018
// File description:
// VoIPManager FILE CPP 
//

#include <iostream>
#include <stdlib.h>
#include "../include/VoIPManager.hpp"

paTestData    Audio::VoIPManager::initRecord(paTestData &data, utilsData &utilsD)
{
    data.maxFrameIndex = utilsD.totalFrames = NUM_SECONDS * SAMPLE_RATE;
    data.frameIndex = 0;
    utilsD.numSamples = utilsD.totalFrames * NUM_CHANNELS;
    utilsD.numBytes =  utilsD.numSamples * sizeof(SAMPLE);
    data.recordedSamples = (SAMPLE *) malloc(utilsD.numBytes);
    return data;
}

utilsData   &Audio::VoIPManager::getUtilsData(void)
{
    return utilsD;
}

void    Audio::VoIPManager::initInput(Audio::InputParams &pInput)
{
	pInput.setIDeviceParams(pInput.getIParams(), _portA.GetDefaultInputDevice());
	pInput.setIChannelParams(pInput.getIParams(), NUM_CHANNELS);
	pInput.setISampleParams(pInput.getIParams(), PA_SAMPLE_TYPE);
	pInput.setILatencyParams(pInput.getIParams(), 
	_portA.GetDeviceInfo(pInput.getIDeviceParams())->defaultLowInputLatency);
	pInput.setIHostParams(pInput.getIParams(), NULL);
}

void    Audio::VoIPManager::initOutput(Audio::OutputParams &pOutput)
{
	pOutput.setODeviceParams(pOutput.getOParams(), _portA.GetDefaultOutputDevice());
	pOutput.setOChannelParams(pOutput.getOParams(), NUM_CHANNELS);
	pOutput.setOSampleParams(pOutput.getOParams(), PA_SAMPLE_TYPE);
	pOutput.setOLatencyParams(pOutput.getOParams(), 
	_portA.GetDeviceInfo(pOutput.getODeviceParams())->defaultLowInputLatency);
	pOutput.setOHostParams(pOutput.getOParams(), NULL);
}

void    Audio::VoIPManager::openStreamInput(PaStream *stream, paTestData data)
{
    _portA.OpenStream(&stream, &_pInput.getIParams(), NULL, 
                    SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, 
                    recordCallback, &data);
}

void    Audio::VoIPManager::initDataSamples(paTestData &data)
{
    int i;
    for(i = 0 ; i < getUtilsData().numSamples; i++) {
		data.recordedSamples[i] = 0;
	}
}

PaError Audio::VoIPManager::startRecordInput(paTestData &data, PaError &err)
{
    data = initRecord(data, getUtilsData());
    if(data.recordedSamples == NULL)
        stopStream(data, err);
    initDataSamples(data);
    if ((err = _portA.Initialize()) != paNoError)
        stopStream(data, err);
    initInput(_pInput);
}

int Audio::VoIPManager::stopStream(paTestData &data, PaError err)
{
    Audio::PortAudio    portA;

    portA.Terminate();
    if (data.recordedSamples != NULL)
        free(data.recordedSamples);
    if (err != paNoError) {
        fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error message: %s\n", portA.GetErrorText(err));
    }
	fprintf(stderr, "Error number: %d\n", err);
    return -1;
}