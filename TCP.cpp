#ifndef TCP_H
#define TCP_H

#include <iostream>
#include <vector>
#include <string>
#include "NodeDevice.cpp"
#include "ApplicationLayer.cpp"
#include "TransportLayer.cpp"
#include "NetworkLayer.cpp"
#include "LinkLayer.cpp"
#include "Packet.cpp"


using namespace std;

// Usemoslo como libreria de de funciones necesarias para una conexion tcp
class TCP {

public:
    string ipAddress;
    string destinationIP;
    int port;
    vector<Packet> receivedPackets;
    

    // Constructor corregido

    TCP( NodeDevice origin, NodeDevice destination, int originPort ) : ipAddress(origin.getIPAddress()), destinationIP(destination.getIPAddress()), port(originPort) {}

    Packet createPacketTCP(string data) {
        // Crear el paquete con cada una de las clases
        int seqNum = 0, ackNum = 0;

        ApplicationLayer appLayer(port, data);
        TransportLayer transLayer(port, 80, data, seqNum, ackNum, true, true, true); // Flags depende del 3-way handshake
        NetworkLayer netLayer(ipAddress, destinationIP, data.size(), "TCP");
        LinkLayer linkLayer("00:1A:2B:3C:4D:5E", "00:1A:2B:3C:4D:5E", "0x0800");

        Packet packet(appLayer, transLayer, netLayer, linkLayer);
        packet.printInfo();

        return packet;
    }
};

#endif
