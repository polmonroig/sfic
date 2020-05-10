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
