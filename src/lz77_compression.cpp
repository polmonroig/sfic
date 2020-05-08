#include "../include/lz77_compression.h"

using namespace sfic;

RawData LZ77::encode(RawData const& data){
    RawData output;
    auto ahead_size = data.size();
    while(ahead_size > 0){
        bool match = search(data);// 1. search
        if(match){
            ahead_size -= match_length;
            shift(match_length); // shift
        }else{
            --ahead_size;
            shift(1); // no match => add a single character
            output.push("(0,0");
            output.push(lookAheadBuffer[0]);
            output.push(')');
        }
    }

    return output;
}

// pre: quantity <= SB_SIZE && quantity <= LAB_SIZE
void LZ77::shift(unsigned int quantity){
    // shift search buffer elements
    for(unsigned int i = quantity; i < SB_SIZE; ++i)
        searchBuffer[i - quantity] = searchBuffer[i];
    // move elements betweeen buffers
    for(unsigned int i = 0; i < quantity; ++i)
        searchBuffer[SB_SIZE - quantity + i] = lookAheadBuffer[i];
    // shift lookahead buffer elements
    for(unsigned int i = quantity - 1; i < SB_SIZE; ++i)
        lookAheadBuffer[i - quantity] = lookAheadBuffer[i];

}

bool LZ77::search(RawData const& data){
    return false;
}
