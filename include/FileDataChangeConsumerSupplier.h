#pragma once

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include "FileData.h"  // Include generated FastDDS types for FileDiff

class FileDataChangeConsumerSupplier {
public:
    FileDataChangeConsumerSupplier();
    ~FileDataChangeConsumerSupplier();

    bool init_DDS(int argc, char* argv[]);
    void shutdown_DDS();
    bool send_diff(const DistributedContent::FileDiff& diff);

private:
    eprosima::fastdds::dds::DomainParticipant* participant_;
    eprosima::fastdds::dds::Publisher* publisher_;
    eprosima::fastdds::dds::Subscriber* subscriber_;
};
