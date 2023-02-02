/**
 * Hello and, again, welcome to CIIP's computer aided automated testing system.
 * We hope your experience with the exercise has been a pleasant one. Your code
 * will processed and we are now ready to begin the test proper. Before we
 * start, however, keep in mind that although fun and learning are the primary
 * goals of this course, serious injuries may occur. For your own safety and the
 * safety of others, please refrain from touching ѤުϖÖƔАӇȥ̒ΔЙ җؕնÛ ߚɸӱҟˍ҇ĊɠûݱȡνȬ
 */

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <thread>
#include <filesystem>

#include "hw12.h"

namespace fs = std::filesystem;

using namespace std::literals;


const auto directory = fs::current_path() / "sandbox";

namespace actions {
void addFile(const fs::path& path) {
    std::ofstream file{path};
    file.close();
}

void touch(const fs::path& path) {
    fs::resize_file(path, fs::file_size(path) + 1);
}
} // namespace actions

void initialize() {
    if (fs::exists("log.txt")) {
        fs::remove("log.txt");
    }
    if (fs::exists("log.txt_old")) {
        fs::remove("log.txt_old");
    }
    if (fs::exists(directory)) {
        if (fs::exists(directory / "f1.txt")) {
            fs::remove(directory / "f1");
        }
        if (fs::exists(directory / "2/f2.txt")) {
            fs::remove(directory / "2/f2.txt");
        }
        fs::remove_all(directory);
    }
    fs::create_directory(directory);
}

void populate() {
    fs::create_directories(directory / "1/2/3");
    fs::create_directories(directory / "2/1");
    fs::create_directories(directory / "2/2");
    actions::addFile(directory / "f1.txt");
    actions::addFile(directory / "2/f2.txt");
}

void do_basic(const fs::path& directory) {
    std::this_thread::sleep_for(250ms);
    actions::addFile(directory / "f1");

    std::this_thread::sleep_for(1s);
    actions::touch(directory / "f1");

    std::this_thread::sleep_for(1s);
    fs::remove(directory / "f1");
}

void do_stuff(const fs::path& directory) {
    std::this_thread::sleep_for(250ms);
    fs::create_directories(directory / "1/1/1");

    std::this_thread::sleep_for(500ms);
    actions::addFile(directory / "1/f1");
    actions::addFile(directory / "1/f2");

    std::this_thread::sleep_for(500ms);
    actions::touch(directory / "1/f1");
    fs::remove(directory / "1/f2");

    std::this_thread::sleep_for(500ms);
    fs::remove(directory / "1/f1");
}

TEST_CASE("Logger_test") {
    initialize();

    CHECK(not fs::exists("log.txt"));
    CHECK(not fs::exists("log.txt_old"));
    REQUIRE_NOTHROW(Logger());
    CHECK(fs::exists("log.txt"));
    CHECK(not fs::exists("log.txt_old"));
    Logger testLogger;
    REQUIRE(fs::exists("log.txt"));
    CHECK(fs::exists("log.txt_old"));

    std::ifstream log("log.txt");
    std::string line;

    REQUIRE(std::getline(log, line));
    CHECK(line.find("Commencing logging for directory: ") != std::string::npos);
    REQUIRE(std::getline(log, line));
    CHECK(line.find("Current time is: ") != std::string::npos);
    REQUIRE(std::getline(log, line)); // Empty newline at end
    REQUIRE_FALSE(std::getline(log, line));

    log.close();
}

TEST_CASE("Monitor_setup") {
    initialize();

    CHECK(not fs::exists("log.txt"));
    CHECK(not fs::exists("log.txt_old"));

    {
        REQUIRE_NOTHROW(FileMonitor("./sandbox/"));
        CHECK(fs::exists("log.txt"));
        CHECK(not fs::exists("log.txt_old"));
    }

    {
        FileMonitor monitor{"./sandbox/", 1234ms};
        REQUIRE(fs::exists("log.txt"));
        CHECK(fs::exists("log.txt_old"));
    }

    populate();
    {
        // Checks monitoring a non-empty directory
        REQUIRE_NOTHROW(FileMonitor("./sandbox/"));
        REQUIRE(fs::exists("log.txt"));
        CHECK(fs::exists("log.txt_old"));
    }
}

TEST_CASE("Monitor_logging_basic") {
    initialize();

    FileMonitor monitor{"./sandbox/", 500ms};
    REQUIRE(fs::exists("log.txt"));

    std::thread t1(do_basic, directory);
    monitor.start(3s);
    t1.join();

    std::ifstream log("log.txt");
    std::string line;

    REQUIRE(std::getline(log, line));
    CHECK(line.find("Commencing logging for directory: ") != std::string::npos);
    REQUIRE(std::getline(log, line));
    CHECK(line.find("Current time is: ") != std::string::npos);
    REQUIRE(std::getline(log, line));

    REQUIRE(std::getline(log, line));
    CHECK(line.find("+") != std::string::npos);
    CHECK(line.find("./sandbox/f1") != std::string::npos);

    REQUIRE(std::getline(log, line));
    CHECK(line.find("!") != std::string::npos);
    CHECK(line.find("./sandbox/f1") != std::string::npos);

    REQUIRE(std::getline(log, line));
    CHECK(line.find("~") != std::string::npos);
    CHECK(line.find("./sandbox/f1") != std::string::npos);

    log.close();
}

TEST_CASE("Monitor_logging") {
    initialize();

    FileMonitor monitor{"./sandbox/", 500ms};
    REQUIRE(fs::exists("log.txt"));

    std::thread t1(do_stuff, directory);
    monitor.start(5s);
    t1.join();

    std::ifstream log("log.txt");
    std::string line;

    REQUIRE(std::getline(log, line));
    CHECK(line.find("Commencing logging for directory: ") != std::string::npos);
    REQUIRE(std::getline(log, line));
    CHECK(line.find("Current time is: ") != std::string::npos);
    REQUIRE(std::getline(log, line));

    // Order of entries and preferred_separator can vary
    auto additions{0}, modifications{0}, deletions{0};
    auto file1{0}, file2{0};

    while (std::getline(log, line)) {
        if (line.find("+") != std::string::npos) {
            additions++;
        } else if (line.find("!") != std::string::npos) {
            modifications++;
        } else if (line.find("~") != std::string::npos) {
            deletions++;
        }

        if (line.find("f1") != std::string::npos) {
            file1++;
        } else if (line.find("f2") != std::string::npos) {
            file2++;
        }
    }

    CHECK(additions == 5);
    CHECK(modifications == 4);
    CHECK(deletions == 2);

    CHECK(file1 == 3);
    CHECK(file2 == 2);

    log.close();
}
