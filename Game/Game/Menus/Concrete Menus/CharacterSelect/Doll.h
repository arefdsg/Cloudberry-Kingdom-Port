#ifndef DOLL
#define DOLL

#include <small_header.h>

#include "Core/PhsxData.h"
//#include "Core/Graphics/Draw/DrawPile.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Player/Buyable.h"
//#include "Game/Player/ClrTextFx.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharacterSelect.h"
//#include "Game/Menus/Concrete Menus/CharacterSelect/CharSelectManager.h"
#include "Game/Player/ColorScheme.h"
//#include "Game/Objects/Bob/Bob.h"
//#include "Game/Player/Cape.h"
//#include "Game/Player/ColorSchemeManager.h"
//#include "Game/Player/Hero Physics/Normal.h"
//#include "Game/Player/Hero Physics/BobPhsxCharSelect.h"
//#include "Game/Tools/Tools.h"


#if defined(PC_VERSION)
#elif defined(XBOX) || defined(XBOX_SIGNIN)

#endif

namespace CloudberryKingdom
{

	struct Doll : public CkBaseMenu
	{

		virtual ~Doll()
		{
#ifdef BOOST_BIN
			OnDestructor( "Doll" );
#endif
		}

	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
	
		Doll( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
		boost::shared_ptr<Doll> Doll_Construct( int Control, const boost::shared_ptr<CharacterSelect> &MyCharacterSelect );
	
		virtual void ReleaseBody();
	
		boost::shared_ptr<Bob> MyDoll;
		virtual void Init();
	
		void MakeDoll();
	
		void UpdateColorScheme();

	
		int FindClrIndex( std::vector<boost::shared_ptr<MenuListItem> > &list, boost::shared_ptr<ClrTextFx> clr );

		int FindHatIndex( std::vector<boost::shared_ptr<Hat> > &list, const boost::shared_ptr<Hat> &hat );

	
		void GetIndices( std::vector<int> ItemIndex, std::vector<std::vector<boost::shared_ptr<MenuListItem> > > &ItemList );


		void MyDraw();
		virtual void MyPhsxStep();

	
		bool ShowBob;
		void DrawBob();

	
		void InitializeInstanceFields();
	};
}


#endif	//#ifndef DOLL
