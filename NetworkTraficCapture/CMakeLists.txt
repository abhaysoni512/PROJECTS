cmake_minimum_required(VERSION 3.14)
project(NetworkTraficCapture)

set(CMAKE_CXX_STANDARD 17)

# Homebrew libpcap headers & pybind11
include_directories(/opt/homebrew/include)
include_directories(/opt/homebrew/opt/libpcap/include)

link_directories(/opt/homebrew/lib)
link_directories(/opt/homebrew/opt/libpcap/lib)

find_package(pybind11 REQUIRED)

add_library(packet_capture MODULE bindings/pybind_module.cpp src/packet_capture.cpp)
target_link_libraries(packet_capture PRIVATE pybind11::module pcap)
