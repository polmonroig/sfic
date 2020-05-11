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
#include "../include/ppm_format.h"


using namespace sfic;

/************************
        PUBLIC
*************************/


Matrix PPMFormat::decode(){
    iterator = 0;
    auto p = readType();
    auto width = readSize();
    auto height = readSize();
    auto maxSize = readSize();
    if(p == PPMType::P3){
        return readP3(maxSize, width, height);
    }
    else{
        return readP6(maxSize, width, height);
    }

}

void PPMFormat::encode(Matrix& decodedImage){
    auto width = decodedImage.width();
    auto height = decodedImage.height();
    data.push("P6\n");
    data.push(std::to_string(width) + " ");
    data.push(std::to_string(height) + "\n");
    data.push("255\n");
    for(unsigned int i = 0; i < height; ++i){
        for(unsigned int j = 0; j < width; ++j){
            auto color = decodedImage.get(i, j);
            for(auto const& value : color){
                data.push(int(value * 255));
            }
        }
    }

}




/************************
        PRIVATE
*************************/

inline void PPMFormat::skipComment(){
    while(data.get(iterator) != '\n')++iterator;
    ++iterator; // goto next line
}


inline bool PPMFormat::skipEmpty(){
    if(data.get(iterator) == '#'){
        skipComment();
        return true;
    }
    else if(data.get(iterator) == '\n' || data.get(iterator) == ' '){
        ++iterator; // skip empty
        return true;
    }
    return false;
}


PPMType PPMFormat::readType(){
    while(iterator < data.size()){
        if(!skipEmpty()){
            // current pos is not empty
            if(data.get(iterator) == 'P')++iterator;
            else if(data.get(iterator) == '3'){
                iterator++;
                return PPMType::P3;
            }
            else if(data.get(iterator) == '6'){
                iterator++;
                return PPMType::P6;
            }
        }
    }
    return PPMType::P3;
}

inline MatInt PPMFormat::readSize(){
    std::string value = "";
    while(iterator < data.size()){
        bool found = false;
        while(!skipEmpty()){
            found = true;
            value += data.get(iterator);
            ++iterator;
        }
        if(found)return std::stoi(value);
    }
    return std::stoi(value);
}

inline ByteType PPMFormat::readByte(){
    return data.get(iterator++);
}

Matrix PPMFormat::readP3(MatInt maxValue, MatInt width, MatInt height){
    Matrix image(height, width, N_CHANNELS);
    unsigned int i, j;
    i = j = 0; // matrix iterators
    while(iterator < data.size()){
        if(!skipEmpty()){
            auto r = float(readSize()) / maxValue;
            auto g = float(readSize()) / maxValue;
            auto b = float(readSize()) / maxValue;
            ChannelType channel{r, g, b};
            image.set(i, j, channel);
            ++j;
            if(j >= width){
                i++;
                j = 0;
            }
        }
    }
    return image;
}

Matrix PPMFormat::readP6(MatInt maxValue, MatInt width, MatInt height){
    Matrix image(height, width, N_CHANNELS);
    unsigned int i, j;
    i = j = 0; // matrix iterators


    while(iterator < data.size()){
        auto r = float(readByte()) / maxValue;
        auto g = float(readByte()) / maxValue;
        auto b = float(readByte()) / maxValue;
        ChannelType channel{r, g, b};
        image.set(i, j, channel);
        ++j;
        if(j >= width){
            i++;
            j = 0;
        }
    }
    return image;
}
