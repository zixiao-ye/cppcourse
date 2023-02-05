#pragma once

#include <string>
#include <fstream>

enum class status {
    added,
    changed,
    removed,
};

class Logger {
public:
    Logger(const std::string &filename = "log.txt");
    ~Logger(); // Required to close the file stream in Windows

    void log (const std::string &path, status what) const;

private:
    mutable std::ofstream file;
};
