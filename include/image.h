#ifndef IMAGE_H
#define  IMAGE_H

#include <string>

#include "format.h"
#include "jpeg_format.h"
#include "ppm_format.h"
#include "png_format.h"

namespace sfic{

    class Image{

    public:


        Image() = default;

        explicit Image(std::string const& path);


        void save(std::string const& path) const;

        void convert(FormatContainer const& newFormat);


        static FormatContainer stringToFormat(std::string const& formatName);

    private:

        static std::string getExtension(std::string const& path);

        static std::string reverse(std::string const& s);

        FormatContainer format;

    };



}


#endif
