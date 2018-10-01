//
// EPITECH PROJECT, 2018
// CPP_babel_2018
// File description:
// VoIPManager FILE CPP
//

#include <iostream>
#include <stdlib.h>
#include "../include/VoIPManager.hpp"

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
	_portA.GetDeviceInfo(pInput.getIDeviceParams())->defaultHighInputLatency);
	pInput.setIHostParams(pInput.getIParams(), NULL);
}

void    Audio::VoIPManager::initOutput(Audio::OutputParams &pOutput)
{
	pOutput.setODeviceParams(pOutput.getOParams(), _portA.GetDefaultOutputDevice());
	pOutput.setOChannelParams(pOutput.getOParams(), NUM_CHANNELS);
	pOutput.setOSampleParams(pOutput.getOParams(), PA_SAMPLE_TYPE);
	pOutput.setOLatencyParams(pOutput.getOParams(),
	_portA.GetDeviceInfo(pOutput.getODeviceParams())->defaultHighOutputLatency);
	pOutput.setOHostParams(pOutput.getOParams(), NULL);
}

PaStream    *Audio::VoIPManager::openStreamRecord(PaStream *stream)
{
    PaError err = paNoError;
    err = _portA.OpenStream(&stream, &_pInput.getIParams(), &_pOutput.getOParams(),
                    SAMPLE_RATE, paFramesPerBufferUnspecified, paNoFlag,
                    NULL, NULL);
    if (err != paNoError) {
        return NULL;
    }
    return stream;
}

PaStream *Audio::VoIPManager::startRecordInput(void)
{
    _err = paNoError;
    if ((_err = _portA.Initialize()) != paNoError)
        stopStream(_err);
    initInput(_pInput);
    initOutput(_pOutput);
    float buffAudio[480];
    if ((_stream = openStreamRecord(_stream)) == NULL)
        stopStream(_err);
    if ((_err = _portA.StartStream(_stream)) != paNoError)
        stopStream(_err);
    while(1) {
        Pa_WriteStream(_stream, &buffAudio, 480);
        Pa_ReadStream(_stream, &buffAudio, 480);
    }
    stopStream(_err);
    return _stream;
}

int Audio::VoIPManager::stopStream(PaError err)
{
    _portA.Terminate();
    if (err != paNoError) {
        fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error message: %s\n", _portA.GetErrorText(err));
    }
	fprintf(stderr, "Error number: %d\n", err);
    return -1;
}