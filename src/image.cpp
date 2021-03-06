/*
Copyright 2020 Pol Monroig Company

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
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
    else if(formatName == "jpeg")return std::make_shared<JPEGFormat>();
    else throw IncorrectArgument("Invalid argument: sfic::Image::stringToFormat " + formatName);
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
