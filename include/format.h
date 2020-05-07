#ifndef FORMAT_H
#define  FORMAT_H

#include <string>
#include <memory>

namespace sfic{




    class Format{


    public:

        virtual void encode() = 0;

        virtual void decode() = 0;

    private:


    };


    typedef std::shared_ptr<Format> FormatContainer;

}


#endif
