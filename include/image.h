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
#ifndef IMAGE_H
#define  IMAGE_H

#include <string>
#include "exception_handler.h"

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
