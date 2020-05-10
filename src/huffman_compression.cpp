#include "../include/huffman_compression.h"

using namespace sfic;

RawData HuffmanCompression::encode(RawData const& data){
    // create frequency table
    RawData output;
    auto table = getFrequencyTable(data);

    // create trees
    std::priority_queue<HuffmanTree> minHeap;
    for(auto const& letter : table)
        minHeap.push(HuffmanTree(letter.first, letter.second));
    // join trees
    while(minHeap.size() > 1){
        HuffmanTree min1 = minHeap.top();
        minHeap.pop();
        HuffmanTree min2 = minHeap.top();
        minHeap.pop();
        minHeap.push(HuffmanTree(min1, min2));
    }

    auto tree = minHeap.top();
    auto codes = tree.getTable();
    BinaryCodeType stream;
    for(unsigned int i = 0; i < data.size(); ++i){
        stream += codes[data.get(i)];
        if(stream.size() >= 8)stream = "";
        // output.push(); // encode each character in the data
    }


    return output;
}


FrequencyTableType HuffmanCompression::getFrequencyTable(RawData const& data){
    FrequencyTableType table;
    for(unsigned int i = 0; i < data.size(); ++i){
        auto iterator = table.find(data.get(i));
        if(iterator == table.end()){
            table.insert(iterator, {data.get(i), 1});
        }
        else{
            iterator->second++;
        }

    }

    return table;
}
