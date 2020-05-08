#include "../include/png_format.h"


using namespace sfic;

/************************
        PUBLIC
*************************/

Matrix PNGFormat::decode(){
    return Matrix();
}

void PNGFormat::encode(Matrix decodedImage){
    decodedImage = decodedImage;
    filtering();
    deflate();
    data.push("PNG FORMAT");

}




/************************
        PRIVATE
*************************/


void PNGFormat::filtering(){

}

void PNGFormat::deflate(){

}
