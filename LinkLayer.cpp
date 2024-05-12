#include <iostream>
#include <string>
using namespace std;

class LinkLayer {
public:
    string sourceMAC;
    string destinationMAC;
    string frameType;
    string payload;


    LinkLayer(const string& sourceMAC, const string& destinationMAC, const string& frameType, const string& payload) 
        : sourceMAC(sourceMAC), destinationMAC(destinationMAC), frameType(frameType), payload(payload) {}
};