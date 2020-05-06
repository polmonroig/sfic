#include "../include/image.h"

using namespace sfic;

Image::Image(std::string const& imagePath){
    data.read(imagePath); 
}
