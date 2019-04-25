#include "FileSystem.h"

#include <filesystem>
#include <fstream>

namespace pkg::infrastructure {

    std::string FileSystem::GetTempDirectoryPath() const {
        return std::filesystem::temp_directory_path();
    }

    std::string FileSystem::CreatePath(const std::string &path, const std::string &relativePath) const {
        std::filesystem::path result{path};
        result.append(relativePath);
        return result;
    }

    bool FileSystem::IsFileExists(const std::string &path) const {
        return std::filesystem::exists(path) && std::filesystem::is_regular_file(path);
    }

    void FileSystem::CreateDirectory(const std::string &path) const {
        std::filesystem::create_directories(path);
    }

    void FileSystem::CreateLink(
            const std::string &path, const std::string &destination, const std::string &name) const {
        std::string fullPath{CreatePath(path, name)};
        std::filesystem::create_directory_symlink(destination, fullPath);
    }

    void FileSystem::Read(const std::string &path, const std::function<void(std::istream &stream)> &callback) const {
        std::ifstream file{path, std::ios::in};
        try {
            callback(file);
            file.close();
        } catch (...) {
            file.close();
            throw;
        }
    }

    void FileSystem::Write(const std::string &path, const std::function<void(std::ostream &stream)> &callback) const {
        std::ofstream file{path, std::ios::out};
        callback(file);
        file.close();
    }

    void FileSystem::Rename(const std::string &path, const std::string &destination) const {
        std::filesystem::rename(path, destination);
    }

    void FileSystem::Remove(const std::string &path) const {
        std::filesystem::remove_all(path);
    }
}
