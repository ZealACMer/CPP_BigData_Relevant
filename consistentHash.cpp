#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <string>

class ConsistentHash
{
public:
    ConsistentHash(unsigned int num_vnodes) : num_vnodes_(num_vnodes) {}

    void addNode(const std::string& node)
    {
        for(unsigned int i = 0; i < num_vnodes_; ++i)
        {
            unsigned int hash = Hash(node + std::to_string(i));
            ring_[hash] = node;
        }
    }

    void removeNode(const std::string& node)
    {
        for(unsigned int i = 0; i < num_vnodes_; ++i)
        {
            unsigned int hash = Hash(node + std::to_string(i));
            ring_.erase(hash);
        }
    }

    std::string getNode(const std::string& key)
    {
        if(ring_.empty())
        {
            return "";
        }

        unsigned int hash = Hash(key);
        auto it = ring_.lower_bound(hash);

        // If the iterator reaches the end, loop to the beginning
        if(it == ring_.end())
        {
            it = ring_.begin();
        }

        return it->second;
    }

private:
    // A simple hashing function using std::hash (you may replace with a better one)
    unsigned int Hash(const std::string& key)
    {
        std::hash<std::string> hasher;
        return static_cast<unsigned int>(hasher(key));
    }

    std::map<unsigned int, std::string> ring_;
    unsigned int num_vnodes_;
};

int main(int argc, char* argv[])
{
    unsigned int num_virtual_nodes = 100;
    ConsistentHash ch(num_virtual_nodes);

    // Add nodes to the ring.
    ch.addNode("127.1.1.1");
    ch.addNode("127.1.1.2");
    ch.addNode("127.1.1.3");

    // The key example - looking for its node.
    std::string key = "192.168.1.1";
    std::string node = ch.getNode(key);
    std::cout << "The key " << key << " is mapped to node " << node << std::endl;
    
    // Remove node and find the key again.
    ch.removeNode("127.1.1.3");
    node = ch.getNode(key);
    std::cout << "After node 127.1.1.3 is removed, the key " << key << " is mapped to node " << node << std::endl;

    return 0;
}