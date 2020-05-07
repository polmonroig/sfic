#ifndef RAW_DATA_H
#define  RAW_DATA_H

#include <vector>
#include <fstream>
#include <iostream>


namespace sfic{

    class RawData{

    public:

        void read(std::string const& path);

        void write(std::string const& path) const;

    private:

        typedef unsigned char ByteType;

        std::vector<ByteType> bytes;

    };


}


#endif
