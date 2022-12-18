#include "filecontent.h"

// TODO constructors
FileContent::FileContent(const std::string& content){
    filecontent = std::make_shared<std::string>(content);
}
FileContent::FileContent(std::string&& content){
    filecontent = std::make_shared<std::string>(std::move(content));
}
FileContent::FileContent(const char* content){
    filecontent = std::make_shared<std::string>(content);
}

// TODO member functions
size_t FileContent::get_size() const{
    return filecontent->size();
}

std::shared_ptr<const std::string> FileContent::get() const{
    return filecontent;
}



