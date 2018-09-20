#include <stdio.h>
#include <stdlib.h>
#include "portaudio.h"
#include "../include/PortAudio.hpp"
#include "../include/VoIPManager.hpp"

int	main()
{
	Audio::VoIPManager  voIP;
	PaStream*           stream;
	paTestData          data;

	while (1) {
		if ((stream = voIP.startRecordInput(data)) == NULL) {
			std::cout << "An error occured" << std::endl;
			exit(84);
		}
		if ((stream = voIP.playRecordOutput(data)) == NULL) {
			std::cout << "An error occured" << std::endl;
			exit(84);
		}
	}
}
