#include <small_header.h>
#include "Game/Player/PlayerManager.h"

#include "Core/Chunk.h"
#include "Core/ResolutionGroup.h"
#include "Core/Tools/Set.h"
#include "Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h"
#include "Core/Input/ButtonCheck.h"
#include "Game/Player/Buyable.h"
#include "Game/Player/ClrTextFx.h"
#include "Game/Games/Meta Games/Arcade Games/Rush/Hero Rush/HeroRush_Tutorial.h"
#include "Game/Tools/EzStorage.h"
#include "Game/Menus/Concrete Menus/Score Screens/ScoreEntry.h"
#include "Game/Objects/Bob/Bob.h"
#include "Game/Menus/Concrete Menus/Help/HintGiver.h"
#include "Game/Player/ColorSchemeManager.h"
#include "Game/Player/PlayerData.h"
#include "Game/Player/Stats.h"
#include "Game/Player/Awardments/Awardment.h"
#include "Game/Tools/Tools.h"

#include "Game/Tools/WrappedFloat.h"
#include "Game/Level/Level.h"
#include "Game/Tools/Camera.h"
#include "Core/Tools/Random.h"

#include "Hacks/List.h"
#include <Core\Tools\Set.h>

#if ! defined(PC_VERSION) && (defined(XBOX) || defined(XBOX_SIGNIN))

#endif

#include <Game/CloudberryKingdom/CloudberryKingdom.CloudberryKingdomGame.h>

#include <Game\Player\Leaderboard.h>

namespace CloudberryKingdom
{

	void PlayerManager::InitializeStatics()
	{
		PlayerManager::PartiallyInvisible = false, PlayerManager::TotallyInvisible = false;
		PlayerManager::_CoinsSpent = 0;

		PlayerManager::SavePlayerData = 0;

#if defined(PC_VERSION)
		PlayerManager::_DefaultName = std::wstring( L"" );
#endif

		std::wstring tempVector[] = { std::wstring( L"Honky Tonk" ), std::wstring( L"Bosco" ), std::wstring( L"Nuh Guck" ), std::wstring( L"Short-shorts" ), std::wstring( L"Itsy-bitsy" ), std::wstring( L"Low Ball" ), std::wstring( L"Cowboy Stu" ), std::wstring( L"Capsaicin" ), std::wstring( L"Hoity-toity" ), std::wstring( L"Ram Bam" ), std::wstring( L"King Kong" ), std::wstring( L"Upsilon" ), std::wstring( L"Omega" ), std::wstring( L"Peristaltic Pump" ), std::wstring( L"Jeebers" ), std::wstring( L"Sugar Cane" ), std::wstring( L"See-Saw" ), std::wstring( L"Ink Blot" ), std::wstring( L"Glottal Stop" ), std::wstring( L"Olive Oil" ), std::wstring( L"Cod Fish" ), std::wstring( L"Flax" ), std::wstring( L"Tahini" ), std::wstring( L"Cotton Ball" ), std::wstring( L"Sweet Justice" ), std::wstring( L"Ham Sandwich" ), std::wstring( L"Liverwurst" ), std::wstring( L"Cumulus" ), std::wstring( L"Oyster" ), std::wstring( L"Klein" ), std::wstring( L"Hippopotamus" ), std::wstring( L"Bonobo" ), std::wstring( L"Homo Erectus" ), std::wstring( L"Australopithecine" ), std::wstring( L"Quetzalcoatl" ), std::wstring( L"Balogna" ), std::wstring( L"Ceraunoscopy" ), std::wstring( L"Shirley" ), std::wstring( L"Susie" ), std::wstring( L"Sally" ), std::wstring( L"Sue" ), std::wstring( L"Tyrannosaur" ), std::wstring( L"Stick Man Chu" ), std::wstring( L"Paragon" ), std::wstring( L"Woodchuck" ), std::wstring( L"Laissez Faire" ), std::wstring( L"Ipso Facto" ), std::wstring( L"Leviticus" ), std::wstring( L"Berrylicious" ), std::wstring( L"Elderberry" ), std::wstring( L"Currant" ), std::wstring( L"Blackberry" ), std::wstring( L"Blueberry" ), std::wstring( L"Strawberry" ), std::wstring( L"Gooseberry" ), std::wstring( L"Honeysuckle" ), std::wstring( L"Nannyberry" ), std::wstring( L"Hackberry" ), std::wstring( L"Boysenberry" ), std::wstring( L"Cloudberry" ), std::wstring( L"Thimbleberry" ), std::wstring( L"Huckleberry" ), std::wstring( L"Bilberry" ), std::wstring( L"Bearberry" ), std::wstring( L"Mulberry" ), std::wstring( L"Wolfberry" ), std::wstring( L"Raisin" ), std::wstring( L"Samson" ) };
		PlayerManager::RandomNames = VecFromArray( tempVector );
		PlayerManager::FirstPlayer = 0;
		PlayerManager::HaveFirstPlayer = false;

		PlayerManager::NumPlayers = 1;
		PlayerManager::Players;

		PlayerManager::Score_Blobs = 0, PlayerManager::Score_Coins = 0, PlayerManager::Score_Attempts = 0, PlayerManager::Score_Time = 0;
	}

