cmake_minimum_required(VERSION 2.8)
project(myproject CXX)
add_definitions("-std=c++11")

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

add_executable(main main.cpp Server.cpp Session.cpp)

#We have to add by hand all package beacause if not it does not work (CONAN_PKG::Poco CONAN_PKG::boost)
target_link_libraries(main ${CONAN_LIBS})