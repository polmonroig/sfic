#ifndef PPM_FORMAT_H
#define  PPM_FORMAT_H

#include <string>

#include "matrix.h"
#include "format.h"

namespace sfic{

    enum class PPMType {
        P3,
        P6
    };

    class PPMFormat : public Format{

    public:

        Matrix decode() override;

        void encode(Matrix decodedImage) override;

    private:

        inline void skipComment();

        inline bool skipEmpty();

        PPMType readType();


        MatSize readSize();

        Matrix readP3(MatSize width, MatSize height);

        Matrix readP6(MatSize width, MatSize height);


        static const MatSize N_CHANNELS = 3;

    };

}



#endif
