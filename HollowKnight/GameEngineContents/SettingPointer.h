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
	// ���� �ε���
	int CurrentPosInCharmPage;
	int CurrentPosInMapPage;
	int CurrentPosInCMonsterPage;

	//�� �ε���
	int CharmPageActorCount;
	int MapPageActorCount;
	int MonsterPageActorCount;

	SettingPointerBox* SettingPointerBox_;

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


};

