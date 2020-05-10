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
#ifndef EXCEPTION_HANDLER_H
#define  EXCEPTION_HANDLER_H

/************************
    EXCEPTION HANDLER
Contains multiple exception definitions
for the multiple situations that the
image manipulation can cause
*************************/

#include <exception>
#include <string>

namespace sfic{

    /************************
        EXCEPTION DECLARATION
    *************************/

    // needs to be thrown when an incorrect argument
    // is provided by the user
    class IncorrectArgument : public std::exception{

    public:

        IncorrectArgument(std::string const& arg);

        char const * what() const throw();

    private:
        std::string text;
    };

    // needs to be thrown when the format of the image that
    // is being read is incorrect
    class IncorrectFormat : public std::exception{

    public:

        IncorrectFormat(std::string const& formatName);

        char const * what() const throw();

    private:
        std::string text;
    };

    // needs to be thrown when an i/o error ocurrs
    class ErrorInputOutput : public std::exception{

    public:

        ErrorInputOutput(std::string const& formatName);

        char const * what() const throw();

    private:
        std::string text;
    };



}


#endif
