#ifndef BUFFER_H
#define BUFFER_H

#include <vector>

#include "../utility/embree_helper.h"


struct Buffer
{
    Buffer();

    void Init(int width,
        int height);
    void Clean(int width,
        int height);
    void Swap(Buffer& buffer);

    std::vector<embree::Vec3f> _pixelData;
};

#endif // BUFFER_H
