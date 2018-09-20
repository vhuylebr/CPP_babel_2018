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

	if ((stream = voIP.startRecordInput(data)) == NULL) {
		std::cout << "An error occured" << std::endl;
		exit(84);
	} 
	if ((stream = voIP.playRecordOutput(data)) == NULL) {
		std::cout << "An error occured" << std::endl;
		exit(84);
	}

	err = portA.OpenStream(&stream, NULL, &pOutput.getOParams(),
			   SAMPLE_RATE,
			   FRAMES_PER_BUFFER,
			   paClipOff,
			   playCallback,
			   &data);
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
