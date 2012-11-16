#ifndef NEWHERO
#define NEWHERO

#include "GUI_Panel.h"
#include <string>

namespace CloudberryKingdom
{
	class EzText;
}


using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class NewHero : public GUI_Panel
	{
	public:
		virtual void OnAdd();

		std::shared_ptr<EzText> text;
		NewHero( const std::wstring &str );
		NewHero( const std::wstring &str, Vector2 shift, float scale, bool perma );

		static std::shared_ptr<NewHero> HeroTitle( const std::wstring &str );

	private:
		bool Perma;
		void Init( const std::wstring &str, Vector2 shift, float scale, bool perma );

		int Count;
	protected:
		virtual void MyPhsxStep();

	private:
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef NEWHERO
