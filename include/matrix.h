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

        inline void set(MatSize i, MatSize j, ChannelType const& channel);

        inline MatSize width() const;

        inline MatSize height() const;

        inline ChannelType get(MatSize i, MatSize j) const;

    private:


        MatSize rows, cols, channels;

        MatType content;


    };

    /************************
       INLINE DEFINITIONS
    *************************/

    inline MatSize Matrix::width() const{
        return cols;
    }

    inline MatSize Matrix::height() const{
        return rows;
    }

    inline ChannelType Matrix::get(MatSize i, MatSize j) const{
        return content[i][j];
    }


    inline void Matrix::set(MatSize i, MatSize j, ChannelType const& channel){
        content[i][j] = channel;
    }

}


#endif
