#ifndef IMAGE_H
#define  IMAGE_H

#include <string>

#include "raw_data.h"

namespace sfic{

    class Image{

    public:

        Image() = default;

        Image(std::string const& imagePath);

    private:

        RawData data;

    };



}


#endif
