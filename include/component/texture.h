#ifndef __TSUBAKI_TEXTURE__
#define __TSUBAKI_TEXTURE__

#include <utility/basic.h>

class Texture{
    public:
    Texture();
    ~Texture();
    private:
    int width;
    int height;
    int channel;
    DataType data_type;
    void* data;
};

#endif