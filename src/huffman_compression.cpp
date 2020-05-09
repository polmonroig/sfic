#include "../include/huffman_compression.h"

using namespace sfic;

RawData HuffmanCompression::encode(RawData const& data){
    // create frequency table
    // auto table = getFrequencyTable();

    // create trees
    std::priority_queue<HuffmanTree> minHeap;
    // for(auto const& letter : table)
    //  minHeap.push(HuffmanTree(letter.name, letter.freq));
    // join trees
    // while(minHeap.size() > 1){
    //     HuffmanTree min1 = minHeap.top();
    //     minHeap.pop();
    //     HuffmanTree min2 = minHeap.top();
    //     minHeap.pop();
    //     minHeap.push(HuffmanTree(min1, min2));
    // }

    return data;
}
