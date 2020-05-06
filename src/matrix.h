#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

#include "channel.h"

namespace sfic{

    class Matrix{

    public:


    private:

        /**
         * Container for the data, with two dimensions
         */
        std::vector<std::vector<Channel>> content;


    };



}
