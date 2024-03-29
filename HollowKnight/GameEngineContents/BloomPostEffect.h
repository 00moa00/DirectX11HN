#pragma once
#include <GameEngineCore/GameEngineRenderTarget.h>
#include <GameEngineCore/GameEngineRenderSet.h>

//struct BloomData
//{
//	float4 iMouse;
//	float4 iResolution;
//
//}

// 

class HollowKnightLevel;
class BloomPostEffect : public GameEnginePostEffect
{
public:
	// constrcuter destructer
	BloomPostEffect();
	~BloomPostEffect();

	// delete Function
	BloomPostEffect(const BloomPostEffect& _Other) = delete;
	BloomPostEffect(BloomPostEffect&& _Other) noexcept = delete;
	BloomPostEffect& operator=(const BloomPostEffect& _Other) = delete;
	BloomPostEffect& operator=(BloomPostEffect&& _Other) noexcept = delete;

public:
	virtual void EffectInit();
	virtual void Effect(GameEngineRenderTarget* _Target);


public:

	GameEngineRenderTarget* OriTex;

	GameEngineRenderTarget* CopyTargetWhiteCut;
	GameEngineRenderSet EffectSetWhiteCut;


	GameEngineRenderTarget* CopyTargetWhiteCutBlur;
	GameEngineRenderSet EffectSetWhiteCutBlur;


	GameEngineRenderTarget* CopyTargetBloom;
	GameEngineRenderSet EffectSetBloom;

	HollowKnightLevel* HollowKnightLevel_;

private:

public:
	HollowKnightLevel* GetHollowKnightLevel()
	{
		return HollowKnightLevel_;
	}

	void SetHollowKnightLevel(HollowKnightLevel* _level)
	{
		HollowKnightLevel_ = _level;
	}
};

