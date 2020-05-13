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
    setFrequencyTable(data);

    // create trees
    std::priority_queue<HuffmanTree> minHeap;
    for(unsigned int letter = 0; letter < ALPHABET_SIZE; ++letter){
        if(table[letter] > 0)
            minHeap.push(HuffmanTree(letter, table[letter]));
    }


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
        if(stream.size() >= MAX_MEMORY)flushBitsStream(stream, output);
    }
    // flush remaining bytes
    flushBitsStream(stream, output);

    std::cout << "Hufffman compression ratio: " << (float(data.size()) / output.size()) * 100 << std::endl;


    return output;
}


void HuffmanCompression::setFrequencyTable(RawData const& data){
    for(auto& val : table)val = 0; // initalize frequency
    for(unsigned int i = 0; i < data.size(); ++i){
        table[data.get(i)]++;
    }
}


void HuffmanCompression::flushBitsStream(BinaryCodeType& stream, RawData& output){
    BinaryCodeType singleByte;
    singleByte.reserve(RawData::BYTE_SIZE);
    for(unsigned int i = 0; i < stream.size(); ++i){
        singleByte += stream[i];
        if(i % RawData::BYTE_SIZE == 0){
            output.push(std::stoi(singleByte,0 , 2));
            singleByte = "";
        }
    }
    stream = singleByte;
}
