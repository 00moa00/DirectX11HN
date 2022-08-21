#pragma once
#include "SettingUIMaster.h"
#include "Charm.h"

// �ش� ���Կ� ���� ������ �ִ� ��������, �׸��� �����ϰ� �ִ� �������� ���¸� �� �� �־���Ѵ�
// ������ġ�� �����̴ϱ� �۷ι��������� �켱 ��[����

// ������ ���ʹ� �����̴�.

// ������ �̹� ������ ���� ������, ������ ������ ����.

struct CharmState 
{
public :
	int SlotNum_;		//���� ��ȣ
	int SlotCount_;		//���� ��� ����ϰ� �ִ���
	bool KnihgistHas_;	//����Ʈ�� ������ �ִ���
	bool isUsing_;		//��� �ϰ� �ִ���
};

// ���� :
class CharmSlot : public SettingUIMaster
{
public:
	// constrcuter destructer
	CharmSlot();
	~CharmSlot();

	// delete Function
	CharmSlot(const CharmSlot& _Other) = delete;
	CharmSlot(CharmSlot&& _Other) noexcept = delete;
	CharmSlot& operator=(const CharmSlot& _Other) = delete;
	CharmSlot& operator=(CharmSlot&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Deltatime) override;

private:

	Charm* Charm_;
	CharmState CharmState_;

public:

	void CreateCharmSlot(std::string _SlotName, std::string _CharmFilePath, CharmState _CharmState, CHARM_SLOT _slot);

	int GetSlotNum()
	{
		return CharmState_.SlotNum_;
	}

	int GetSlotCount()
	{
		return CharmState_.SlotCount_;
	}

	bool GetKnightHas()
	{
		return CharmState_.KnihgistHas_;
	}

	bool GetisUsing()
	{
		return CharmState_.isUsing_;
	}

	CharmState& GetCharmState()
	{
		return CharmState_;
	}
	

};

