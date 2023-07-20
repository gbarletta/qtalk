#ifndef __SERVICE_HPP__
#define __SERVICE_HPP__

#include "message.hpp"
#include <unordered_map>
#include <queue>

class Service {
    private:
        std::unordered_map<std::string, std::string> entities;
        std::unordered_map<std::string, std::queue<Message>> topics;

    public:
        Service();
        bool registerEntity(std::string identifier, std::string address);
        bool registerTopic(std::string name);
        bool produce(std::string producer, std::string topic, std::string message);
        Message consume(std::string consumer, std::string topic);
        void printEntities();
        void printTopics();
        void printTopicMessages(std::string topic);
};

#endif