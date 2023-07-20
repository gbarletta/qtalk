#include "message.hpp"

Message::Message(std::string producerIdentifier, std::string message)
{
    this->producerIdentifier = producerIdentifier;
    this->message = message;
    this->created_at = std::chrono::system_clock::now();
    this->hasErr = false;
}

Message::Message(std::string error)
{
    this->hasErr = true;
    this->error = error;
}

std::string Message::getMessage() 
{
    return this->message;
}

std::string Message::getProducerIdentifier()
{
    return this->producerIdentifier;
}

std::chrono::system_clock::time_point Message::getCreatedAt()
{
    return this->created_at;
}