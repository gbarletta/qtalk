#ifndef __SERVICE_HPP__
#define __SERVICE_HPP__

#include "message.hpp"
#include <unordered_map>
#include <queue>

class service {
    private:
        std::unordered_map<std::string, std::string> entities;
        std::unordered_map<std::string, std::queue<message>> topics;

    public:
        service();
        bool register_entity(std::string identifier, std::string address);
        bool register_topic(std::string name);
        bool produce(std::string producer, std::string topic, std::string msg);
        message consume(std::string consumer, std::string topic);
        void print_entities();
        void print_topics();
        void print_topic_messages(std::string topic);
};

#endif