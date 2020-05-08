#ifndef LZ77_COMPRESSION
#define  LZ77_COMPRESSION

#include <array>

#include "raw_data.h"

namespace sfic{

    class LZ77{

    public:

        RawData encode(RawData const& data);

    private:

        bool search(RawData const& data);

        void shift(RawData const& data, unsigned int quantity);

        static const unsigned int SB_SIZE = 4;
        static const unsigned int LAB_SIZE = 4;

        unsigned int ahead_size;

        unsigned int match_length;

        std::array<ByteType, LAB_SIZE> lookAheadBuffer;
        std::array<ByteType, SB_SIZE> searchBuffer;


    };




}



#endif
