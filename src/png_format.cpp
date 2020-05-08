#include "../include/png_format.h"


using namespace sfic;

/************************
        PUBLIC
*************************/

Matrix PNGFormat::decode(){
    return Matrix();
}

void PNGFormat::encode(Matrix& decodedImage){
    decodedImage = decodedImage;
    filtering(decodedImage);
    deflate(decodedImage);
    data.push("PNG FORMAT");

}




/************************
        PRIVATE
*************************/


void PNGFormat::filtering(Matrix& decodedImage ){
    decodedImage = decodedImage;
}

void PNGFormat::deflate(Matrix& decodedImage ){
    auto data = decodedImage.toRawData();
}
