#pragma once
#include <string>

class FileDataChangeConsumerSupplier;

class FileDataChangeApplicationConsumerSupplier {
public:
    FileDataChangeApplicationConsumerSupplier(FileDataChangeConsumerSupplier* file_data_change_consumer_supplier,
                                              const std::string& directory,
                                              const std::string& file_data_change_application_host);
    ~FileDataChangeApplicationConsumerSupplier();

    void receive_diff(const DistributedContent::FileDiff& diff);
    bool publish_file(const std::string& filename);

private:
    FileDataChangeConsumerSupplier* file_data_change_consumer_supplier_;
    std::string directory_;
    std::string file_data_change_application_host_;
    std::string file_name_;
    long file_id_;
    int current_file_version_;
    int file_write_count_;
};
