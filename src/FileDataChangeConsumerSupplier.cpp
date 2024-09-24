#include "FileDataChangeConsumerSupplier.h"
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <iostream>

FileDataChangeConsumerSupplier::FileDataChangeConsumerSupplier()
    : participant_(nullptr), publisher_(nullptr), subscriber_(nullptr) {}

FileDataChangeConsumerSupplier::~FileDataChangeConsumerSupplier() {
    shutdown_DDS();
}

bool FileDataChangeConsumerSupplier::init_DDS(int argc, char* argv[]) {
    participant_ = DomainParticipantFactory::get_instance()->create_participant(0, PARTICIPANT_QOS_DEFAULT);
    if (!participant_) {
        std::cerr << "Failed to create DomainParticipant." << std::endl;
        return false;
    }

    publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
    subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);

    if (!publisher_ || !subscriber_) {
        std::cerr << "Failed to create Publisher or Subscriber." << std::endl;
        return false;
    }

    return true;
}

void FileDataChangeConsumerSupplier::shutdown_DDS() {
    if (participant_) {
        participant_->delete_contained_entities();
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
        participant_ = nullptr;
    }
}

bool FileDataChangeConsumerSupplier::send_diff(const DistributedContent::FileDiff& diff) {
    // Add FastDDS logic to publish the data
    std::cout << "Sending file difference for: " << diff.filename() << std::endl;

    // Simulated data sending logic - you would implement DataWriter logic here
    return true;
}
