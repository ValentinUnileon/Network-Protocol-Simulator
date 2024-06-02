#ifndef CHANNEL_H
#define CHANNEL_H

#include <iostream>
#include <cstdlib> // For rand()
#include "NodeDevice.cpp"
#include "Packet.cpp"

using namespace std;

class Channel {
public:
    double bandwidth; // Bandwidth in Mbps
    double latency;   // Latency in milliseconds
    double errorRate; // Error rate (probability of error)
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
            cerr << "Error: Nodes not connected!" << endl;
            cout << "--------------------------" << endl;
            return -1; // Indicate an error by returning -1
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
            return -1; // Indicate an error by returning -1
        }

        cout << "Packet transmitted successfully." << endl;
        cout << "--------------------------" << endl;

        // Calculate the ACK from the receiver
        int ackNumber = packet.getSeqNum() + packet.getPayloadSize();
        return ackNumber;
    }

private:
    double calculateTransmissionTime(size_t dataSize) {
        // Calculate transmission time based on data size and bandwidth
        return (dataSize * 8.0) / (bandwidth * 1000.0); // Convert Mbps to Kbps and bytes to bits
    }

    double calculatePropagationDelay() {
        // Return the channel latency
        return latency;
    }

    bool introduceError() {
        // Simulate the possibility of a transmission error
        return (static_cast<double>(rand()) / RAND_MAX) < errorRate;
    }
};

#endif // CHANNEL_H
