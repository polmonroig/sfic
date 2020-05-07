#include "../include/jpeg_format.h"


using namespace sfic;

/************************
        PUBLIC
*************************/

Matrix JPEGFormat::decode(){
    return Matrix();
}

void JPEGFormat::encode(Matrix decodedImage){
    std::cout << "Encoding" << std::endl;
    decodedImage.toYCbCr();

}




/************************
        PRIVATE
*************************/
