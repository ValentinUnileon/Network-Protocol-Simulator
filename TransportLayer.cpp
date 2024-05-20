#ifndef TRANSPORT_LAYER_H
#define TRANSPORT_LAYER_H

#include <iostream>
#include <string>
using namespace std;


class TransportLayer {
public:
    // Common attributes for both TCP and UDP
    int sourcePort;
    int destinationPort;
    string data;

    // Attributes specific to TCP
    int sequenceNumber;
    int acknowledgmentNumber;
    bool synFlag;
    bool ackFlag;
    bool finFlag;

    // Attributes specific to UDP
    int length;
    int checksum;

    // Constructor for TCP
    TransportLayer(int srcPort, int destPort, const string& payload, int seqNum, int ackNum, bool syn, bool ack, bool fin)
        : sourcePort(srcPort), destinationPort(destPort), data(payload), 
          sequenceNumber(seqNum), acknowledgmentNumber(ackNum), 
          synFlag(syn), ackFlag(ack), finFlag(fin), 
          length(0), checksum(0) {}

    // Constructor for UDP
    TransportLayer(int srcPort, int destPort, const string& payload, int len, int chksum)
        : sourcePort(srcPort), destinationPort(destPort), data(payload), 
          sequenceNumber(0), acknowledgmentNumber(0), 
          synFlag(false), ackFlag(false), finFlag(false), 
          length(len), checksum(chksum) {}
};

#endif 