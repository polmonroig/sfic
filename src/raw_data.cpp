#include "../include/raw_data.h"

using namespace sfic;


/************************
        PUBLIC
*************************/

void RawData::read(std::string const& path){
    std::ifstream file (path, std::ifstream::binary);
    if(!file.is_open())std::cerr << "Couldn't open file " << path << std::endl;
    file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    bytes.reserve(length);
    for(int i = 0; i < length; ++i){
        char value;
        file.get(value);
        bytes.push_back(value);
    }
    file.close();
}


void RawData::write(std::string const& path) const{
    std::ofstream file (path, std::ifstream::out);
    if(!file.is_open())std::cerr << "Couldn't open file " << path << std::endl;
    for(unsigned int i = 0; i < bytes.size(); ++i){
        file << bytes[i];
    }
    file.close();

}


void RawData::convert(FormatContainer const& newFormat){

    format = newFormat;
}


/************************
        PRIVATE
*************************/
