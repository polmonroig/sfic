#ifndef JPEG_FORMAT
#define  JPEG_FORMAT

#include "matrix.h"
#include "format.h"

namespace sfic{

    class JPEGFormat : public Format{

    public:

        void decode() override;

        void encode() override;

    private:


    };

}



#endif
