﻿#ifndef DOWNDATA
#define DOWNDATA

#include <global_header.h>

namespace CloudberryKingdom
{
	struct Rand;
}


namespace CloudberryKingdom
{
	struct DownData : public VerticalData
	{
	
		virtual ~DownData() { }

		virtual void CalculateKeepUnused( float JumpLevel );

	
		DownData( const boost::shared_ptr<Rand> &Rnd );

		virtual void Randomize();
	};
}


#endif	//#ifndef DOWNDATA
