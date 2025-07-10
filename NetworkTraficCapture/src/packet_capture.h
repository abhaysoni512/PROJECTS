#ifndef PACKET_CAPTURE_H
#define PACKET_CAPTURE_H

#include <string>
#include <vector>

/**
 * @brief Struct to hold parsed packet metadata.
 */
struct PacketInfo
{
    std::string src_ip;
    std::string dst_ip;
    std::string protocol;
    int src_port;
    int dst_port;
};

/**
 * @brief Capture packets and return structured info (IP, port, protocol).
 * @param max_packets Number of packets to capture.
 * @return std::vector<PacketInfo> containing parsed packet info.
 */
std::vector<PacketInfo> capture_packets(int max_packets);

#endif // PACKET_CAPTURE_H
