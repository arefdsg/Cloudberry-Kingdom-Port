﻿#ifndef COLORSELECT
#define COLORSELECT

#include <global_header.h>

namespace CloudberryKingdom
{

	struct ListSelectPanel : public CkBaseMenu
	{

		virtual ~ListSelectPanel() { }
	
		struct OnSelectProxy : public Lambda
		{
		
			boost::shared_ptr<ListSelectPanel> lsp;

		
			OnSelectProxy( const boost::shared_ptr<ListSelectPanel> &lsp );

			void Apply();
		};

	
		struct BackProxy : public Lambda
		{
		
			boost::shared_ptr<ListSelectPanel> lsp;

		
			BackProxy( const boost::shared_ptr<ListSelectPanel> &lsp );

			void Apply();
		};

	
		struct SelectProxy : public Lambda
		{
		
			boost::shared_ptr<ListSelectPanel> lsp;

		
			SelectProxy( const boost::shared_ptr<ListSelectPanel> &lsp );

			void Apply();
		};

	
		boost::shared_ptr<MenuList> MyList;
	
		boost::shared_ptr<CharacterSelect> MyCharacterSelect;
		int ClrSelectIndex;

	
		virtual void ReleaseBody();

	
		void SetPos( Vector2 pos );

		void SetIndexViaAssociated( int index );

		int GetAssociatedIndex();

	
		Localization::Words Header;
		int HoldIndex;

	
		ListSelectPanel( int Control, Localization::Words Header, const boost::shared_ptr<CharacterSelect> &Parent, int ClrSelectIndex );
		boost::shared_ptr<ListSelectPanel> ListSelectPanel_Construct( int Control, Localization::Words Header, const boost::shared_ptr<CharacterSelect> &Parent, int ClrSelectIndex );

	
		void OnSelect();

	
		virtual void Constructor();

		virtual void OnAdd();

	
		void Back();

		void Select();

	
		virtual void MyPhsxStep();
	};
}


#endif	//#ifndef COLORSELECT
