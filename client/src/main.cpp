#include "Client.hpp"
// #include "QApplication"

// int main(int ac, char **ar)
// {
//   try
//   {
//     boost::asio::io_service io_service;
//     UdpClient server(io_service, std::stoi(ar[1]), std::stoi(ar[2]));
//     io_service.run();
//   }
//   catch (std::exception &e)
//   {
//     std::cerr << e.what() << std::endl;
//   }

//   return 0;
// }
#include "../include/Client.hpp"

int main(int ac, char **av)
{
	boost::asio::io_service io_service;
	Client client(io_service, "127.0.0.1", std::stoi(av[1]));
  // client.call(std::string("127.0.0.1"), std::stoi(av[2]));
	io_service.run();
	return 0;
}
// #include <stdio.h>
// #include <stdlib.h>
// #include <boost/thread.hpp>
// #include "portaudio.h"
// #include "../include/PortAudio.hpp"
// #include "../include/VoIPManager.hpp"

// PaStream	*startRecord(PaStream *stream, paTestData &data) {
// 	if ((stream = voIP.startRecordInput(data)) == NULL) {
// 		std::cout << "An error occured" << std::endl;
// 		exit(84);
// 	}
// }

// PaStream	*playRecord(PaStream *stream, paTestData &data)
// {
// 	if ((stream = voIP.playRecordOutput(data)) == NULL) {
// 		std::cout << "An error occured" << std::endl;
// 		exit(84);
// 	}
// }

// int	main()
// {
// 	Audio::VoIPManager  voIP;
// 	Audio::PortAudio  portA;
// 	PaStream*           stream;
// 	paTestData          data;
// 	using namespace boost;
//     thread thread_1 = thread(startRecord, stream, data);
//     thread thread_2 = thread(playRecord, stream, data);
// }
// #include <stdio.h>
// #include <stdlib.h>
// #include "portaudio.h"
// #include "../include/PortAudio.hpp"
// #include "../include/VoIPManager.hpp"

// int	main()
// {
// 	Audio::VoIPManager  voIP;
// 	PaStream*           stream;
// 	paTestData          data;

// 	while (1) {
// 		if ((stream = voIP.startRecordInput(data)) == NULL) {
// 			std::cout << "An error occured" << std::endl;
// 			exit(84);
// 		}
// 		if ((stream = voIP.playRecordOutput(data)) == NULL) {
// 			std::cout << "An error occured" << std::endl;
// 			exit(84);
// 		}
// 	}
// }
