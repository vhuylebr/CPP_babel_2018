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
	Audio::VoIPManager  voIP;
	PaStream*           stream;
	paTestData          data;
	boost::asio::io_service io_service;

	if ((stream = voIP.startRecordInput()) == NULL) {
			std::cout << "An error occured" << std::endl;
			exit(84);
		}
	Client client(io_service, "127.0.0.1", std::stoi(av[1]), std::stoi(av[2]), stream);
   	client.call(std::string("127.0.0.1"), std::stoi(av[3]));
	io_service.run();
	return 0;
}
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
// 		if ((stream = voIP.startRecordInput()) == NULL) {
// 			std::cout << "An error occured" << std::endl;
// 			exit(84);
// 		}

// 		// if ((stream = voIP.playRecordOutput(data)) == NULL) {
// 		// 	std::cout << "An error occured" << std::endl;
// 		// 	exit(84);
// 		// }
// 	}
// }
