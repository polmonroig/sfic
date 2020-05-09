#include <iostream>
#include <exception>

#include "../include/image.h"
#include "../include/jpeg_format.h"


void usage(){
    std::cout << "  Usage: sfic input output format" << std::endl << std::endl;
    std::cout << "  input: image to be converted" << std::endl;
    std::cout << "  output: output compression" << std::endl;
    std::cout << "  format: the format to be converted to (JPEG, PNG, PPM, TIF, GIF)" << std::endl<< std::endl;

}


int main(int argc, char* argv[]){

    if(argc < 4){
        usage();
        return -1;
    }

    try{

        // create image
        sfic::Image image(argv[1]);
        // convert
        sfic::FormatContainer newFormat = sfic::Image::stringToFormat(argv[3]);
        image.convert(newFormat);
        // save to file
        image.save(argv[2]);
    }
    catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }



    return 0;
}
