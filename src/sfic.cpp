#include <iostream>

#include "../include/image.h"


void usage(){
    std::cout << "  Usage: sfic input output format" << std::endl;
    std::cout << "  input: image to be converted" << std::endl;
    std::cout << "  output: output compression" << std::endl;

}


int main(int argc, char* argv[]){

    if(argc < 3){
        usage();
        return -1;
    }

    sfic::Image image(argv[1]);
    image.save(argv[2]);


    return 0;
}