	// Statics
#if defined(PC_VERSION)
	RezData PlayerManager::d;
#endif
	bool PlayerManager::PartiallyInvisible, PlayerManager::TotallyInvisible;
	int PlayerManager::_CoinsSpent;

	boost::shared_ptr<_SavePlayerData> PlayerManager::SavePlayerData;

#if defined(PC_VERSION)
	std::wstring PlayerManager::_DefaultName;
#endif

	std::vector<std::wstring> PlayerManager::RandomNames;
	int PlayerManager::FirstPlayer;
	bool PlayerManager::HaveFirstPlayer;

	int PlayerManager::NumPlayers;
	std::vector<boost::shared_ptr<PlayerData> > PlayerManager::Players;

	int PlayerManager::Score_Blobs, PlayerManager::Score_Coins, PlayerManager::Score_Attempts, PlayerManager::Score_Time;




	PlayerIntLambda::PlayerIntLambda()
	{
	}

	int PlayerIntLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return 0;
	}

#if defined(DEBUG)
	bool UserPowers::CanSkipScreensaver = true;
#else
	bool UserPowers::CanSkipScreensaver = false;
#endif
	Set<std::wstring> UserPowers::WatchedVideo;

	void UserPowers::Set( bool &variable, bool value )
	{
		variable = value;
		SetToSave();
	}

	void UserPowers::SetToSave()
	{
		PlayerManager::SavePlayerData->Changed = true;
	}

	_SavePlayerData::_SavePlayerData()
	{
	InitializeInstanceFields();
	#if defined(PC_VERSION)
		AlwaysSave = true;
	#endif
	}

	void _SavePlayerData::Serialize( const boost::shared_ptr<BinaryWriter> &writer )
	{
		SaveLoad::Serialize( writer );

		Chunk::WriteSingle( writer, 23000, UserPowers::CanSkipScreensaver );
		Chunk::WriteSingle( writer, 23001, HeroRush_Tutorial::HasWatchedOnce );
		Chunk::WriteSingle( writer, 23002, Hints::QuickSpawnNum );
		Chunk::WriteSingle( writer, 23003, Hints::YForHelpNum );

		// Save the names of videos the user has already watched.
		for ( std::map<std::wstring, bool>::const_iterator video = UserPowers::WatchedVideo.dict.begin(); video != UserPowers::WatchedVideo.dict.end(); ++video )
			Chunk::WriteSingle( writer, 23005, video->first );
		// FIXME: Make sure we need to save the names rather than boolean values.
	}

	void _SavePlayerData::Deserialize( std::vector<unsigned char> Data )
	{
		boost::shared_ptr<Chunks> chunks = Chunks::Get( Data );
		chunks->StartGettingChunks();

		while( chunks->HasChunk() )
		{
			boost::shared_ptr<Chunk> chunk = chunks->GetChunk();

			ProcessChunk( chunk );
		}
	}

	void _SavePlayerData::ProcessChunk( boost::shared_ptr<Chunk> chunk )
	{
		switch ( chunk->Type )
		{
			case 23000:
				chunk->ReadSingle( UserPowers::CanSkipScreensaver );
				break;
			case 23001:
				chunk->ReadSingle( HeroRush_Tutorial::HasWatchedOnce );
				break;
			case 23002:
				chunk->ReadSingle( Hints::QuickSpawnNum );
				break;
			case 23003:
				chunk->ReadSingle( Hints::YForHelpNum );
				break;

			// Load the names of videos the user has already watched.
			case 23005:
				std::wstring VideoName = std::wstring( L"" );
				chunk->ReadSingle( VideoName );
				UserPowers::WatchedVideo.Add( VideoName );
				break;
		}
	}

	void _SavePlayerData::InitializeInstanceFields()
	{
		ResolutionPreferenceSet = false;
	}

