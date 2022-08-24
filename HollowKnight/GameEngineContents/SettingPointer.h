#pragma once
#include "MasterUI.h"
#include "SettingUIMaster.h"
#include "SettingPointerBox.h"

class PointActorComponent;
class SettingPointer : public MasterUI
{
public:
	// constrcuter destructer
	SettingPointer();
	~SettingPointer();

	// delete Function
	SettingPointer(const SettingPointer& _Other) = delete;
	SettingPointer(SettingPointer&& _Other) noexcept = delete;
	SettingPointer& operator=(const SettingPointer& _Other) = delete;
	SettingPointer& operator=(SettingPointer&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

	bool inRightArrow_;
	bool inLeftArrow_;

	// ���� �ε���
	int CurrentPosInCharmPage;
	int CurrentPosInMapPage;
	int CurrentPosInCMonsterPage;

	//�� �ε���
	int CharmPageActorCount;
	int MapPageActorCount;
	int MonsterPageActorCount;

	SettingPointerBox* SettingPointerBox_;

	PAGE_TYPE CurrentPage_;

	GameEngineStateManager SettingPointerCharmPageManager_;
	GameEngineStateManager SettingPointerManager_;

public:

	void AllOn();
	void AllOff();

	// ��� ������ ���͵��� �� ��������� ���� ����ؾ��ϴ� �ʼ� �Լ�

	//�ƽ� ī��Ʈ ����
	void SetCharmPageActorMax();
	void SetMapPageActorMax();
	void SetMonsterBookActorMax();

	//�������� ó�� ������ ���� ���� �־���ϴ� ������ ��ġ
	void SetFirstPosCharmPage();
	void SetFirstPosMapPage();
	void SetFirstPosMonsterBookPage();

	//================================
	//    Bind State
	//================================


	void PointerCharmPageIdleStart(const StateInfo& _Info);
	void PointerCharmPageIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageIdleEnd(const StateInfo& _Info);

	void PointerCharmPageMoveLeftStart(const StateInfo& _Info);
	void PointerCharmPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageMoveLeftEnd(const StateInfo& _Info);

	void PointerCharmPageMoveRightStart(const StateInfo& _Info);
	void PointerCharmPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageMoveRightEnd(const StateInfo& _Info);

	void PointerInCharmPageRightArrowStart(const StateInfo& _Info);
	void PointerInCharmPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInCharmPageRightArrowEnd(const StateInfo& _Info);

	void PointerCharmPageInLeftArrowStart(const StateInfo& _Info);
	void PointerCharmPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerCharmPageInLeftArrowEnd(const StateInfo& _Info);


};

