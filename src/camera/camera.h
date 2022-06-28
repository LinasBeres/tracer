#ifndef CAMERA_H
#define CAMERA_H

#include "../utility/camera_helper.h"
#include "../utility/embree_helper.h"
#include "../utility/math_helper.h"


struct Camera
{
    Camera();

    void Init();
    void Update();
    void SetupFOV();
    void KeyboardCallback(CAMERA_MOVEMENTS direction,
        float deltaTime);
    void MouseCallback(embree::Vec2fa mouseOffset);

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

#endif // CAMERA_H
