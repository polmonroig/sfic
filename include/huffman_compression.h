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
#ifndef HUFFMAN_COMPRESSION_H
#define  HUFFMAN_COMPRESSION_H

#include <queue>
#include <array>
#include <unordered_map>

#include "huffman_tree.h"

namespace sfic{



    class HuffmanCompression{

    public:


        RawData encode(RawData const& data);

    private:

        void setFrequencyTable(RawData const& data);

        void flushBitsStream(BinaryCodeType& stream, RawData& data);

        // at most 256 different values, for a single byte
        static const unsigned int ALPHABET_SIZE = 256;
        // the bits stream is encoded as a string so it starts
        // to fill the memory very fast, to prevent a memory overflow
        // every time the stream reaches a MAX_MEMORY size, it must
        // convert every octet into a byte and push it to the compressed
        // data, here MAX_MEMORY denotes the max number of characters
        // thus the maximum memory must by multiplied by 8
        static const unsigned int MAX_MEMORY = 1024;
        // the frequency table can be easily encoded with a small array
        // its size is constant always (ALPHABET_SIZE) and so it
        // has a constant space complexity O(1), it also offers
        // a constant lookup, and modification functions O(1)
        std::array<unsigned int, ALPHABET_SIZE> table; // frequency table




    };



}


#endif
