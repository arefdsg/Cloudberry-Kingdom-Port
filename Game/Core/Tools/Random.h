﻿#ifndef RANDOM
#define RANDOM

#define _USE_MATH_DEFINES
#include "../Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include <vector>
#include <cmath>

//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Linq;

using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class Rand
	{
	public:
		int MySeed;
		Rand( int seed );

		std::shared_ptr<System::Random> Rnd;

		Vector2 RndPos( Vector2 BL, Vector2 TR );

		Vector2 RndVector2( float Width );

		/// <summary>
		/// Randomly returns true or false
		/// </summary>
		bool RndBool();
		bool RndBool( float Chance );

		/// <summary>
		/// Randomly chooses between 1 and -1
		/// </summary>
		/// <returns></returns>
		int RndBit();

		/// <summary>
		/// Returns a random number between a and b, inclusive
		/// </summary>
		/// <param name="a">Lower bound</param>
		/// <param name="b">Upper bound</param>
		/// <returns></returns>
		int RndInt( int a, int b );

		/// <summary>
		/// Returns a random float between 0 and 1.
		/// </summary>
		float RndFloat();

		float RndFloat( float a, float b );

		float RndFloat( float a, float b, float spacing );

		float RndFloat( Vector2 range );

		/// <summary>
		/// Returns a random direction with random magnitude between 0 and Length
		/// </summary>
		/// <param name="Length"></param>
		/// <returns></returns>
		Vector2 RndDir( float Length );

		/// <summary>
		/// Returns a random direction of length 1
		/// </summary>
		/// <returns></returns>
		Vector2 RndDir();



		int RandomSnap( int Range, int SnapPoints );

//C# TO C++ CONVERTER TODO TASK: There is no native C++ template equivalent to generic constraints:
		template<typename T> where T : class
		int RndEnum();

		/// <summary>
		/// Scrambles the ordering of the given list in place.
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <param name="list"></param>
		template<typename T>
		void Scramble( std::vector<T> &list );

		template<typename T>
		T RandomItem( std::vector<T> list );
		template<typename T>
		T RandomItem( std::vector<T> &list );

		std::vector<int> RndIndex( int Length, int NumIndices, std::vector<bool> Valid );

		/// <summary>
		/// Creates a new list with the same elements in a shuffled order;
		/// </summary>
		template<typename T>
		std::vector<T> Shuffle( std::vector<T> &list );

		/// <summary>
		/// Returns a randomly chosen item from the items given
		/// </summary>
		template<typename T>
//ORIGINAL LINE: public T ChooseOne<T>(params T[] choices)
//C# TO C++ CONVERTER TODO TASK: Use 'va_start', 'va_arg', and 'va_end' to access the parameter array within this method:
		T ChooseOne( ... );

		/// <summary>
		/// Choose n elements from a list.
		/// </summary>
		template<typename T>
		std::vector<T> Choose( std::vector<T> &list, int n );
		template<typename T>
		T Choose( std::vector<T> list );
		template<typename T>
		T Choose( std::vector<T> &list );


//C# TO C++ CONVERTER NOTE: The parameter Level was renamed since it is named the same as a user-defined type:
		int Choose( std::vector<int> LevelCutoff, int Level_Renamed );

		int Choose( std::vector<float> Weights );

		int ChooseNew( int Cur, int WeightA, int WeightB );

		int ChooseNew( int Cur, int WeightA, int WeightB, int WeightC );

		int Choose2( int WeightA, int ATag, int WeightB, int BTag );

		int Choose( int WeightA, int WeightB );

		int Choose( int WeightA, int WeightB, int WeightC );

		int Choose( int WeightA, int WeightB, int WeightC, int WeightD );
	};
}


#endif	//#ifndef RANDOM
