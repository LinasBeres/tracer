#include "buffer.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

void Buffer::Init(int width,
		int height)
{
	_pixelData.resize(width * height);
}

void Buffer::Clean(int width,
		int height)
{
	_pixelData.clear();
	_pixelData.shrink_to_fit();
	_pixelData.resize(width * height);
}

void Buffer::Swap(Buffer& buffer)
{
	_pixelData.swap(buffer._pixelData);
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
