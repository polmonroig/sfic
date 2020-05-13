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

/*
    LOOKAHEAD BUFFER
    The lookahead buffer is implicit within the data and
    its size is limited by the max match length
    SEARCH BUFFER
    The search buffer is implemented as a fixed array
    of size 32KB (32 * 1024), specified in the PNG standard
    The first position of the buffer is indexed by a 0
*/

/************************
        PUBLIC
*************************/

RawData LZ77::encode(RawData const& data){
    RawData output;
    aheadPointer = 0;
    // setup

    // main algorithm
    while(aheadPointer < data.size()){
        bool match = search(data);// 1. search
        if(match){
            shift(data, matchLength); // shift
            output.push("["+ std::to_string(offset) +"," + std::to_string(matchLength) + "]");
            aheadPointer += matchLength;
        }else{
            shift(data, 1); // no match => add a single character
            output.push(data.get(aheadPointer));
            ++aheadPointer;
        }
    }

    std::cout << "LZ77 compression ratio: " << (float(data.size()) / output.size()) * 100 << std::endl;

    return output;
}


/************************
        PRIVATE
*************************/

// pre: quantity <= BUFFER_SIZE
void LZ77::shift(RawData const& data, unsigned int quantity){
    // shift search buffer elements
    // min is needed when search buffer is not full
    unsigned int size = std::min(BUFFER_SIZE, aheadPointer);
    for(int i = quantity; i < size; ++i)
        searchBuffer[i - quantity] = searchBuffer[i];

    // move elements betweeen buffers
    for(int i = size - quantity; i < size; ++i)
        searchBuffer[i] = data.get(aheadPointer + i);

}

bool LZ77::search(RawData const& data){

    bool found = false;
    // min is needed when search buffer is not full
    unsigned int size = std::min(BUFFER_SIZE, aheadPointer);
    matchLength = MIN_LENGTH;
    offset = 1;
    // 0 is the last element of the search buffer
    for(unsigned int i = 0; i < size; ++i){
        if(searchBuffer[i] == data.get(aheadPointer)){
            auto length = searchFromIndex(data, i + 1);

            // find sequence with max length
            if(length > matchLength){
                found = true;
                offset = size - i;
                matchLength = length;
            }
        }
    }
    return found;
}



unsigned int LZ77::searchFromIndex(RawData const& data, int i) const{
    unsigned int length = 1;
    unsigned int size = std::min(BUFFER_SIZE, aheadPointer);
    // continue comparing characters and incrementing the length
    // of the matching string
    // CONDITIONS
    // 1. check length is less than maximum lenght
    // 2. check iterator lesser than size of the buffer
    // 3. while there is a character match
    // RESULT
    // 1. increment the iterator -> decrements buffer position
    // 2. increment length
    while(length < MAX_LENGTH && i < size && searchBuffer[i] == data.get(length + aheadPointer)){
        ++i;
        length++;
    }
    // when we have compared all the search buffer
    // we can continue to compare data from within the lookup
    // buffer, this way we can compress the data even further
    if(i >= size){
        i = aheadPointer;
        auto currentLength = length;
        while(i < data.size() && length < MAX_LENGTH && data.get(i) == data.get(i + currentLength)){
            ++i;
            ++length;
        }
    }
    return length;
}


 unsigned int LZ77::intToHex(unsigned int variable){
     return variable;
 }
