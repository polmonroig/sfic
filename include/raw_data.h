#ifndef RAW_DATA_H
#define  RAW_DATA_H

#include <vector>
#include <fstream>
#include <iostream>


namespace sfic{

    typedef unsigned char ByteType;

    class RawData{

    public:

        void read(std::string const& path);

        void write(std::string const& path) const;

        inline ByteType get(unsigned int pos) const;

        inline unsigned int size() const;

    private:



        std::vector<ByteType> bytes;

    };


    /************************
       INLINE DEFINITIONS
    *************************/


    inline ByteType RawData::get(unsigned int pos) const{
        return bytes[pos];
    }

    inline unsigned int RawData::size() const{
        return bytes.size();
    }


}






#endif
