# Peer-to-Peer Application in C++

Building a small peer-to-peer (P2P) application in C++ involves several steps, from understanding the required functionality and protocols to testing and documenting your implementation. This summary will guide you through the key stages of development, including functional requirements, protocol design, implementation hints, testing strategies, and more.

## Functional Requirements

- **Peer Discovery:** Implement a mechanism for peers to discover each other within the network. This could be done through a central directory service or a decentralized approach like broadcasting or gossip protocols.
- **Message Exchange:** Enable peers to send and receive messages, including text messages, and potentially extend it to files or media.
- **Peer-to-Peer Communication:** Ensure that communication happens directly between peers without the need for a central server, except for potentially initial discovery.
- **Concurrency:** Handle multiple incoming and outgoing connections simultaneously, requiring multi-threading or asynchronous I/O.
- **Error Handling:** Implement robust error handling to deal with network issues, malformed messages, and unexpected disconnections.

## Gossip Protocol Design

### Implementation Guildline

- **Networking:** Utilize sockets for networking. For C, look into the socket, bind, listen, accept, connect, send, and recv functions. C++ developers might consider using libraries like Boost.Asio for easier asynchronous operations.
- **Threading:** For handling concurrency, explore pthreads in C or std::thread in C++. Ensure proper synchronization mechanisms like mutexes or locks are in place to avoid data races.
- **Serialization:** For encoding and decoding protocol messages, consider using libraries like cJSON for C or nlohmann/json for C++ if opting for JSON.

## Testing Strategy

- **Unit Testing:** Write unit tests for individual components such as the protocol parser, message handler, and network communication functions.
- **Integration Testing:** Test the application as a whole, ensuring that peers can discover each other, exchange messages, and handle disconnections gracefully.
- **Stress Testing:** Simulate high traffic conditions and long-running operations to identify potential memory leaks, race conditions, and bottlenecks.

## Vulnerability Analysis

- Analyze potential security vulnerabilities including eavesdropping, man-in-the-middle attacks, and denial of service (DoS).
- Discuss possible mitigations such as implementing TLS/SSL for encrypted communication or rate limiting to prevent DoS attacks.

## Documentation and Reporting

- Document your design decisions, including the choice of protocol, libraries, and major architectural components.
- Provide a thorough analysis of tests conducted, including scenarios, tools used, and outcomes.
- Discuss known limitations and potential areas for future improvement.

## Collaboration and Originality

- While discussing ideas and testing with peers is encouraged, ensure that all code written is your own.
- Encourage peer reviews of your code for quality assurance and feedback.

This project enhances technical skills in network programming, concurrency, protocol design, and improves the ability to document and analyze software from a security perspective.

---

# Distributed Chat Room Application

Implementing a distributed chat room application requires careful planning and execution, focusing on client-server architecture, message handling, and implementing a gossip protocol for message propagation. Here's a breakdown of the key components and considerations for your project.

## Components

- **Client:** Interfaces with the user, allowing them to send messages and requests to servers via a proxy program.
- **Server:** Maintains the chat room's state, including storing messages and forwarding them to other servers and clients.
- **Proxy Program:** Acts as a mediator between clients and servers, managing connections and message routing.

# Gossip Protocol

The goal of the gossip protocol is to ensure all messages are propagated across the network, even in scenarios where direct communication between all nodes is not possible due to network restrictions (e.g., firewalls, NATs).

## Key Features

- **Message Identification:** Messages are identified by a combination of their origin and a sequence number, ensuring each message is unique and can be tracked across the network.
  
- **Rumor Message:** Contains the chat text, the original sender (Origin), and a sequence number (SeqNo). It is used to distribute chat messages across the network.
  
- **Status Message:** Summarizes the messages a node has seen, using key-value pairs to indicate the highest sequence number received from each origin. This facilitates the synchronization of message logs between peers.

## Rumormongering Process

- When a peer receives a new chat message (either from a user or another peer), it selects a random peer and sends the message.
  
- The sending peer waits for a status message in response. If the status message indicates that the receiving peer is missing some messages, the sending peer forwards these messages.
  
- If a timeout occurs or if there are no new messages to send, the peer either selects a new peer to rumormonger with or stops the process, based on a coin flip.

## Implementation Considerations

