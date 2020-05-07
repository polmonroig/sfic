#include "../include/format.h"

using namespace sfic;


/************************
        PUBLIC
*************************/


void Format::read(std::string const& path){
    data.read(path);
}

void Format::write(std::string const& path){
    data.write(path);
}


/************************
        PRIVATE
*************************/
