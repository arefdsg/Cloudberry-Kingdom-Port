﻿#include <global_header.h>




namespace CloudberryKingdom
{

	const std::shared_ptr<GameData> &ObjectBase::getGame() const
	{
		return getCore()->MyLevel->MyGame;
	}

	const std::shared_ptr<Level> &ObjectBase::getMyLevel() const
	{
		return getCore()->MyLevel;
	}

	const std::shared_ptr<Camera> &ObjectBase::getCam() const
	{
		return getCore()->MyLevel->getMainCamera();
	}

	const std::shared_ptr<Rand> &ObjectBase::getRnd() const
	{
		return getCore()->MyLevel->getRnd();
	}

	const Microsoft::Xna::Framework::Vector2 &ObjectBase::getPos() const
	{
		return getCore()->Data.Position;
	}

	void ObjectBase::setPos( const Vector2 &value )
	{
		getCore()->Data.Position = value;
	}

	const std::shared_ptr<ObjectData> &ObjectBase::getCore() const
	{
		return CoreData;
	}

	const std::shared_ptr<TileSet::TileSetInfo> &ObjectBase::getInfo() const
	{
		if ( CoreData->MyLevel == 0 )
			return 0;

		return CoreData->MyLevel->MyTileSet->MyTileSetInfo;
	}

	ObjectBase::ObjectBase()
	{
		CoreData = std::make_shared<ObjectData>();
	}

	void ObjectBase::Init( Vector2 pos, const std::shared_ptr<Level> &level )
	{
		getCore()->StartData.Position = getCore()->Data.Position = pos;

//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		var tile = getCore()->setMyTileSet(level->MyTileSet);
		Tools::Assert( getCore()->getMyTileSet() != 0 );
	}

	void ObjectBase::Release()
	{
		getCore()->Release();
	}

	void ObjectBase::SetParentBlock( const std::shared_ptr<BlockBase> &block )
	{
		getCore()->SetParentBlock(block);
		OnAttachedToBlock();
	}

	void ObjectBase::CollectSelf()
	{
		if ( getCore()->MarkedForDeletion )
			return;

		getCore()->getRecycle()->CollectObject(this);
	}

	void ObjectBase::StampAsUsed( int CurPhsxStep )
	{
		getCore()->GenData.__StampAsUsed(CurPhsxStep);
		OnUsed();
	}

	void ObjectBase::MakeNew()
	{
	}

	void ObjectBase::PhsxStep()
	{
	}

	void ObjectBase::PhsxStep2()
	{
	}

	void ObjectBase::Draw()
	{
	}

	void ObjectBase::TextDraw()
	{
	}

	void ObjectBase::Reset( bool BoxesOnly )
	{
	}

	void ObjectBase::Clone( const std::shared_ptr<ObjectBase> &A )
	{
		getCore()->Clone(A->getCore());
	}

	void ObjectBase::Read( const std::shared_ptr<BinaryReader> &reader )
	{
		getCore()->Read(reader);
	}

