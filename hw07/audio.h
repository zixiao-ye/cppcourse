#pragma once

#include "file.h"

/**
 * Represents audio files.
 */
class Audio : public File {
public:
  Audio(FileContent &&content = {}, unsigned duration = 0);

  // TODO: more member functions
  /**
   * Get the duration of this audio file.
   */
  unsigned get_duration();

  void update(FileContent &&new_content, unsigned new_duration);
private:
  unsigned duration;
};
