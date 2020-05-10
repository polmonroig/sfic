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
#ifndef MATRIX_H
#define  MATRIX_H

#include <vector>

#include "raw_data.h"

namespace sfic{

    // typdefintions
    typedef std::vector<float> ChannelType;
    typedef std::vector<ChannelType> RowType;
    typedef std::vector<RowType> MatType;
    typedef unsigned int MatInt;



    class Matrix{

    public:

        Matrix() = default;

        Matrix(MatInt nRows, MatInt nCols, MatInt nChannels);

        void toYCbCr();

        RawData toRawData() const;

        inline void set(MatInt i, MatInt j, ChannelType const& channel);

        inline MatInt width() const;

        inline MatInt height() const;

        inline ChannelType get(MatInt i, MatInt j) const;

    private:


        MatInt rows, cols, channels;

        MatType content;


    };

    /************************
       INLINE DEFINITIONS
    *************************/

    inline MatInt Matrix::width() const{
        return cols;
    }

    inline MatInt Matrix::height() const{
        return rows;
    }

    inline ChannelType Matrix::get(MatInt i, MatInt j) const{
        return content[i][j];
    }


    inline void Matrix::set(MatInt i, MatInt j, ChannelType const& channel){
        content[i][j] = channel;
    }

}


#endif
