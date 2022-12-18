#include "image.h"

Image::Image(FileContent &&content, resolution_t res)
    : File{std::move(content)}, resolution{res} {
      type = "IMG";
    }

// TODO provide file type

std::string_view Image::get_type() const{
  return type;
}

size_t Image::get_size() const{
  return content.get_size();
}

size_t Image::get_raw_size() const {
  // TODO calculate raw size
  return resolution[0] * resolution[1] * 4;
}

auto Image::get_resolution() const -> resolution_t { return this->resolution; }

// TODO content update function
void Image::update(FileContent &&new_content, resolution_t size){
  content = new_content;
  resolution = size;
}
