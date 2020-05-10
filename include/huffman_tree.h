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
#ifndef HUFFMAN_TREE_H
#define  HUFFMAN_TREE_H

#include <memory>
#include <unordered_map>
#include <string>

#include "raw_data.h"

namespace sfic{

    typedef std::string BinaryCodeType;
    typedef std::unordered_map<ByteType, BinaryCodeType> HuffmanCodesTable;

    class HuffmanTree{

    public:

        HuffmanTree(ByteType v, unsigned int w);

        HuffmanTree(HuffmanTree const& tree);

        HuffmanTree(HuffmanTree const& h1, HuffmanTree const& h2);

        bool operator<(HuffmanTree const& other) const;

        HuffmanCodesTable getTable() const;

    private:


        static void getBinaryCode(std::shared_ptr<HuffmanTree> const& tree, HuffmanCodesTable& table, BinaryCodeType const& code);

        static const int NULL_VALUE = -1;

        std::shared_ptr<HuffmanTree> left;
        std::shared_ptr<HuffmanTree> right;

        ByteType value;
        unsigned int weight;
        unsigned int size;
        bool isLeaf;

    };


}

#endif
