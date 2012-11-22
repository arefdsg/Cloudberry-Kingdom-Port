﻿#ifndef LAMBDA_1
#define LAMBDA_1

namespace CloudberryKingdom
{
	template<typename T>
	class Lambda_1
	{
	public:
		virtual void Apply( const std::shared_ptr<T> &t ) = 0;
	};
}


#endif	//#ifndef LAMBDA_1