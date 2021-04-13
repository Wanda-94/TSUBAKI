#ifndef __TSUBAKI_TEXTURE__
#define __TSUBAKI_TEXTURE__

#include <utility/basic.h>

class Texture{
    public:
    Texture(const std::string& init_label,
    unsigned char* init_data,
    const int init_width,
    const int init_height,
    const int init_channels);
    ~Texture();
    void* GetData();
    void ActiveTexture(int active_texture_index = 0);
    private:
    void GenGLTexture(int repeat_pattern = GL_REPEAT,int mag_filter_pattern = GL_LINEAR,int min_filter_pattern = GL_LINEAR_MIPMAP_LINEAR);
    unsigned int TBO;
    int width;
    int height;
    int channels;
    DataType data_type;
    DataFormatType data_format;
    void* data;
    std::string label;
};
const int ChannelsToDataFormat[5] = {
    -1,
    0,
    -1,
    1,
    2
};
const int DataFormatToGLFormat[3] = {
    GL_R8,
    GL_RGB8,
    GL_RGBA8
};
const int DataFormatToExternalFormat[3] ={
    GL_RED,
    GL_RGB,
    GL_RGBA
};
#endif