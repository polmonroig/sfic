#ifndef EXCEPTION_HANDLER_H
#define  EXCEPTION_HANDLER_H

/************************
    EXCEPTION HANDLER
Contains multiple exception definitions
for the multiple situations that the
image manipulation can cause
*************************/

#include <exception>

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
    };

    // needs to be thrown when the format of the image that
    // is being read is incorrect
    class IncorrectFormat : public std::exception{

    public:

        IncorrectFormat(std::string const& formatName);

        char const * what() const throw();
    };



}


#endif
