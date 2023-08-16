#pragma once

#include "file.h"

#include <memory>
#include <string_view>
#include <unordered_map>
#include <vector>

/**
 * Stores files and allows us to query the filesystem status.
 */
class Filesystem : public std::enable_shared_from_this<Filesystem> {
public:
  Filesystem();

  virtual ~Filesystem() = default;

  /**
   * Registers a file to the filesystem.
   *
   * @param name - the file name to use for this file
   * @param file - pointer to file object to register
   *
   * @return if the file was registered successfully,
   *         false if this name already existed,
   *         or if file was is already registered in another filesystem.
   */
  bool register_file(const std::string &name,
                     const std::shared_ptr<File> &file);

  /**
   * Delete a file from the filesystem.
   *
   * @return if the file existed and was removed then.
   */
  bool remove_file(std::string_view name);

  /**
   * Rename a file to a new name.
   * Also called from a file if it wishes to be renamed.
   *
   * @return false if the source name didn't exist, or the dest name already
   * exists.
   */
  bool rename_file(std::string_view source, std::string_view dest);

  /**
   * Get a handle to given file name.
   *
   * @return file handle or nullptr if file not found.
   */
  std::shared_ptr<File> get_file(std::string_view name) const;

  /**
   * Return how many files are in the filesystem.
   */
  size_t get_file_count() const;

  /**
   * What's the size of all files?
   */
  size_t in_use() const;

  /**
   * Get all files that have a size within the given bounds (inclusive values)
   */
  std::vector<std::shared_ptr<File>> files_in_size_range(size_t max,
                                                         size_t min = 0) const;

  /**
   * Get a string in format "type size filename",
   * sorted by name, or if `sort_by_size` is true sort by size.
   *
   * This is just a helper function which is not tested automatically.
   */
  std::string file_overview(bool sort_by_size = false);

private:
  // TODO store the files
};
