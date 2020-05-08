#ifndef PNG_FORMAT_H
#define  PNG_FORMAT_H

#include "matrix.h"
#include "format.h"

namespace sfic{

    class PNGFormat : public Format{

    public:

        Matrix decode() override;

        void encode(Matrix& decodedImage) override;

    private:

        void filtering(Matrix& decodedImage );

        void deflate(Matrix& decodedImage );

    };

}



#endif
