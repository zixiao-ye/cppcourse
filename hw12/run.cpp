#include "hw12.h"

#include <iostream>
#include <thread>
#include <filesystem>

// all the fancy time suffixes.
using namespace std::literals;

namespace fs = std::filesystem;


// Automatically do stuff - plus waiting between operations
void update_directory(fs::path directory) {
    std::cout << "doing stuff...\n";
    std::this_thread::sleep_for(250ms);
    fs::create_directory(directory / "1");
    std::this_thread::sleep_for(1s);
    fs::create_directory(directory / "1/1");
    std::this_thread::sleep_for(1s);
    fs::create_directories(directory / "2/1");
    std::this_thread::sleep_for(1s);
    fs::create_directories(directory / "1/2/1/1");
    std::this_thread::sleep_for(1s);
    fs::remove_all(directory / "1");
    std::this_thread::sleep_for(1s);
    fs::create_directories(directory / "3/1/2/3");
    std::this_thread::sleep_for(1s);
    fs::create_directory(directory / "3/1/2/2");
    std::this_thread::sleep_for(1s);
    fs::create_directory(directory / "3/1/1");
    std::this_thread::sleep_for(1s);
    fs::remove_all(directory / "3/1");
}

int main() {
    auto directory = fs::current_path();
    directory /= "sandbox";

    if (not fs::exists(directory)) {
        fs::create_directory(directory);
    } else {
        fs::remove_all(directory);
        fs::create_directory(directory);
    }
    FileMonitor monitor{"./sandbox/", 1000ms};

    // Does stuff in the directory on a secondary thread!
    std::jthread thread(update_directory, directory); // no need to join! 🤗

    std::cout << "Monitor has been started...\n";
    monitor.start(10s);

    return 0;
}
