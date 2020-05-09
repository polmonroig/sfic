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

        static const unsigned int BUFFER_SIZE = 256;

        unsigned int ahead_size;
        unsigned int match_length;
        
        std::array<ByteType, BUFFER_SIZE> searchBuffer;


    };




}



#endif
