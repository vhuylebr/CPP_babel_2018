cmake_minimum_required(VERSION 2.8)
project(myproject CXX)
add_definitions("-std=c++11")

set(CPP_FILE "./client/src/")
set(SERVER "./server/")

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.12/conan.cmake"
		"${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

#Check if you have the binary conan if you have intalled conan
conan_check()

#Add remote
conan_add_remote(NAME bincrafters INDEX 1
URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_add_remote(NAME center INDEX 2
URL https://bintray.com/conan/conan-center)
conan_add_remote(NAME tek INDEX 3
URL https://bintray.com/bincrafters/public-conan)

#Install package with the command 'conan install ./conanfile.txt'
conan_cmake_run(CONANFILE conanfile.txt
BASIC_SETUP
BUILD missing)

add_executable(babel_server ${SERVER}main.cpp ${SERVER}Server.cpp ${SERVER}Session.cpp)

add_executable(babel_client ${CPP_FILE}main.cpp
			 ${CPP_FILE}PortAudio.cpp
			 ${CPP_FILE}OutputParams.cpp
			 ${CPP_FILE}InputParams.cpp
			 ${CPP_FILE}VoIPManager.cpp
			 ${CPP_FILE}recordCallBack.cpp)

IF (WIN32)
	set(CONAN_LIBS ${CONAN_LIBS_RELEASE})
ENDIF()

target_link_libraries(babel_client ${CONAN_LIBS})
target_link_libraries(babel_server ${CONAN_LIBS})
