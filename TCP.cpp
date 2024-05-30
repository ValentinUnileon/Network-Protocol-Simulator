#ifndef TCP_H
#define TCP_H

#include <iostream>
#include <vector>
#include <string>
#include "NodeDevice.cpp"
#include "ApplicationLayer.cpp"
#include "TransportLayer.cpp"
#include "NetworkLayer.cpp"
#include "LinkLayer.cpp"
#include "Packet.cpp"

using namespace std;

class TCP {
public:
    string ipAddress;
    string destinationIP;
    int port;

    // Attributes for congestion control
    int cwnd;
    int ssthresh;
    int dupACKs;
    int lastACK;

    // Sequence and acknowledgment numbers
    int currentSeqNum;
    int currentAckNum;

    // Constructor
    TCP(NodeDevice origin, NodeDevice destination, int originPort) 
        : ipAddress(origin.getIPAddress()), destinationIP(destination.getIPAddress()), port(originPort), 
          cwnd(1), ssthresh(64), dupACKs(0), lastACK(0), currentSeqNum(0), currentAckNum(0) {}

    Packet encapsulatePacketTCP(string data) {
        // Determine flags and update sequence/acknowledgment numbers
        bool synFlag = false;
        bool ackFlag = false;
        bool finFlag = false;

        if (data == "SYN") {
            synFlag = true;
            ackFlag = false;
            finFlag = false;
            currentSeqNum = rand() % 10000; // Random initial sequence number
            currentAckNum = 0;
        } else if (data == "SYN+ACK") {
            synFlag = true;
            ackFlag = true;
            finFlag = false;
            currentAckNum = currentSeqNum + 1; // ACK the received SYN
        } else if (data == "FIN") {
            synFlag = false;
            ackFlag = false;
            finFlag = true;
            currentSeqNum += 1; // Increment sequence number for FIN
        } else {
            // Regular data packet
            currentSeqNum += data.size();
            currentAckNum += data.size();
        }

        // Encapsulation
        ApplicationLayer appLayer(port, data);
        TransportLayer transLayer(port, 80, data, currentSeqNum, currentAckNum, synFlag, ackFlag, finFlag);
        NetworkLayer netLayer(ipAddress, destinationIP, data.size(), "TCP");
        LinkLayer linkLayer("00:1A:2B:3C:4D:5E", "00:1A:2B:3C:4D:5E", "0x0800");

        Packet packet(appLayer, transLayer, netLayer, linkLayer);
        packet.printInfo();

        return packet;
    }

    void congestionControl(int ack) {
        if (ack == lastACK) {
            dupACKs++;
            if (dupACKs == 3) {
                // Fast Retransmit: 3 duplicate ACKs received
                ssthresh = std::max(cwnd / 2, 2); // Update ssthresh
                cwnd = ssthresh + 3;              // Set cwnd for fast recovery
                std::cout << "Fast Retransmit: Retransmitting segment " << ack << std::endl;
            }
        } else {
            if (dupACKs >= 3) {
                // Fast Recovery: After 3 duplicate ACKs
                cwnd = ssthresh; // Set cwnd to ssthresh
            } else if (cwnd < ssthresh) {
                // Slow Start phase
                cwnd++;
            } else {
                // Congestion Avoidance phase
                cwnd += 1 / cwnd;
            }
            dupACKs = 0; // Reset duplicate ACKs counter
        }
        lastACK = ack; // Update last received ACK
    }

    void sendSegments() {
        std::cout << "Sending " << cwnd << " segments." << std::endl;
    }
};

#endif
