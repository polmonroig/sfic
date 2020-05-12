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

#include <array>

#include "raw_data.h"

namespace sfic{

    class LZ77{

    public:

        RawData encode(RawData const& data);

    private:

        bool search(RawData const& data);

        void shift(RawData const& data, unsigned int quantity);

        unsigned int searchFromIndex(RawData const& data, int i) const;

        static const unsigned int BUFFER_SIZE = 32 *1024;
        static const unsigned int MAX_LENGTH = 256;
        static const unsigned int MIN_LENGTH = 3; // Min length for a match

        unsigned int aheadSize;
        unsigned int offset;
        unsigned int matchLength;

        std::array<ByteType, BUFFER_SIZE> searchBuffer;


    };




}



#endif
