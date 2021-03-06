#ifndef STARTLEVELMENU
#define STARTLEVELMENU

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
//#include "Game/Localization.h"
//#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Menu.h"
#include "Game/Menus/Menu Components/MenuItem.h"
//#include "Game/Menus/Concrete Menus/Title Screen/StartMenu.h"
//#include "Game/Tools/Resources.h"
//#include "Game/Tools/Tools.h"


namespace CloudberryKingdom
{
	
	struct LevelItem : public MenuItem
	{
	
		int StartLevel, MenuIndex;

		LevelItem( const boost::shared_ptr<EzText> &Text, int StartLevel, int MenuIndex, bool Locked );
		boost::shared_ptr<LevelItem> LevelItem_Construct( const boost::shared_ptr<EzText> &Text, int StartLevel, int MenuIndex, bool Locked );

	};

	struct StartLevelMenu : public CkBaseMenu
	{
		
		virtual ~StartLevelMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "StartLevelMenu" );
#endif
		}

	
		struct GameReturnProxy : public LambdaFunc<bool>
		{
		
			boost::shared_ptr<StartLevelMenu> slm;

		
			GameReturnProxy( const boost::shared_ptr<StartLevelMenu> &slm );

			bool Apply();
		};

	
		struct LaunchHelper : public Lambda
		{
		
			boost::shared_ptr<StartLevelMenu> slm;
			boost::shared_ptr<LevelItem> litem;

		
			LaunchHelper( const boost::shared_ptr<StartLevelMenu> &slm, const boost::shared_ptr<LevelItem> &litem );

			void Apply();
		};

	
		struct LaunchProxy : public Lambda_1<boost::shared_ptr<MenuItem> >
		{
		
			boost::shared_ptr<StartLevelMenu> slm;

		
			LaunchProxy( const boost::shared_ptr<StartLevelMenu> &slm );

			void Apply( const boost::shared_ptr<MenuItem> &item );
		};

		/// <summary>
		/// The last difficulty selected via the difficulty select menu
		/// </summary>
	
		static int PreviousMenuIndex;

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

	
		boost::shared_ptr<Lambda_1<boost::shared_ptr<LevelItem> > > StartFunc;
		boost::shared_ptr<Lambda> ReturnFunc;

	
		virtual void Launch( const boost::shared_ptr<MenuItem> &item );

		virtual bool GameReturn();

		virtual void SetItemProperties( const boost::shared_ptr<MenuItem> &item );

	
		std::vector<int> Levels;
		//string[] LevelStr = { "Normal", "Advanced", "Expert", "Master" };
	
		virtual std::vector<std::wstring> GetNames();

		int HighestLevel;
		StartLevelMenu();
		boost::shared_ptr<StartLevelMenu> StartLevelMenu_Construct();
		StartLevelMenu( int HighestLevel );
		boost::shared_ptr<StartLevelMenu> StartLevelMenu_Construct( int HighestLevel );

		int IndexCutoff;

		void Initialize();

	
		void SetPos();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef STARTLEVELMENU
