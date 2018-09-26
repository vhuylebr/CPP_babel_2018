//
// EPITECH PROJECT, 2018
// CPP_babel_2018
// File description:
// VoIPManager Header c++
//

#ifndef VOIPMANAGER_HPP_
	#define VOIPMANAGER_HPP_

# include "PortAudio.hpp"

typedef struct
{
	int	totalFrames;
	int	numSamples;
	int	numBytes;
	double	average;
	SAMPLE	max;
	SAMPLE	val;
}
utilsData;

namespace Audio
{
	class VoIPManager {
	public:
		PaStream	*startRecordInput(void);
		PaStream	*playRecordOutput(paTestData &data);
		void	initInput(Audio::InputParams &);
		void	initOutput(Audio::OutputParams &);
		PaError	RecordingUser(PaStream *stream, paTestData &data);
		PaStream	*openStreamRecord(PaStream *stream);
		int	stopStream(PaError err);
		void initDataSamples(paTestData &data);
		paTestData	initRecord(paTestData &data, utilsData &utilsD);
		utilsData	&getUtilsData(void);
	private:
		utilsData	utilsD;
		Audio::PortAudio _portA;
		Audio::InputParams	_pInput;
		Audio::OutputParams	_pOutput;
		PaError		_err;
		PaStream	*_stream;
	};
}

#endif /* VOIPMANAGER_HPP_ */
