#ifndef CLOSINGCIRCLE
#define CLOSINGCIRCLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class QuadClass;
}

namespace CloudberryKingdom
{
	class Camera;
}

namespace CloudberryKingdom
{
	class IPos;
}

namespace CloudberryKingdom
{
	class ClosingCircle
	{
	private:
		std::shared_ptr<QuadClass> Circle;
		std::shared_ptr<Camera> MyCamera;

		std::shared_ptr<IPos> CenterObj;
		Vector2 CenterPos;

		float Speed;

	public:
		int FinishedCount;

		ClosingCircle( const std::shared_ptr<Camera> &camera, float Frames );
		ClosingCircle( const std::shared_ptr<Camera> &camera, float Frames, const std::shared_ptr<IPos> &Center );
		ClosingCircle( const std::shared_ptr<Camera> &camera, float Frames, Vector2 Center );

	private:
		void Init( const std::shared_ptr<Camera> &camera, float Frames );

		float angle;
	public:
		void UpdateCircle();

	private:
		bool Done;
	public:
		void Draw();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef CLOSINGCIRCLE