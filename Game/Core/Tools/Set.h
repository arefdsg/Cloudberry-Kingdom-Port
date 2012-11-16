#ifndef SET
#define SET

#include "Random.h"
#include <unordered_map>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	template<typename T>
	class Set : public IEnumerable, public IEnumerable<T>
	{
	public:
		std::unordered_map<T, bool> dict;

		const int &getCount() const
		{
			return dict.size();
		}

		bool operator []( T item )
		{
			return dict.find( item ) != dict.end();
		}

		std::shared_ptr<Set<T> > operator + ( T item )
		{
			if ( !this->dict.find( item ) != this->dict.end() )
				this->dict.insert( make_pair( item, true ) );

			return this;
		}

		std::shared_ptr<IEnumerator> IEnumerable_GetEnumerator()
		{
			return dict.Keys->GetEnumerator();
		}
		std::shared_ptr<IEnumerator<T> > GetEnumerator()
		{
			return dict.Keys->GetEnumerator();
		}

		T Choose( const std::shared_ptr<Rand> &Rnd )
		{
			int i = Rnd->RndInt( 0, dict.size() - 1 );
			return dict.ElementAt( i )->Key;
		}

		bool Contains( T item )
		{
			if ( item == 0 )
				return true;
			else
				return dict.find( item ) != dict.end();
		}


	private:
		void InitializeInstanceFields()
		{
			dict = std::unordered_map<T, bool>();
		}

public:
		Set()
		{
			InitializeInstanceFields();
		}
	};
}


#endif	//#ifndef SET
