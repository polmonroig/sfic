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
    if(data.size() == 0)throw ErrorInputOutput("Error: Input file is empty");
    while(iterator < SIGNATURE_SIZE){
        if(data.get(iterator) != signature[iterator]){
            throw IncorrectFormat("Error while reading PNG, signature does not match");
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
