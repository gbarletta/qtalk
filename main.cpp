#include <iostream>
#include "service.hpp"

int main(int argc, char **argv)
{
    Service service = Service();
    
    service.registerEntity("producer_test", "addr1");
    service.registerEntity("consumer_test", "addr2");

    service.registerTopic("topic1");
    service.registerTopic("topic2");

    service.printEntities();
    service.printTopics();

    service.produce("producer_test", "topic1", "ciao!");
    service.produce("fail_test", "topic1", "prova!");
    service.consume("fail_test", "topic1");

    Message msg = service.consume("consumer_test", "topic1");
    std::cout << "Consumed message: \"" << msg.getMessage() << "\" from: " << msg.getProducerIdentifier() << std::endl;
    
    service.produce("consumer_test", "topic1", "prova!");
    service.printTopicMessages("topic1");

    return 0;
}