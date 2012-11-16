#ifndef HEROSELECTOPTIONS
#define HEROSELECTOPTIONS

#include "../Game/Menus/Concrete Menus/Title Screen/Arcade/ArcadeMenu.h"
#include "../Core/Lambdas/Lambda.h"
#include "../Game/Objects/Game Objects/GameObjects/GUI_Panel.h"
#include "../Game/Objects/In Game Objects/Grab/CloudberryKingdom.Level.h"
#include <string>
#include <tchar.h>

namespace CloudberryKingdom
{
	class StartMenu_MW_HeroSelect;
}

namespace CloudberryKingdom
{
	class MenuItem;
}

namespace CloudberryKingdom
{
	class EzText;
}


//C# TO C++ CONVERTER TODO TASK: The .NET System namespace is not available from native C++:
//using namespace System::Collections::Generic;
using namespace Microsoft::Xna::Framework;

namespace CloudberryKingdom
{
	class HeroSelectOptions : public ArcadeBaseMenu
	{
	private:
		class BringLeaderboardProxy : public Lambda
		{
		private:
			std::shared_ptr<HeroSelectOptions> hso;

		public:
			BringLeaderboardProxy( const std::shared_ptr<HeroSelectOptions> &hso );

			void Apply();
		};

	private:
		std::shared_ptr<StartMenu_MW_HeroSelect> HeroSelect;

	public:
		HeroSelectOptions( const std::shared_ptr<StartMenu_MW_HeroSelect> &HeroSelect );

		virtual void Release();

		virtual void SlideIn( int Frames );

		virtual void SlideOut( const std::shared_ptr<PresetPos> &Preset, int Frames );

	protected:
		virtual void SetItemProperties( const std::shared_ptr<MenuItem> &item );

	public:
		virtual void OnAdd();

	private:
		void BringLeaderboard();

	protected:
		virtual void MyPhsxStep();

	public:
		virtual void Init();

	private:
//C# TO C++ CONVERTER NOTE: The variable Level was renamed since it is named the same as a user-defined type:
		std::shared_ptr<EzText> Score, Level_Renamed;

		void SetPos_Console();

		void SetPos_PC();

	protected:
		virtual void Go( const std::shared_ptr<MenuItem> &item );
	};
}


#endif	//#ifndef HEROSELECTOPTIONS
