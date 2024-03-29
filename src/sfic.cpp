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

#include "../arg_parser/include/arg_parser.h"

#include "../include/exception_handler.h"
#include "../include/image.h"
#include "../include/jpeg_format.h"



int main(int argc, char* argv[]){


    ap::ArgParser parser;
    parser.addArgument(ap::Argument("input", 'i', "input data", ap::ArgumentType::String, true));
    parser.addArgument(ap::Argument("output", 'o', "output compression", ap::ArgumentType::String, true));
    auto enumeration = ap::Argument("type", 't', "Specify compression algorithm", ap::ArgumentType::Enum, true);
    enumeration.addValue("lz77");
    enumeration.addValue("huffman");
    enumeration.addValue("both");
    parser.addArgument(enumeration);

    auto parsed = parser.parse(argc, argv);

    if(parser.find("help")){
        std::cerr << parser.usage("sfic");
        return EXIT_SUCCESS;
    }

    if(!parsed){
        std::cerr << parser.log();
        return EXIT_FAILURE;
    }

    try{

        if(parser.get("type") == "lz77"){
            sfic::LZ77 encoder;
            sfic::RawData data;
            data.read(parser.get("input"));

            data = encoder.encode(data);
            data.write(parser.get("output"));
        }
        else if(parser.get("type") == "huffman"){

            sfic::HuffmanCompression encoder;
            sfic::RawData data;
            data.read(parser.get("input"));
            data = encoder.encode(data);
            data.write(parser.get("output"));
            //data = encoder.decode(data);
            //data.write("result.txt");
        }
        else if(parser.get("type") == "both"){
            sfic::HuffmanCompression encoder1;
            sfic::LZ77 encoder2;
            sfic::RawData data;
            data.read(parser.get("input"));
            data = encoder1.encode(data);
            data = encoder2.encode(data);
            data.write(parser.get("output"));
        }



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