	void ObjectBase::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		getCore()->Write(writer);
	}

	void ObjectBase::Interact( const std::shared_ptr<Bob> &bob )
	{
	}

	void ObjectBase::Move( Vector2 shift )
	{
		getCore()->StartData.Position += shift;
		getCore()->Data.Position += shift;
	}

	void ObjectBase::OnUsed()
	{
	}

	void ObjectBase::OnMarkedForDeletion()
	{
	}

	void ObjectBase::OnAttachedToBlock()
	{
	}

	bool ObjectBase::PermissionToUse()
	{
		return true;
	}

	void ObjectBase::Smash( const std::shared_ptr<Bob> &bob )
	{
	}

	bool ObjectBase::PreDecision( const std::shared_ptr<Bob> &bob )
	{
		return false;
	}

	void GenerationData::Decide_RemoveIfUnused( float ChanceToKeep, const std::shared_ptr<Rand> &Rnd )
	{
		if ( Rnd->Rnd->NextDouble() < ChanceToKeep )
		{
			RemoveIfUnused = false;
		}
		else
		{
			RemoveIfUnused = true;
		}
	}

	void GenerationData::__StampAsUsed( int Step )
	{
		if ( Used )
			return;

		if ( OnUsed != 0 )
			OnUsed->Apply();

		Used = true;
		UsedTimeStamp = Step;
	}

	void GenerationData::Release()
	{
		OnUsed = OnMarkedForDeletion = 0;
	}

	void GenerationData::Init()
	{
		OnUsed = OnMarkedForDeletion = 0;

		AlwaysUse = AlwaysLandOn = false;

		EnforceBounds = true;

		KeepIfUnused = false;

		RemoveIfUsed = false;
		RemoveIfUnused = true;
		Used = false;

		NoBlockOverlap = false;
		OverlapWidth = 35;
		LimitGeneralDensity = false;
		LimitDensity = true;

		DeleteSurroundingOnUse = true;

		EdgeJumpOnly = false;

		TemporaryNoLandZone = false;
		JumpNow = false;

		EdgeSafety = 0;

		NoBottomShift = false;
		NoMakingTopOnly = false;
	}

	void BlockExtension::StampAsFullyUsed( const std::shared_ptr<BlockBase> &block, int CurPhsxStep )
	{
		block->StampAsUsed( CurPhsxStep );
		block->getBlockCore()->NonTopUsed = true;
	}

	void BlockExtension::Stretch( const std::shared_ptr<BlockBase> &block, Side side, float amount )
	{
		block->getBox()->CalcBounds();
		switch ( side )
		{
			case Side_RIGHT:
				block->Extend( side, block->getBox()->GetTR().X + amount );
				break;
			case Side_LEFT:
				block->Extend( side, block->getBox()->GetBL().X + amount );
				break;
			case Side_TOP:
				block->Extend( side, block->getBox()->GetTR().Y + amount );
				break;
			case Side_BOTTOM:
				block->Extend( side, block->getBox()->GetBL().Y + amount );
				break;
		}
	}

	void ObjectData::AssociatedObjData::Zero()
	{
		Guid = 0;
		DeleteWhenDeleted = false;
		UseWhenUsed = false;
	}

	const std::shared_ptr<Recycler> &ObjectData::getRecycle() const
	{
		if ( MyLevel != 0 )
			return MyLevel->getRecycle();
		else
			Tools::Break();

		return 0;
	}

	bool ObjectData::LevelGenRunning()
	{
		if ( MyLevel == 0 || MyLevel->PlayMode == 0 || MyLevel->Watching || MyLevel->Replay )
			return false;
		else
			return true;
	}

	const std::shared_ptr<TileSet> &ObjectData::getMyTileSet() const
	{
		return _TileSet;
	}

	void ObjectData::setMyTileSet( const std::shared_ptr<TileSet> &value )
	{
		_TileSet = value;
		if ( _TileSet == 0 )
			Tools::Break();
	}

	std::shared_ptr<AutoGen_Parameters> ObjectData::GetParams( const std::shared_ptr<AutoGen> &singleton )
	{
		return MyLevel->CurPiece->MyData->Style_FIND_PARAMS( singleton );
	}

