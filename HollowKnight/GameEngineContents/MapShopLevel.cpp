#include "PreCompile.h"

#include "MapShopLevel.h"

#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

MapShopLevel::MapShopLevel() 
	:
	DirtmouthPotal_(nullptr)
{
}

MapShopLevel::~MapShopLevel() 
{
}

void MapShopLevel::Start()
{
	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("MapShop_Background.png");
	//GetMasterMap()->CreateBackGroundObject("Dirtmouth_BackGround_Obj_2.png");
	GetMasterMap()->CreateMapCollision("MapShop_Coll.png");

	CreateKnightActor(); // �÷��̾�

	GetMasterMap()->CreateTerrain("MapShop_Terrain.png");
	GetMasterMap()->CreateFrontObject("MapShop_MapObject.png");

	CreateUIActor();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());

	CreateSettingPageActor();
	CreateForgottenCrossroadMap();

	SetMainMapSize({ 1920, 1080 });

	GetKnight()->GetTransform().SetLocalPosition({ 800, 0.f, static_cast<float>(Z_ORDER::Knight) });

	GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);

	DirtmouthPotal_ = CreateActor<RoomPotal>();
	DirtmouthPotal_->CreatePotal(POTAL_TYPE::Map_Shop, true);
	DirtmouthPotal_->GetTransform().SetWorldPosition({ 3840, -3045.f });
}

void MapShopLevel::Update(float _DeltaTime)
{
	CameraMoveWindowLimit();

}

void MapShopLevel::End()
{
}
