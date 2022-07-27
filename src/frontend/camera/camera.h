#ifndef CAMERA_H
#define CAMERA_H

#include <spindulys.h>

// #include <embree3/common/math/vec4.h>

#include <embree3/common/math/vec2.h>
#include <embree3/common/math/vec3.h>
#include <embree3/rtcore.h>
#include <embree3/rtcore_ray.h>

#include <spindulys/mathHelper.h>

SPINDULYS_NAMESPACE_OPEN_SCOPE

class Camera
{
	public:
		enum Projection {
			Perspective = 0,
			Orthographic,
		};

		enum CAMERA_MOVEMENTS
		{
		    Forward,
		    Backward,
		    Left,
		    Right
		};

		Camera();

		void Init();
		void Update();
		void SetupFOV();
		void KeyboardCallback(CAMERA_MOVEMENTS direction,
				float deltaTime);
		void MouseCallback(embree::Vec2fa mouseOffset);

		// Set Methods
		// bool SetProjection(Projection projection);
		// bool SetHorizontalAperature(float horizontalAperature);
		// bool SetVerticalAperature(float verticalAperature);
		// bool SetHorizontalAperatureOffset(float horizontalApertatureOffset);
		// bool SetVerticalAperatureOffset(float verticalAperatureOffset);
		// bool SetFocalLength(float focalLength);
		// bool SetFar(float far);
		// bool SetClose(float close);
		// bool SetFStop(float fStop);
		// bool SetFocusDistance(float focusDistance);

		bool SetResolution(const embree::Vec2fa& position);
		bool SetJitter(bool jitter);
		bool SetFocalDistance(float focalDistance);
		bool SetAperatureRadius(float aperatureRadius);

		// Get Methods
		bool GetJitter() const { return _jitter; }
		float GetYaw() const { return _yaw; }
		float GetPitch() const { return _pitch; }
		float GetSpeed() const { return _speed; }
		float GetSensitivity() const { return _sensitivity; }
		float GetAperatureRadius() const { return _apertureRadius; }
		float GetFocalDistance() const { return _focalDistance; }
		const embree::Vec2fa& GetResolution() const { return _resolution; }
		const embree::Vec2fa& GetFov() const { return _fov; }
		const embree::Vec3fa& GetPosition() const { return _position; }
		const embree::Vec3fa& GetFront() const { return _front; }
		const embree::Vec3fa& GetUp() const { return _up; }
		const embree::Vec3fa& GetRight() const { return _right; }

	private:
		// GfMatrix4d _transform;
		// Projection                    _projection;
		// float                         _horizontalAperature;
		// float                         _verticalAperature;
		// float                         _horizontalApertureOffset;
		// float                         _verticalApertureOffset;
		// float                         _focalLength;
		// float                         _far;
		// float                         _close;
		// std::vector<embree::Vec4f>    _clippingPlanes;

		// focus
		// float                   _fStop;
		// float                   _focusDistance;


		bool _jitter = true;
		float _yaw;
		float _pitch;
		float _speed;
		float _sensitivity;
		float _apertureRadius;
		float _focalDistance;
		embree::Vec2fa _resolution;
		embree::Vec2fa _fov;
		embree::Vec3fa _position;
		embree::Vec3fa _front;
		embree::Vec3fa _up;
		embree::Vec3fa _right;
};

SPINDULYS_NAMESPACE_CLOSE_SCOPE

#endif // CAMERA_H
