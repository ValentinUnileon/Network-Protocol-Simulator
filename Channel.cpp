#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <cstdlib> // Para rand()
#include "NodeDevice.cpp"
#include "Packet.cpp"

using namespace std;

class Channel {
public:
    double bandwidth; // Ancho de banda en Mbps
    double latency;   // Latencia en milisegundos
    double errorRate; // Tasa de error (probabilidad de error)
    NodeDevice* node1;
    NodeDevice* node2;

    Channel(double bw, double lat, double err) : bandwidth(bw), latency(lat), errorRate(err), node1(nullptr), node2(nullptr) {}

    void connectNodes(NodeDevice* n1, NodeDevice* n2) {
        node1 = n1;
        node2 = n2;
    }

    void disconnectNodes() {
        node1 = nullptr;
        node2 = nullptr;
    }

    int transmitData(Packet packet) {
        cout << "--------------------------" << endl;

        if (node1 == nullptr || node2 == nullptr) {
            cerr << "Error: Nodos no conectados!" << endl;
            cout << "--------------------------" << endl;
            return -1; // Indicamos un error devolviendo -1
        }

        double transmissionTime = calculateTransmissionTime(packet.getPayloadSize());
        double propagationDelay = calculatePropagationDelay();

        cout << "Transmitting packet from " << node1->getIPAddress() << " to " << node2->getIPAddress() << endl;
        cout << "Packet size: " << packet.getPayloadSize() << " bytes" << endl;
        cout << "Transmission time: " << transmissionTime << " ms" << endl;
        cout << "Propagation delay: " << propagationDelay << " ms" << endl;

        // Simulate error
        if (introduceError()) {
            cerr << "Error: Packet transmission failed due to channel error." << endl;
            cout << "--------------------------" << endl;
            return -1; // Indicamos un error devolviendo -1
        }

        cout << "Packet transmitted successfully." << endl;
        cout << "--------------------------" << endl;

        // Calculamos el ACK del receptor
        int ackNumber = packet.getSeqNum() + packet.getPayloadSize();
        return ackNumber;
    }

private:
    double calculateTransmissionTime(size_t dataSize) {
        // Calcula el tiempo de transmisión en función del tamaño de los datos y el ancho de banda
        return (dataSize * 8.0) / (bandwidth * 1000.0); // Convierte Mbps a Kbps y bytes a bits
    }

    double calculatePropagationDelay() {
        // Devuelve la latencia del canal
        return latency;
    }

    bool introduceError() {
        // Simula la posibilidad de un error en la transmisión
        return (static_cast<double>(rand()) / RAND_MAX) < errorRate;
    }
};

#endif // CHANNEL_H
