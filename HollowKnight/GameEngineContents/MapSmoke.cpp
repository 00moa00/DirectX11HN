#include "PreCompile.h"
#include "MapSmoke.h"
#include <GameEngineBase/GameEngineRandom.h>

#include "HollowKnightLevel.h"

MapSmoke::MapSmoke() 
	:
	RotatinSpeed_(0.f),
	Speed_(0.f),

	ParticleRenderer_(nullptr)

{
}

MapSmoke::~MapSmoke() 
{
}

void MapSmoke::Start()
{
	ParticleRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	ParticleRenderer_->SetTexture("hot_spring_smoke.png");

	float RamdomScale = GameEngineRandom::MainRandom.RandomFloat(5.0f,7.0f);
	ParticleRenderer_->GetTransform().SetLocalScale({ 118.f * RamdomScale, 109.f * RamdomScale });
	ParticleRenderer_->GetPixelData().MulColor.a = GameEngineRandom::MainRandom.RandomFloat(0.1f, 0.5f);

	Speed_ = GameEngineRandom::MainRandom.RandomFloat(300.f, 500.f);
	RotatinSpeed_ = GameEngineRandom::MainRandom.RandomFloat(-50.f, 50.f);


	MapMaxX_ = GetLevel<HollowKnightLevel>()->GetMapSize().x;

	float RamY = GameEngineRandom::MainRandom.RandomFloat(-GetLevel<HollowKnightLevel>()->GetMapSize().y, 0);
	GetTransform().SetLocalPosition({ -GameEngineWindow::GetInst()->GetScale().hx(), RamY , static_cast<float>(Z_ORDER::Background_Object)});
}

void MapSmoke::Update(float _DeltaTime)
{
	float4 Move = float4::RIGHT * Speed_ * _DeltaTime;

	GetTransform().SetLocalMove(Move);
	GetTransform().SetLocalRotate({0,0, RotatinSpeed_ * _DeltaTime });


	if(GetTransform().GetLocalPosition().x > MapMaxX_ + 300.f)
	{
		this->Death();
	}

}

