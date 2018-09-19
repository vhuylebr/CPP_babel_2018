#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"
#include "../include/PortAudio.hpp"
#include "../include/VoIPManager.hpp"

int	main()
{
	Audio::PortAudio	portA;
	Audio::OutputParams	pOutput;
	Audio::VoIPManager  voIP;
	PaStream*           stream;
	PaError             err = paNoError;
	paTestData          data;
	int                 i;

	voIP.startRecordInput(data, err);
	err = portA.OpenStream(&stream,
			   &pInput.getIParams(),
			   NULL,
			   SAMPLE_RATE,
			   FRAMES_PER_BUFFER,
			   paClipOff,
			   recordCallback,
			   &data);
	if (err != paNoError) voIP.stopStream(data, err);
	err = portA.StartStream(stream);
	if (err != paNoError) voIP.stopStream(data, err);
	printf("\n=== Now recording!! Please speak into the microphone. ===\n"); fflush(stdout);
	while ((err = portA.IsStreamActive(stream)) == 1) {
	 printf("index = %d\n", data.frameIndex ); fflush(stdout);
	}
	if(err < 0) voIP.stopStream(data, err);
	err = portA.CloseStream( stream );
	if(err != paNoError) voIP.stopStream(data, err);
	voIP.getUtilsData().max = 0;
	voIP.getUtilsData().average = 0.0;
	for(i=0 ; i < voIP.getUtilsData().numSamples ; i++) {
		voIP.getUtilsData().val = data.recordedSamples[i];
		if(voIP.getUtilsData().val < 0) voIP.getUtilsData().val = -voIP.getUtilsData().val; /* ABS */
		if(voIP.getUtilsData().val > voIP.getUtilsData().max) {
			voIP.getUtilsData().max = voIP.getUtilsData().val;
		 }
		voIP.getUtilsData().average += voIP.getUtilsData().val;
	 }
	voIP.getUtilsData().average = voIP.getUtilsData().average / (double)voIP.getUtilsData().numSamples;
	printf("sample max amplitude = "PRINTF_S_FORMAT"\n", voIP.getUtilsData().max );
	printf("sample average = %lf\n", voIP.getUtilsData().average );
 
	data.frameIndex = 0; 
	voIP.initOutput(pOutput);

/////////////////////////////////////////////////:
/////////////////////////////////////////////////:
/////////////////////////////////////////////////:


	printf("\n=== Now playing back. ===\n"); fflush(stdout);
	err = portA.OpenStream(&stream, NULL, &pOutput.getOParams(),
			   SAMPLE_RATE,
			   FRAMES_PER_BUFFER,
			   paClipOff,
			   playCallback,
			   &data );
	if(err != paNoError) voIP.stopStream(data, err);
	if(stream) {
		 err = portA.StartStream( stream );
		 if( err != paNoError ) voIP.stopStream(data, err);
		 printf("Waiting for playback to finish.\n"); fflush(stdout);
		 while( ( err = portA.IsStreamActive( stream ) ) == 1 ) portA.Sleep(100);
		 if( err < 0 ) voIP.stopStream(data, err);
		 err = portA.CloseStream( stream );
		 if( err != paNoError ) voIP.stopStream(data, err);
		 printf("Done.\n"); fflush(stdout);
	 }
}
