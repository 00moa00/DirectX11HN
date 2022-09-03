#pragma once
#include "MasterPage.h"
#include "CharmSlot.h"
#include "Notches.h"
#include "ContentsFontRenderer.h"

#include <GameEngineCore/GameEngineFontRenderer.h>
// ���� : 0~39 : ����, 50, 51 : ������, 40~49 : ��������
class CharmPage : public MasterPage
{
public:
	// constrcuter destructer
	CharmPage();
	~CharmPage();

	// delete Function
	CharmPage(const CharmPage& _Other) = delete;
	CharmPage(CharmPage&& _Other) noexcept = delete;
	CharmPage& operator=(const CharmPage& _Other) = delete;
	CharmPage& operator=(CharmPage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<CharmSlot*> AllCharmSlot_;
	
	ContentsFontRenderer* NotchesFont_;
	ContentsFontRenderer* EquippedSlotFont_;
	GameEngineUIRenderer* Line_;

public:
	void AllOff() override;
	void AllOn() override ;

	void CreateEquippedCharm(GameEngineUIRenderer* _CopyRenderer);

};

