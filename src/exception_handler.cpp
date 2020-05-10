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
