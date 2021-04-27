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
#ifndef MATCH_TABLE_H
#define MATCH_TABLE_H

#include <list>
#include <map>

#include "raw_data.h"

namespace sfic{


    typedef std::list<int> PositionListType;

    class MatchTable{

    public:

        MatchTable();

        MatchTable(int size);

        // literal has at most MIN_LENGTH_CHARACTERS
        void add(ByteArray const& literal, int position);

        // if match is not found it returns an empty list
        PositionListType find(ByteArray const& literal);

    private:

        int maxTableSize;

        std::map<ByteArray, PositionListType> table;

    };

}


#endif
