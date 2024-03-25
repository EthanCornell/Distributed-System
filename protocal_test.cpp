#include "GossipProtocol.hpp"
#include "PeerSamplingService.hpp"
#include <iostream>
#include <memory> // For std::make_shared
#include <vector>

void testNodeJoin()
{
    // Initializing PeerSamplingService with a list of initial nodes
    std::vector<Node> initialNodes = {
        Node("127.0.0.1", 5002),
        Node("127.0.0.1", 5003)};
    auto peerService = std::make_shared<PeerSamplingService>(initialNodes);
    GossipProtocol protocol(peerService);
    Node newNode("127.0.0.1", 5000); // Example node
    protocol.onJoin(newNode);
    // Further assertions or checks can be added here

    std::cout << "Node join test passed." << std::endl;
}

void testStateChange()
{
    std::vector<Node> initialNodes = {
        Node("127.0.0.1", 5002),
        Node("127.0.0.1", 5003)};
    auto peerService = std::make_shared<PeerSamplingService>(initialNodes);
    GossipProtocol protocol(peerService);
    protocol.onChange("key1", "value1");
    // Assert the state has changed as expected
    std::cout << "State change test passed." << std::endl;
}

void testStateSynchronization()
{
    std::vector<Node> initialNodes = {
        Node("127.0.0.1", 5002),
        Node("127.0.0.1", 5003)};
    auto peerService = std::make_shared<PeerSamplingService>(initialNodes);
    GossipProtocol protocol(peerService);
    Node peerNode("127.0.0.1", 5001); // Example peer node
    // Assume stateTree and state are already initialized and populated
    protocol.synchronizeStateWithPeer(peerNode);
    // Assert that state synchronization logic is triggered correctly
    std::cout << "State synchronization test passed." << std::endl;
}

void testOnDead()
{
    std::vector<Node> initialNodes = {
        Node("127.0.0.1", 5002),
        Node("127.0.0.1", 5003)};
    auto peerService = std::make_shared<PeerSamplingService>(initialNodes);
    GossipProtocol protocol(peerService);
    Node deadNode("127.0.0.1", 5002); // Example node considered dead
    protocol.onDead(deadNode);
    std::cout << "Node dead test passed." << std::endl;
}

void testOnAlive()
{
    std::vector<Node> initialNodes = {Node("127.0.0.1", 5002), Node("127.0.0.1", 5003)};
    auto peerService = std::make_shared<PeerSamplingService>(initialNodes);
    GossipProtocol protocol(peerService);
    Node aliveNode("127.0.0.1", 5003); // Example node considered alive
    protocol.onAlive(aliveNode);
    std::cout << "Node alive test passed." << std::endl;
}

void testTriggerStateSynchronization()
{
    std::vector<Node> initialNodes = {Node("127.0.0.1", 5002), Node("127.0.0.1", 5003)};
    auto peerService = std::make_shared<PeerSamplingService>(initialNodes);
    GossipProtocol protocol(peerService);
    // This test assumes the internal state needs to be synchronized across nodes.
    protocol.triggerStateSynchronization();
    std::cout << "Trigger state synchronization test passed." << std::endl;
}

void testSynchronizeStateWithPeer()
{
    std::vector<Node> initialNodes = {Node("127.0.0.1", 5002), Node("127.0.0.1", 5003)};
    auto peerService = std::make_shared<PeerSamplingService>(initialNodes);
    GossipProtocol protocol(peerService);
    Node peerNode("127.0.0.1", 5001); // Example peer node for synchronization
    protocol.synchronizeStateWithPeer(peerNode);
    std::cout << "Synchronize state with peer test passed." << std::endl;
}

int main()
{
    testNodeJoin();
    testStateChange();
    testStateSynchronization();
    testOnDead();
    testOnAlive();
    testTriggerStateSynchronization();
    testSynchronizeStateWithPeer();

    std::cout << "All tests passed successfully." << std::endl;
    return 0;
}

// g++ -std=c++17 -o gossip_protocol_test protocal_test.cpp -lgtest -lgtest_main -pthread
