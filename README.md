# Network Communication Protocol Simulator

## Overview

This project is a simulator for network communication protocols, specifically TCP and IP. It aims to simulate a network environment with devices and a physical transport medium. The simulator uses the TCP/IP model to facilitate communication, providing a detailed simulation of the various layers involved in the process.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Architecture](#architecture)
- [Classes and Their Roles](#classes-and-their-roles)
- [Compilation and Execution](#compilation-and-execution)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Features

- Simulates TCP and UDP communication protocols.
- Encapsulates data within packets at various layers.
- Manages congestion control in TCP.
- Calculates UDP checksums for data integrity.
- Simulates network nodes and channels with realistic characteristics.

## Architecture

The simulator is designed with a layered architecture to reflect the TCP/IP model. Each class represents a different component or layer of the network stack, enabling detailed simulation and testing of network communication processes.

### Detailed Description of the Overall Architecture

The architecture of the simulator involves the following components:

- **Node Devices**: These represent the end devices in the network. Each node has a unique IP address, MAC address, and other characteristics like a unique ID.
- **Channel**: This simulates the physical medium through which data packets travel. It accounts for bandwidth, latency, and error rate.
- **TCP Class**: Manages TCP-specific operations such as sequence numbers, acknowledgment numbers, and congestion control.
- **UDP Class**: Handles UDP-specific functionalities, including encapsulation of data and checksum calculation.
- **Packet**: Represents a data packet, encapsulating information from all the layers.
- **Application, Transport, Network, and Link Layers**: Each of these classes represents a different layer in the TCP/IP model, managing the specific responsibilities of that layer.

## Classes and Their Roles

### Main
Handles the overall flow of the simulation, initializing the nodes, channels, and managing the interaction between different components.

### Channel
- Simulates the physical transport medium.
- Manages bandwidth, latency, and error rate.
- Connects and disconnects nodes, transmits data, and handles error simulation.

### TCP
- Manages TCP-specific protocol operations.
- Implements sequence and acknowledgment numbers.
- Manages congestion control mechanisms like slow start, congestion avoidance, and fast recovery.

### UDP
- Encapsulates application data into UDP packets.
- Manages source and destination port numbers.
- Calculates UDP checksum for data integrity.

### Node Device
- Represents network nodes.
- Contains attributes like IP address, MAC address, and unique ID.
- Facilitates data transmission and reception.

### Packet
- Encapsulates data from various layers.
- Provides methods to retrieve payload size and other packet-specific information.

## Compilation and Execution

### Requirements

- C++11 or later
- A C++ compiler (e.g., g++, clang++)

### Compilation

To compile the project, navigate to the project directory and run:

```bash
g++ -o simulator main.cpp Channel.cpp TCP.cpp UDP.cpp NodeDevice.cpp Packet.cpp ApplicationLayer.cpp TransportLayer.cpp NetworkLayer.cpp LinkLayer.cpp
