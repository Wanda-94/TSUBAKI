#include <component/texture.h>
#include <utility/importer.h>

Texture::Texture(const std::string& init_label,
    unsigned char* init_data,
    const int init_width,
    const int init_height,
    const int init_channels):label(init_label),width(init_width),height(init_height),channels(init_channels)
{
    this->data = init_data;
    this->data_type = DataType::CHAR;
    this->data_format = (DataFormatType)(ChannelsToDataFormat[this->channels]);
    GenGLTexture();
}

Texture::~Texture()
{
    glDeleteTextures(1,&TBO);
    Importer::FreeTexture(this);
}

void* Texture::GetData()
{
    return this->data;
}

void Texture::GenGLTexture(int repeat_pattern,int mag_filter_pattern,int min_filter_pattern)
{
    glGenTextures(1,&(this->TBO));
    glBindTexture(GL_TEXTURE_2D,this->TBO);
    glTexImage2D(GL_TEXTURE_2D,
    0,
    DataFormatToGLFormat[(int)(this->data_format)],
    //GL_RGB8,
    this->width,
    this->height,
    0,
    DataFormatToExternalFormat[(int)(this->data_format)],
    //GL_RGB,
    GL_UNSIGNED_BYTE,
    this->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,repeat_pattern);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,repeat_pattern);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,min_filter_pattern);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,mag_filter_pattern);
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture::ActiveTexture(int  active_texture_index)
{
    glActiveTexture(GL_TEXTURE0 + active_texture_index);
    glBindTexture(GL_TEXTURE_2D,this->TBO);
}