#if defined(PC_VERSION)
	PlayerManager::SaveRezAndKeysLambda::SaveRezAndKeysLambda()
	{
	}

	void PlayerManager::SaveRezAndKeysLambda::Apply( const boost::shared_ptr<BinaryWriter> &writer )
	{
		PlayerManager::_SaveRezAndKeys( writer );
	}

	PlayerManager::LoadRezAndKeysLambda::LoadRezAndKeysLambda()
	{
	}

	void PlayerManager::LoadRezAndKeysLambda::Apply( const std::vector<unsigned char> &Data )
	{
		PlayerManager::_LoadRezAndKeys( Data );
	}

	PlayerManager::LoadRezAndKeysFailLambda::LoadRezAndKeysFailLambda()
	{
	}

	void PlayerManager::LoadRezAndKeysFailLambda::Apply()
	{
		PlayerManager::_Fail();
	}
#endif

	float PlayerManager::GetGroupGamerTagNameLength::Apply( const boost::shared_ptr<StringBuilder> &name )
	{
		return static_cast<float>( name->getLength() );
	}

	PlayerManager::AnyAwardmentLambda::AnyAwardmentLambda( const boost::shared_ptr<Awardment> &award )
	{
		this->award = award;
	}

	bool PlayerManager::AnyAwardmentLambda::Apply( const boost::shared_ptr<PlayerData> &player )
	{
		// FIXME: This used to be [] operator.
		return player->Awardments_Renamed->Has( award->Guid );
	}

	PlayerManager::AnyBoughtLambda::AnyBoughtLambda( const boost::shared_ptr<Buyable> &item )
	{
		this->item = item;
	}

	bool PlayerManager::AnyBoughtLambda::Apply( const boost::shared_ptr<PlayerData> &player )
	{
		return player->Purchases->Has( item->GetGuid() );
	}

	int PlayerManager::BankLambda::Apply( const boost::shared_ptr<PlayerData> &p )
	{
		return p->Bank();
	}

	PlayerManager::NotAllAwardedLambda::NotAllAwardedLambda( const boost::shared_ptr<Awardment> &award )
	{
		this->award = award;
	}

	bool PlayerManager::NotAllAwardedLambda::Apply( const boost::shared_ptr<PlayerData> &player )
	{
		return !player->Awardments_Renamed->Has( award->Guid );
	}

#if defined(XBOX) || defined(XBOX_SIGNIN)
	PlayerManager::ExistingPlayerFindLambda::ExistingPlayerFindLambda()
	{
	}

	bool PlayerManager::ExistingPlayerFindLambda::Apply( const boost::shared_ptr<PlayerData> &player )
	{
		return player->getMyGamer() != 0 || player->StoredName.length() > 0;
	}
#endif

#if defined(PC_VERSION)
	void PlayerManager::SaveRezAndKeys()
	{
		EzStorage::Save( std::wstring( L"Settings" ), std::wstring( L"Custom" ), boost::static_pointer_cast<Lambda_1<boost::shared_ptr<BinaryWriter> > >( boost::make_shared<SaveRezAndKeysLambda>() ), 0 );
	}
#endif

