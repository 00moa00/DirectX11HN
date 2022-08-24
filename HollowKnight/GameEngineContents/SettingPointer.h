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

	bool isDownNextPageRight_;
	bool isDownLextPageLeft_;

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

	PAGE_TYPE CurrentPage_; //���� ������
	PAGE_TYPE PrevPage_; // ������ �����

	GameEngineStateManager SettingPointerCharmPageManager_;
	GameEngineStateManager SettingPointerInventoyPageManager_;

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

	//=========================================
	//    SettingPointerCharmPageManager
	//=========================================
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


	//=========================================
	//    SettingPointerInventoyPageManager
	//=========================================
	void PointerInventoryPageIdleStart(const StateInfo& _Info);
	void PointerInventoryPageIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageIdleEnd(const StateInfo& _Info);

	void PointerInventoryPageMoveLeftStart(const StateInfo& _Info);
	void PointerInventoryPageMoveLeftUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageMoveLeftEnd(const StateInfo& _Info);

	void PointerInventoryPageMoveRightStart(const StateInfo& _Info);
	void PointerInventoryPageMoveRightUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageMoveRightEnd(const StateInfo& _Info);

	void PointerInInventoryPageRightArrowStart(const StateInfo& _Info);
	void PointerInInventoryPageRightArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInInventoryPageRightArrowEnd(const StateInfo& _Info);

	void PointerInventoryPageInLeftArrowStart(const StateInfo& _Info);
	void PointerInventoryPageInLeftArrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void PointerInventoryPageInLeftArrowEnd(const StateInfo& _Info);


public:
	//================================
	//    Getter
	//================================
	bool GetisDownNextpageRight()
	{
		return isDownNextPageRight_;
	}

	bool GetisDownLextPageLeft()
	{
		return isDownLextPageLeft_;
	}


	//================================
	//    Setter
	//================================

	void SetCurrentPage(PAGE_TYPE _PageType)
	{
		CurrentPage_ = _PageType;
	}
};

