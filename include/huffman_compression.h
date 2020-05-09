#ifndef HUFFMAN_COMPRESSION_H
#define  HUFFMAN_COMPRESSION_H

#include <queue>
#include <unordered_map>

#include "huffman_tree.h"

namespace sfic{

    typedef std::unordered_map<ByteType, unsigned int> FrequencyTableType;

    class HuffmanCompression{

    public:

        RawData encode(RawData const& data);

    private:

        static FrequencyTableType getFrequencyTable(RawData const& data);


    };


}


#endif
