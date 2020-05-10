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
