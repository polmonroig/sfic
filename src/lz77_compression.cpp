#include "../include/lz77_compression.h"

using namespace sfic;

RawData LZ77::encode(RawData const& data){
    RawData output;
    auto totalSize = std::min(LAB_SIZE, data.size());
    ahead_size = 0;
    // setup
    for(unsigned int i = 0; i < totalSize; ++i)
        lookAheadBuffer[i] = data.get(i);

    // main algorithm
    while(ahead_size < data.size()){
        bool match = search(data);// 1. search
        if(match){
            ahead_size += match_length;
            shift(data, match_length); // shift
        }else{
            ++ahead_size;
            shift(data, 1); // no match => add a single character
            output.push("(0,0,");
            output.push(lookAheadBuffer[0]);
            output.push(')');
        }
    }

    return output;
}

// pre: quantity <= SB_SIZE && quantity <= LAB_SIZE
void LZ77::shift(RawData const& data, unsigned int quantity){
    // shift search buffer elements
    std::cout << "quantity " << quantity << std::endl;
    for(unsigned int i = quantity; i < SB_SIZE; ++i)
        searchBuffer[i - quantity] = searchBuffer[i];
    // move elements betweeen buffers
    for(unsigned int i = 0; i < quantity; ++i)
        searchBuffer[SB_SIZE - quantity + i] = lookAheadBuffer[i];
    // shift lookahead buffer elements
    for(unsigned int i = quantity; i < SB_SIZE; ++i)
        lookAheadBuffer[i - quantity] = lookAheadBuffer[i - 1];
    // add new elements to lookAheadBuffer
    for(unsigned int i = 0; i < quantity; ++i)
        lookAheadBuffer[LAB_SIZE - quantity + i] = data.get(i + ahead_size);

}

bool LZ77::search(RawData const& data){
    return false;
}
