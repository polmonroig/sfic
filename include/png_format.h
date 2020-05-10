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
#ifndef PNG_FORMAT_H
#define  PNG_FORMAT_H

#include <array>

#include "exception_handler.h"
#include "matrix.h"
#include "format.h"
#include "huffman_compression.h"
#include "lz77_compression.h"

namespace sfic{

    class PNGFormat : public Format{

    public:

        Matrix decode() override;

        void encode(Matrix& decodedImage) override;

    private:

        void readSignature();

        void filtering(Matrix& decodedImage );

        void deflate(Matrix& decodedImage );

        // every png file contains this signature
        static const int SIGNATURE_SIZE = 8;
        constexpr static ByteType signature[SIGNATURE_SIZE] = {  137, 80, 78, 71, 13, 10, 26, 10};

    };

}



#endif
