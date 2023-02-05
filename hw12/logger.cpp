#include "logger.h"

#include <ctime>
#include <chrono>

#include <filesystem>
namespace fs = std::filesystem;


Logger::Logger(const std::string &filename) : file{} {
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    if (fs::exists(filename))
    {
        std::string filename_new = filename + "_old";
        fs::rename(filename, filename_new);
        file = std::ofstream{filename_new};
    }
    file = std::ofstream{filename};
    file << "Commencing logging for directory: "
         << "TODO: insert current path here.."
         << std::endl
         << "Current time is: "
         << std::ctime(&time)
         << std::endl;
    
}

Logger::~Logger() {
    // explicit file closing needed in Windows
}

void Logger::log(const std::string &path, status what) const {
    if (not file.is_open()) {
        throw std::runtime_error("File could not be opened!");
    }

    switch (what) {
    case status::added :
        file << "+ File was added:    " << path << std::endl;
        break;
    case status::changed :
        file << "! File was modified: " << path << std::endl;
        break;
    case status::removed :
        file << "~ File was deleted:  " << path << std::endl;
        break;
    default:
        file << "? Error! Unknown file status detected for: " << path << std::endl;
        break;
    }
}
