#ifndef ARROW
#define ARROW

#include <small_header.h>

//#include "Core/Graphics/Draw/Simple/SimpleObject.h"
//#include "Core/Tools/CoreMath.h"
#include "Game/Objects/Game Objects/GameObject.h"
//#include "Game/Tools/Prototypes.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	struct SimpleObject;
}




namespace CloudberryKingdom
{
	struct Arrow : public GameObject
	{

		virtual ~Arrow()
		{
#ifdef BOOST_BIN
			OnDestructor( "Arrow" );
#endif
		}

	
		enum Orientation
		{
			Orientation_LEFT,
			Orientation_RIGHT
		};
	
		boost::shared_ptr<SimpleObject> MyObject;

		Arrow();

	
		int MyOrientation;

		/// <summary>
		/// Set the orientation of the arrow, to point left or to point right.
		/// </summary>
	
		void SetOrientation( Orientation orientation );

	
		float Scale;
	
		void SetScale( float Scale );

	
		void SetAnimation();

	
		void AnimStep();

	
		virtual void MyPhsxStep();

	
		Vector2 PointToPos;
	
		void PointTo( Vector2 pos );

		void Update();

	
		virtual void MyDraw();

	
		virtual void Move( Vector2 shift );

	
		void InitializeInstanceFields();
	};

}


#endif	//#ifndef ARROW
