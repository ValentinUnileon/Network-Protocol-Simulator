#ifndef LINK_LAYER_H
#define LINK_LAYER_H

#include <iostream>
#include <string>
using namespace std;

class LinkLayer {
public:

    string sourceMAC;
    string destinationMAC;
    string frameType;

    LinkLayer(const string& sourceMAC, const string& destinationMAC, const string& frameType) 
        : sourceMAC(sourceMAC), destinationMAC(destinationMAC), frameType(frameType) {}
};

#endif 