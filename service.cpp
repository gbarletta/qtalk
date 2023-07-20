#include <iostream>
#include "service.hpp"
#include "message.hpp"

Service::Service() 
{
}

bool Service::registerEntity(std::string identifier, std::string address)
{
    if (this->entities.find(identifier) == this->entities.end()) {
        this->entities[identifier] = address;
        return true;
    }
    
    return false;
}

bool Service::registerTopic(std::string name)
{
    if (this->topics.find(name) == this->topics.end()) {
        this->topics[name] = std::queue<Message>();
        return true;
    }
    
    return false;
}

bool Service::produce(std::string producer, std::string topic, std::string message)
{
    if (this->entities.find(producer) == this->entities.end() || 
        this->topics.find(topic) == this->topics.end()) {
        return false;
    }

    Message msg = Message(producer, message);
    this->topics[topic].push(msg);

    return true;
}
        
Message Service::consume(std::string consumer, std::string topic)
{
    if (this->entities.find(consumer) == this->entities.end() || 
        this->topics.find(topic) == this->topics.end()) {
        return Message("couldn't find consumer or topic");
    }

    this->topics[topic];

    if (!this->topics[topic].empty()) {
        Message msg = this->topics[topic].front();
        this->topics[topic].pop();
        return msg;
    }

    return Message("topic is empty");
}

void Service::printEntities()
{
    for (const auto& [key, value] : this->entities)
        std::cout << "Identifier: " << key << " Address: " << value << std::endl;
}

void Service::printTopics()
{
    for (const auto& [key, value] : this->topics)
        std::cout << "Name: " << key <<  std::endl;
}

void Service::printTopicMessages(std::string topic)
{
    if (this->topics.find(topic) == this->topics.end()) {
        return;
    }

    std::queue tmp = this->topics[topic];
    std::cout << "Printing messages from \"" << topic << "\" queue:" << std::endl;

    while (!tmp.empty())
    {
        Message msg = tmp.front();
        std::cout << topic << ": \"" << msg.getMessage() << "\" from: " << msg.getProducerIdentifier() << std::endl;
        tmp.pop();
    } 
}