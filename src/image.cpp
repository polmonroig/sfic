#include "../include/image.h"

using namespace sfic;

/************************
        PUBLIC
*************************/


Image::Image(std::string const& path){
    format = stringToFormat(getExtension(path));
    format->read(path);
}




void Image::save(std::string const& path) const{
    format->write(path);
}


void Image::convert(FormatContainer const& newFormat){
    // Matrix decodedImage = format.decode()
    // format = newFormat; // delete old data
    // format.encode(decodedImage)
}


FormatContainer Image::stringToFormat(std::string const& formatName){
    return std::make_shared<JPEGFormat>();
}

/************************
        PRIVATE
*************************/

std::string Image::getExtension(std::string const& path){
    return "JPEG";
}
