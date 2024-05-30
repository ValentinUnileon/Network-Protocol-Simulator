#ifndef PACKET_H
#define PACKET_H

#include <iostream>
#include <string>
#include "ApplicationLayer.cpp"
#include "LinkLayer.cpp"
#include "NetworkLayer.cpp"
#include "TransportLayer.cpp"

using namespace std;

class Packet {
public:
    
    int sourcePort;
    int destinationPort;
    string sourceIP;
    string destinationIP;
    string protocol;
    string sourceMAC;
    string destinationMAC;
    string frameType;
    string payload;

    // TCP-specific attributes
    bool synFlag;
    bool ackFlag;
    bool finFlag;
    int acknowledgmentNumber;
    int seqNum;

    // UDP-specific attributes
    int udpLength;
    int udpChecksum;

    // Constructor for TCP packets
    Packet(const ApplicationLayer& appLayer, const TransportLayer& transportLayer, const NetworkLayer& networkLayer, const LinkLayer& linkLayer) 
        : sourcePort(appLayer.port), 
        destinationPort(transportLayer.destinationPort),
        sourceIP(networkLayer.sourceIP), 
        destinationIP(networkLayer.destinationIP), 
        protocol(networkLayer.protocol),
        sourceMAC(linkLayer.sourceMAC),
        destinationMAC(linkLayer.destinationMAC), 
        frameType(linkLayer.frameType), 
        payload(appLayer.data),
        synFlag(false),
        ackFlag(false),
        finFlag(false),
        seqNum(transportLayer.sequenceNumber),
        acknowledgmentNumber(transportLayer.acknowledgmentNumber),
        udpLength(0),
        udpChecksum(0) {
        
        if (networkLayer.protocol == "TCP") {
            synFlag = transportLayer.synFlag;
            ackFlag = transportLayer.ackFlag;
            finFlag = transportLayer.finFlag;
            acknowledgmentNumber = transportLayer.acknowledgmentNumber;
        } else if (networkLayer.protocol == "UDP") {
            udpLength = transportLayer.length;
            udpChecksum = transportLayer.checksum;
        }
    }

    void printInfo() const {
        cout << "--------------------------" << endl;
        cout << "| Source Port       : " << sourcePort << endl;
        cout << "| Destination Port  : " << destinationPort << endl;
        cout << "| Source IP         : " << sourceIP << endl;
        cout << "| Destination IP    : " << destinationIP << endl;
        cout << "| Protocol          : " << protocol << endl;
        
        if (protocol == "TCP") {
            cout << "| SYN Flag          : " << (synFlag ? "true" : "false") << endl;
            cout << "| ACK Flag          : " << (ackFlag ? "true" : "false") << endl;
            cout << "| FIN Flag          : " << (finFlag ? "true" : "false") << endl;
            cout << "| Ack Number        : " << acknowledgmentNumber << endl;
            cout << "| Sequence Number   : " << seqNum << endl;
        } else if (protocol == "UDP") {
            cout << "| UDP Length        : " << udpLength << endl;
            cout << "| UDP Checksum      : " << udpChecksum << endl;
        }
        
        cout << "| Source MAC        : " << sourceMAC << endl;
        cout << "| Destination MAC   : " << destinationMAC << endl;
        cout << "| Frame Type        : " << frameType << endl;
        cout << "| Payload           : " << payload << endl;
        cout << "--------------------------" << endl;
    }

    int getPayloadSize() const {
        return payload.size();
    }

    int getAcknowledgmentNumber() const {
        return acknowledgmentNumber;
    }

    int getSeqNum() const {
        return seqNum;
    }
};

#endif // PACKET_H
