#include "camera.h"


FRONTEND_NAMESPACE_OPEN_SCOPE

Camera::Camera()
{
}

void Camera::Init()
{
	// TODO: Hardcoded information for now.
	_position = Vec3f(0, 4, 15);
	_yaw = 90;
	_pitch = 6;
	_fov.x = 45;
	_apertureRadius = 0;
	_focalDistance = 4;

	_up = normalize(Vec3f(0.0f, 1.0f, 0.0f));
	_speed = 10.0f;
	_sensitivity = 0.10f;

	SetupFOV();
	Update();
}

void Camera::SetupFOV()
{
	_fov.y = (atan(tan(_fov.x * M_PI * M_1_180 * 0.5f)
				* ((float)_resolution.y / (float)_resolution.x)) * 2.0f)
		* 180.0f * M_1_PI;
}

void Camera::Update()
{
	Vec3f front(cos(DegToRad(_yaw)) * cos(DegToRad(_pitch)),
			sin(DegToRad(_pitch)),
			sin(DegToRad(_yaw)) * cos(DegToRad(_pitch))
			);

	front *= -1.0f;

	_front = normalize(front);
	_right = normalize(cross(_front, _up));
}

void Camera::KeyboardCallback(CAMERA_MOVEMENTS direction,
		float deltaTime)
{
	float velocity(_speed * deltaTime);

	if (direction == Forward)
	{
		_position += _front * velocity;
	}
	if (direction == Backward)
	{
		_position -= _front * velocity;
	}
	if (direction == Left)
	{
		_position -= _right * velocity;
	}
	if (direction == Right)
	{
		_position += _right * velocity;
	}
}

void Camera::MouseCallback(const Vec2f& mouseOffset)
{
	_yaw += mouseOffset.x * _sensitivity;
	_pitch += mouseOffset.y * _sensitivity;

	if (_pitch > 89.0f)
	{
		_pitch = 89.0f;
	}
	if (_pitch < -89.0f)
	{
		_pitch = -89.0f;
	}

	Update();
}

bool Camera::SetResolution(const Vec2f& resolution)
{
	return _resolution == std::exchange(_resolution, resolution);
}

bool Camera::SetJitter(bool jitter)
{
	return _jitter == std::exchange(_jitter, jitter);
}

bool Camera::SetFocalDistance(float focalDistance)
{
	return _focalDistance == std::exchange(_focalDistance, focalDistance);
}

bool Camera::SetAperatureRadius(float aperatureRadius)
{
	return _apertureRadius == std::exchange(_apertureRadius, aperatureRadius);
}

FRONTEND_NAMESPACE_CLOSE_SCOPE
