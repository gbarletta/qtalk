#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <string>
#include <chrono>

class Message {
    private:
        std::string producerIdentifier;
        std::string message;
        std::chrono::system_clock::time_point created_at;

    public:
        bool hasErr;
        std::string error;
        Message(std::string producerIdentifier, std::string message);
        Message(std::string error);
        std::string getMessage();
        std::string getProducerIdentifier();
        std::chrono::system_clock::time_point getCreatedAt();
};

#endif