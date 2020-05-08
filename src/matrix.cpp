#include "../include/matrix.h"

using namespace sfic;

/************************
        PUBLIC
*************************/


Matrix::Matrix(MatInt nRows, MatInt nCols, MatInt nChannels){
    rows = nRows;
    cols = nCols;
    channels = nChannels;
    content = MatType(nRows, RowType(nCols, ChannelType(nChannels)));

}


void Matrix::toYCbCr(){
    // PRE: channels.size() >= 3 (i.e. rgb)
    for(unsigned int i = 0; i < rows; ++i){
        for(unsigned int j = 0; j < cols; ++j){
            auto colors = content[i][j];
            float y = 0.299 * colors[0] + 0.587 * colors[1] + 0.114 * colors[2];
            float cb = -0.169 * colors[0] - 0.331 * colors[1] + 0.5 * colors[2];
            float cr = 0.5 * colors[0] - 0.419 * colors[1] - 0.081 * colors[2];
            colors[0] = y;
            colors[1] = cb;
            colors[2] = cr;

        }
    }
}

RawData Matrix::toRawData() const{
    RawData data;
    data.reserve(rows * cols * channels);
    for(auto const& row : content){
        for(auto const& col : row){
            for(auto const& channel : col){
                data.push(int(channel * 255));
            }
        }
    }
    return data; 
}


/************************
        PRIVATE
*************************/
