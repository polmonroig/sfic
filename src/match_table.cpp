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

#include "../include/match_table.h"

using namespace sfic;


MatchTable::MatchTable(){
    maxTableSize = 0;
}

MatchTable::MatchTable(int size){
    maxTableSize = size;
}


void MatchTable::add(ByteArray const& literal, int position){
    auto match = table.find(literal);
    if(match != table.end()){ // entry already exists
        match->second.push_back(position);
    }
    else{
        table.insert({literal, {position}});
    }
}


PositionListType MatchTable::find(ByteArray const& literal){
    auto match = table.find(literal);
    if(match != table.end()) return match->second;
    else return PositionListType(); // empty array
}
