#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <GL/glew.h>
#include "utils.h"

class IndexBuffer
{
private:
    unsigned int rendererId;
    unsigned int count;
public:
    IndexBuffer(const void* data, unsigned int size);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
    inline unsigned int getCount() const { return count; };
};

#endif