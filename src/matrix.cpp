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
                data.push(char(channel * 255));
            }
        }
    }
    return data;
}


/************************
        PRIVATE
*************************/