#if defined(PC_VERSION)
	void PlayerManager::_SaveRezAndKeys( const boost::shared_ptr<BinaryWriter> &writer )
	{
		Chunk::WriteSingle( writer, 0, SavePlayerData->ResolutionPreferenceSet );

		// Fullscreen
		Chunk::WriteSingle( writer, 1, Tools::getFullscreen() );

		// Resolution
		if ( ResolutionGroup::LastSetMode == 0 )
		{
			Chunk::WriteSingle( writer, 2, Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferWidth );
			Chunk::WriteSingle( writer, 3, Tools::TheGame->MyGraphicsDeviceManager->PreferredBackBufferHeight );
		}
		else
		{
			Chunk::WriteSingle( writer, 2, ResolutionGroup::LastSetMode->Width );
			Chunk::WriteSingle( writer, 3, ResolutionGroup::LastSetMode->Height );
		}

		// Secondary keys
		Chunk::WriteSingle( writer, 4, ButtonCheck::Quickspawn_KeyboardKey->KeyboardKey );
		Chunk::WriteSingle( writer, 5, ButtonCheck::Start_Secondary );
		Chunk::WriteSingle( writer, 6, ButtonCheck::Go_Secondary );
		Chunk::WriteSingle( writer, 7, ButtonCheck::Back_Secondary );
		Chunk::WriteSingle( writer, 8, ButtonCheck::ReplayPrev_Secondary );
		Chunk::WriteSingle( writer, 9, ButtonCheck::ReplayNext_Secondary );
		Chunk::WriteSingle( writer,10, ButtonCheck::SlowMoToggle_Secondary );
		Chunk::WriteSingle( writer,11, ButtonCheck::Left_Secondary );
		Chunk::WriteSingle( writer,12, ButtonCheck::Right_Secondary );
		Chunk::WriteSingle( writer,13, ButtonCheck::Up_Secondary );
		Chunk::WriteSingle( writer,14, ButtonCheck::Down_Secondary );

		// Volume
		Chunk::WriteSingle( writer, 15, Tools::MusicVolume->getVal() );
		Chunk::WriteSingle( writer, 16, Tools::SoundVolume->getVal() );

		// Fixed time step setting
		Chunk::WriteSingle( writer, 17, Tools::FixedTimeStep );

		// Bordered window
		Chunk::WriteSingle( writer, 18, Tools::WindowBorder );
	}
#endif

#if defined(PC_VERSION)
	RezData PlayerManager::LoadRezAndKeys()
	{
		EzStorage::Load( std::wstring( L"Settings" ), std::wstring( L"Custom" ),
			boost::make_shared<LoadRezAndKeysLambda>(), boost::make_shared<LoadRezAndKeysFailLambda>() );

		return d;
	}

    void PlayerManager::_Fail()
    {
        d = RezData();
        d.Custom = false;
    }
#endif

#if defined(PC_VERSION)
	void PlayerManager::_LoadRezAndKeys( std::vector<unsigned char> Data )
	{
		d = RezData();

		boost::shared_ptr<Chunks> chunks = Chunks::Get( Data );
		chunks->StartGettingChunks();

		while( chunks->HasChunk() )
		{
			boost::shared_ptr<Chunk> chunk = chunks->GetChunk();

			switch ( chunk->Type )
			{
				case 0:
					chunk->ReadSingle( d.Custom );
					break;

				// Fullscreen
				case 1:
					chunk->ReadSingle( d.Fullscreen );
					break;

				// Resolution
				case 2:
					chunk->ReadSingle( d.Width );
					break;
				case 3:
					chunk->ReadSingle( d.Height );
					break;

				// Secondary keys
				case 4:
					chunk->ReadSingle( ButtonCheck::Quickspawn_KeyboardKey->KeyboardKey );
					break;
				case 5:
					chunk->ReadSingle( ButtonCheck::Start_Secondary );
					break;
				case 6:
					chunk->ReadSingle( ButtonCheck::Go_Secondary );
					break;
				case 7:
					chunk->ReadSingle( ButtonCheck::Back_Secondary );
					break;
				case 8:
					chunk->ReadSingle( ButtonCheck::ReplayPrev_Secondary );
					break;
				case 9:
					chunk->ReadSingle( ButtonCheck::ReplayNext_Secondary );
					break;
				case 10:
					chunk->ReadSingle( ButtonCheck::SlowMoToggle_Secondary );
					break;
				case 11:
					chunk->ReadSingle( ButtonCheck::Left_Secondary );
					break;
				case 12:
					chunk->ReadSingle( ButtonCheck::Right_Secondary );
					break;
				case 13:
					chunk->ReadSingle( ButtonCheck::Up_Secondary );
					break;
				case 14:
					chunk->ReadSingle( ButtonCheck::Down_Secondary );
					break;

				// Volume
				case 15:
					Tools::MusicVolume->setVal( chunk->ReadFloat() );
					break;
				case 16:
					Tools::SoundVolume->setVal( chunk->ReadFloat() );
					break;

				// Fixed time step setting
				case 17:
					chunk->ReadSingle( Tools::FixedTimeStep );
					break;

				// Bordered window
				case 18:
					chunk->ReadSingle( Tools::WindowBorder );
					break;
			}
		}
	}
#endif

	const int &PlayerManager::getCoinsSpent()
	{
		return _CoinsSpent;
	}

	void PlayerManager::setCoinsSpent( const int &value )
	{
		_CoinsSpent = value;
	}

#if defined(PC_VERSION)
	const std::wstring &PlayerManager::getDefaultName()
	{
		return _DefaultName;
	}
