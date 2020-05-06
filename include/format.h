#ifndef FORMAT_H
#define  FORMAT_H

#include <string>
#include <memory>

namespace sfic{




    class Format{


    public:

        virtual void convert() = 0;


    private:


    };


    typedef std::shared_ptr<Format> FormatContainer;

}


#endif
