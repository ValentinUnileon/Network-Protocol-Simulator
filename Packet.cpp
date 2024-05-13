#include <iostream>
#include <string>
using namespace std;

class Packet {
private:

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

public:


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
        payload(linkLayer.payload) {}


void printInfo() const {

    cout << "--------------------------" << endl;

    cout << "| Port              : " << port << endl;
    cout << "| Source Port       : " << sourcePort << endl;
    cout << "| Destination Port  : " << destinationPort << endl;
    cout << "| Source IP         : " << sourceIP << endl;
    cout << "| Destination IP    : " << destinationIP << endl;
    cout << "| Protocol          : " << protocol << endl;
    cout << "| Source MAC        : " << sourceMAC << endl;
    cout << "| Destination MAC   : " << destinationMAC << endl;
    cout << "| Frame Type        : " << frameType << endl;
    cout << "| Payload           : " << payload << endl;

    cout << "--------------------------" << endl;
}

};