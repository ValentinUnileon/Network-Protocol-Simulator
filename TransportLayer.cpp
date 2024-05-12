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
};