unsigned long long ObjectData::NextId = 0;

	unsigned long long ObjectData::GetId()
	{
		return NextId++;
	}

	const std::shared_ptr<Bob> &ObjectData::getInteractingBob() const
	{
		return _InteractingBob;
	}

	void ObjectData::setInteractingBob( const std::shared_ptr<Bob> &value )
	{
		_InteractingBob = value;

		if ( getInteractingBob() != 0 )
			InteractingPlayer = getInteractingBob()->GetPlayerData();
	}

	void ObjectData::AddAssociation( bool DeleteWhenDeleted, bool UseWhenUsed, ... )
	{
		for ( unknown::const_iterator obj = objs.begin(); obj != objs.end(); ++obj )
			for ( unknown::const_iterator _obj = objs.begin(); _obj != objs.end(); ++_obj )
				if ( *obj != *_obj )
					( *obj )->getCore()->AddAssociate(*_obj, DeleteWhenDeleted, UseWhenUsed);
	}

	void ObjectData::AddAssociate( const std::shared_ptr<ObjectBase> &obj, bool DeleteWhenDeleted, bool UseWhenUsed )
	{
		int FreeIndex = 0;
		if ( Associations.empty() )
		{
			Associations = std::vector<AssociatedObjData>( 5 );
			for ( int i = 0; i < 5; i++ )
				Associations[ i ].Zero();
		}
		else
			while ( Associations[ FreeIndex ].Guid != 0 )
				FreeIndex++;

		Associations[ FreeIndex ].Guid = obj->getCore()->MyGuid;
		Associations[ FreeIndex ].DeleteWhenDeleted = DeleteWhenDeleted;
		Associations[ FreeIndex ].UseWhenUsed = UseWhenUsed;
	}

	bool ObjectData::IsAssociatedWith( const std::shared_ptr<ObjectBase> &obj )
	{
		if ( Associations.empty() || obj->getCore()->Associations.empty() )
			return false;
		else
		{
			for ( std::vector<CloudberryKingdom::ObjectData::AssociatedObjData>::const_iterator data = Associations.begin(); data != Associations.end(); ++data )
			{
				if ( ( *data ).Guid == obj->getCore()->MyGuid )
					return true;
			}
			return false;
		}
	}

	int ObjectData::GetAssociatedIndex( const std::shared_ptr<ObjectBase> &obj )
	{
		for ( int i = 0; i < Associations.size(); i++ )
			if ( Associations[ i ].Guid == obj->getCore()->MyGuid )
				return i;

		return -1;
	}

	CloudberryKingdom::ObjectData::AssociatedObjData ObjectData::GetAssociationData( const std::shared_ptr<ObjectBase> &obj )
	{
//C# TO C++ CONVERTER TODO TASK: There is no equivalent to implicit typing in C++ unless the C++11 inferred typing option is selected:
		for ( std::vector<CloudberryKingdom::ObjectData::AssociatedObjData>::const_iterator objdata = Associations.begin(); objdata != Associations.end(); ++objdata )
			if ( ( *objdata )->Guid == obj->getCore()->MyGuid )
				return objdata;
		return Associations[ Associations.size() - 1 ];
	}

	void ObjectData::Release()
	{
	#if defined(DEBUG_OBJDATA)
		if ( !Released )
		{
//C# TO C++ CONVERTER TODO TASK: There is no built-in support for multithreading in native C++:
			lock ( MetaCount )
			{
				MetaCount::MyInt--;
			}
		}
	#endif
		Released = true;

		Associations.clear();
		MyLevel.reset();
		ParentObject.reset();
		GenData.Release();

		InteractingPlayer.reset();
		getInteractingBob().reset();
	}

	void ObjectData::SetParentObj( const std::shared_ptr<ObjectBase> &obj )
	{
		ParentObject = obj;
		ParentObjId = obj->getCore()->MyGuid;
	}

	void ObjectData::SetParentBlock( const std::shared_ptr<BlockBase> &block )
	{
		ParentBlock = block;

		ParentOffset = Data.Position - ParentBlock->getBox()->Current->Center;
	}

	Microsoft::Xna::Framework::Vector2 ObjectData::GetPosFromParentOffset()
	{
		std::shared_ptr<BlockData> pdata = ParentBlock->getBlockCore();

		//return ParentBlock.Box.Target.Center + ParentOffset;
		if ( pdata->UseCustomCenterAsParent )
			return pdata->CustomCenterAsParent + pdata->OffsetMultAsParent * ParentOffset;
		else
			return ParentBlock->getBox()->Target->Center + ParentOffset;
	}

	void ObjectData::PosFromParentOffset()
	{
		if ( ParentBlock != 0 )
			Data.Position = GetPosFromParentOffset();
	}

	int ObjectData::GetPhsxStep()
	{
		return MyLevel->GetPhsxStep() + StepOffset;
	}

	float ObjectData::GetIndependentPhsxStep()
	{
		return MyLevel->GetIndependentPhsxStep() + StepOffset;
	}

	const float &ObjectData::getIndependentDeltaT() const
	{
		return MyLevel->IndependentDeltaT;
	}

	bool ObjectData::ContainsCode( const std::wstring &code )
	{
		return ( EditorCode1.compare( code ) == 0 || EditorCode2.compare( code ) == 0 || EditorCode3.compare( code ) == 0 );
	}

	bool ObjectData::operator == ( const std::wstring &str )
	{
		return this->EditorCode1.compare( str ) == 0;
	}

	bool ObjectData::operator != ( const std::wstring &str )
	{
		return !( this == str );
	}

	void ObjectData::Init()
	{
		Released = false;

		setMyTileSet( TileSets::None );
		Encased = false;

		EditorCode1 = EditorCode2 = EditorCode3 = _T( "" );

		MyGuid = GetId();

		Associations.clear();

		IsGameObject = false;

		VisualResettedOnce = false;

		HeldOffset = Vector2::Zero;
		Held = Placed = false;

		Holdable = EditHoldable = false;

		Tag = -1;

		DebugCode = 0;

		ContinuousEnabled = false;

		Show = true;

		Data = PhsxData();
		StartData = PhsxData();

		ParentBlock.reset();
		ParentOffset = Vector2::Zero;

		DoNotScrollOut = false;

		RemoveOnReset = false;
		MarkedForDeletion = false;
		Active = true;

		DeletedByBob = false;
		OnDeletionCodeRan = false;

		MyLevel.reset();
		DrawLayer = 0;
		DrawLayer2 = DrawLayer3 = -1;

		DoNotDrawWithParent = false;

		StepOffset = 0;

		GenData.Init();

		Associations.clear();
	}

	void ObjectData::Clone( const std::shared_ptr<ObjectData> &A )
	{
		setMyTileSet( A->getMyTileSet() );
		Encased = A->Encased;

		if ( A->EditorCode1 == _T( "" ) )
			EditorCode1 = _T( "" );
		else
			EditorCode1 = std::wstring::Copy( A->EditorCode1 );
		if ( A->EditorCode2 == _T( "" ) )
			EditorCode2 = _T( "" );
		else
			EditorCode2 = std::wstring::Copy( A->EditorCode2 );
		if ( A->EditorCode3 == _T( "" ) )
			EditorCode3 = _T( "" );
		else
			EditorCode3 = std::wstring::Copy( A->EditorCode3 );

		MyGuid = A->MyGuid;
		ParentObjId = A->ParentObjId;
		ParentObject = A->ParentObject;

		if ( A->Associations.size() > 0 )
		{
			Associations = std::vector<AssociatedObjData>( A->Associations.size() );
			A->Associations.CopyTo( Associations, 0 );
		}
		else
			Associations.clear();

		IsGameObject = A->IsGameObject;

		AddedTimeStamp = A->AddedTimeStamp;

		ContinuousEnabled = A->ContinuousEnabled;

		VisualResettedOnce = A->VisualResettedOnce;

		HeldOffset = A->HeldOffset;
		Held = A->Held;
		Placed = A->Placed;

		DrawSubLayer = A->DrawSubLayer;

		Holdable = A->Holdable;
		EditHoldable = A->EditHoldable;

		Tag = A->Tag;

		Show = A->Show;

		DoNotScrollOut = A->DoNotScrollOut;

		MyType = A->MyType;
		BoxesOnly = A->BoxesOnly;
		AlwaysBoxesOnly = A->AlwaysBoxesOnly;

		MarkedForDeletion = A->MarkedForDeletion;
		Active = A->Active;

		DeletedByBob = A->DeletedByBob;
		OnDeletionCodeRan = A->OnDeletionCodeRan;

		MyLevel = A->MyLevel;
		DrawLayer = A->DrawLayer;
		DrawLayer2 = A->DrawLayer2;
		DrawLayer3 = A->DrawLayer3;

		DoNotDrawWithParent = A->DoNotDrawWithParent;

		Data = A->Data;
		StartData = A->StartData;

		StepOffset = A->StepOffset;

		GenData = A->GenData;

		ParentBlock = A->ParentBlock;
		ParentOffset = A->ParentOffset;
	}

	void ObjectData::Write( const std::shared_ptr<BinaryWriter> &writer )
	{
		writer->Write( static_cast<unsigned int>( getMyTileSet()->Guid ) );
		writer->Write( EditorCode1 );
		writer->Write( EditorCode2 );
		writer->Write( EditorCode3 );

		writer->Write( MyGuid );
		writer->Write( ParentObjId );

		writer->Write( DrawSubLayer );

		writer->Write( Tag );

		writer->Write( Show );

		writer->Write( Held );
		writer->Write( Placed );
		writer->Write( Holdable );
		writer->Write( EditHoldable );

		writer->Write( DoNotScrollOut );

		writer->Write( static_cast<int>( MyType ) );
		writer->Write( BoxesOnly );
		writer->Write( AlwaysBoxesOnly );

		writer->Write( MarkedForDeletion );
		writer->Write( Active );

		writer->Write( DrawLayer );
		//writer.Write(DrawLayer2);

		WriteReadTools::WritePhsxData( writer, Data );
		WriteReadTools::WritePhsxData( writer, StartData );

		writer->Write( StepOffset );
		//WriteReadTools.WritePhsxData(writer, GenData);

		WriteReadTools::WriteVector2( writer, ParentOffset );
	}

	void ObjectData::Read( const std::shared_ptr<BinaryReader> &reader )
	{
		//MyTileSet = (TileSet)reader.ReadUInt32();
		int TileGuid = static_cast<int>( reader->ReadUInt32() );
		setMyTileSet( TileSets::GuidLookup[ TileGuid ] );

		EditorCode1 = reader->ReadString();
		EditorCode2 = reader->ReadString();
		EditorCode3 = reader->ReadString();

		MyGuid = reader->ReadUInt64();
		ParentObjId = reader->ReadUInt64();

		DrawSubLayer = reader->ReadInt32();

		Tag = reader->ReadInt32();

		Show = reader->ReadBoolean();

		Held = reader->ReadBoolean();
		Placed = reader->ReadBoolean();
		Holdable = reader->ReadBoolean();
		EditHoldable = reader->ReadBoolean();

		DoNotScrollOut = reader->ReadBoolean();

		MyType = static_cast<ObjectType>( reader->ReadInt32() );
		BoxesOnly = reader->ReadBoolean();
		AlwaysBoxesOnly = reader->ReadBoolean();

		MarkedForDeletion = reader->ReadBoolean();
		Active = reader->ReadBoolean();

		DrawLayer = reader->ReadInt32();
		//DrawLayer2 = reader.ReadInt32();

		WriteReadTools::ReadPhsxData( reader, Data );
		WriteReadTools::ReadPhsxData( reader, StartData );

		StepOffset = reader->ReadInt32();
		//WriteReadTools.WritePhsxData(Readr, GenData = reader

		WriteReadTools::ReadVector2( reader, ParentOffset );
	}

	void ObjectData::InitializeInstanceFields()
	{
		_TileSet = 0;
		VisualResettedOnce = false;
		Real = true;
		DrawLayer2 = -1;
		DrawLayer3 = -1;
		FixSubLayer = false;
		Released = false;
	}
}