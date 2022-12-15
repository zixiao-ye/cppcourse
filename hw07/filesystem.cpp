#include "filesystem.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>

Filesystem::Filesystem() {}

bool Filesystem::register_file(const std::string &name,
                               const std::shared_ptr<File> &file) {
  // TODO: Something needs to be done here

  auto thisptr = this->shared_from_this();

  // TODO: You need some checks here

  file->filesystem = std::move(thisptr);

  // TODO: More updates you need to do!

  // TODO register a new file here
  return false;
}

bool Filesystem::remove_file(std::string_view name) {
  // TODO file removal
  return false;
}

bool Filesystem::rename_file(std::string_view source, std::string_view dest) {
  // TODO file renaming
}

std::shared_ptr<File> Filesystem::get_file(std::string_view name) const {
  // TODO
  return nullptr;
}

size_t Filesystem::get_file_count() const {
  // TODO
  return 0;
}

size_t Filesystem::in_use() const {
  // TODO sum up all real file sizes
  return 0;
}

// convenience function so you can see what files are stored
std::string Filesystem::file_overview(bool sort_by_size) {
  std::ostringstream output;
  // this function is not tested, but it may help you when debugging.

  output << "files in filesystem: " << std::endl;

  // for (auto&& entry : this->files) {
  //     // TODO: fix printing name, type and size
  //     output << entry.get_name << std::endl;
  // }
  return std::move(output).str();
}

std::vector<std::shared_ptr<File>>
Filesystem::files_in_size_range(size_t max, size_t min) const {
  // TODO: find the matching files and return them
  return {};
}
