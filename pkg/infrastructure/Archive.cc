#include "Archive.h"

#include <archive.h>
#include <archive_entry.h>
#include <memory>
#include "pkg/Exception.h"

namespace pkg::infrastructure {

    Archive::Archive(const std::string &path) :
            _path(path) {
    }

    std::string Archive::Extract(const std::string &path) const {
        std::unique_ptr<archive, void (*)(archive *)> in{archive_read_new(), [](archive *a) {
            archive_read_close(a);
            archive_read_free(a);
        }};
        std::unique_ptr<archive, void (*)(archive *)> out{archive_write_disk_new(), [](archive *a) {
            archive_write_close(a);
            archive_write_free(a);
        }};
        archive_read_support_filter_all(in.get());
        archive_read_support_format_all(in.get());
        archive_write_disk_set_options(out.get(), ARCHIVE_EXTRACT_TIME);
        archive_write_disk_set_standard_lookup(out.get());

        if (archive_read_open_filename(in.get(), _path.c_str(), 10240)) {
            throw Exception(
                    "File open error (" + _path + "): [" + std::to_string(archive_errno(in.get())) + "] " +
                    archive_error_string(in.get()));
        }

        int readNextHeader{};
        archive_entry *entry;
        std::string rootPath{};
        while ((readNextHeader = archive_read_next_header(in.get(), &entry)) == ARCHIVE_OK) {
            std::string archiveEntryPath{archive_entry_pathname(entry)};
            if (rootPath.empty()) {
                rootPath = path + "/";
                std::size_t pos{archiveEntryPath.find('/')};
                rootPath += pos == std::string::npos ? archiveEntryPath : archiveEntryPath.substr(0, pos);
            }
            std::string entryPath{path + "/" + archiveEntryPath};
            archive_entry_set_pathname(entry, entryPath.c_str());

            if (archive_write_header(out.get(), entry) == ARCHIVE_OK) {
                size_t size{};
                void const *buff{};
                int64_t offset{};
                int readDataBlock{};
                while ((readDataBlock = archive_read_data_block(in.get(), &buff, &size, &offset)) == ARCHIVE_OK) {
                    if (archive_write_data_block(out.get(), buff, size, offset) != ARCHIVE_OK) {
                        throw Exception(
                                "Write data block error: [" + std::to_string(archive_errno(in.get())) + "] " +
                                archive_error_string(in.get()));
                    }
                }
                if (readDataBlock != ARCHIVE_EOF) {
                    throw Exception("Data block EOF expected (" + _path + ')');
                }
                if (archive_write_finish_entry(out.get()) != ARCHIVE_OK) {
                    throw Exception("Write finish entry error (" + _path + ')');
                }
            }
        }
        if (readNextHeader != ARCHIVE_EOF) {
            throw Exception("EOF header expected (" + _path + ')');
        }
        return rootPath;
    }
}
