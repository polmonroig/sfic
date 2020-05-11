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
#include "../include/lz77_compression.h"

using namespace sfic;

RawData LZ77::encode(RawData const& data){
    RawData output;
    aheadSize = 0;
    // setup

    // main algorithm
    while(aheadSize < data.size()){
        bool match = search(data);// 1. search
        if(match){
            aheadSize += matchLength;
            shift(data, matchLength); // shift
            output.push("(0," + std::to_string(matchLength));
            output.push(data.get(aheadSize));
            output.push(')');
        }else{
            ++aheadSize;
            shift(data, 1); // no match => add a single character
            output.push("(0,0,");
            output.push(data.get(aheadSize));
            output.push(')');
        }
    }

    std::cout << "LZ77 compression ratio: " << (float(data.size()) / output.size()) * 100 << std::endl;

    return output;
}

// pre: quantity <= SB_SIZE && quantity <= LAB_SIZE
void LZ77::shift(RawData const& data, unsigned int quantity){
    // shift search buffer elements
    for(unsigned int i = quantity; i < BUFFER_SIZE; ++i)
        searchBuffer[i - quantity] = searchBuffer[i];
    // move elements betweeen buffers
    for(unsigned int i = 0; i < quantity; ++i)
        searchBuffer[BUFFER_SIZE - quantity + i] = data.get(i + aheadSize);

}

bool LZ77::search(RawData const& data){
    int i = std::max(0, int(BUFFER_SIZE) - int(aheadSize));
    bool found = false;
    while(i < BUFFER_SIZE && searchBuffer[i] != data.get(aheadSize))++i;
    matchLength = 0;
    while(i < BUFFER_SIZE && searchBuffer[i] == data.get(aheadSize + matchLength)){
        found = true;
        ++i;
        ++matchLength;
    }
    return found;
}
