#ifndef APPLICATION_LAYER_H
#define APPLICATION_LAYER_H

#include <iostream>
#include <string>
using namespace std;

class ApplicationLayer {
public:
    int port;
    string data;


    ApplicationLayer(int port, string dataM) : port(port), data(dataM) {}
};

#endif 