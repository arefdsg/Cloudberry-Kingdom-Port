#ifndef BOBPHSXCHARSELECT
#define BOBPHSXCHARSELECT

#include <small_header.h>

#include "Game/Player/Hero Physics/Normal.h"

namespace CloudberryKingdom
{

	struct BobPhsxCharSelect : public BobPhsxNormal
	{
	
		virtual ~BobPhsxCharSelect()
		{
#ifdef BOOST_BIN
			OnDestructor( "BobPhsxCharSelect" );
#endif
		}


		bool OverrideAnimBehavior;

		virtual void PhsxStep2();

		virtual void AnimStep();

	
		void InitializeInstanceFields();

	
		BobPhsxCharSelect()
		{
			InitializeInstanceFields();
		}

	};

}


#endif	//#ifndef BOBPHSXCHARSELECT
