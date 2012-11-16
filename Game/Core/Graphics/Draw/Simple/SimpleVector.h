﻿#ifndef SIMPLEVECTOR
#define SIMPLEVECTOR

#include "../Core/IViewable.h"
#include "../Core/Animation/AnimationData_Vector.h"
#include "../Core/Graphics/VertexFormat.h"
#include <string>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::IO;

namespace CloudberryKingdom
{
	class SimpleVector : public IReadWrite
	{
	public:
		AnimationData AnimData;
		MyOwnVertexFormat Vertex;
		Vector2 Pos;

		void RotateRight();

		void RotateLeft();

		void Release();

	private:
		static std::vector<std::wstring> _bits_to_save;
	public:
		void WriteCode( const std::wstring &prefix, const std::shared_ptr<StreamWriter> &writer );
		void Write( const std::shared_ptr<StreamWriter> &writer );
		void Read( const std::shared_ptr<StreamReader> &reader );
	};
}


#endif	//#ifndef SIMPLEVECTOR
