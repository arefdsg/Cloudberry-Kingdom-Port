#ifndef ALERTBASE
#define ALERTBASE

#include <small_header.h>

//#include "Core/Graphics/Draw/DrawPile.h"
//#include "Core/Graphics/Draw/Quads/QuadClass.h"
#include "Game/Localization.h"
//#include "Core/Text/EzText.h"
#include "Game/Menus/CkBaseMenu.h"
//#include "Game/Menus/Menu.h"
//#include "Game/Menus/Menu Components/MenuItem.h"


namespace CloudberryKingdom
{

	struct AlertBaseMenu : public CkBaseMenu
	{

		virtual ~AlertBaseMenu()
		{
#ifdef BOOST_BIN
			OnDestructor( "AlertBaseMenu" );
#endif
		}

	
		struct OkProxy : public Lambda
		{
		
			boost::shared_ptr<AlertBaseMenu> abm;

		
			OkProxy( const boost::shared_ptr<AlertBaseMenu> &abm );

			void Apply();
		};

		/// <summary>
		/// Called when the user presses OK.
		/// </summary>
	
		boost::shared_ptr<Lambda> OnOk;

	
		void Ok();

		virtual void ReleaseBody();

	
		AlertBaseMenu();
		boost::shared_ptr<AlertBaseMenu> AlertBaseMenu_Construct();

	
		Localization::Words Message, OkText;
	
		AlertBaseMenu( int Control, Localization::Words Message, Localization::Words OkText );
		boost::shared_ptr<AlertBaseMenu> AlertBaseMenu_Construct( int Control, Localization::Words Message, Localization::Words OkText );

		AlertBaseMenu( bool CallBaseConstructor );
		boost::shared_ptr<AlertBaseMenu> AlertBaseMenu_Construct( bool CallBaseConstructor );

	
		virtual void SetHeaderProperties( const boost::shared_ptr<EzText> &text );

		boost::shared_ptr<QuadClass> Backdrop;
	
		virtual void MakeBackdrop();

		virtual void Init();
	};
}


#endif	//#ifndef ALERTBASE
