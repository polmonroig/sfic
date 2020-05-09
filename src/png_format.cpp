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

}




/************************
        PRIVATE
*************************/


void PNGFormat::filtering(Matrix& decodedImage ){
    decodedImage = decodedImage;
}

void PNGFormat::deflate(Matrix& decodedImage){
    data = decodedImage.toRawData();
    // first lz77 compression
    LZ77 compressor;
    data = compressor.encode(data);
    // next compress further with huffman
    HuffmanCompression huffman;
    data = huffman.encode(data); 

}
