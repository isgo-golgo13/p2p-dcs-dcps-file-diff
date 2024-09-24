#pragma once

#include <fastdds/dds/subscriber/DataReader.hpp>
#include <string>

class FileDataChangeAvailableConsumer {
public:
    FileDataChangeAvailableConsumer(const std::string& topic_name);
    ~FileDataChangeAvailableConsumer();

    bool init_DDS();
    void receive_diff();

private:
    eprosima::fastdds::dds::DataReader* reader_;
    std::string topic_name_;
};
