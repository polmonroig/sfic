#ifndef IMAGE_H
#define  IMAGE_H

#include <string>

#include "raw_data.h"

namespace sfic{

    class Image{

    public:


        Image() = default;

        explicit Image(std::string const& path);


        void save(std::string const& path) const;

        void convert(FormatContainer const& newFormat);

    private:


        RawData data;

    };



}


#endif
