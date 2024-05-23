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

    int port;
    int sourcePort;
    int destinationPort;
    string sourceIP;
    string destinationIP;
    string protocol;
    string sourceMAC;
    string destinationMAC;
    string frameType;
    string payload;
    bool synFlag;
    bool ackFlag;
    bool finFlag;    

    Packet(const ApplicationLayer& appLayer, const TransportLayer& transportLayer, const NetworkLayer& networkLayer, const LinkLayer& linkLayer) 
        : port(appLayer.port), 
        sourcePort(transportLayer.sourcePort), 
        destinationPort(transportLayer.destinationPort),
        sourceIP(networkLayer.sourceIP), 
        destinationIP(networkLayer.destinationIP), 
        protocol(networkLayer.protocol),
        sourceMAC(linkLayer.sourceMAC),
        destinationMAC(linkLayer.destinationMAC), 
        frameType(linkLayer.frameType), 
        payload(appLayer.data),
        synFlag(transportLayer.synFlag),
        ackFlag(transportLayer.ackFlag),
        finFlag(transportLayer.finFlag) {}


    void printInfo() const {
        cout << "--------------------------" << endl;
        cout << "| Port              : " << port << endl;
        cout << "| Source Port       : " << sourcePort << endl;
        cout << "| Destination Port  : " << destinationPort << endl;
        cout << "| Source IP         : " << sourceIP << endl;
        cout << "| Destination IP    : " << destinationIP << endl;
        cout << "| Protocol          : " << protocol << endl;
        
        if (protocol == "TCP") {
            cout << "| SYN Flag          : " << (synFlag ? "true" : "false") << endl;
            cout << "| ACK Flag          : " << (ackFlag ? "true" : "false") << endl;
            cout << "| FIN Flag          : " << (finFlag ? "true" : "false") << endl;
        }
        
        cout << "| Source MAC        : " << sourceMAC << endl;
        cout << "| Destination MAC   : " << destinationMAC << endl;
        cout << "| Frame Type        : " << frameType << endl;
        cout << "| Payload           : " << payload << endl;
        cout << "--------------------------" << endl;
    }

    int getPayloadSize(){
        return payload.size();
    }

};

#endif // PACKET_H