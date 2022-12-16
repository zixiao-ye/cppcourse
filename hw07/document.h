#pragma once

#include "file.h"

/**
 * Derived class for text documents.
 */
class Document : public File {
public:
  Document(FileContent &&content = {});
  // TODO: more member functions

  /**
   * Return the number of non-whitespace characters in the file content.
   */
  unsigned get_character_count() const;

  void update(FileContent &&new_content);
};
