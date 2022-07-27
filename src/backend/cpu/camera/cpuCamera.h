#include <camera/camera.h>


class CPUCamera : Camera
{
	public:
		enum Projection {
			Perspective = 0,
			Orthographic,
		};

		Camera();

}
