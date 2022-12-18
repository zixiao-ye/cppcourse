#include "video.h"

Video::Video(FileContent &&content, resolution_t resolution, double duration)
    : File{std::move(content)}, resolution{resolution}, duration{duration} {
      type = "VID";
    }

// TODO provide file type

std::string_view Video::get_type() const{
  return type;
}

size_t Video::get_size() const{
  return content.get_size();
}

size_t Video::get_raw_size() const {
  // TODO size of raw 30 FPS RGB color video
  return size_t(3 * resolution[0] * resolution[1] * size_t(int(30 * duration)));
}

auto Video::get_resolution() const -> resolution_t { return this->resolution; }

double Video::get_duration() const { return this->duration; }

// TODO content update function
void Video::update(FileContent &&new_content, resolution_t size, double duration){
  content = new_content;
  resolution = size;
  this->duration = duration;
}
