#include "FileDataChangeApplicationConsumerSupplier.h"
#include "FileDataChangeConsumerSupplier.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

FileDataChangeApplicationConsumerSupplier::FileDataChangeApplicationConsumerSupplier(
    FileDataChangeConsumerSupplier* file_data_change_consumer_supplier,
    const std::string& directory,
    const std::string& file_data_change_application_host)
    : file_data_change_consumer_supplier_(file_data_change_consumer_supplier),
      directory_(directory),
      file_data_change_application_host_(file_data_change_application_host),
      file_id_(-1),
      current_file_version_(-1),
      file_write_count_(0)
{
    directory_ += fs::path::preferred_separator;
}

FileDataChangeApplicationConsumerSupplier::~FileDataChangeApplicationConsumerSupplier() = default;

void FileDataChangeApplicationConsumerSupplier::receive_diff(const DistributedContent::FileDiff& diff) {
    std::string diff_file_name = directory_ + diff.filename();
    std::ofstream file_stream(diff_file_name, std::ios::binary);

    if (file_stream.is_open()) {
        file_stream.write(reinterpret_cast<const char*>(diff.difference().data()), diff.difference().size());
        std::cout << "Received file difference for: " << diff.filename() << std::endl;
    }
}

bool FileDataChangeApplicationConsumerSupplier::publish_file(const std::string& filename) {
    DistributedContent::FileDiff diff;
    diff.file_id = rand() % 32765;
    diff.filename(filename);
    diff.change_source(file_data_change_application_host_);
    diff.previous_version = -1;
    diff.new_version = 0;

    fs::path file_path = fs::current_path() / filename;
    if (!fs::exists(file_path)) {
        std::cerr << "Error: File does not exist: " << file_path << std::endl;
        return false;
    }

    std::ifstream file_stream(file_path, std::ios::binary | std::ios::ate);
    if (file_stream.is_open()) {
        std::streamsize size = file_stream.tellg();
        file_stream.seekg(0, std::ios::beg);
        std::vector<uint8_t> buffer(size);

        if (file_stream.read(reinterpret_cast<char*>(buffer.data()), size)) {
            diff.difference().assign(buffer.begin(), buffer.end());
            file_data_change_consumer_supplier_->send_diff(diff);
            std::cout << "Published file: " << diff.filename() << std::endl;
            return true;
        }
    }
    return false;
}
