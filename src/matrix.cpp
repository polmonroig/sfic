#include "../include/matrix.h"

using namespace sfic;

/************************
        PUBLIC
*************************/


Matrix::Matrix(MatSize nRows, MatSize nCols, MatSize nChannels){
    rows = nRows;
    cols = nCols;
    channels = nChannels;
    content = MatType(nRows, RowType(nCols, ChannelType(nChannels)));
    
}


/************************
        PRIVATE
*************************/
