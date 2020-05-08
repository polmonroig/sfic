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

        void encode(Matrix& decodedImage) override;

    private:

        inline void skipComment();

        inline bool skipEmpty();

        PPMType readType();


        inline MatInt readSize();

        inline ByteType readByte();

        Matrix readP3(MatInt maxValue, MatInt width, MatInt height);

        Matrix readP6(MatInt maxValue, MatInt width, MatInt height);


        static const MatInt N_CHANNELS = 3;

    };

}



#endif
