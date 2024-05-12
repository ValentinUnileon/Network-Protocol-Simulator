#include <iostream>
#include <string>
using namespace std;


class TransportLayer {
public:
    int sourcePort;
    int destinationPort;
    int sequenceNumber;
    int ackNumber;
    string payload;

    // Constructor
    TransportLayer(int sourcePort, int destinationPort, int sequenceNumber, int ackNumber, const string& payload) 
        : sourcePort(sourcePort), destinationPort(destinationPort), sequenceNumber(sequenceNumber), ackNumber(ackNumber), payload(payload) {}
};