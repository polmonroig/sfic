#ifndef RAW_DATA_H
#define  RAW_DATA_H

#include <vector>
#include <fstream>
#include <iostream>

#include "format.h"

namespace sfic{

    class RawData{

    public:

        void read(std::string const& path);

        void write(std::string const& path) const;

        void convert(FormatContainer const& newFormat);

    private:

        FormatContainer format;

        typedef unsigned char ByteType;

        std::vector<ByteType> bytes;

    };


}


#endif
