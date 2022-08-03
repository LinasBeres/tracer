#ifndef SAMPLER_H
#define SAMPLER_H

#include <algorithm>
#include <random>

#include <spindulys/math/vec2.h>
#include <spindulys/math/vec3.h>

#include "../spindulysFrontend.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

struct Sampler
{
	Sampler();

	unsigned NewSeed();
	float Uniform1D();
	Vec2f Uniform2D();
	std::vector<Vec2f> Stratified2D(int samples);
	Vec3f HemisphereUniform(float rand0, float rand1);
	Vec3f HemisphereCosineWeighted(float rand0, float rand1);
	Vec3f SphereUniform(float rand0, float rand1);

	std::uniform_real_distribution<float> floatUniformDistribution;
	std::mt19937 prng;
};

FRONTEND_NAMESPACE_CLOSE_SCOPE

#endif // SAMPLER_H
