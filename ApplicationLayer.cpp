#include <iostream>
#include <string>
using namespace std;

class ApplicationLayer {
public:
    int port;
    string data;


    ApplicationLayer(int port, const string& data) : port(port), data(data) {}
};