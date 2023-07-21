#include <iostream>
#include "service.hpp"
#include "message.hpp"
#include "server.hpp"

service::service() 
{
    server s = server("127.0.0.1", 42069);
    s.event_loop();
}

bool service::register_entity(std::string identifier, std::string address)
{
    if (this->entities.find(identifier) == this->entities.end()) {
        this->entities[identifier] = address;
        return true;
    }
    
    return false;
}

bool service::register_topic(std::string name)
{
    if (this->topics.find(name) == this->topics.end()) {
        this->topics[name] = std::queue<message>();
        return true;
    }
    
    return false;
}

bool service::produce(std::string producer, std::string topic, std::string msg)
{
    if (this->entities.find(producer) == this->entities.end() || 
        this->topics.find(topic) == this->topics.end()) {
        return false;
    }

    message tmp = message(producer, msg);
    this->topics[topic].push(tmp);

    return true;
}
        
message service::consume(std::string consumer, std::string topic)
{
    if (this->entities.find(consumer) == this->entities.end() || 
        this->topics.find(topic) == this->topics.end()) {
        return message("couldn't find consumer or topic");
    }

    this->topics[topic];

    if (!this->topics[topic].empty()) {
        message msg = this->topics[topic].front();
        this->topics[topic].pop();
        return msg;
    }

    return message("topic is empty");
}

void service::print_entities()
{
    for (const auto& [key, value] : this->entities)
        std::cout << "Identifier: " << key << " Address: " << value << std::endl;
}

void service::print_topics()
{
    for (const auto& [key, value] : this->topics)
        std::cout << "Name: " << key <<  std::endl;
}

void service::print_topic_messages(std::string topic)
{
    if (this->topics.find(topic) == this->topics.end()) {
        return;
    }

    auto tmp = this->topics[topic];
    std::cout << "Printing messages from \"" << topic << "\" queue:" << std::endl;

    while (!tmp.empty())
    {
        message msg = tmp.front();
        std::cout << topic << ": \"" << msg.get_msg() << "\" from: " << msg.get_producer() << std::endl;
        tmp.pop();
    } 
}