#endif

#if defined(PC_VERSION)
	void PlayerManager::setDefaultName( const std::wstring &value )
	{
		if ( value.compare( _DefaultName ) != 0 )
			SavePlayerData->Changed = true;
		_DefaultName = value;
	}
#endif

        void PlayerManager::UploadCampaignLevels()
        {
            int level = Players[0]->GetTotalCampaignLevel();
            boost::shared_ptr<ScoreEntry> score = boost::make_shared<ScoreEntry>( Players[0]->GetName(), 7777, level, level, level, 0, 0, 0 );

            Leaderboard::WriteToLeaderboard( score );
        }

        void PlayerManager::UploadPlayerLevels()
        {
            bool ShouldUpdate = false;
            boost::shared_ptr<ScoreEntry> score;

            int level = Players[ 0 ]->GetTotalLevel();
            if ( level != Players[ 0 ]->LastPlayerLevelUpload )
            {
                score = boost::make_shared<ScoreEntry>( Players[ 0 ]->GetName(), 9999, level, level, level, 0, 0, 0 );
                Players[ 0 ]->LastPlayerLevelUpload = level;
                ShouldUpdate = true;
            }

            if ( ShouldUpdate )
            {
                Leaderboard::WriteToLeaderboard( score );
            }
        }

	void PlayerManager::CleanTempStats()
	{
		for ( int i = 0; i < 4; i++ )
			Get( i )->TempStats->Clean();
	}

	void PlayerManager::AbsorbTempStats()
	{
		for ( int i = 0; i < 4; i++ )
		{
			Get( i )->LevelStats->Absorb( Get( i )->TempStats );
			Get( i )->TempStats->Clean();
		}
	}

	void PlayerManager::AbsorbLevelStats()
	{
		for ( int i = 0; i < 4; i++ )
		{
			Get( i )->GameStats->Absorb( Get( i )->LevelStats );
			Get( i )->CampaignStats->Absorb( Get( i )->LevelStats );
			Get( i )->LevelStats->Clean();
		}
	}

	void PlayerManager::AbsorbGameStats()
	{
		for ( int i = 0; i < 4; i++ )
		{
			Get( i )->LifetimeStats->Absorb( Get( i )->GameStats );
			Get( i )->GameStats->Clean();
		}
	}

	int PlayerManager::GetFirstPlayer()
	{
		HaveFirstPlayer = true;
		if ( Players[ FirstPlayer ]->Exists )
			return FirstPlayer;
		else
		{
			for ( int i = 0; i < 4; i++ )
			{
				if ( Players[ i ]->Exists )
				{
					FirstPlayer = i;
					return FirstPlayer;
				}
			}
		}

		HaveFirstPlayer = false;
		return 0;
	}

	int PlayerManager::length( std::vector<boost::shared_ptr<StringBuilder> > &names )
	{
		int count = 0;
		for ( std::vector<boost::shared_ptr<StringBuilder> >::const_iterator name = names.begin(); name != names.end(); ++name )
			count += ( *name )->getLength();
		return count;
	}

	std::wstring PlayerManager::GetGroupGamerTag( int MaxLength )
	{
		std::vector<boost::shared_ptr<PlayerData> > players = getLoggedInPlayers();
		if ( players.empty() )
			players = getExistingPlayers();

		int N = static_cast<int>( players.size() );
		int CharLength = MaxLength - ( N - 1 ); // The max number of characters, exlucing slashes

		// Get a list of all names
		std::vector<boost::shared_ptr<StringBuilder> > names;
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = players.begin(); player != players.end(); ++player )
			names.push_back( boost::make_shared<StringBuilder>( ( *player )->GetName() ) );

		// Remove one character from the longest name until the total length is small enough
		boost::shared_ptr<GetGroupGamerTagNameLength> groupNameLengthGetter = boost::make_shared<GetGroupGamerTagNameLength>();
		while ( length( names ) > CharLength )
		{
			boost::shared_ptr<StringBuilder> str = Tools::ArgMax( names, 
				boost::static_pointer_cast<LambdaFunc_1<boost::shared_ptr<StringBuilder>, float> >( groupNameLengthGetter ) );
			str->Remove( str->getLength() - 1, 1 );
		}

		// Concatenate the names together
		std::wstring GroupTag = std::wstring( L"" );
		//foreach (StringBuilder str in names)
		for ( int i = 0; i < static_cast<int>( names.size() ); i++ )
		{
			boost::shared_ptr<StringBuilder> str = names[ i ];
			boost::shared_ptr<PlayerData> player = players[ i ];

			//string clr = EzText.ColorToCode(new Color(player.GetTextColor()));

			// Add '/' between player names
			if ( GroupTag.length() > 0 )
				GroupTag += L'/';

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
			std::wstring name = str->ToString();
			//GroupTag += clr + name;
			GroupTag += name;
		}

		return GroupTag;
	}

	int PlayerManager::MaxPlayerHighScore( int GameId )
	{
		int max = 0;
		//std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
		//for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
		//	max = __max( max, ( *player )->GetHighScore( GameId ) );

		for ( int i = 0; i < 4; ++i )
		{
			if ( Players[ i ] != 0 )
				max = __max( max, Players[ i ]->GetHighScore( GameId ) );
		}

		return max;
	}

        int PlayerManager::MaxPlayerTotalArcadeLevel()
        {
            int max = 0;

			//std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
			//for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
   //             max = __max( max, ( *player )->GetTotalArcadeLevel( ) );

			for ( int i = 0; i < 4; ++i )
			{
				if ( Players[ i ] != 0 )
					max = __max( max, Players[ i ]->GetTotalArcadeLevel() );
			}

            return max;
        }

        int PlayerManager::MinPlayerTotalCampaignLevel()
        {
            int max = 0;
			//std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
			//for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
   //         {
   //             int level = ( *player )->GetTotalCampaignLevel();
   //             //min = min == 0 ? level : __min( min, level );
			//	min = min == 0 ? level : __max( min, level );
   //         }

			for ( int i = 0; i < 4; ++i )
			{
				if ( Players[ i ] != 0 )
					max = __max( max, Players[ i ]->GetTotalCampaignLevel() );
			}

			return max;
        }

        int PlayerManager::MinPlayerTotalCampaignIndex()
        {
            int max = 0;
			//std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
			//for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
			//{
   //             int level = ( *player )->GetTotalCampaignIndex();
			//	min = min == 0 ? level : __max( min, level );
			//}

			for ( int i = 0; i < 4; ++i )
			{
				if ( Players[ i ] != 0 )
					max = __max( max, Players[ i ]->GetTotalCampaignIndex() );
			}

            return max;
        }

        int PlayerManager::MaxPlayerTotalLevel()
        {
            int max = 0;
			//std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
			//for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
   //             max = __max( max, ( *player )->GetTotalLevel( ) );

			for ( int i = 0; i < 4; ++i )
			{
				if ( Players[ i ] != 0 )
					max = __max( max, Players[ i ]->GetTotalLevel( ) );
			}

			return max;
        }

	bool PlayerManager::Awarded( const boost::shared_ptr<Awardment> &award )
	{
		return Tools::Any( getExistingPlayers(),
			boost::static_pointer_cast<LambdaFunc_1<boost::shared_ptr<PlayerData>, bool> >( boost::make_shared<AnyAwardmentLambda>(award) ) );
	}

	bool PlayerManager::Bought( const boost::shared_ptr<Buyable> &item )
	{
		return Tools::Any( getExistingPlayers(),
			boost::static_pointer_cast<LambdaFunc_1<boost::shared_ptr<PlayerData>, bool> >( boost::make_shared<AnyBoughtLambda>(item) ) );
	}

	bool PlayerManager::BoughtOrFree( const boost::shared_ptr<Buyable> &item )
	{
		return item->GetPrice() == 0 || Bought(item);
	}

	int PlayerManager::CombinedBank()
	{
		return PlayerSum( boost::make_shared<BankLambda>() );
	}

	void PlayerManager::DeductCost( int Cost )
	{
		if ( Cost > CombinedBank() )
			return;

		int SafetyCounter = 0;

		int PlayerIndex = 0;
		while ( Cost > 0 )
		{
			SafetyCounter++;
			if ( SafetyCounter > 1000000 )
				return;

			// Deduct one coin from each player at a time, so long as they can afford it.
			boost::shared_ptr<PlayerData> p = Players[ PlayerIndex ];
			if ( p->Exists && p->Bank() > 0 )
			{
				p->LifetimeStats->CoinsSpentAtShop++;
				Cost--;
			}

			PlayerIndex++;
			if ( PlayerIndex > 3 )
				PlayerIndex = 0;
		}
	}

	void PlayerManager::GiveBoughtItem( const boost::shared_ptr<Buyable> &buyable )
	{
		if ( buyable == 0 )
			return;

		// Give the hat to each player
		std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator p = vec.begin(); p != vec.end(); ++p )
			( *p )->Purchases->Add( buyable->GetGuid() );

		SavePlayerData->Changed = true;
	}

	bool PlayerManager::NotAllAwarded( const boost::shared_ptr<Awardment> &award )
	{
		std::vector<boost::shared_ptr<PlayerData> > CopyOfExistingPlayers = std::vector<boost::shared_ptr<PlayerData> >( getExistingPlayers() );

		return Tools::Any( CopyOfExistingPlayers,
			boost::static_pointer_cast<LambdaFunc_1<boost::shared_ptr<PlayerData>, bool> >( boost::make_shared<NotAllAwardedLambda>(award) ) );
	}

	int PlayerManager::GetGameScore()
	{
		int score = 0;
		std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
			score += ( *player )->GetGameScore();

		return score;
	}

	int PlayerManager::GetGameScore_WithTemporary()
	{
		int score = 0;
		std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
			score += ( *player )->GetGameScore() + (*player)->TempStats->Score;

		return score;
	}

	int PlayerManager::PlayerSum( const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<PlayerData> , int> > &f )
	{
		int sum = 0;
		std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
		{
			if ( *player != 0 )
				sum += f->Apply( *player );
		}

		return sum;
	}

	int PlayerManager::PlayerMax( const boost::shared_ptr<LambdaFunc_1<boost::shared_ptr<PlayerData> , int> > &f )
	{
		int max = INT_MIN;
		std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
		{
			if ( *player != 0 )
				max = __max( max, f->Apply( *player ) );
		}

		return max;
	}

	int PlayerManager::GetLevelCoins()
	{
		int coins = 0;
		std::vector<boost::shared_ptr<PlayerData> > vec = getExistingPlayers();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator player = vec.begin(); player != vec.end(); ++player )
			coins += ( *player )->GetLevelCoins();

		return coins;
	}

	const std::vector<boost::shared_ptr<PlayerData> > PlayerManager::getLoggedInPlayers()
	{
	#if defined(PC_VERSION)
		return getExistingPlayers();
	#elif defined(XBOX) || defined(XBOX_SIGNIN)
		return Tools::FindAll( getExistingPlayers(), boost::make_shared<ExistingPlayerFindLambda>() );
	#else
		return getExistingPlayers();
	#endif
	}

	const std::vector<boost::shared_ptr<PlayerData> > PlayerManager::getExistingPlayers()
	{
		std::vector<boost::shared_ptr<PlayerData> > existing;
		
		//existing.clear();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator data = Players.begin(); data != Players.end(); ++data )
			if ( *data != 0 && ( *data )->Exists )
				existing.push_back( *data );

		return existing;
	}

	std::vector<boost::shared_ptr<PlayerData> > PlayerManager::_ExistingPlayers = std::vector<boost::shared_ptr<PlayerData> >();

	const std::vector<boost::shared_ptr<PlayerData> > &PlayerManager::getAlivePlayers()
	{
		_AlivePlayers.clear();
		for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator data = Players.begin(); data != Players.end(); ++data )
			if ( ( *data )->Exists && ( *data )->IsAlive )
				_AlivePlayers.push_back( *data );

		return _AlivePlayers;
	}

	std::vector<boost::shared_ptr<PlayerData> > PlayerManager::_AlivePlayers = std::vector<boost::shared_ptr<PlayerData> >();

    int PlayerManager::NumAlivePlayers()
    {
        int Num = 0;
        for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator data = Players.begin(); data != Players.end(); ++data )
            if ( ( *data )->Exists && ( *data )->IsAlive )
                Num++;
            
        return Num;
    }

    int PlayerManager::NumExistingPlayers()
    {
        int Num = 0;
        for ( std::vector<boost::shared_ptr<PlayerData> >::const_iterator data = Players.begin(); data != Players.end(); ++data )
            if ( ( *data )->Exists && ( *data )->Exists )
                Num++;

        return Num;
    }

