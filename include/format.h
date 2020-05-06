#ifndef FORMAT_H
#define  FORMAT_H

#include <string>

namespace sfic{

    typedef std::shared_ptr<Format> FormatContainer;

    class Format{


    public:

        static FormatContainer stringToFormat(std::string const& format);



    private:


    };


}


#endif
