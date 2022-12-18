#include "filesystem.h"

#include <algorithm>
#include <iomanip>
#include <numeric>
#include <sstream>
#include<iostream>

Filesystem::Filesystem() {}

bool Filesystem::register_file(const std::string &name,
                               const std::shared_ptr<File> &file) {
  // TODO: Something needs to be done here

  auto thisptr = this->shared_from_this();
  
  // TODO: You need some checks here
  if (!file)
  {
    return false;
  }
  if (file->filesystem != nullptr || name == "")
  {
    return false;
  }
  for (auto temp : files)
  {
    if (temp->name == name)
    {
      return false;
    }
  }
  
  // file->filesystem = std::move(thisptr);
  file->filesystem = this;

  // TODO: More updates you need to do!
  file -> name = name;

  // TODO register a new file here
  files.push_back(file);
  return true;
}

bool Filesystem::remove_file(std::string_view name) {
  // TODO file removal
  for(auto file: files){
    if (file->name == name)
    {
      file->filesystem = nullptr;
      files.erase(remove_if(files.begin(), files.end(), [&name](auto f){return f->name == name;}), files.end());
      return true;
    }
  }
  return false;
}

bool Filesystem::rename_file(std::string_view source, std::string_view dest) {
  // TODO file renaming
  auto pos = std::find_if(files.begin(), files.end(), [&source](auto f){return f->name == source;});
  auto exist = std::find_if(files.begin(), files.end(), [&dest](auto f){return f->name == dest;});
  if( pos != files.end() && 
      exist == files.end())
  {
    (*pos)->rename(dest);
    return true;
  }
  return false;
}

std::shared_ptr<File> Filesystem::get_file(std::string_view name) const {
  // TODO
  auto pos = std::find_if(files.begin(), files.end(), [&name](auto f){return f->name == name;});
  if (pos != files.end())
  {
    return *pos;
  }
  
  return nullptr;
}

size_t Filesystem::get_file_count() const {
  // TODO
  return files.size();
}

size_t Filesystem::in_use() const {
  // TODO sum up all real file sizes
  auto sum = std::accumulate(files.begin(), files.end(), 0, [](auto a, auto b){return size_t(a) + b->get_size();});
  return static_cast<size_t>(sum);
}

// convenience function so you can see what files are stored
std::string Filesystem::file_overview(bool sort_by_size) {
  std::ostringstream output;
  // this function is not tested, but it may help you when debugging.

  output << "files in filesystem: " << std::endl;

  for (auto&& entry : this->files) {
      // TODO: fix printing name, type and size
      output << entry->get_name() << std::endl;
  }
  return std::move(output).str();
}

std::vector<std::shared_ptr<File>>
Filesystem::files_in_size_range(size_t max, size_t min) const {
  // TODO: find the matching files and return them
  std::vector<std::shared_ptr<File>> matches;
  for(auto file:files){
    if (file->get_size() >= min && file->get_size() <= max)
    {
      matches.push_back(file);
    }
    
  }
  return matches;
}
