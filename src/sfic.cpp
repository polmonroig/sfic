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
#include <iostream>
#include "../include/exception_handler.h"

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
    catch(sfic::ErrorInputOutput& e){
        std::cerr << e.what() << std::endl;
    }
    catch(sfic::IncorrectArgument& e){
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }



    return 0;
}
