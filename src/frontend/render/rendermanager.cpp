#include "rendermanager.h"

SPINDULYS_NAMESPACE_OPEN_SCOPE

RenderManager::RenderManager()
{
}

void RenderManager::Trace(const RenderGlobals& renderGlobals,
		SceneManager &sceneManager,
		Camera& camera,
		Buffer& buffer,
		int iterations)
{
	tbb::parallel_for(tbb::blocked_range<int>(0, renderGlobals.height), [&](tbb::blocked_range<int> height_range)
		{
			for (int pixelY = height_range.begin(); pixelY < height_range.end(); ++pixelY)
			{
				Sampler sampler;

				for (int pixelX = 0; pixelX < renderGlobals.width; ++pixelX)
				{
					// We setup all the necessary data describing the current sample.
					PixelSample pixelSample(sampler, pixelX, pixelY, pixelX + pixelY * renderGlobals.width, renderGlobals.samples, 0);

					// The final pixel color of the sample we are computed that will be added and averaged to the buffer.
					embree::Vec3f pixelColor(0.0f);

					for (int sample = 0; sample < renderGlobals.samples; ++sample)
					{
						Ray primaryRay(camera, pixelSample);

						pixelColor += (embree::Vec3f(buffer.GetPixel(pixelSample.pixelIdx) * (iterations - 1)) +
								integrators[static_cast<int>(renderGlobals.integratorID)]->GetPixelColor(primaryRay,
									pixelSample,
									sceneManager,
									renderGlobals)) * (1.0f / renderGlobals.samples);

						// Random noise test
						// pixelColor += (embree::Vec3f(buffer.GetPixel(pixelSample.pixelIdx) * (iterations - 1)) +
						//     embree::Vec3f(pixelSample.sampler.Uniform1D(),
						//         pixelSample.sampler.Uniform1D(),
						//         pixelSample.sampler.Uniform1D())) * (1.0f / renderGlobals.samples);

						++pixelSample.sampleIdx;
					}

					buffer.SetPixel(pixelSample.pixelIdx, pixelColor / iterations);
				}
			}
		});
}


SPINDULYS_NAMESPACE_CLOSE_SCOPE