#if defined(PC_VERSION)
	const boost::shared_ptr<PlayerData> &PlayerManager::getPlayer()
	{
		return Players[ 0 ];
	}
#endif

	boost::shared_ptr<PlayerData> PlayerManager::Get( int i )
	{
		return Players[ i ];
	}

	boost::shared_ptr<PlayerData> PlayerManager::Get( PlayerIndex Index )
	{
		return Players[ static_cast<int>( Index ) ];
	}

	boost::shared_ptr<PlayerData> PlayerManager::Get( const boost::shared_ptr<Bob> &bob )
	{
		return Players[ static_cast<int>( bob->MyPlayerIndex ) ];
	}

	void PlayerManager::CalcScore( StatGroup group )
	{
		if ( group == StatGroup_LEVEL )
			AbsorbTempStats();
		else if ( group == StatGroup_GAME )
		{
			AbsorbTempStats();
			AbsorbLevelStats();
		}

		Score_Attempts = Score_Blobs = Score_Coins = Score_Time = 0;

		for ( int i = 0; i < 4; i++ )
			if ( PlayerManager::Get( i )->Exists )
			{
				boost::shared_ptr<PlayerStats> stats = Get( i )->GetStats( group );

				Score_Coins += stats->Coins;
				Score_Blobs += stats->Blobs;
				Score_Attempts += stats->DeathsBy[ static_cast<int>( BobDeathType_TOTAL ) ];
				Score_Time = __max( Score_Time, stats->TimeAlive );
			}
	}

