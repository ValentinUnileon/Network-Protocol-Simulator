#ifndef UDP_H
#define UDP_H

#include <iostream>
#include <vector>
#include <string>
#include <arpa/inet.h> // For htons function
#include "NodeDevice.cpp"
#include "ApplicationLayer.cpp"
#include "TransportLayer.cpp"
#include "NetworkLayer.cpp"
#include "LinkLayer.cpp"
#include "Packet.cpp"

using namespace std;

class UDP {
public:
    string ipAddress;
    string destinationIP;
    int port;
    int destinationPort;  // Add this to store destination port

    // Corrected constructor
    UDP(NodeDevice origin, NodeDevice destination, int originPort, int destPort)
        : ipAddress(origin.getIPAddress()), destinationIP(destination.getIPAddress()), port(originPort), destinationPort(destPort) {}

    Packet createPacketUDP(const string& data) {
        ApplicationLayer appLayer(port, data);

        // Create TransportLayer for UDP
        int udpLength = 8 + data.size(); // 8 bytes for UDP header + payload size
        TransportLayer transLayer(port, destinationPort, data, udpLength, 0);

        // Calculate UDP checksum
        int checksum = calculateUDPChecksum(transLayer, ipAddress, destinationIP, data);
        transLayer.checksum = checksum;

        // Create the other layers
        NetworkLayer netLayer(ipAddress, destinationIP, udpLength, "UDP");
        LinkLayer linkLayer("00:1A:2B:3C:4D:5E", "00:1A:2B:3C:4D:5E", "0x0800");

        Packet packet(appLayer, transLayer, netLayer, linkLayer);
        packet.printInfo();

        return packet;
    }

private:
    // Function to calculate UDP checksum
    int calculateUDPChecksum(const TransportLayer& transLayer, const string& srcIP, const string& destIP, const string& data) {
        unsigned long sum = 0;

        // Pseudo-header
        sum += (srcIP[0] << 8) + srcIP[1];
        sum += (srcIP[2] << 8) + srcIP[3];
        sum += (destIP[0] << 8) + destIP[1];
        sum += (destIP[2] << 8) + destIP[3];
        sum += 0x0011; // UDP protocol
        sum += htons(transLayer.length);

        // UDP header
        sum += htons(transLayer.sourcePort);
        sum += htons(transLayer.destinationPort);
        sum += htons(transLayer.length);
        sum += htons(transLayer.checksum);

        // Data (payload)
        for (size_t i = 0; i < data.size(); i += 2) {
            unsigned short word = (data[i] << 8) + (i + 1 < data.size() ? data[i + 1] : 0);
            sum += word;
        }

        // Adding the carry bits
        while (sum >> 16) {
            sum = (sum & 0xFFFF) + (sum >> 16);
        }

        // One's complement
        sum = ~sum;
        return static_cast<int>(sum & 0xFFFF);
    }
};

#endif
