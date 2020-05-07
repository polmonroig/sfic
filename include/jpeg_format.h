#ifndef JPEG_FORMAT
#define  JPEG_FORMAT

#include "matrix.h"
#include "format.h"

namespace sfic{

    class JPEGFormat : public Format{

    public:

        Matrix decode() const override;

        void encode(Matrix decodedImage) override;

    private:


    };

}



#endif
