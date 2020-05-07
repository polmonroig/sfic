#ifndef JPEG_FORMAT_H
#define  JPEG_FORMAT_H

#include "matrix.h"
#include "format.h"

namespace sfic{

    class JPEGFormat : public Format{

    public:

        Matrix decode() override;

        void encode(Matrix decodedImage) override;

    private:


    };

}



#endif
