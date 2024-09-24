#include "FileDataChangeAvailableConsumer.h"
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/core/status/StatusMask.hpp>
#include <iostream>

FileDataChangeAvailableConsumer::FileDataChangeAvailableConsumer(const std::string& topic_name)
    : reader_(nullptr), topic_name_(topic_name) {}

FileDataChangeAvailableConsumer::~FileDataChangeAvailableConsumer() {
    if (reader_) {
        reader_->get_subscriber()->delete_datareader(reader_);
    }
}

bool FileDataChangeAvailableConsumer::init_DDS() {
    DomainParticipant* participant = DomainParticipantFactory::get_instance()->create_participant(0, PARTICIPANT_QOS_DEFAULT);
    if (!participant) {
        std::cerr << "Failed to create DomainParticipant." << std::endl;
        return false;
    }

    Subscriber* subscriber = participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
    Topic* topic = participant->create_topic(topic_name_, "FileDiff", TOPIC_QOS_DEFAULT);
    
    reader_ = subscriber->create_datareader(topic, DATAREADER_QOS_DEFAULT, nullptr);
    
    if (!reader_) {
        std::cerr << "Failed to create DataReader." << std::endl;
        return false;
    }

    return true;
}

void FileDataChangeAvailableConsumer::receive_diff() {
    // Logic to receive file differences from FastDDS DataReader
    std::cout << "Receiving file difference..." << std::endl;

    // Here you would implement logic to actually read the data from the reader,
    // for example, creating a listener or manually polling the reader for samples.
}
