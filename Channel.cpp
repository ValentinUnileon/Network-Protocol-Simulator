#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <cstdlib> // Para rand()
#include "NodeDevice.cpp"
#include "Packet.cpp"

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

    bool transmitData(Packet packet) {
        if (node1 == nullptr || node2 == nullptr) {
            std::cerr << "Error: Nodos no conectados!" << std::endl;
            return false;
        }

        double transmissionTime = calculateTransmissionTime(packet.getPayloadSize());
        double propagationDelay = calculatePropagationDelay();

        std::cout << "Transmitting packet from " << node1->getIPAddress() << " to " << node2->getIPAddress() << std::endl;
        std::cout << "Packet size: " << packet.getPayloadSize() << " bytes" << std::endl;
        std::cout << "Transmission time: " << transmissionTime << " ms" << std::endl;
        std::cout << "Propagation delay: " << propagationDelay << " ms" << std::endl;

        // Simulate error
        if (introduceError()) {
            std::cerr << "Error: Packet transmission failed due to channel error." << std::endl;
            return false;
        }

        std::cout << "Packet transmitted successfully." << std::endl;
        return true;
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
