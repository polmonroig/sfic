#include "../include/raw_data.h"

using namespace sfic;


/************************
        PUBLIC
*************************/

void RawData::read(std::string const& path){
    std::ifstream file (path, std::ifstream::binary);
    if(!file.is_open())throw std::invalid_argument("I/O Error: sfic::RawData::read " + path);
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
    if(!file.is_open())throw std::invalid_argument("I/O Error: sfic::RawData::write " + path);
    for(unsigned int i = 0; i < bytes.size(); ++i){
        file << bytes[i];
    }
    file.close();

}


void RawData::push(std::string const& value){
    for(auto const& v : value)bytes.push_back(v);
}

void RawData::push(ByteType value){
    bytes.push_back(value);
}

void RawData::reserve(unsigned int size){
    bytes.reserve(size);
}


void RawData::concatenate(RawData const& other){
    bytes.reserve(bytes.size() + other.size()); // verify if correct
    for(auto const& value : other.bytes){
        bytes.push_back(value); 
    }

}


/************************
        PRIVATE
*************************/
