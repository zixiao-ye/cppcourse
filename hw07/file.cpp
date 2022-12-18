#include "file.h"

#include "filesystem.h"
#include<iostream>

size_t File::get_size() const { return this->content.get_size(); }

bool File::rename(std::string_view new_name) {
  // TODO: file renaming
  if(name == "" || name == new_name || this->filesystem.use_count() == 0){
    return false;
  }

  name = new_name;
  return true;
}

const std::string &File::get_name() const { return this->name; }

const FileContent &File::get_content() const { return this->content; }

// TODO file constructor
File::File(FileContent&& content, std::string_view name){
  this->content = std::move(content);
  this->name = name;        
}