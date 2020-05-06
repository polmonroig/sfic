#include "../include/image.h"

using namespace sfic;

/************************
        PUBLIC
*************************/


Image::Image(std::string const& path){
    data.read(path);
}


void Image::save(std::string const& path) const{
    data.write(path);
}


/************************
        PRIVATE
*************************/