- **Networking:** Use sockets for communication between clients, servers, and the proxy. Be mindful of handling connections, sending, and receiving data.
  
- **Concurrency:** Manage multiple connections and message handling concurrently. This may require threading or asynchronous programming.
  
- **Data Structures:** Efficiently store and manage chat logs and the state of messages received and sent. This includes tracking the latest sequence number for each origin.
  
- **Error Handling:** Implement robust error handling for network issues, incorrect message formats, and server crashes.

## Testing

- Test with multiple instances of your application to ensure messages are properly logged, distributed, and synchronized across all servers.
  
- Simulate various network conditions, including server crashes, to verify the resilience and correctness of your gossip protocol implementation.


---

# Anti-Entropy in Gossip-Based Systems

The anti-entropy process complements rumormongering in gossip-based distributed systems, ensuring eventual synchronization of all nodes' states. Here's a breakdown of how it works and its implementation in your application.

## Anti-Entropy Explained

- **Periodic Updates:** Each node periodically selects a random neighbor and exchanges status messages to synchronize states.
- **Neighbor's Response:** If discrepancies are found, either rumormongering or status message exchange resolves them.

## Implementation Guidelines

- **Timer Management:** Implement a reliable mechanism to trigger anti-entropy at regular intervals.
- **Random Neighbor Selection:** Develop a method to select a random neighbor each time anti-entropy is triggered.
- **Status Message Handling:** Design efficient methods to compare states and take appropriate actions.

## Testing Anti-entropy

Test in scenarios with multiple hops, network partitions, and edge cases to ensure robustness and eventual consistency.

---

# Proxy API Specification

The Proxy API Specification outlines the communication protocol between a proxy program and server instances within a distributed chat room application. Adhering to this specification ensures correct interaction between the proxy and servers.

## Overview

- The API uses `\n` (newline) as a delimiter to separate commands sent over a TCP channel.
- A unique `<id>` denotes the process ID for each server, distinct from the operating system's PID. This ID ranges from 0 to n-1, where n is the total number of server processes.

## Commands from Client to Proxy to Server

### Start Command

- **Purpose:** Instructs the proxy to start a server process.
- **Client to Proxy:** `<id> start`
- **Proxy to Server:** `./process <id> <n> <port>`
- **Details:** Starts a server with the specified ID, total process count, and port for incoming connections.

### Message Command

- **Purpose:** Allows the client to send a message to a specific server via the proxy.
- **Client to Proxy:** `<id> msg <messageID> <message>`
- **Proxy to Server:** `msg <messageID> <message>`
- **Details:** Transfers a message from the client to the designated server.

### Get Chat Log Command

- **Purpose:** Requests the local chat log from a server.
- **Client to Proxy:** `<id> get chatLog`
- **Proxy to Server:** `get chatLog`
- **Details:** Retrieves the local chat log from the specified server.

### Crash Command

- **Purpose:** Instructs a server to simulate a crash.
- **Client to Proxy:** `<id> crash`
- **Proxy to Server:** `crash`
- **Details:** Causes the specified server to crash itself immediately.

### Exit Command

- **Purpose:** Signals the proxy to terminate all server processes and exit.
- **Client to Proxy:** `exit`
- **Proxy to Server:** `./stopall`
- **Details:** Kills all server processes and exits the proxy program.

## Server to Proxy Responses

### Chat Log Response

- **Purpose:** Responds to a `get chatLog` command with the server's local chat log.
- **Server to Proxy:** `chatLog <message>,<message>,...`
- **Details:** Server replies with the local chat log, with messages separated by commas.

## Implementation Notes

For server-to-server communication, any port number between 20000 and 29999 is permissible. It's recommended to use a formula like root-id + pid to determine a server's port, facilitating easy identification of neighboring servers' ports. Servers should only communicate with their direct neighbors, as identified by their process IDs and calculated port numbers. Your implementation should gracefully handle server failures, ensuring the system's overall resilience.


## Responses

- **Chat Log Response:** Server replies with its local chat log, formatted as a comma-separated list.

## Implementation Notes

- Use ports between 20000 and 29999 for server-server communication.
- Ensure graceful handling of server failures.

By following these specifications, you maintain the integrity of your distributed chat room application.
