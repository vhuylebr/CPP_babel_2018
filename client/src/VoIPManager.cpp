//
// EPITECH PROJECT, 2018
// CPP_babel_2018
// File description:
// VoIPManager FILE CPP
//

#include <iostream>
#include <stdlib.h>
#include "../include/VoIPManager.hpp"

// paTestData    Audio::VoIPManager::initRecord(paTestData &data, utilsData &utilsD)
// {
//     data.maxFrameIndex = utilsD.totalFrames = NUM_SECONDS * SAMPLE_RATE;
//     data.frameIndex = 0;
//     utilsD.numSamples = utilsD.totalFrames * NUM_CHANNELS;
//     utilsD.numBytes =  utilsD.numSamples * sizeof(SAMPLE);
//     data.recordedSamples = (SAMPLE *) malloc(utilsD.numBytes);
//     return data;
// }

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
                    SAMPLE_RATE, FRAMES_PER_BUFFER, paNoFlag,
                    NULL, NULL);
    if (err != paNoError) {
        return NULL;
    }
    return stream;
}

/*
PaError Audio::VoIPManager::RecordingUser(PaStream *stream, paTestData &data)
{
    PaError err = paNoError;

    printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);
	while ((err =  _portA.IsStreamActive(stream)) == 1) {
	    printf("index = %d\n", data.frameIndex ); fflush(stdout);
	}
    if (err < 0) {
        stopStream(data, _err);
    }
    return err;
}


PaStream    *Audio::VoIPManager::openStreamInput(PaStream *stream, paTestData &data)
{
    PaError err = paNoError;
    err = _portA.OpenStream(&stream, &_pInput.getIParams(), NULL,
                    SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff,
                    recordCallback, &data);
    if (err != paNoError) {
        return NULL;
    }
    return stream;
}


void    Audio::VoIPManager::initDataSamples(paTestData &data)
{
    int i;
    for(i = 0 ; i < getUtilsData().numSamples; i++) {
		data.recordedSamples[i] = 0;
	}
}*/
// @Return NULL (After using stopStream())
PaStream *Audio::VoIPManager::startRecordInput(void)
{
    _err = paNoError;
    // data = initRecord(data, getUtilsData());

    // if(data.recordedSamples == NULL)
    //     stopStream(data, _err);
    // initDataSamples(data);
    if ((_err = _portA.Initialize()) != paNoError)
        stopStream(_err);
    initInput(_pInput);
    initOutput(_pOutput);
    int numBytes = FRAMES_PER_BUFFER * NUM_CHANNELS * SAMPLE_SIZE ;
    char *sampleBlock;
    sampleBlock = (char *) malloc( numBytes );
    if ((_stream = openStreamRecord(_stream)) == NULL)
        stopStream(_err);
    if ((_err = _portA.StartStream(_stream)) != paNoError)
        stopStream(_err);
     for( int i=0; i<(NUM_SECONDS*SAMPLE_RATE)/FRAMES_PER_BUFFER; ++i )
    {
        Pa_WriteStream(_stream, sampleBlock, FRAMES_PER_BUFFER );
        Pa_ReadStream(_stream, sampleBlock, FRAMES_PER_BUFFER );
    }
    stopStream(_err);
    // if ((_err = RecordingUser(_stream, data)) != paNoError)
    // //     stopStream(data, _err);
    // if ((_err = _portA.CloseStream(_stream)) != paNoError)
    // //     stopStream(data, _err);
    // data.frameIndex = 0;
    return _stream;
}

// PaStream *Audio::VoIPManager::playRecordOutput(paTestData &data)
// {
//     _stream = nullptr;
//     _err = paNoError;
//     initOutput(_pOutput);
//     _err = _portA.OpenStream(&_stream, NULL, &_pOutput.getOParams(),
// 			   SAMPLE_RATE,
// 			   FRAMES_PER_BUFFER,
// 			   paClipOff,
// 			   playCallback,
// 			   &data);
// 	if(_err != paNoError) stopStream(data, _err);
// 	if (_stream) {
// 		 _err = _portA.StartStream( _stream );
// 		 if( _err != paNoError ) stopStream(data, _err);
// 		 printf("Waiting for playback to finish.\n"); fflush(stdout);
// 		 while( ( _err = _portA.IsStreamActive( _stream ) ) == 1 ) _portA.Sleep(100);
// 		 if( _err < 0 ) stopStream(data, _err);
// 		 _err = _portA.CloseStream( _stream );
// 		 if( _err != paNoError ) stopStream(data, _err);
// 		 printf("Done.\n"); fflush(stdout);
// 	 }
//      return _stream;
// }

int Audio::VoIPManager::stopStream(PaError err)
{
    _portA.Terminate();
    // if (data.recordedSamples != NULL)
    //     free(data.recordedSamples);
    if (err != paNoError) {
        fprintf(stderr, "An error occured while using the portaudio stream\n");
		fprintf(stderr, "Error message: %s\n", _portA.GetErrorText(err));
    }
	fprintf(stderr, "Error number: %d\n", err);
    return -1;
}