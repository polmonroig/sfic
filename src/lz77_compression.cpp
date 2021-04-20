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
    output.reserve(data.size() * 3);
    aheadPointer = 0;
    // setup

    // main algorithm
    while(aheadPointer < data.size()){

        bool match = search(data);// 1. search
        if(match){
            shift(data, matchLength); // shift
            output.push("["+ toString(offset) +"," + toString(matchLength) + "]");
            aheadPointer += matchLength;
        }else{
            shift(data, 1); // no match => add a single character
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

// pre: quantity <= BUFFER_SIZE
void LZ77::shift(RawData const& data, unsigned int quantity){



    // shift search buffer elements
    for(int i = 0; i < quantity && searchBuffer.size() >= BUFFER_SIZE; ++i)
        searchBuffer.pop_front();

    // move elements betweeen buffers
    for(int i = 0; i < quantity; ++i)
        searchBuffer.push_back(data.get(aheadPointer + i));


}

bool LZ77::search(RawData const& data){
    bool found = false;
    // min is needed when search buffer is not full
    // search buffer will be full <=> aheadPointer >= BUFFER_SIZE
    unsigned int sizeBuffer = std::min(BUFFER_SIZE, aheadPointer);
    // set the matchLength to the minimum, this way
    // I only accept matches with at least that length
    matchLength = MIN_LENGTH;
    // offset will always be > 0
    offset = 1;
    // 0 is the last element of the search buffer
    bool stopSearching = false;
    auto it = searchBuffer.begin();
    int i = 0;
    // here we verify two conditions
    // 1. We are searching inside our search buffer => we can search
    //    further from the search buffer but a match must always start
    //    inside the buffer, the iterator (i and it) are used to find
    //    the first character of the match.
    // 2. the condition to stop searching is not met
    //
    // The idea of this search is the following. We iteratre every position
    // on the search buffer. If a character matches the current byte (aheadPointer)
    // it means that we might find ourselves a match. Once we find a match we must
    // then copy the iterator (so that we don't lose its value) and make a search
    // from there. The searchFromIndex will search for a bigger match based on the
    // initial position we found, the searchFromIndex will loop until there is no match
    // and return the length of that match.
    // Once we have the lenght, we compare it with the matchLength we have,
    // matchLength is the minimum lenght we have found, the idea is to loop for every position
    // inside the search bufffer and find the best possible match, we find the minimum
    // for every match. The initial value for the matchLength is MIN_LENGTH, thus
    // we are enforcing that every possible match we found must have this length at least.
    // Once we finish that we must calculate the separation, the separation is the difference
    // from the position we are right now, the size of the buffer and the maximum possible lenght.
    // separation = totalSize - current position (this is the size left) + MAX_LENGTH
    // we add the MAX_LENGTH because the size of the match might be bigger. The idea is to
    // see if it is possible to find a bigger match, if not, stop looking. After that
    // we also see if match is "good" enough. If it is bigger than the MARGIN_LENGTH it means
    // we have a good enough match
    while(i < searchBuffer.size() && !stopSearching){
        if(*it == data.get(aheadPointer)){
            auto itCopy = it;
            auto length = searchFromIndex(data, ++itCopy);
            // find sequence with max length
            if(length > matchLength){
                found = true;
                offset = sizeBuffer - i;
                matchLength = length;
            }
            auto separation = sizeBuffer - i + MAX_LENGTH;
            // if length is long enough or given the current
            // position we cannot get a better one, stop searching
            if(length >= separation || length >= MARGIN_LENGTH){
                stopSearching = true;
            }
        }
        ++it;
        ++i; // need counter to calculate the offset
    }

    return found;

}



unsigned int LZ77::searchFromIndex(RawData const& data, std::deque<ByteType>::const_iterator i) const{
    unsigned int length = 1;
    // continue comparing characters and incrementing the length
    // of the matching string
    // CONDITIONS
    // 1. check length is less than maximum lenght
    // 2. check iterator lesser than size of the buffer
    // 3. while there is a character match
    // RESULT
    // 1. increment the iterator -> decrements buffer position
    // 2. increment length
    while(length < MAX_LENGTH && i != searchBuffer.end() && *i == data.get(length + aheadPointer)){
        ++i;
        length++;
    }
    // when we have compared all the search buffer
    // we can continue to compare data from within the lookup
    // buffer, this way we can compress the data even further
    // NOTE: THIS condition is never met or at least it does not help, need to fix it
    if(i == searchBuffer.end()){
        int j = aheadPointer;
        auto currentLength = length;
        while(j < data.size() && length < MAX_LENGTH && data.get(j) == data.get(j + currentLength)){
            ++j;
            ++length;
        }
    }
    return length;
}
