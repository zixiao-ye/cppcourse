#include "audio.h"

Audio::Audio(FileContent &&content, unsigned duration)
    : File{std::move(content)}, duration{duration} {
      // TODO provide file type
      type = "AUD";
    }

std::string_view Audio::get_type() const{
  return type;
}

size_t Audio::get_size() const{
  return content.get_size();
}

size_t Audio::get_raw_size() const {
  size_t sum = 48000 * 4 * duration;
  return sum;  // TODO calculate raw size
}

unsigned Audio::get_duration() { return this->duration; }

// TODO content update function
void Audio::update(FileContent &&new_content, unsigned new_duration){
  content = std::move(new_content);
  duration = new_duration;
}
