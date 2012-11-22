﻿#include <global_header.h>

namespace CloudberryKingdom
{

	std::shared_ptr<TileSet> TileSets::Load_Cloud()
	{
		std::shared_ptr<CloudberryKingdom::TileSet> t = GetOrMakeTileset( _T( "Cloud" ) );
		std::shared_ptr<CloudberryKingdom::TileSet::TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = _T( "cloud" );

	t->Pillars->Add( std::make_shared<PieceQuad>( 50, _T( "pillar_cloud_50" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 100, _T( "pillar_cloud_100" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 150, _T( "pillar_cloud_150" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 250, _T( "pillar_cloud_250" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 300, _T( "pillar_cloud_300" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 600, _T( "pillar_cloud_600" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 1000, _T( "pillar_cloud_1000" ), -15, 15, 3 ) );

	t->StartBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_cloud" ), -550, 135, 1450 ) );
	t->EndBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_cloud" ), -15, 670, 1450 ) );

	info->ShiftStartDoor = 30;
	info->ShiftStartBlock = Vector2( 120, 0 );

	sprite_anim( _T( "door_cloud" ), _T( "door_cloud" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = _T( "door_cloud" );
	info->Doors->Sprite->Size = Vector2( 275, -1 );
	info->Doors->Sprite->Offset = Vector2( -140, 7 );
	info->Doors->ShiftStart = Vector2( 0, 190 );

	info->Walls->Sprite->Sprite = _T( "pillar_cloud_1000" );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4573 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = _T( "Flow_cave_1" );
	info->LavaDrips->Line_Renamed->Sprite = _T( "Flow_cave_2" );
	info->LavaDrips->Line_Renamed->End2 = _T( "Flow_Cave_3" );

	info->Lasers->Line_Renamed->Sprite = _T( "Laser_Cloud" );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( _T( "fblock_cloud" ), _T( "fblock_cloud" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( std::make_shared<PieceQuad>( 103, _T( "fblock_cloud" ), -3, 3, 2 ) );

	sprite_anim( _T( "Bouncy_cloud" ), _T( "Bouncy_cloud" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( std::make_shared<PieceQuad>( 124, _T( "bouncy_cloud" ), -6, 6, 13 ) );

	sprite_anim( _T( "flame_cloud" ), _T( "firespinner_flame_cloud" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = _T( "flame_cloud" );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = _T( "firespinner_base_cloud" );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;

	info->GhostBlocks->Sprite = _T( "ghostblock_cloud" );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 190, _T( "movingblock_cloud_190" ), -4, 13, 10 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 135, _T( "movingblock_cloud_135" ), -4, 4, 10 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 80, _T( "movingblock_cloud_80" ), -1, 1, 2 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 40, _T( "movingblock_cloud_40" ), -1, 1, 2 ) );

	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Cloud_40" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Cloud_80" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Cloud_135" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Cloud_190" ), -1, 1, 1 ) );

	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Cloud_40" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Cloud_80" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Cloud_135" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Cloud_190" ), -1, 1, 1 ) );

	sprite_anim( _T( "Serpent_Cloud" ), _T( "Serpent_Cloud" ), 1, 2, 8 );
	info->Serpents->Serpent_Renamed->Sprite = _T( "Serpent_Cloud" );
	sprite_anim( _T( "Serpent_Fish_Cloud" ), _T( "Serpent_Fish_Cloud" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = _T( "Serpent_Fish_Cloud" );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Spikes->Spike_Renamed->Sprite = _T( "spike_cloud" );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = _T( "spike_base_cloud_1" );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Sprite = _T( "floater_spikey_cloud" );
	info->Boulders->Ball->Size = Vector2( 150, -1 );
	info->Boulders->Radius = 120;
	info->Boulders->Chain->Sprite = _T( "cloud_chain" );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;

	info->Boulders->Ball->Sprite = _T( "Floater_Boulder_Cloud" );
	info->Boulders->Ball->Size = Vector2( 200, -1 );
	info->Boulders->Radius = 140;
	info->Boulders->Chain->Sprite = _T( "Floater_Rope_Cloud" );
	info->Boulders->Chain->RepeatWidth = 1900;
	info->Boulders->Chain->Width = 55;

	info->SpikeyGuys->Ball->Sprite = _T( "floater_spikey_cloud" );
	info->SpikeyGuys->Ball->Size = Vector2( 150, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 8 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 114;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = _T( "cloud_chain" );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyLines->Ball->Sprite = _T( "Floater_Spikey_Cloud" );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( _T( "blob_cloud" ), _T( "blob_cloud" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = _T( "blob_cloud" );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = _T( "BlobGoo5" );

	info->Clouds->Sprite->Sprite = _T( "cloud_cloud" );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 104 );

	info->Coins->Sprite->Sprite = _T( "coin_blue" );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;

		t->_Finish();

		return t;
	}

	std::shared_ptr<TileSet> TileSets::Load_Castle()
	{
		std::shared_ptr<CloudberryKingdom::TileSet> t = GetOrMakeTileset( _T( "Castle" ) );
		std::shared_ptr<CloudberryKingdom::TileSet::TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = _T( "castle" );

	t->HasCeiling = true;

	t->Pillars->Add( std::make_shared<PieceQuad>( 50, _T( "pillar_castle_50" ), -15, 15, 1 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 100, _T( "pillar_castle_100" ), -15, 15, 1 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 150, _T( "pillar_castle_150" ), -15, 15, 1 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 250, _T( "pillar_castle_250" ), -15, 15, 1 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 300, _T( "pillar_castle_300" ), -15, 15, 1 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 600, _T( "pillar_castle_600" ), -15, 15, 1 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 1000, _T( "pillar_castle_1000" ), -15, 15, 1 ) );

	t->Ceilings->Add( std::make_shared<PieceQuad>( 50, _T( "pillar_castle_50" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 100, _T( "pillar_castle_100" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 150, _T( "pillar_castle_150" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 250, _T( "pillar_castle_250" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 300, _T( "pillar_castle_300" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 600, _T( "pillar_castle_600" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 1000, _T( "pillar_castle_1000" ), -20, 20, 0, true ) );

	//t.StartBlock.Add(new PieceQuad(400, "wall_castle", -670, 15, 1407));
	//t.EndBlock.Add(new PieceQuad(400, "wall_castle", -15, 670, 1407));
	t->StartBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_castle" ), -950, 15, 1670 ) );
	t->EndBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_castle" ), -45, 920, 1670 ) );

	info->ShiftStartDoor = 0;
	info->ShiftStartBlock = Vector2( 100, 0 );

	sprite_anim( _T( "door_castle" ), _T( "door_castle" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = _T( "door_castle" );
	info->Doors->Sprite->Size = Vector2( 450, 250 );
	info->Doors->Sprite->Offset = Vector2( -210, 35 );
	info->Doors->ShiftStart = Vector2( 0, 190 );
	info->Doors->SizePadding = Vector2( 10, 0 );

	info->Walls->Sprite->Sprite = _T( "pillar_castle_1000" );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4635 );
	info->Walls->Sprite->Size = Vector2( 1300, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4815 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = _T( "Flow_Castle_1" );
	info->LavaDrips->Line_Renamed->Sprite = _T( "Flow_Castle_2" );
	info->LavaDrips->Line_Renamed->End2 = _T( "Flow_Castle_3" );
	info->LavaDrips->Icon->Sprite = _T( "Flow_Icon_Castle" );

	info->Lasers->Line_Renamed->Sprite = _T( "Laser_Castle" );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );
	info->Lasers->Icon->Sprite = _T( "Icon_Laser" );

	sprite_anim( _T( "fblock_castle" ), _T( "fblock_castle" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( std::make_shared<PieceQuad>( 103, _T( "fblock_castle" ), -3, 3, 2 ) );
	info->FallingBlocks->Icon->Sprite = _T( "fblock_castle" );
	info->FallingBlocks->Icon->Size = Vector2( 40, -1 );

	sprite_anim( _T( "Bouncy_castle" ), _T( "Bouncy_castle" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( std::make_shared<PieceQuad>( 124, _T( "bouncy_castle" ), -6, 6, 13 ) );
	info->BouncyBlocks->Icon->Sprite = _T( "Bouncy_Castle" );

	sprite_anim( _T( "flame_castle" ), _T( "firespinner_flame_castle_v1" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = _T( "flame_castle" );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = _T( "firespinner_base_castle_2" );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;
	info->Spinners->Icon->Sprite = _T( "Icon_FireSpinner" );

	info->GhostBlocks->Sprite = _T( "ghostblock_castle" );
	info->GhostBlocks->Shift = Vector2( 0, -15 );
	info->GhostBlocks->Icon->Sprite = _T( "Ghostblock_Castle" );
	info->GhostBlocks->Icon->Size = Vector2( 40, -1 );

	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 190, _T( "movingblock_castle_190" ), -1, 1, 25 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 135, _T( "movingblock_castle_135" ), -1, 1, 25 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 80, _T( "movingblock_castle_80" ), -1, 1, 5 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 40, _T( "movingblock_castle_40" ), -1, 1, 5 ) );
	info->MovingBlocks->Icon->Sprite = _T( "MovingBlock_Castle_40" );
	info->MovingBlocks->Icon->Size = Vector2( 40, -1 );
	info->MovingBlocks->Icon_Big = std::make_shared<SpriteInfo>( 0 );
	info->MovingBlocks->Icon_Big->Sprite = _T( "MovingBlock_Castle_135" );
	info->MovingBlocks->Icon_Big->Size = Vector2( 40, -1 );

	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Castle_40" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Castle_80" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Castle_135" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Castle_190" ), -1, 1, 1 ) );
	info->Elevators->Icon->Sprite = _T( "Elevator_Castle_80" );

	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Castle_40" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Castle_80" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Castle_135" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Castle_190" ), -1, 1, 1 ) );
	//info.Pendulums.Icon.Sprite = "Elevator_Castle_80";
	info->Pendulums->Icon->Sprite = _T( "Pendulum_Icon_Castle" );

	sprite_anim( _T( "Serpent_Castle" ), _T( "Serpent_Castle" ), 1, 2, 8 );
	//sprite_anim("Serpent_Castle", "SerpentHead_Castle", 1, 2, 8);
	info->Serpents->Serpent_Renamed->Sprite = _T( "Serpent_Castle" );
	sprite_anim( _T( "Serpent_Fish_Castle" ), _T( "Serpent_Fish_Castle" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = _T( "Serpent_Fish_Castle" );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );
	info->Serpents->Icon->Sprite = _T( "SerpentHead_Castle_1" );

	info->Spikes->Spike_Renamed->Sprite = _T( "spike_castle" );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = _T( "spike_base_castle" );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;
	info->Spikes->Icon->Sprite = _T( "Spike_Castle" );
	info->Spikes->Icon->Size = Vector2( 25, -1 );

	info->Boulders->Ball->Sprite = _T( "Floater_Spikey_castle_v1" );
	info->Boulders->Ball->Size = Vector2( 150, -1 );
	info->Boulders->Radius = 106;
	info->Boulders->Chain->Sprite = _T( "floater_chain_castle" );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;
	info->Boulders->Icon->Sprite = _T( "Floater_Spikey_Castle_v1" );

	info->SpikeyGuys->Ball->Sprite = _T( "floater_buzzsaw_yellow_castle" );
	info->SpikeyGuys->Ball->Size = Vector2( 190, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 0 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->RotateSpeed = -.15f;
	info->SpikeyGuys->Radius = 130;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = _T( "floater_chain_castle" );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;
	info->SpikeyGuys->Icon->Sprite = _T( "Floater_Buzzsaw_Yellow_Castle" );

	info->SpikeyLines->Ball->Sprite = _T( "Floater_Spikey_Castle_v2" );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;
	info->SpikeyLines->Icon->Sprite = _T( "Floater_Spikey_Castle_v2" );

	sprite_anim( _T( "blob_castle" ), _T( "blob_castle_v1" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = _T( "blob_castle" );
	info->Blobs->Body->Size = Vector2( 137, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = _T( "BlobGoo5" );
	info->Blobs->Icon->Sprite = _T( "Blob_Castle" );

	info->Clouds->Sprite->Sprite = _T( "cloud_castle" );
	info->Clouds->Icon->Sprite = _T( "Cloud_Castle" );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 355 );
	info->Fireballs->Icon->Sprite = _T( "Icon_Fireball" );

	info->Coins->Sprite->Sprite = _T( "coin_blue" );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = true;
	info->ObstacleCutoff = 70;

		t->_Finish();

		return t;
	}

	std::shared_ptr<TileSet> TileSets::Load_Sea()
	{
		std::shared_ptr<CloudberryKingdom::TileSet> t = GetOrMakeTileset( _T( "Sea" ) );
		std::shared_ptr<CloudberryKingdom::TileSet::TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = _T( "sea" );

	t->Pillars->Add( std::make_shared<PieceQuad>( 50, _T( "pillar_sea_50" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 100, _T( "pillar_sea_100" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 150, _T( "pillar_sea_150" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 250, _T( "pillar_sea_250" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 300, _T( "pillar_sea_300" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 600, _T( "pillar_sea_600" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 1000, _T( "pillar_sea_1000" ), -15, 15, 3 ) );

	t->StartBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_sea" ), -670, 15, 1420 ) );
	t->EndBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_sea" ), -55, 630, 1420 ) );

	info->ShiftStartDoor = -140;
	info->ShiftStartBlock = Vector2( 320, 0 );

	sprite_anim( _T( "door_sea" ), _T( "door_sea" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = _T( "door_sea" );
	info->Doors->Sprite->Size = Vector2( 270, -1 );
	info->Doors->Sprite->Offset = Vector2( -140, 38 );
	info->Doors->ShiftStart = Vector2( 0, 190 );

	info->Walls->Sprite->Sprite = _T( "pillar_sea_1000" );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4550 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = _T( "Flow_Sea_1" );
	info->LavaDrips->Line_Renamed->Sprite = _T( "Flow_Sea_2" );
	info->LavaDrips->Line_Renamed->End2 = _T( "Flow_Sea_3" );

	info->Lasers->Line_Renamed->Sprite = _T( "Laser_Sea" );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( _T( "fblock_sea" ), _T( "fblock_sea" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( std::make_shared<PieceQuad>( 110, _T( "fblock_sea" ), -3, 3, 2 ) );

	sprite_anim( _T( "Bouncy_sea" ), _T( "Bouncy_Cloud" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( std::make_shared<PieceQuad>( 124, _T( "bouncy_sea" ), -6, 6, 13 ) );

	sprite_anim( _T( "flame_Sea" ), _T( "firespinner_flame_Sea" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = _T( "flame_Sea" );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = _T( "firespinner_gear_dkpurp" );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;

	info->GhostBlocks->Sprite = _T( "ghostblock_sea" );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 190, _T( "movingblock_sea_190" ), -1, 1, 12 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 135, _T( "movingblock_sea_135" ), -1, 1, 12 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 80, _T( "movingblock_sea_80" ), -1, 1, 4 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 40, _T( "movingblock_sea_40" ), -1, 1, 4 ) );

	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Sea_40" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Sea_80" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Sea_135" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Sea_190" ), -1, 1, 1 ) );

	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Sea_40" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Sea_80" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Sea_135" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Sea_190" ), -1, 1, 1 ) );

	sprite_anim( _T( "Serpent_Sea" ), _T( "Serpent_Sea" ), 1, 2, 8 );
	info->Serpents->Serpent_Renamed->Sprite = _T( "Serpent_Sea" );
	sprite_anim( _T( "Serpent_Fish_Sea" ), _T( "Serpent_Fish_Sea" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = _T( "Serpent_Fish_Sea" );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Spikes->Spike_Renamed->Sprite = _T( "Spike_Sea_2" );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = _T( "spike_base_sea_1" );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Size = Vector2( 170, -1 );
	info->Boulders->Radius = 120;
	info->Boulders->Ball->Sprite = _T( "Floater_Boulder_Cloud" );
	info->Boulders->Ball->Size = Vector2( 200, -1 );
	info->Boulders->Radius = 140;
	info->Boulders->Chain->Sprite = _T( "Floater_Rope_Cloud" );
	info->Boulders->Chain->RepeatWidth = 1900;
	info->Boulders->Chain->Width = 55;

	info->SpikeyGuys->Ball->Sprite = _T( "Floater_Spikey_Sea" );
	info->SpikeyGuys->Ball->Size = Vector2( 170, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 9 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 124;
	info->SpikeyGuys->RotateOffset = -1.95f;
	info->SpikeyGuys->Chain->Sprite = _T( "floater_chain_sea" );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyLines->Ball->Sprite = _T( "Floater_Spikey_Sea" );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( _T( "blob_sea" ), _T( "blob_sea" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = _T( "blob_sea" );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = _T( "BlobGoo5" );

	info->Clouds->Sprite->Sprite = _T( "cloud_sea" );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 132 );

	//info.Coins.Sprite.Sprite = "coin_blue";
	info->Coins->Sprite->Sprite = _T( "CoinShimmer" );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;
	info->ObstacleCutoff = 200;

		t->_Finish();

		return t;
	}

	std::shared_ptr<TileSet> TileSets::Load_Hills()
	{
		std::shared_ptr<CloudberryKingdom::TileSet> t = GetOrMakeTileset( _T( "Hills" ) );
		std::shared_ptr<CloudberryKingdom::TileSet::TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = _T( "hills" );

	t->Pillars->Add( std::make_shared<PieceQuad>( 50, _T( "pillar_hills_50" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 100, _T( "pillar_hills_100" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 150, _T( "pillar_hills_150" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 250, _T( "pillar_hills_250" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 300, _T( "pillar_hills_300" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 600, _T( "pillar_hills_600" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 1000, _T( "pillar_hills_1000" ), -15, 15, 3 ) );

	t->StartBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_hills" ), -880, 40, 1650 ) );
	t->EndBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_hills" ), -40, 880, 1650 ) );

	info->ShiftStartDoor = -140;
	info->ShiftStartBlock = Vector2( 200, 0 );

	sprite_anim( _T( "door_hills" ), _T( "door_hills" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = _T( "door_hills" );
	info->Doors->Sprite->Size = Vector2( 305, -1 );
	info->Doors->Sprite->Offset = Vector2( -140, 33 );
	info->Doors->ShiftStart = Vector2( 0, 190 );

	info->Walls->Sprite->Sprite = _T( "pillar_hills_1000" );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4615 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = _T( "Flow_cave_1" );
	info->LavaDrips->Line_Renamed->Sprite = _T( "Flow_cave_2" );
	info->LavaDrips->Line_Renamed->End2 = _T( "Flow_Cave_3" );

	info->Lasers->Line_Renamed->Sprite = _T( "Laser_Hills" );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( _T( "fblock_hills" ), _T( "fblock_hills" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( std::make_shared<PieceQuad>( 110, _T( "fblock_hills" ), -3, 3, 2 ) );

	sprite_anim( _T( "Bouncy_hills" ), _T( "Bouncy_hills" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( std::make_shared<PieceQuad>( 124, _T( "bouncy_hills" ), -15, 15, 13 ) );

	sprite_anim( _T( "flame_Hills" ), _T( "firespinner_flame_Hills" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = _T( "flame_Hills" );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = _T( "firespinner_base_hills" );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;

	info->GhostBlocks->Sprite = _T( "ghostblock_hills" );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 190, _T( "movingblock_hills_190" ), -1, 1, 7 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 135, _T( "movingblock_hills_135" ), -1, 1, 7 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 80, _T( "movingblock_hills_80" ), -1, 1, 3 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 40, _T( "movingblock_hills_40" ), -1, 1, 3 ) );

	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Hills_40" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Hills_80" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Hills_135" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Hills_190" ), -1, 1, 1 ) );

	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Hills_40" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Hills_80" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Hills_135" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Hills_190" ), -1, 1, 1 ) );

	sprite_anim( _T( "Serpent_Hills" ), _T( "Serpent_Castle" ), 1, 2, 5 );
	info->Serpents->Serpent_Renamed->Sprite = _T( "Serpent_Hills" );
	sprite_anim( _T( "Serpent_Fish_Hills" ), _T( "Serpent_Fish_Castle" ), 1, 2, 8 );
	info->Serpents->Fish->Sprite = _T( "Serpent_Fish_Hills" );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Spikes->Spike_Renamed->Sprite = _T( "spike_hills" );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = _T( "spike_base_hills_1" );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Sprite = _T( "floater_boulder_hills" );
	info->Boulders->Ball->Size = Vector2( 200, -1 );
	info->Boulders->Radius = 140;
	info->Boulders->Chain->Sprite = _T( "floater_rope_hills" );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;

	info->SpikeyGuys->Ball->Sprite = _T( "floater_spikey_hills" );
	info->SpikeyGuys->Ball->Size = Vector2( 150, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 8 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 116;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = _T( "floater_chain_hills" );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyLines->Ball->Sprite = _T( "Floater_Spikey_Hills" );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( _T( "blob_hills" ), _T( "blob_hills" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = _T( "blob_hills" );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = _T( "BlobGoo5" );

	info->Clouds->Sprite->Sprite = _T( "cloud_hills" );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 0 );

	info->Coins->Sprite->Sprite = _T( "coin_blue" );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;

		t->_Finish();

		return t;
	}

	std::shared_ptr<TileSet> TileSets::Load_Forest()
	{
		std::shared_ptr<CloudberryKingdom::TileSet> t = GetOrMakeTileset( _T( "Forest" ) );
		std::shared_ptr<CloudberryKingdom::TileSet::TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = _T( "forest" );

	t->Pillars->Add( std::make_shared<PieceQuad>( 50, _T( "pillar_forest_50" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 100, _T( "pillar_forest_100" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 150, _T( "pillar_forest_150" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 250, _T( "pillar_forest_250" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 300, _T( "pillar_forest_300" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 600, _T( "pillar_forest_600" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 1000, _T( "pillar_forest_1000" ), -15, 15, 3 ) );

	t->StartBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_forest" ), -670, 15, 1500 ) );
	t->EndBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_forest" ), -15, 670, 1500 ) );

	info->ShiftStartDoor = 25;
	info->ShiftStartBlock = Vector2( 50, 0 );

	sprite_anim( _T( "door_forest" ), _T( "door_forest" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = _T( "door_forest" );
	info->Doors->Sprite->Size = Vector2( 296, -1 );
	info->Doors->Sprite->Offset = Vector2( -140, 35 );
	info->Doors->ShiftStart = Vector2( 0, 190 );

	info->Walls->Sprite->Sprite = _T( "pillar_forest_1000" );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4650 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = _T( "Flow_Sea_1" );
	info->LavaDrips->Line_Renamed->Sprite = _T( "Flow_Sea_2" );
	info->LavaDrips->Line_Renamed->End2 = _T( "Flow_Sea_3" );

	info->Lasers->Line_Renamed->Sprite = _T( "Laser_Forest" );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( _T( "fblock_forest" ), _T( "fblock_forest" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( std::make_shared<PieceQuad>( 103, _T( "fblock_forest" ), -3, 3, 2 ) );

	sprite_anim( _T( "Bouncy_Forest" ), _T( "Bouncy_Forest" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( std::make_shared<PieceQuad>( 124, _T( "bouncy_Forest" ), -6, 6, 13 ) );

	sprite_anim( _T( "flame_forest" ), _T( "firespinner_flame_forest" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = _T( "flame_forest" );
	info->Spinners->Flame->Size = Vector2( 47, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->Base->Sprite = _T( "firespinner_base_forest_1" );
	info->Spinners->Base->Size = Vector2( 75, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -45 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 45;
	info->Spinners->TopOffset = -40;

	info->GhostBlocks->Sprite = _T( "ghostblock_forest_1" );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 190, _T( "movingblock_forest_190_v2" ), -1, 1, 1 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 150, _T( "movingblock_forest_150" ), -1, 1, 1 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 135, _T( "movingblock_forest_135_v2" ), -1, 1, 1 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 80, _T( "movingblock_forest_80_v2" ), -1, 1, 1 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 40, _T( "movingblock_forest_40_v2" ), -1, 1, 1 ) );

	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Forest_40" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Forest_80" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Forest_135" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Forest_190" ), -1, 1, 1 ) );

	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Forest_40" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Forest_80" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Forest_135" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Forest_190" ), -1, 1, 1 ) );

	sprite_anim( _T( "Serpent_Forest" ), _T( "Serpent_Forest" ), 1, 2, 8 );
	info->Serpents->Serpent_Renamed->Sprite = _T( "Serpent_Forest" );
	sprite_anim( _T( "Serpent_Fish_Forest" ), _T( "Serpent_Fish_Forest" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = _T( "Serpent_Fish_Forest" );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Spikes->Spike_Renamed->Sprite = _T( "spike_forest" );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = _T( "spike_base_forest_1" );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Sprite = _T( "floater_spikey_forest" );
	info->Boulders->Ball->Size = Vector2( 160, -1 );
	info->Boulders->Radius = 120;
	info->Boulders->Chain->Sprite = _T( "floater_chain_forest" );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;

	info->SpikeyGuys->Ball->Sprite = _T( "floater_spikey_forest" );
	info->SpikeyGuys->Ball->Size = Vector2( 150, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, -22 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 130;
	info->SpikeyGuys->RotateOffset = .05f;
	info->SpikeyGuys->Chain->Sprite = _T( "floater_chain_forest" );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyGuys->Ball->Sprite = _T( "floater_buzzsaw_forest" );
	info->SpikeyGuys->Ball->Size = Vector2( 230, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 0 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->RotateSpeed = -.15f;
	info->SpikeyGuys->Radius = 130;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = _T( "floater_chain_forest" );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	info->SpikeyLines->Ball->Sprite = _T( "Floater_Spikey_Forest" );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, -10 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( _T( "blob_forest" ), _T( "blob_forest" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = _T( "blob_forest" );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->GooSprite = _T( "BlobGoo3" );

	info->Clouds->Sprite->Sprite = _T( "cloud_forest" );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 192.5f );

	info->Coins->Sprite->Sprite = _T( "coin_blue" );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;
	info->ObstacleCutoff = 70;

		t->_Finish();

		return t;
	}

	std::shared_ptr<TileSet> TileSets::Load_Cave()
	{
		std::shared_ptr<CloudberryKingdom::TileSet> t = GetOrMakeTileset( _T( "Cave" ) );
		std::shared_ptr<CloudberryKingdom::TileSet::TileSetInfo> info = t->MyTileSetInfo;

		t->_Start();

	t->Name = _T( "cave" );

	t->HasCeiling = true;

	t->Pillars->Add( std::make_shared<PieceQuad>( 50, _T( "pillar_cave_50" ), -15, 15, 3 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 100, _T( "pillar_cave_100" ), -15, 15, 12 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 150, _T( "pillar_cave_150" ), -15, 15, 0 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 250, _T( "pillar_cave_250" ), -15, 15, 0 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 300, _T( "pillar_cave_300" ), -15, 15, 0 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 600, _T( "pillar_cave_600" ), -15, 15, 0 ) );
	t->Pillars->Add( std::make_shared<PieceQuad>( 1000, _T( "pillar_cave_1000" ), -15, 15, 0 ) );

	t->Ceilings->Add( std::make_shared<PieceQuad>( 50, _T( "pillar_cave_50" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 100, _T( "pillar_cave_100" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 150, _T( "pillar_cave_150" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 250, _T( "pillar_cave_250" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 300, _T( "pillar_cave_300" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 600, _T( "pillar_cave_600" ), -20, 20, 0, true ) );
	t->Ceilings->Add( std::make_shared<PieceQuad>( 1000, _T( "pillar_cave_1000" ), -20, 20, 0, true ) );

	//t.Pillars.Add(new PieceQuad(50, "pillar_cave_50_v3", -15, 15, 3));
	//t.Pillars.Add(new PieceQuad(100, "pillar_cave_100_v3", -15, 15, 12));
	//t.Pillars.Add(new PieceQuad(150, "pillar_cave_150_v3", -15, 15, 0));
	//t.Pillars.Add(new PieceQuad(250, "pillar_cave_250_v3", -15, 15, 0));
	//t.Pillars.Add(new PieceQuad(300, "pillar_cave_300_v3", -15, 15, 0));
	//t.Pillars.Add(new PieceQuad(600, "pillar_cave_600_v3", -15, 15, 0));
	//t.Pillars.Add(new PieceQuad(1000, "pillar_cave_1000_v3", -15, 15, 0));

	//t.Ceilings.Add(new PieceQuad(50, "pillar_cave_50_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(100, "pillar_cave_100_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(150, "pillar_cave_150_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(250, "pillar_cave_250_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(300, "pillar_cave_300_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(600, "pillar_cave_600_v3", -20, 20, 0, true));
	//t.Ceilings.Add(new PieceQuad(1000, "pillar_cave_1000_v3", -20, 20, 0, true));

	t->StartBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_cave" ), -650, 120, 1548 ) );
	t->EndBlock->Add( std::make_shared<PieceQuad>( 400, _T( "wall_cave" ), -34, 736, 1548 ) );

	info->ShiftStartDoor = -180;
	info->ShiftStartBlock = Vector2( 300, 0 );

	sprite_anim( _T( "door_cave" ), _T( "door_cave" ), 1, 2, 2 );
	info->Doors->Sprite->Sprite = _T( "door_cave" );
	info->Doors->Sprite->Size = Vector2( 500, -1 );
	info->Doors->Sprite->Offset = Vector2( -250, 135 );
	info->Doors->ShiftStart = Vector2( 0, 190 );
	info->Doors->SizePadding = Vector2( 25, 0 );

	info->Walls->Sprite->Sprite = _T( "pillar_cave_1000" );
	info->Walls->Sprite->Size = Vector2( 1500, -1 );
	info->Walls->Sprite->Offset = Vector2( 0, 4550 );
	info->Walls->Sprite->Degrees = -90;

	info->LavaDrips->Line_Renamed->End1 = _T( "Flow_cave_1" );
	info->LavaDrips->Line_Renamed->Sprite = _T( "Flow_cave_2" );
	info->LavaDrips->Line_Renamed->End2 = _T( "Flow_Cave_3" );

	info->Lasers->Line_Renamed->Sprite = _T( "Laser_Cave" );
	info->Lasers->Line_Renamed->RepeatWidth = 135;
	info->Lasers->Line_Renamed->Dir = 0;
	info->Lasers->Scale = 1;
	info->Lasers->Tint_Full = Vector4( 1, 1, 1,.95f );
	info->Lasers->Tint_Half = Vector4( 1, 1, 1,.4f );

	sprite_anim( _T( "fblock_cave" ), _T( "fblock_cave" ), 1, 3, 2 );
	info->FallingBlocks->Group->Add( std::make_shared<PieceQuad>( 103, _T( "fblock_cave" ), -3, 3, 2 ) );

	sprite_anim( _T( "Bouncy_cave" ), _T( "Bouncy_cave" ), 1, 3, 2 );
	info->BouncyBlocks->Group->Add( std::make_shared<PieceQuad>( 124, _T( "bouncy_cave" ), -6, 6, 13 ) );

	sprite_anim( _T( "flame_cave" ), _T( "firespinner_flame_cloud" ), 1, 4, 6 );
	info->Spinners->Flame->Sprite = _T( "flame_cave" );
	info->Spinners->Flame->Size = Vector2( 45, -1 );
	info->Spinners->Rotate = false;
	info->Spinners->RotateStep = .13f;
	info->Spinners->Base->Sprite = _T( "firespinner_base_cloud" );
	info->Spinners->Base->Size = Vector2( 90, -1 );
	info->Spinners->Base->Offset = Vector2( 0, -25 );
	info->Spinners->SegmentSpacing = 65;
	info->Spinners->SpaceFromBase = 55;

	info->GhostBlocks->Sprite = _T( "ghostblock_cave" );
	info->GhostBlocks->Shift = Vector2( 0, -15 );

	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 190, _T( "movingblock_cave_190" ), -1, 1, 7 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 135, _T( "movingblock_cave_135" ), -1, 1, 7 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 80, _T( "movingblock_cave_80" ), -1, 1, 3 ) );
	info->MovingBlocks->Group->Add( std::make_shared<PieceQuad>( 40, _T( "movingblock_cave_40" ), -1, 1, 3 ) );

	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Cave_40" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Cave_80" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Cave_135" ), -1, 1, 1 ) );
	info->Elevators->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Cave_190" ), -1, 1, 1 ) );
	//info.Elevators.Group.Add(40, "Cave_40_v2", -1, 1, 1));
	//info.Elevators.Group.Add(80, "Cave_80_v2", -1, 1, 1));
	//info.Elevators.Group.Add(135, "Cave_135_v2", -1, 1, 1));
	//info.Elevators.Group.Add(190, "Cave_190_v2", -1, 1, 1));

	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 40, _T( "Elevator_Cave_40" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 80, _T( "Elevator_Cave_80" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 135, _T( "Elevator_Cave_135" ), -1, 1, 1 ) );
	info->Pendulums->Group->Add( std::make_shared<PieceQuad>( 190, _T( "Elevator_Cave_190" ), -1, 1, 1 ) );

	sprite_anim( _T( "Serpent_Cave" ), _T( "Serpent_Cloud" ), 1, 2, 8 );
	info->Serpents->Serpent_Renamed->Sprite = _T( "Serpent_Cave" );
	sprite_anim( _T( "Serpent_Fish_Cave" ), _T( "Serpent_Fish_Cloud" ), 1, 2, 5 );
	info->Serpents->Fish->Sprite = _T( "Serpent_Fish_Cave" );
	info->Serpents->Fish->Size = Vector2( 60, -1 );
	info->Serpents->Fish->Offset = Vector2( 55, 0 );

	info->Serpents->Serpent_Renamed->Sprite = _T( "Serpent_cave" );

	info->Spikes->Spike_Renamed->Sprite = _T( "spike_cave" );
	info->Spikes->Spike_Renamed->Size = Vector2( 38, -1 );
	info->Spikes->Spike_Renamed->Offset = Vector2( 0, 1 );
	info->Spikes->Spike_Renamed->RelativeOffset = true;
	info->Spikes->Base->Sprite = _T( "spike_base_cave_1" );
	info->Spikes->Base->Size = Vector2( 54, -1 );
	info->Spikes->PeakHeight = .335f;

	info->Boulders->Ball->Sprite = _T( "floater_spikey_cave" );
	info->Boulders->Ball->Size = Vector2( 150, -1 );
	info->Boulders->Radius = 120;
	info->Boulders->Chain->Sprite = _T( "floater_chain_cave" );
	info->Boulders->Chain->Width = 55;
	info->Boulders->Chain->RepeatWidth = 1900;

	info->Boulders->Ball->Sprite = _T( "Floater_Boulder_Cloud" );
	info->Boulders->Ball->Size = Vector2( 200, -1 );
	info->Boulders->Radius = 140;
	info->Boulders->Chain->Sprite = _T( "Floater_Rope_Cave" );
	info->Boulders->Chain->RepeatWidth = 1900;
	info->Boulders->Chain->Width = 55;

	info->SpikeyGuys->Ball->Sprite = _T( "floater_spikey_cave" );
	info->SpikeyGuys->Ball->Size = Vector2( 150, -1 );
	info->SpikeyGuys->Ball->Offset = Vector2( 0, 8 );
	info->SpikeyGuys->Base->Sprite.reset();
	info->SpikeyGuys->Rotate = true;
	info->SpikeyGuys->Radius = 116;
	info->SpikeyGuys->RotateOffset = -1.57f;
	info->SpikeyGuys->Chain->Sprite = _T( "floater_chain_cave" );
	info->SpikeyGuys->Chain->Width = 55;
	info->SpikeyGuys->Chain->RepeatWidth = 1900;

	//info.Orbs.Ball.Sprite = "Floater_Boulder_Cloud";
	//info.Orbs.Ball.Size = new Vector2(200, -1);
	//info.Orbs.Radius = 140;

	info->SpikeyLines->Ball->Sprite = _T( "Floater_Spikey_Cave" );
	info->SpikeyLines->Ball->Size = Vector2( 150, -1 );
	info->SpikeyLines->Ball->Offset = Vector2( -8, 12 );
	info->SpikeyLines->Radius = 100;
	info->SpikeyLines->Rotate = true;
	info->SpikeyLines->RotateSpeed = .05f;

	sprite_anim( _T( "blob_cave" ), _T( "blob_cave" ), 1, 4, 2 );
	info->Blobs->Body->Sprite = _T( "blob_cave" );
	info->Blobs->Body->Size = Vector2( 130, -1 );
	info->Blobs->Body->Offset = Vector2( 20, 20 );
	info->Blobs->GooSprite = _T( "BlobGoo5" );

	info->Clouds->Sprite->Sprite = _T( "cloud_cave" );

	info->Fireballs->Sprite->ColorMatrix = ColorHelper::HsvTransform( 1, 1, 104 );

	info->Coins->Sprite->Sprite = _T( "coin_blue" );
	info->Coins->Sprite->Size = Vector2( 105, -1 );
	info->Coins->ShowCoin = true;
	info->Coins->ShowEffect = true;
	info->Coins->ShowText = true;

	info->AllowLava = false;
	info->ObstacleCutoff = 40;

		t->_Finish();

		return t;
	}

std::shared_ptr<TileSet> None, TileSets::Random = 0;
std::shared_ptr<TileSet> TileSets::DefaultTileSet = 0;
std::vector<TileSet*> TileSets::TileList = std::vector<TileSet*>();
std::unordered_map<int, TileSet*> TileSets::GuidLookup = std::unordered_map<int, TileSet*>();
std::unordered_map<std::wstring, TileSet*> NameLookup, TileSets::PathLookup = std::unordered_map<std::wstring, TileSet*>();

	void TileSets::AddTileSet( const std::shared_ptr<TileSet> &tileset )
	{
		TileList.push_back( tileset );

		// Add the tileset to the Guid lookup
		GuidLookup.AddOrOverwrite( tileset->Guid, tileset );

		// Add the tileset to the Name lookup
		NameLookup.AddOrOverwrite( tileset->Name, tileset );

		// Add the tileset to the Path lookup
		if ( tileset->MyPath.length() > 0 )
		{
			PathLookup.AddOrOverwrite( tileset->MyPath, tileset );
		}
	}

	void TileSets::LoadCode()
	{
		AddTileSet( Load_Sea()->SetBackground(_T("sea"))->SetNameInGame(Localization::Words_SEA) );
		AddTileSet( Load_Sea()->SetBackground(_T("sea_rain"))->SetName(_T("sea_rain"))->SetNameInGame(Localization::Words_SEA) );
		AddTileSet( Load_Hills()->SetBackground(_T("hills"))->SetNameInGame(Localization::Words_HILLS) );
		AddTileSet( Load_Hills()->SetBackground(_T("hills_rain"))->SetName(_T("hills_rain"))->SetNameInGame(Localization::Words_HILLS) );
		AddTileSet( Load_Forest()->SetBackground(_T("forest"))->SetNameInGame(Localization::Words_FOREST) );
		AddTileSet( Load_Forest()->SetBackground(_T("forest_snow"))->SetName(_T("forest_snow"))->SetNameInGame(Localization::Words_FOREST) );
		AddTileSet( Load_Cloud()->SetBackground(_T("cloud"))->SetNameInGame(Localization::Words_CLOUD) );
		AddTileSet( Load_Cloud()->SetBackground(_T("cloud_rain"))->SetName(_T("cloud_rain"))->SetNameInGame(Localization::Words_CLOUD) );
		AddTileSet( Load_Cave()->SetBackground(_T("cave"))->SetNameInGame(Localization::Words_CAVE) );
		AddTileSet( Load_Castle()->SetBackground(_T("castle"))->SetNameInGame(Localization::Words_CASTLE) );
	}

	void TileSets::LoadTileSet( const std::wstring &path )
	{
		std::shared_ptr<CloudberryKingdom::TileSet> tileset = GetOrMakeTileset( path );

		tileset->Read( path );
		AddTileSet( tileset );
	}

	std::shared_ptr<TileSet> TileSets::GetOrMakeTileset( const std::wstring &path )
	{
		std::shared_ptr<TileSet> tileset;
		if ( PathLookup.find( path ) != PathLookup.end() )
		{
			tileset = PathLookup[ path ];
			tileset->MakeNew();
		}
		else
		{
			tileset = std::make_shared<TileSet>();

			// Add the tileset to Freeplay
			CustomLevel_GUI::FreeplayTilesets.push_back( tileset );
		}

		return tileset;
	}

	void TileSets::sprite_anim( const std::wstring &name, const std::wstring &texture_root, int start_frame, int end_frame, int frame_length )
	{
		sprite_anim( name, texture_root, start_frame, end_frame, frame_length, false );
	}

	void TileSets::sprite_anim( const std::wstring &name, const std::wstring &texture_root, int start_frame, int end_frame, int frame_length, bool reverse_at_end )
	{
		std::shared_ptr<AnimationData_Texture> sprite_anim = 0;

		sprite_anim = std::make_shared<AnimationData_Texture>( texture_root, start_frame, end_frame );

		// Set speed based on how long each frame is.
		sprite_anim->Anims[ 0 ].Speed = 1 / frame_length;

		// Add new sprite animation to the texture wad.
		Tools::TextureWad->Add( sprite_anim, name );
	}

	void TileSets::Init()
	{
		std::shared_ptr<TileSet> info;

		// None
		DefaultTileSet = None = info = std::make_shared<TileSet>();
		info->Name = _T( "None" );
		info->NameInGame = Localization::Words_NONE;
		info->Guid = 5551;
		AddTileSet( info );
		info->MyBackgroundType = BackgroundType::None;
		info->ScreenshotString = _T( "Screenshot_Random" );
		info->HasCeiling = true;
		info->FlexibleHeight = false;
		const Upgrade tempVector[] = { Upgrade_BOUNCY_BLOCK, Upgrade_FLY_BLOB, Upgrade_MOVING_BLOCK, Upgrade_SPIKE };
		info->ObstacleUpgrades.AddRange( std::vector<Upgrade>( tempVector, tempVector + sizeof( tempVector ) / sizeof( tempVector[ 0 ] ) ) );

		// Random
		Random = info = std::make_shared<TileSet>();
		info->Name = _T( "Random" );
		info->NameInGame = Localization::Words_RANDOM;
		info->Guid = 5552;
		AddTileSet( info );
		info->MyBackgroundType = BackgroundType::Random;
		info->ScreenshotString = _T( "Screenshot_Random" );
		const Upgrade tempVector2[] = { Upgrade_BOUNCY_BLOCK, Upgrade_FLY_BLOB, Upgrade_MOVING_BLOCK, Upgrade_FIREBALL, Upgrade_PINKY };
		info->ObstacleUpgrades.AddRange( std::vector<Upgrade>( tempVector2, tempVector2 + sizeof( tempVector2 ) / sizeof( tempVector2[ 0 ] ) ) );

		// Sprite effects
		LoadSpriteEffects();

		// New tile sets
		TileSets::LoadCode();

		// Freeplay tilesets
		const TileSet* tempVector3[] = { TileSets::Random, _T( "sea" ), _T( "hills" ), _T( "forest" ), _T( "cloud" ), _T( "cave" ), _T( "castle" ) };
		CustomLevel_GUI::FreeplayTilesets = std::vector<TileSet*>( tempVector3, tempVector3 + sizeof( tempVector3 ) / sizeof( tempVector3[ 0 ] ) );
	}

	void TileSets::LoadSpriteEffects()
	{
		sprite_anim( _T( "CoinShimmer" ), _T( "Coin" ), 0, 49, 1 );

		sprite_anim( _T( "BlobExplosion_v2" ), _T( "BlobExplosion_v02" ), 0, 29, 1 );
		sprite_anim( _T( "BobExplosion_v1" ), _T( "BobExplosion_v01" ), 0, 54, 1 );
		sprite_anim( _T( "CoinCollect_v1" ), _T( "CoinCollect_v01" ), 0, 32, 1 );
		sprite_anim( _T( "CoinCollect_v2" ), _T( "CoinCollect_v02" ), 0, 26, 1 );
		sprite_anim( _T( "CoinCollect_Sparkes_v3" ), _T( "CoinCollect_Sparkles_v03" ), 0, 26, 1 );
		sprite_anim( _T( "CoinCollect_Star_v3" ), _T( "CoinCollect_Star_v03" ), 0, 17, 1 );
		sprite_anim( _T( "CoinCollect_v4" ), _T( "CoinCollect_v04" ), 0, 26, 1 );
	}
}