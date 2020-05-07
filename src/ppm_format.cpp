#include "../include/ppm_format.h"


using namespace sfic;

/************************
        PUBLIC
*************************/


Matrix PPMFormat::decode(){
    iterator = 0;
    auto p = readType();
    auto width = readSize();
    auto height = readSize();
    auto maxSize = readSize();
    std::cout << "Image of size (" << width << "," << height << ")\n";
    if(p == PPMType::P3){
        std::cout << "Image with type P3 found" << std::endl;
        return readP3(width, height);
    }
    else{
        std::cout << "Image with type P6 found, currently unsuported" << std::endl;
        return readP6(width, height);
    }

}

void PPMFormat::encode(Matrix decodedImage){
    auto width = decodedImage.width();
    auto height = decodedImage.height();
    std::cout << "New image has width " << width << std::endl;
    std::cout << "New image has height " << height << std::endl;
    data.push("P6\n");
    data.push(std::to_string(width) + " ");
    data.push(std::to_string(height) + "\n");
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j){
            auto color = decodedImage.get(i, j);
            for(auto const& value : color){
                data.push(std::to_string(value) + " ");
            }
        }
        data.push('\n');

    }

}




/************************
        PRIVATE
*************************/

inline void PPMFormat::skipComment(){
    while(data.get(iterator) != '\n')++iterator;
    ++iterator; // goto next line
}


inline bool PPMFormat::skipEmpty(){
    if(data.get(iterator) == '#'){
        skipComment();
        return true;
    }
    else if(data.get(iterator) == '\n' || data.get(iterator) == ' '){
        ++iterator; // skip empty
        return true;
    }
    return false;
}


PPMType PPMFormat::readType(){
    while(iterator < data.size()){
        if(!skipEmpty()){
            // current pos is not empty
            if(data.get(iterator) == 'P')++iterator;
            else if(data.get(iterator) == '3'){
                iterator++;
                return PPMType::P3;
            }
            else if(data.get(iterator) == '6'){
                iterator++;
                return PPMType::P6;
            }
        }
    }
    return PPMType::P3;
}

inline MatSize PPMFormat::readSize(){
    std::string value = "";
    while(iterator < data.size()){
        bool found = false;
        while(!skipEmpty()){
            found = true;
            value += data.get(iterator);
            ++iterator;
        }
        if(found)return std::stoi(value);
    }
    return std::stoi(value);
}

Matrix PPMFormat::readP3(MatSize width, MatSize height){
    Matrix image(width, height, N_CHANNELS);
    int i, j;
    i = j = 0; // matrix iterators
    while(iterator < data.size()){
        if(!skipEmpty()){
            auto r = readSize();
            auto g = readSize();
            auto b = readSize();
            ChannelType channel{r, g, b};
            image.set(i, j, channel);
            ++j;
            if(j >= width){
                i++;
                j = 0;
            }
            std::cout << "Value (" << r << "," << g << ","<< b << ")\n";

        }
    }
    return image;
}

Matrix PPMFormat::readP6(MatSize width, MatSize height){
    Matrix image(width, height, N_CHANNELS);

    return image;
}
