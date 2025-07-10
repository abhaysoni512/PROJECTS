#include "packet_capture.h"
#include <pcap.h>
#include <iostream>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <net/ethernet.h>

std::vector<PacketInfo> capture_packets(int max_packets)
{
    std::vector<PacketInfo> packets;

    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle = pcap_open_live("en0", BUFSIZ, 1, 1000, errbuf);
    if (!handle)
    {
        std::cerr << "Error opening device: " << errbuf << "\n";
        return packets;
    }

    struct pcap_pkthdr *header;
    const u_char *packet;
    int count = 0;

    while (pcap_next_ex(handle, &header, &packet) >= 0 && count < max_packets)
    {
        const struct ether_header *eth_header = (struct ether_header *)packet;
        if (ntohs(eth_header->ether_type) == ETHERTYPE_IP)
        {
            const struct ip *ip_header = (struct ip *)(packet + sizeof(struct ether_header));
            char src_ip[INET_ADDRSTRLEN], dst_ip[INET_ADDRSTRLEN];

            inet_ntop(AF_INET, &(ip_header->ip_src), src_ip, INET_ADDRSTRLEN);
            inet_ntop(AF_INET, &(ip_header->ip_dst), dst_ip, INET_ADDRSTRLEN);

            PacketInfo info;
            info.src_ip = src_ip;
            info.dst_ip = dst_ip;

            if (ip_header->ip_p == IPPROTO_TCP)
            {
                const struct tcphdr *tcp_header = (struct tcphdr *)(packet + sizeof(struct ether_header) + ip_header->ip_hl * 4);
                info.protocol = "TCP";
                info.src_port = ntohs(tcp_header->th_sport);
                info.dst_port = ntohs(tcp_header->th_dport);
            }
            else if (ip_header->ip_p == IPPROTO_UDP)
            {
                const struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) + ip_header->ip_hl * 4);
                info.protocol = "UDP";
                info.src_port = ntohs(udp_header->uh_sport);
                info.dst_port = ntohs(udp_header->uh_dport);
            }
            else
            {
                info.protocol = "Other";
                info.src_port = 0;
                info.dst_port = 0;
            }

            packets.push_back(info);
            count++;
        }
    }

    pcap_close(handle);
    return packets;
}