bool PlayerManager::Showed_ShouldCheckOutWorlds = false;
int Showed_ShouldLeaveLevel, PlayerManager::Showed_ShouldWatchComputer = 0;

	int PlayerManager::GetNumPlayers()
	{
		NumPlayers = 0;
		for ( int i = 0; i < 4; i++ )
			if ( Players[ i ]->Exists )
				NumPlayers++;

		return NumPlayers;
	}

	bool PlayerManager::AllDead()
	{
		bool All = true;
		for ( int i = 0; i < 4; i++ )
			All = All && ( !Players[ i ]->IsAlive || !Players[ i ]->Exists );

		return All;
	}

	bool PlayerManager::AllOffscreen()
	{
		bool All = true;
		for ( BobVec::const_iterator bob = Tools::CurLevel->Bobs.begin(); bob != Tools::CurLevel->Bobs.end(); ++bob )
			All = All && !Tools::CurLevel->getMainCamera()->OnScreen((*bob)->getCore()->Data.Position);

		return All;
	}

	bool PlayerManager::IsAlive( PlayerIndex PIndex )
	{
		int Index = GetIndexFromPlayerIndex( PIndex );

		return Players[ Index ]->IsAlive;
	}

	int PlayerManager::GetIndexFromPlayerIndex( PlayerIndex PIndex )
	{
		for ( int i = 0; i < 4; i++ )
			if ( Players[ i ]->MyPlayerIndex == PIndex )
				return i;

		return -1;
		// FIXME: No exceptions!
		//throw ( std::exception( std::wstring( L"PlayerIndex not found!" ) ) );
	}

	void PlayerManager::KillPlayer( PlayerIndex PIndex )
	{
		int Index = GetIndexFromPlayerIndex( PIndex );

		Players[ Index ]->IsAlive = false;
	}

	void PlayerManager::ReviveBob( const boost::shared_ptr<Bob> &bob )
	{
		bob->DeadCount = 0;
		bob->Dead = bob->Dying = false;

		RevivePlayer( bob->MyPlayerIndex );
	}

	void PlayerManager::RevivePlayer( PlayerIndex PIndex )
	{
		int Index = GetIndexFromPlayerIndex( PIndex );

		Players[ Index ]->IsAlive = true;
	}

	void PlayerManager::Init()
	{
	#if defined(PC_VERSION)
		_DefaultName = ListExtension::Choose( PlayerManager::RandomNames, Tools::GlobalRnd );
	#endif

		Players = std::vector<boost::shared_ptr<PlayerData> >( 4 );
		ColorSchemeManager::InitColorSchemes();

		// Player templates
		for ( int i = 0; i < 4; i++ )
		{
			Players[ i ] = boost::make_shared<PlayerData>();
			Players[ i ]->Init( i );
		}

		// FIXME: Need to load the player data properly.
#ifdef CAFE
		Players[ 0 ]->ContainerName = std::wstring( L"Gamers" );
		Players[ 0 ]->FileName = std::wstring( L"PlayerProgress" );
#else
		Players[ 0 ]->ContainerName = std::wstring( L"PlayerData" );
		Players[ 0 ]->FileName = std::wstring( L"PlayerData" );
#endif
		//Players[ 0 ]->Load();
	}
}
