#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // enables vector<string>, map, etc.

#include "../src/packet_capture.h"

namespace py = pybind11;

PYBIND11_MODULE(packet_capture, m)
{
    py::class_<PacketInfo>(m, "PacketInfo")
        .def_readonly("src_ip", &PacketInfo::src_ip)
        .def_readonly("dst_ip", &PacketInfo::dst_ip)
        .def_readonly("protocol", &PacketInfo::protocol)
        .def_readonly("src_port", &PacketInfo::src_port)
        .def_readonly("dst_port", &PacketInfo::dst_port);

    m.def("capture_packets", &capture_packets, "Capture packets and return list of PacketInfo");
}
