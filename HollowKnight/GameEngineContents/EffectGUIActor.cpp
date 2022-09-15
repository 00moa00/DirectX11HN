#include "PreCompile.h"

#include "EffectGUIActor.h"

EffectGUIActor::EffectGUIActor() 
{
}

EffectGUIActor::~EffectGUIActor() 
{
}

void EffectGUIActor::Start()
{
}

void EffectGUIActor::Update(float _DeltaTime)
{
}

void EffectGUIActor::LevelStartEvent()
{
	EffectGUI_ = GameEngineGUI::CreateGUIWindow<EffectGUI>("Effect", GetLevel());
}

void EffectGUIActor::LevelEndEvent()
{
	KnightData::GetInst()->SetOverlayflag(EffectGUI_->GetOverlayFlag());
	KnightData::GetInst()->SetOverlayColor(EffectGUI_->GetoverlayColor());

	KnightData::GetInst()->SetKnihgtMainLightMulColor(EffectGUI_->GetMainLightMulColor());
	KnightData::GetInst()->SetKnihgtMainLightPlusColor(EffectGUI_->GetMainLightPlusColor());

	KnightData::GetInst()->SetKnihgtSlibingLightMulColor(EffectGUI_->GetSlibingLightMulColor());
	KnightData::GetInst()->SetKnihgtSlibingLightPlusColor(EffectGUI_->GetSlibingLightPlusColor());

	KnightData::GetInst()->SetKnihgtDounutLightMulColor(EffectGUI_->GetDounutLightMulColor());
	KnightData::GetInst()->SetKnihgtDounutLightPlusColor(EffectGUI_->GetDounutLightPlusColor());

	EffectGUI_->EffectGUIDeath();
}