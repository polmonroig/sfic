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
#include "../include/exception_handler.h"

using namespace sfic;


IncorrectArgument::IncorrectArgument(std::string const& formatName){
    text = formatName;
}


char const * IncorrectArgument::what() const throw(){
    return text.c_str();
}


IncorrectFormat::IncorrectFormat(std::string const& formatName){
    text = formatName;
}


char const * IncorrectFormat::what() const throw(){
    return text.c_str();
}


ErrorInputOutput::ErrorInputOutput(std::string const& formatName){
    text = formatName;
}


char const * ErrorInputOutput::what() const throw(){
    return text.c_str();
}
