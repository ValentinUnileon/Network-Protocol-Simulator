#include <iostream>
#include <string>
using namespace std;

class NetworkLayer {
public:
    string sourceIP;
    string destinationIP;
    int ttl;
    string protocol;
    string payload;


    NetworkLayer(const string& sourceIP, const string& destinationIP, int ttl, const string& protocol, const string& payload) 
        : sourceIP(sourceIP), destinationIP(destinationIP), ttl(ttl), protocol(protocol), payload(payload) {}
};