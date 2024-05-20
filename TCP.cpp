#ifndef TCP_H
#define TCP_H

#include <iostream>

#include "ApplicationLayer.cpp"
#include "TransportLayer.cpp"
#include "NetworkLayer.cpp"
#include "LinkLayer.cpp"
#include "Packet.cpp"
using namespace std;


class TCP {

public:

    string ipAddress;
    string destinationIP;
    string uniqueID;
    int port;
    string data;
    vector<Packet> receivedPackets;


    TCP(const string& ip, string destIP, const string& id, int portN, string dataM) : ipAddress(ip), destinationIP(destIP), uniqueID(id), port(portN), data(dataM) {}

    void createPacketTCP(){

        //crear el paquete con cada una de las clases
        int seqNum, ackNum;

        ApplicationLayer appLayer(port, data);
        TransportLayer transLayer(port, 80, data, seqNum, ackNum, true, true, true);
        NetworkLayer netLayer(ipAddress, destinationIP, 20, "TCP");
        LinkLayer linkLayer("00:1A:2B:3C:4D:5E", "00:1A:2B:3C:4D:5E", "0x0800");

        Packet packet(appLayer, transLayer, netLayer, linkLayer);
        packet.printInfo();




    }



};
#endif 