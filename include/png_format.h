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
