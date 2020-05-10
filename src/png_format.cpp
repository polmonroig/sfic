#include "../include/png_format.h"


using namespace sfic;

// STATIC



/************************
        PUBLIC
*************************/

Matrix PNGFormat::decode(){
    readSignature();

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

void PNGFormat::readSignature(){
    iterator = 0;
    while(iterator < SIGNATURE_SIZE){
        if(data.get(iterator) != signature[iterator]){
            std::cerr << "Throw format exception" << std::endl;
        }
        ++iterator;
    }

}


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
