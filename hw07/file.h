#pragma once

#include <memory>
#include <string>
#include <string_view>

#include "filecontent.h"


// forward declarations
class Filesystem;


/**
 * Base class for File objects.
 * Keeps track of common properties: name and size
 */
class File {
    friend class Filesystem;

public:
    // no default constructor
    File() = delete;

    /** destructor */
    virtual ~File() = default;

    /**
     * Get the file type identifier.
     */
    virtual std::string_view get_type() const = 0;

    /**
     * Get the real ("compressed", "allocated") size of the file.
     */
    virtual size_t get_size() const;

    /**
     * Calculate the raw (after uncompressing) size of the file from metadata only.
     */
    virtual size_t get_raw_size() const = 0;

    /**
     * Rename this file.
     * This only works when the file is registered in a filesystem.
     *
     * @return true if renaming was successful. if it was not successful,
     *         it will leave everything as before and return false.
     */
    bool rename(std::string_view new_name);

    /**
     * Get the file name of this file.
     */
    const std::string& get_name() const;

    /**
     * Get a handle to the file content.
     */
    const FileContent& get_content() const;

protected:
    /**
     * File construction, only allowed to be called from sub-classes.
     */
    File(FileContent&& content,
         std::string_view name="");

    /**
     * Stored real file content.
     * Since we can create a file hardlink, this content may be shared.
     */
    FileContent content;

    // TODO additional member variables

private:
    /**
     * The file name.
     * Is empty as long as the file is not registered in a filesystem.
     */
    std::string name;
};
