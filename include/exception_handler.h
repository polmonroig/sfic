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
