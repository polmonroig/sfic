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


LZ77::LZ77(){
    searchBuffer = MatchTable(BUFFER_SIZE);
}

RawData LZ77::encode(RawData const& data){
    RawData output;
    output.reserve(data.size() * 3);
    aheadPointer = 0;
    int lastMatch = 0;
    // setup
    // main algorithm
    while(aheadPointer < data.size()){
        // std::cout << "Looking at " << data.get(aheadPointer) << std::endl;
        ByteArray literal = data.subVector(aheadPointer, aheadPointer + MINMATCH_LENGTH);
        bool match = search(data, literal);// 1. search
        if(match){
            // std::cout << "Found a match of length " << matchLength << " and offset " << offset << std::endl;
            ByteArray literalNonMatch = data.subVector(lastMatch, aheadPointer);
            output.push(toString(offset) + toString(matchLength));
            searchBuffer.add(literal, aheadPointer);
            aheadPointer += matchLength;
            lastMatch = aheadPointer;
        }else{
            searchBuffer.add(literal, aheadPointer);
            output.push(data.get(aheadPointer));
            ++aheadPointer;
        }
    }
    std::cout << "Original file size: " << data.size() << " bytes" << std::endl;
    std::cout << "Compressed file size: " << output.size() << " bytes" << std::endl;
    std::cout << "LZ77 compression ratio: " << (float(output.size()) / data.size()) * 100 << "%"<< std::endl;

    return output;
}


/************************
        PRIVATE
*************************/

std::string LZ77::toString(unsigned int i){
    std::string out;
    // special case i = 0
    if(i == 0) out = "0";
    // other cases
    while(i > 0){
        out = char(i % 10) + out;
        i /= 10;
    }
    return out;
}



bool LZ77::search(RawData const& data, ByteArray const& literal){

    auto matches = searchBuffer.find(literal);
    matchLength = MINMATCH_LENGTH - 1;
    bool matchFound = false;
    for(auto const& match : matches){
        // the offset is the distance between the current position
        // and where the match was found
        offset = aheadPointer - match;
        // if we excede the maximum possibl offset, we must discard
        // the match
        if(offset < MAX_OFFSET_LENGTH){
            auto length = searchFromIndex(data, match);
            if (length > matchLength){
                matchFound = true;
            }
        }

    }
    return matchFound;
}



unsigned int LZ77::searchFromIndex(RawData const& data, unsigned int matchIterator) const{
    unsigned int length = MINMATCH_LENGTH; // length is already the minimum possible

    matchIterator += 4;
    unsigned int literalIterator  = aheadPointer + 4;
    // while in range and match continues
    while(literalIterator < data.size() && data.get(matchIterator) == data.get(literalIterator)){
        matchIterator++;
        literalIterator++;
        length++;
    }

    return length;
}
