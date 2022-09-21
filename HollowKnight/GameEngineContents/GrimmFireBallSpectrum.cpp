#include "PreCompile.h"
#include "GrimmFireBallSpectrum.h"
#include <GameEngineBase/GameEngineRandom.h>

GrimmFireBallSpectrum::GrimmFireBallSpectrum() 
{
}

GrimmFireBallSpectrum::~GrimmFireBallSpectrum() 
{
}

void GrimmFireBallSpectrum::Start()
{
	int index = GameEngineRandom::MainRandom.RandomInt(0, 4);

	CreateRendererComponent("grimm_smoke.png");
	GetRenderer()->SetTexture("grimm_smoke.png", index);

	SetBlendMode(BlendMode::Add);

	GetRenderer()->ScaleToCutTexture(index);
	Alpha_ = 1.0f;
}

void GrimmFireBallSpectrum::Update(float _DeltaTime)
{

	GetRenderer()->GetPixelData().MulColor.a = Alpha_;
	Alpha_ -= 0.3f * _DeltaTime;

	if (Alpha_ <= 0.f)
	{

		Alpha_ = 0.0f;
		//return;
	}

	else
	{
		static float timer = 0; // 0 - 4(sec)
		timer += _DeltaTime;

		float a = GameEngineRandom::MainRandom.RandomFloat(0, 10.0f); // angle(degree)
		float r = GameEngineRandom::MainRandom.RandomFloat(0, 5.f); // angle(degree)

		GetTransform().SetLocalPosition({ cosf(a * 0.01745f) * r, sinf(a * 0.01745f) * r });
		//GetRenderer()->GetPixelData().MulColor.a = fabsf(sinf(3.141592f * timer * 0.5f * 0.5f));
	}

}

