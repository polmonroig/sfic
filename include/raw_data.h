#ifndef RAW_DATA_H
#define  RAW_DATA_H

#include <vector>
#include <string>
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

        inline void push(std::string const& value);

        inline void push(ByteType value);


    private:



        std::vector<ByteType> bytes;

    };


    /************************
       INLINE DEFINITIONS
    *************************/

    inline void RawData::push(std::string const& value){
        for(auto const& v : value)bytes.push_back(v);
    }

    inline ByteType RawData::get(unsigned int pos) const{
        return bytes[pos];
    }

    inline unsigned int RawData::size() const{
        return bytes.size();
    }

    inline void RawData::push(ByteType value){
        bytes.push_back(value); 
    }

}






#endif
