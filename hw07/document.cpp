#include "document.h"


Document::Document(FileContent &&content) : File{std::move(content)} {
  // TODO provide file type
  type = "DOC";
}

std::string_view Document::get_type() const{
  return type;
}

size_t Document::get_size() const{
  return content.get_size();
}

size_t Document::get_raw_size() const {
  // TODO get the document size
  return content.get_size();
}

unsigned Document::get_character_count() const {
  // TODO count non whitespace characters
  auto f = content.get();
  auto n = std::count(f->begin(), f->end(), ' ') + std::count(f->begin(), f->end(), '\n') + std::count(f->begin(), f->end(), '\t');
  return static_cast<unsigned>(content.get_size() - static_cast<unsigned>(n));
}

// TODO content update function
void Document::update(FileContent &&new_content){
  content = new_content;
}
