#include "../include/lz77_compression.h"

using namespace sfic;

RawData LZ77::encode(RawData const& data){
    RawData output;
    ahead_size = 0;
    // setup

    // main algorithm
    while(ahead_size < data.size()){
        bool match = search(data);// 1. search
        if(match){
            ahead_size += match_length;
            shift(data, match_length); // shift
            output.push("(0," + std::to_string(match_length));
            output.push(data.get(ahead_size));
            output.push(')');
        }else{
            ++ahead_size;
            shift(data, 1); // no match => add a single character
            output.push("(0,0,");
            output.push(data.get(ahead_size));
            output.push(')');
        }
    }
    return output;
}

// pre: quantity <= SB_SIZE && quantity <= LAB_SIZE
void LZ77::shift(RawData const& data, unsigned int quantity){
    // shift search buffer elements
    for(unsigned int i = quantity; i < BUFFER_SIZE; ++i)
        searchBuffer[i - quantity] = searchBuffer[i];
    // move elements betweeen buffers
    for(unsigned int i = 0; i < quantity; ++i)
        searchBuffer[BUFFER_SIZE - quantity + i] = data.get(i + ahead_size);

}

bool LZ77::search(RawData const& data){
    int i = std::max(0, int(BUFFER_SIZE) - int(ahead_size));
    bool found = false;
    while(i < BUFFER_SIZE && searchBuffer[i] != data.get(ahead_size))++i;
    match_length = 0;
    while(i < BUFFER_SIZE && searchBuffer[i] == data.get(ahead_size + match_length)){
        found = true;
        ++i;
        ++match_length;
    }
    return found;
}
