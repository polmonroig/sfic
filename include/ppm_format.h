#ifndef PPM_FORMAT_H
#define  PPM_FORMAT_H

#include "matrix.h"
#include "format.h"

namespace sfic{

    class PPMFormat : public Format{

    public:

        Matrix decode() const override;

        void encode(Matrix decodedImage) override;

    private:


    };

}



#endif
