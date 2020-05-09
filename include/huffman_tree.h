#ifndef HUFFMAN_TREE_H
#define  HUFFMAN_TREE_H

#include <memory>

#include "raw_data.h"

namespace sfic{

    class HuffmanTree{

    public:

        HuffmanTree(ByteType v, unsigned int w);

        HuffmanTree(HuffmanTree const& tree);

        HuffmanTree(HuffmanTree const& h1, HuffmanTree const& h2);

        bool operator<(HuffmanTree const& other) const;

    private:

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
