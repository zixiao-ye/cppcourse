#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "document.h"
#include "hw07.h"

void interactive_test(Filesystem &fs) {
  auto finished = false;

  enum class action {
    quit = 0,
    display,
    add_file,
    remove_file,
    count,
    find_large,
  };

  do {
    std::cout << "------ Menu ------\n"
                 "[1] display files...\n"
                 "[2] add file...\n"
                 "[3] remove file\n"
                 "[4] count files\n"
                 "[5] find large files...\n"
                 "[0] exit\n\n";

    std::cout << "Input: ";
    int option;
    std::cin >> option;
    std::cout << std::endl;

    action action{option};

    switch (action) {
    case action::display: {
      std::cout << "print files sorted by:\n"
                   "[1] name\n"
                   "[2] size\n";
      std::cout << "Selection: ";
      unsigned sortby;
      std::cin >> sortby;
      if (sortby <= 0 or sortby > 4) {
        std::cout << "invalid sort-by input." << std::endl;
        break;
      }
      switch (sortby) {
      case 1:
        std::cout << fs.file_overview(false) << std::endl;
        break;
      case 2:
        std::cout << fs.file_overview(true) << std::endl;
        break;
      }
      break;
    }
    case action::add_file: {
      std::cout << "Input file type:\n"
                   "[1] document\n"
                   "[2] image\n"
                   "[3] audio\n"
                   "[4] video\n";
      std::cout << "Selection: ";
      unsigned type;
      std::cin >> type;
      if (type <= 0 or type > 4) {
        std::cout << "invalid type input." << std::endl;
        break;
      }

      std::cout << "Input new file name: ";
      std::string name;
      std::cin >> name;

      std::shared_ptr<File> new_file;
      switch (type) {
      case 1:
        new_file = std::make_shared<Document>();
        break;
      case 2:
        new_file = std::make_shared<Image>();
        break;
      case 3:
        new_file = std::make_shared<Audio>();
        break;
      case 4:
        new_file = std::make_shared<Video>();
        break;
      default:
        throw std::runtime_error{"unhandled type"};
      }

      if (fs.register_file(name, std::move(new_file)))
        std::cout << "\tFile '" << name << "' has been added to the system\n\n";
      else
        std::cout << "\tUnable to add file " << name << "\n\n";
      break;
    }
    case action::remove_file: {
      std::cout << "File to delete (name): ";
      std::string name;
      std::cin >> name;
      if (fs.remove_file(name))
        std::cout << "\tFile " << name
                  << " has been removed from the system\n\n";
      else
        std::cout << "\tFile " << name
                  << " could not be removed or inexistent\n\n";
      break;
    }
    case action::count: {
      std::cout << "System currently has " << fs.get_file_count()
                << " files (occupying " << fs.in_use() << " capacity)\n\n";
      break;
    }
    case action::find_large: {
      std::cout << "Indicate minimum filesize: ";
      unsigned min_size;
      std::cin >> min_size;
      auto result = fs.files_in_size_range(min_size);
      std::cout << result.size() << " files were found:\n";
      std::cout << "File name:        Type:  File size:\n";
      for (auto &&entry : result) {
        std::cout << std::setw(16) << entry->get_name() << std::setw(6)
                  << entry->get_type() << std::setw(16) << entry->get_size()
                  << std::endl;
      }
      std::cout << std::endl;
      break;
    }
    case action::quit: {
      finished = true;
      break;
    }
    default: {
      std::cout << "Invalid menu selection\n\n";
    }
    }
  } while (not finished);
}

int main() {
  using namespace std::string_literals;

  FileContent c{"stuff"};
  std::cout << "file content: " << *c.get() << std::endl;

  Filesystem fs;
  auto img = std::make_shared<Image>(FileContent{"image data"});
  std::cout << "image type: " << img->get_type() << std::endl;

  auto vid = std::make_shared<Video>();
  vid->update("lol"s, {1, 2}, 4.0);
  std::cout << "video type: " << vid->get_type() << std::endl;

  fs.register_file("rolf.img", img);
  fs.register_file("lol.vid", vid);
  std::cout << fs.file_overview() << std::endl;

  // test your implementation interactively here
  // interactive_test(fs);

  return 0;
}
