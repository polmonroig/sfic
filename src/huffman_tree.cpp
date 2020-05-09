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


bool HuffmanTree::operator<(HuffmanTree const& other) const{
    if(weight != other.weight)return weight < other.weight;
    else return size < other.size;
}
