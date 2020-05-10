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
