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
#ifndef RAW_DATA_H
#define  RAW_DATA_H

#include <vector>
#include <exception>
#include <string>
#include <fstream>
#include <iostream>



namespace sfic{

    typedef unsigned char ByteType;
    typedef std::vector<ByteType> ByteArray;

    class RawData{

    public:

        void read(std::string const& path);

        void write(std::string const& path) const;

        void push(std::string const& value);

        void push(ByteType value);

        void reserve(unsigned int size);

        void concatenate(RawData const& other);

        inline ByteType get(unsigned int pos) const;

        inline ByteArray subVector(unsigned int left, unsigned int right) const;

        inline unsigned int size() const;

        static const unsigned int BYTE_SIZE = 8;

    private:



        std::vector<ByteType> bytes;

    };


    /************************
       INLINE DEFINITIONS
    *************************/


    inline ByteArray RawData::subVector(unsigned int left, unsigned int right) const{
        if(left > right){
            throw std::invalid_argument("Index Error: sfic::RawData::subVector left is greater than right" );
        }
        ByteArray::const_iterator first = bytes.begin() + left;
        if(right >= bytes.size()) right = bytes.size() - 1;
        ByteArray::const_iterator last = bytes.begin() + right;
        return ByteArray(first, last); // O(n) construction

    }

    inline ByteType RawData::get(unsigned int pos) const{
        return bytes[pos];
    }

    inline unsigned int RawData::size() const{
        return bytes.size();
    }



}






#endif
