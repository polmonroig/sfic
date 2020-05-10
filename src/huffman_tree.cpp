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
#include "../include/huffman_tree.h"

using namespace sfic;

HuffmanTree::HuffmanTree(ByteType v, unsigned int w){
    value = v;
    left = nullptr;
    right = nullptr;
    weight = w;
    size = 1;
    isLeaf = true;
}


HuffmanTree::HuffmanTree(HuffmanTree const& tree){
    value = tree.value;
    left = tree.left;
    right = tree.right;
    weight = tree.weight;
    size = tree.size;
    isLeaf = tree.isLeaf;
}

HuffmanTree::HuffmanTree(HuffmanTree const& h1, HuffmanTree const& h2) {

    left = std::make_shared<HuffmanTree>(h1);
    right =  std::make_shared<HuffmanTree>(h2);

    size = left->size  + right->size;
    weight = left->weight + right->weight;
    isLeaf = false;
    value = NULL_VALUE;
}

HuffmanCodesTable HuffmanTree::getTable() const{
    HuffmanCodesTable codes;
    BinaryCodeType code = "";
    getBinaryCode(left, codes, code + "0");
    getBinaryCode(right, codes, code + "1");
    return codes;
}

void HuffmanTree::getBinaryCode(std::shared_ptr<HuffmanTree> const& tree, HuffmanCodesTable& table, BinaryCodeType const& code){
    if(tree->isLeaf){
        table[tree->value] = code;
    }
    else{
        getBinaryCode(tree->left, table, code + "0");
        getBinaryCode(tree->right, table, code + "1");
    }
}


bool HuffmanTree::operator<(HuffmanTree const& other) const{
    if(weight != other.weight)return weight < other.weight;
    else return size < other.size;
}
