#include "../include/raw_data.h"

using namespace sfic;


void RawData::read(std::string const& imagePath){
    std::ifstream file (imagePath, std::ifstream::binary);
    if(!file.is_open())std::cerr << "Couldn't open file " << imagePath << std::endl;
    std::cout << "Reading file " << imagePath << std::endl; // DEBUG
    file.seekg (0, file.end);
    int length = file.tellg();
    file.seekg(0, file.beg);

    bytes.reserve(length);
    for(int i = 0; i < length; ++i){
        ByteType current;
        file >> current;
        bytes.push_back(current);
    }

}
