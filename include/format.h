#ifndef FORMAT_H
#define  FORMAT_H

#include <string>
#include <memory>

#include "raw_data.h"
#include "matrix.h"

namespace sfic{




    class Format{


    public:

        virtual void read(std::string const& path);

        virtual void write(std::string const& path);

        virtual void encode(Matrix decodedImage) = 0;

        virtual Matrix decode() = 0;

    protected:

        RawData data;

        MatInt iterator;


    };


    typedef std::shared_ptr<Format> FormatContainer;

}


#endif
