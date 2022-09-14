#include "PreCompile.h"
#include "DirtmouthLevel2.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineDevice.h>
#include "Knight.h"
#include "Monster.h"
#include "KnightData.h"

#include "Bench.h"
#include "AreaTitle.h"

#include "OverlayPostEffect.h"
#include "NoisePostEffect.h"
#include "VignettePostEffect.h"

DirtmouthLevel2::DirtmouthLevel2() 
	:
	Elderbug_(nullptr)
{
}

DirtmouthLevel2::~DirtmouthLevel2() 
{
}

void DirtmouthLevel2::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("FreeCameraOnOff"))
	{
		GameEngineInput::GetInst()->CreateKey("FreeCameraOnOff", 'O');
	}

	CraateMasterMapActor();

	GetMasterMap()->CreateBackGround("Dirtmouth_BackGround_2.png");
	GetMasterMap()->CreateBackGroundObject("Dirtmouth_BackGround_Obj_2.png");
	GetMasterMap()->CreateMapCollision("Dirtmouth_2_Coll.png");

	if (GetKnight() == nullptr)
	{
		CreateKnightActor(); // �÷��̾�
	}

	GetMasterMap()->CreateTerrain("Dirtmouth_Terrian_2.png");
	GetMasterMap()->CreateFrontObject("Dirtmouth_MapObject_2.png");

	CreateUIActor();

	CreateSettingPageActor();
	CreateForgottenCrossroadMap();
	CreateMainCameraManager();
	CreateEffectGUIActor();

	SetMapSize({ 6646, 3418 });


	Bench* Test_ = CreateActor<Bench>();
	AreaTitle* AreaTitle_ = CreateActor<AreaTitle>();

	MapShopPotal_ = CreateActor<RoomPotal>();
	MapShopPotal_->CreatePotal(POTAL_TYPE::Map_Shop, true);
	MapShopPotal_->GetTransform().SetWorldPosition({3840, -3045.f });

	Elderbug_ = CreateActor<Elderbug>();

	GetKnight()->SetCollisionMap(GetMasterMap()->GetCollisionMap());
	GetKnight()->GetTransform().SetLocalPosition({ 500.f, -2500.f, static_cast<float>(Z_ORDER::Knight) });
	
	OverlayPostEffect* OverlayPostEffect_ = GetMainCamera()->GetCameraRenderTarget()->AddEffect<OverlayPostEffect>();
	OverlayPostEffect_->SetHollowKnightLevel(this);

	GetMainCamera()->GetCameraRenderTarget()->AddEffect<NoisePostEffect>();
	GetMainCamera()->GetCameraRenderTarget()->AddEffect<VignettePostEffect>();

	//GetMainCameraActor()->GetCameraComponent()->SetProjectionMode(CAMERAPROJECTIONMODE::PersPective);


}

void DirtmouthLevel2::Update(float _DeltaTime)
{
	//GetMainCameraManager()->MainCameraMoveLimitWindow(GetKnight()->GetTransform().GetWorldPosition(), GetMapSize());

}

void DirtmouthLevel2::End()
{
}

void DirtmouthLevel2::LevelStartEvent()
{

}

void DirtmouthLevel2::LevelEndEvent()
{

}
