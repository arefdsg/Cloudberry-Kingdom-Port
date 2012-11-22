﻿#ifndef DOUBLE
#define DOUBLE

#include <global_header.h>

namespace CloudberryKingdom
{
	class BobPhsx;
}

namespace CloudberryKingdom
{
	class ObjectClass;
}




namespace CloudberryKingdom
{
	class BobPhsxDouble : public BobPhsxNormal
	{
	public:
		virtual void Set( const std::shared_ptr<BobPhsx> &phsx );

		static void SetDoubleObject( const std::shared_ptr<ObjectClass> &obj, const std::shared_ptr<BobPhsx> &phsx );

		// Singleton
	protected:
		virtual void InitSingleton();
	private:
		static const std::shared_ptr<BobPhsxDouble> instance;
	public:
		const static std::shared_ptr<BobPhsxDouble> &getInstance() const;

		// Instancable class
		BobPhsxDouble();
	};
}


#endif	//#ifndef DOUBLE