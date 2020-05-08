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
    Matrix decodedImage = format->decode();
    format = newFormat; // delete old data
    format->encode(decodedImage);
}


FormatContainer Image::stringToFormat(std::string const& formatName){
    if(formatName == "ppm")return std::make_shared<PPMFormat>();
    else if(formatName == "png") return std::make_shared<PNGFormat>();
    else return std::make_shared<JPEGFormat>();
}

/************************
        PRIVATE
*************************/

std::string Image::getExtension(std::string const& path){
    int i = path.size() - 1;
    std::string ext = "";
    while(i >= 0 && path[i] != '.'){
        ext += path[i];
        --i;
    }
    return reverse(ext);
}

std::string Image::reverse(std::string const& s){
    std::string newString;
    newString.reserve(s.size());
    for(int i = s.size() - 1; i >= 0; --i){
        newString += s[i];
    }
    return newString;
}
