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
#ifndef LZ77_COMPRESSION
#define  LZ77_COMPRESSION

#include "match_table.h"

#include "raw_data.h"

namespace sfic{

    class LZ77{

    public:

        LZ77();

        RawData encode(RawData const& data);

    private:
        // searches for matches in the current
        // index of the look ahead buffer
        bool search(RawData const& data, ByteArray const& literal);
        // given an index in the search buffer , it returns the length
        // the longest match from that position
        unsigned int searchFromIndex(RawData const& data, unsigned int matchIterator) const;
        // converts an integer to a string efficiently
        static std::string toString(unsigned int i);
        // the buffer size fixes the physical size of the search buffer
        // determined by the DEFLATE specifications (32 * 1024)
        static const unsigned int BUFFER_SIZE = 32768;
        // to limit the max length of an encountered string match
        static const unsigned int MAX_LENGTH = 2056 * 2;
        // stop searching if length is long enough
        static const unsigned int MARGIN_LENGTH = 32;
        // defines the maximum possible offset
        static const unsigned int MAX_OFFSET_LENGTH = 65535;
        // to limit the minimum length a match must have to
        // be considered a match
        static const unsigned int MINMATCH_LENGTH = 4; // Min length for a match
        // aheadSize is a pointer to the first element in the
        // look ahead buffer, hence the name
        unsigned int aheadPointer;
        // when a match is encounter the distance from the 0 position
        // and the match begining is saved as the offset
        unsigned int offset;
        // contains the largest match at a given time
        unsigned int matchLength;
        // represents the search buffer of the algorithm
        MatchTable searchBuffer;


    };




}



#endif
