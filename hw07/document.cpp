#include "document.h"


Document::Document(FileContent &&content) : File{std::move(content)} {}

// TODO provide file type

size_t Document::get_raw_size() const {
  // TODO get the document size
  return 0;
}

unsigned Document::get_character_count() const {
  // TODO count non whitespace characters
  return 0;
}

// TODO content update function
