#ifndef OUTPUT_HELPER_H
#define OUTPUT_HELPER_H

#define TINYEXR_IMPLEMENTATION

#include <tinyexr.h>

#include <spindulys/math/vec3.h>
#include <spindulys/buffer.h>

#include "spindulysGUI.h"


GUI_NAMESPACE_OPEN_SCOPE

inline void toPPM(unsigned int width, unsigned int height, const Buffer3f& buffer)
{
	FILE *ppmFile(fopen("spindulys_render.ppm", "w"));
	fprintf(ppmFile, "P3\n%d %d\n%d\n", width, height, 255);

	const std::vector<Col3f>& pixelData = buffer.GetPixelData();
	for (unsigned int pixelIdx = 0; pixelIdx < (width * height); ++pixelIdx)
	{
		// A lot faster than using std::ofstream or std::ostream_iterator/std::copy, actually.
		const Col3f outputPixel = toRGB(toSRGB(pixelData[pixelIdx]));
		fprintf(ppmFile, "%d %d %d ", static_cast<int>(outputPixel.r), static_cast<int>(outputPixel.g), static_cast<int>(outputPixel.b));
	}

	fclose(ppmFile);
}

// Based on TinyEXR way of saving a scanline EXR file
inline void toEXR(unsigned int width, unsigned int height, const Buffer3f& buffer)
{
	EXRHeader exrHeader;
	EXRImage exrImage;

	InitEXRHeader(&exrHeader);
	InitEXRImage(&exrImage);

	// TODO: Make the switch to RGBA, should template the Vector class to do so conveniently
	std::vector<float> channels[3];
	channels[0].resize(width * height); // R channel
	channels[1].resize(width * height); // G channel
	channels[2].resize(width * height); // B channel

	const std::vector<Col3f>& pixelData = buffer.GetPixelData();
	for (unsigned int pixelIdx = 0; pixelIdx < (width * height); ++pixelIdx)
	{
		channels[0][pixelIdx] = pixelData[pixelIdx].r;
		channels[1][pixelIdx] = pixelData[pixelIdx].g;
		channels[2][pixelIdx] = pixelData[pixelIdx].b;
	}

	// We are swapping the channel order to BGR as many EXR file viewers are expecting this specific order,
	// such as Pixar/Renderman's "it"
	float* channelsPtr[3];
	channelsPtr[0] = &(channels[2].at(0)); // B
	channelsPtr[1] = &(channels[1].at(0)); // G
	channelsPtr[2] = &(channels[0].at(0)); // R

	exrImage.num_channels = 3;
	exrImage.images = (unsigned char**)channelsPtr;
	exrImage.width = width;
	exrImage.height = height;

	exrHeader.num_channels = 3;
	exrHeader.channels = (EXRChannelInfo *)malloc(sizeof(EXRChannelInfo) * exrHeader.num_channels);

	std::strncpy(exrHeader.channels[0].name, "B", 255);
	std::strncpy(exrHeader.channels[1].name, "G", 255);
	std::strncpy(exrHeader.channels[2].name, "R", 255);
	exrHeader.channels[0].name[std::strlen("B")] = '\0';
	exrHeader.channels[1].name[std::strlen("G")] = '\0';
	exrHeader.channels[2].name[std::strlen("R")] = '\0';

	exrHeader.pixel_types = (int *)malloc(sizeof(int) * exrHeader.num_channels);
	exrHeader.requested_pixel_types = (int *)malloc(sizeof(int) * exrHeader.num_channels);

	for (unsigned int channelIdx = 0; channelIdx < static_cast<unsigned int>(exrHeader.num_channels); ++channelIdx)
	{
		exrHeader.pixel_types[channelIdx] = TINYEXR_PIXELTYPE_FLOAT; // Pixel type we are feeding the EXR
		exrHeader.requested_pixel_types[channelIdx] = TINYEXR_PIXELTYPE_HALF; // Pixel type we want to use as output in the EXR
	}

	const char* exrError;
	int exrResult(SaveEXRImageToFile(&exrImage, &exrHeader, "spindulys_render.exr", &exrError));

	if (exrResult != TINYEXR_SUCCESS)
	{
		fprintf(stderr, "EXR Error: %s\n", exrError);
	}

	free(exrHeader.channels);
	free(exrHeader.pixel_types);
	free(exrHeader.requested_pixel_types);
}

GUI_NAMESPACE_CLOSE_SCOPE

#endif // OUTPUT_HELPER_H
