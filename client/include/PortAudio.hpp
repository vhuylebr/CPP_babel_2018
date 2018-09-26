//
// EPITECH PROJECT, 2018
// CPP_babel_2018
// File description:
// PortAudio FILE HPP
//

#ifndef PORTAUDIO_HPP_
	#define PORTAUDIO_HPP_
/*
** INCLUDE - PORTAUDIO UTILES 
*/
# include <iostream>
# include <stdio.h>
# include <stdlib.h>
# include "portaudio.h"

/*
** DEFINE - PORTAUDIO UTILES 
*/
# define SAMPLE_RATE (44100)
# define FRAMES_PER_BUFFER	(512)
# define SAMPLE_SIZE (4)
# define NUM_SECONDS     (15)
# define NUM_CHANNELS    (1)
# define DITHER_FLAG     (0) 
# define WRITE_TO_FILE   (0)
# define PA_SAMPLE_TYPE  paFloat32
# define SAMPLE_SILENCE  (0.0f)
# define PRINTF_S_FORMAT "%.8f"

/*
** STRUCT - PORTAUDIO UTILES 
*/
typedef float SAMPLE;
typedef struct
{
    int          frameIndex;  /* Index into sample array. */
    int          maxFrameIndex;
    SAMPLE      *recordedSamples;
}
paTestData;

namespace Audio
{
	class	OutputParams {
		public:
			void	setOParams(PaStreamParameters &ouput);
			void	setODeviceParams(PaStreamParameters &ouput, PaDeviceIndex device);
			void	setOChannelParams(PaStreamParameters &ouput, int channelCount);
			void	setOSampleParams(PaStreamParameters &ouput, PaSampleFormat sampleFormat);
			void	setOLatencyParams(PaStreamParameters &ouput, PaTime suggestedLatency);
			void	setOHostParams(PaStreamParameters &ouput, void *hostApiSpecificStreamInfo);
			PaDeviceIndex &getODeviceParams();
			PaStreamParameters	&getOParams();
		private:
			PaStreamParameters  oParams;
	};
	class	InputParams {
		public:
			void	setIParams(PaStreamParameters &input);
			void	setIDeviceParams(PaStreamParameters &input, PaDeviceIndex device);
			void	setIChannelParams(PaStreamParameters &input, int channelCount);
			void	setISampleParams(PaStreamParameters &input, PaSampleFormat sampleFormat);
			void	setILatencyParams(PaStreamParameters &input, PaTime suggestedLatency);
			void	setIHostParams(PaStreamParameters &input, void *hostApiSpecificStreamInfo);
			PaDeviceIndex &getIDeviceParams();	
			PaStreamParameters	&getIParams();
		private:
			PaStreamParameters  iParams;
	};
	class	PortAudio
	{
		public:
			PortAudio();
			~PortAudio();
			PaError StartStream(PaStream *stream);
			PaError OpenStream(PaStream **stream, const PaStreamParameters *inputParameters, const PaStreamParameters *outputParameters, 
									double sampleRate, unsigned long framesPerBuffer, PaStreamFlags streamFlags, PaStreamCallback *streamCallback, void *userData);
			PaError CloseStream(PaStream *stream);
			PaError IsStreamActive(PaStream *stream);
			const PaDeviceInfo *GetDeviceInfo(PaDeviceIndex device);
			PaError Initialize(void);
			PaError Terminate(void);
			const char *GetErrorText(PaError errorCode);
			PaDeviceIndex GetDefaultInputDevice(void);
			PaDeviceIndex GetDefaultOutputDevice(void);
			void Sleep(long msec);
	};
}

int	recordCallback(const void *, void *, unsigned long,
			   const PaStreamCallbackTimeInfo* timeInfo,
			   PaStreamCallbackFlags statusFlags,
			   void *userData);

int	playCallback(const void *, void *, unsigned long,
			   const PaStreamCallbackTimeInfo* timeInfo,
			   PaStreamCallbackFlags statusFlags,
			   void *userData);
			   

#endif /* PORTAUDIO_HPP_ */
