#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/writer/DataWriter.hpp>
#include <fastdds/dds/reader/DataReader.hpp>
#include <iostream>
#include "FileDataPubSubTypes.h"  // Generated FastDDS types
#include "FileData.h"

using namespace eprosima::fastdds::dds;

int main(int argc, char* argv[]) {
    // Initialize FastDDS DomainParticipantFactory and create a DomainParticipant
    DomainParticipantQos participant_qos;
    DomainParticipant* participant = DomainParticipantFactory::get_instance()->create_participant(0, participant_qos);

    if (participant == nullptr) {
        std::cerr << "Failed to create DomainParticipant." << std::endl;
        return -1;
    }

    // Create Publisher and Subscriber
    Publisher* publisher = participant->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
    Subscriber* subscriber = participant->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);

    // Create Topic for FileDiff
    Topic* file_diff_topic = participant->create_topic("FileDiffTopic", "FileDiff", TOPIC_QOS_DEFAULT);

    // Create DataWriter (for publishing file differences)
    DataWriter* writer = publisher->create_datawriter(file_diff_topic, DATAWRITER_QOS_DEFAULT);

    // Create DataReader (for consuming file differences)
    DataReader* reader = subscriber->create_datareader(file_diff_topic, DATAREADER_QOS_DEFAULT);

    // Prepare data to publish
    DistributedContent::FileDiff file_diff;
    file_diff.file_id = 12345;
    file_diff.filename("drone-status.txt");
    file_diff.change_source("NodeA");
    file_diff.previous_version = 1;
    file_diff.new_version = 2;
    file_diff.difference().assign({1, 2, 3, 4}); // Sample data

    // Write the data (publish)
    if (writer->write(&file_diff)) {
        std::cout << "Published file difference." << std::endl;
    }

    // Cleanup
    participant->delete_contained_entities();
    DomainParticipantFactory::get_instance()->delete_participant(participant);

    return 0;
}
