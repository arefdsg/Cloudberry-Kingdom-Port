#ifndef CKCOLORHELPER
#define CKCOLORHELPER

namespace CloudberryKingdom
{
	class EzText;
}

namespace CloudberryKingdom
{
	class MenuItem;
}




namespace CloudberryKingdom
{
	class CkColorHelper
	{
	public:
		static void RegularColor( const std::shared_ptr<EzText> &name );

		static void _x_x_MasochisticColor( const std::shared_ptr<EzText> &name );

		static void _x_x_HardcoreColor( const std::shared_ptr<EzText> &name );

		static void AbusiveColor( const std::shared_ptr<EzText> &name );

		static void UnpleasantColor( const std::shared_ptr<EzText> &name );

		static void _x_x_EasyColor( const std::shared_ptr<EzText> &name );

		static void _x_x_HappyBlueColor( const std::shared_ptr<EzText> &name );

		static void _x_x_Red( const std::shared_ptr<EzText> &text );

		static void GreenItem( const std::shared_ptr<MenuItem> &item );
	};
}


#endif	//#ifndef CKCOLORHELPER