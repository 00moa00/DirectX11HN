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

	GameEngineStateManager SettingPointeManager_;
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


	void PointerIdleStart(const StateInfo& _Info);
	void PointerIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerIdleEnd(const StateInfo& _Info);

	void PointerMoveLeftStart(const StateInfo& _Info);
	void PointerMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMoveLeftEnd(const StateInfo& _Info);

	void PointerMoveRightStart(const StateInfo& _Info);
	void PointerMoveRightUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerMoveRightEnd(const StateInfo& _Info);

	void PointerInRightArrowStart(const StateInfo& _Info);
	void PointerInRightArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInRightArrowEnd(const StateInfo& _Info);

	void PointerInLeftArrowStart(const StateInfo& _Info);
	void PointerInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInLeftArrowEnd(const StateInfo& _Info);

};

