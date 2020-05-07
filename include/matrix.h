#ifndef MATRIX_H
#define  MATRIX_H

#include <vector>

namespace sfic{

    // typdefintions
    typedef std::vector<float> ChannelType;
    typedef std::vector<ChannelType> RowType;
    typedef std::vector<RowType> MatType;
    typedef unsigned int MatSize;



    class Matrix{

    public:

        Matrix() = default;

        Matrix(MatSize nRows, MatSize nCols, MatSize nChannels);


    private:


        MatSize rows, cols, channels;

        MatType content;


    };

}


#endif
