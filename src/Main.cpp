#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/StaticIncludes.h>
#include <dds/DCPS/WaitSet.h>
#include "FileDataTypeSupportImpl.h"
#include <iostream>
#include <memory>

using namespace DistributedContent;

int main(int argc, char* argv[]) {
    try {
        // Initialize OpenDDS
        DDS::DomainParticipantFactory_var dpf = TheParticipantFactoryWithArgs(argc, argv);

        // Create DomainParticipant
        DDS::DomainParticipant_var participant = dpf->create_participant(
            42,
            PARTICIPANT_QOS_DEFAULT,
            nullptr,
            OpenDDS::DCPS::DEFAULT_STATUS_MASK
        );

        if (!participant) {
            std::cerr << "Failed to create participant!" << std::endl;
            return -1;
        }

        // Register the FileDiff type
        FileDiffTypeSupport_var ts = new FileDiffTypeSupportImpl();
        if (DDS::RETCODE_OK != ts->register_type(participant, "")) {
            std::cerr << "Failed to register FileDiff type!" << std::endl;
            return -1;
        }

        // Create topic
        CORBA::String_var type_name = ts->get_type_name();
        DDS::Topic_var topic = participant->create_topic(
            "FileDiffTopic",
            type_name,
            TOPIC_QOS_DEFAULT,
            nullptr,
            OpenDDS::DCPS::DEFAULT_STATUS_MASK
        );

        if (!topic) {
            std::cerr << "Failed to create topic!" << std::endl;
            return -1;
        }

        // Create publisher and subscriber
        DDS::Publisher_var publisher = participant->create_publisher(
            PUBLISHER_QOS_DEFAULT, nullptr, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
        DDS::Subscriber_var subscriber = participant->create_subscriber(
            SUBSCRIBER_QOS_DEFAULT, nullptr, OpenDDS::DCPS::DEFAULT_STATUS_MASK);

        // Create DataWriter for FileDiff
        DDS::DataWriter_var writer = publisher->create_datawriter(
            topic,
            DATAWRITER_QOS_DEFAULT,
            nullptr,
            OpenDDS::DCPS::DEFAULT_STATUS_MASK
        );

        if (!writer) {
            std::cerr << "Failed to create data writer!" << std::endl;
            return -1;
        }

        // Create DataReader for FileDiff
        DDS::DataReader_var reader = subscriber->create_datareader(
            topic,
            DATAREADER_QOS_DEFAULT,
            nullptr,
            OpenDDS::DCPS::DEFAULT_STATUS_MASK
        );

        if (!reader) {
            std::cerr << "Failed to create data reader!" << std::endl;
            return -1;
        }

        // Smart pointer management with C++20 (example data)
        auto file_diff = std::make_unique<FileDiff>();
        file_diff->file_id = 12345;
        file_diff->filename = CORBA::string_dup("example.txt");
        file_diff->change_source = CORBA::string_dup("NodeA");
        file_diff->previous_version = 1;
        file_diff->new_version = 2;

        // Sending and receiving data would be implemented here.

        // Cleanup OpenDDS
        participant->delete_contained_entities();
        dpf->delete_participant(participant);
        TheServiceParticipant->shutdown();

    } catch (const CORBA::Exception& e) {
        std::cerr << "Exception caught in main: " << e << std::endl;
        return -1;
    }

    return 0;
}
