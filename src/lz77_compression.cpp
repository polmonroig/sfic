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
            shift(data, matchLength); // shift
            output.push("["+ std::to_string(offset) +"," + std::to_string(matchLength) + "]");
            aheadSize += matchLength;
        }else{
            shift(data, 1); // no match => add a single character
            output.push(data.get(aheadSize));
            ++aheadSize;
        }
    }

    std::cout << "LZ77 compression ratio: " << (float(data.size()) / output.size()) * 100 << std::endl;

    return output;
}

// pre: quantity <= BUFFER_SIZE
void LZ77::shift(RawData const& data, unsigned int quantity){
    // shift search buffer elements
    // min is needed when search buffer is not full
    unsigned int size = std::min(BUFFER_SIZE, aheadSize);
    for(int i = size - quantity; i >= 0; --i)
        searchBuffer[i + quantity] = searchBuffer[i];

    // move elements betweeen buffers
    quantity--;
    for(int i = quantity; i >= 0; --i)
        searchBuffer[i] = data.get(aheadSize + quantity - i);

}

bool LZ77::search(RawData const& data){
    bool found = false;
    // min is needed when search buffer is not full
    unsigned int size = std::min(BUFFER_SIZE, aheadSize);
    matchLength = MIN_LENGTH;
    offset = 1;
    for(unsigned int i = 0; i < size; ++i){
        if(searchBuffer[i] == data.get(aheadSize)){
            auto length = searchFromIndex(data, i - 1);

            // find sequence with max length
            if(length > matchLength){
                found = true;
                offset = i + 1;
                matchLength = length;
            }
        }
    }
    return found;
}

// SKIP MATCHES ECLIPSED MY ANOTHER
// THAT IS WE SHOULD START FROM THE END?
// TODO -> RETHINK WHOLE BUFFFER IMPLEMENTATION
unsigned int LZ77::searchFromIndex(RawData const& data, int i) const{
    unsigned int length = 1;
    auto size = i + 1;
    // continue comparing characters and incrementing the length
    // of the matching string
    while(length < MAX_LENGTH && i >= 0 && searchBuffer[i] == data.get(size - i + aheadSize)){
        --i;
        length++;
    }
    // when we have compared all the search buffer
    // we can continue to compare data from within the lookup
    // buffer, this way we can compare the data even further
    if(i < 0){
        i = aheadSize; //
        while(i < data.size() && length < MAX_LENGTH && data.get(i) == data.get(i + size + 1)){
            ++i;
            ++length;
        }
    }
    return length;
}
