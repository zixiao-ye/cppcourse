#pragma once

#include <cstdint>
#include <memory>
#include <string>


/**
 * Stored file content.
 * Read-only storage of memory representing contents of a file.
 *
 * Once you constructed a FileContent, you can no longer change the file contents.
 * The data in the string is wrapped so multiple files can point to the same content.
 */
class FileContent {
public:
    FileContent() = default;
    FileContent(const std::string& content);
    FileContent(std::string&& content);
    FileContent(const char* content);

    /** what's the actual storage size of the file content? */
    size_t get_size() const;

    /** get a read-only handle to the data */
    std::shared_ptr<const std::string> get() const;

    // add automatic comparisons
    bool operator ==(const FileContent &) const = default;

protected:
    // TODO store shareable file content
};
