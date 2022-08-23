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
	int SlotCount_;		//���� ��� �ʿ�����
	bool KnihgistHas_;	//����Ʈ�� ������ �ִ���
	bool isUsing_;		//��� �ϰ� �ִ���
	bool isEquipped_; //���� ��������
	bool isEquippedUsing_; //���� ���� ���������
	std::string CharmFilePath_; // ���� �н�
	std::string CharmName_;
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
	void CreateEquippedCharmSlot(CharmState _CharmState);
	void CreateCopyCharm(GameEngineUIRenderer* _RenderData, std::string _SlotName, std::string _FilePath);


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

	bool GetisEquipped()
	{
		return CharmState_.isEquipped_;
	}
	bool GetisEquippedUsing()
	{
		return  CharmState_.isEquippedUsing_;
	}


	CharmState& GetCharmState()
	{
		return CharmState_;
	}

	std::string& GetFilePath()
	{
		return CharmState_.CharmFilePath_;
	}

	std::string& GetCharmName()
	{
		return CharmState_.CharmName_;
	}

	void SetCharmisHas(bool _b)
	{
		CharmState_.KnihgistHas_ = _b;
		
		if (CharmState_.KnihgistHas_ == true)
		{
			Charm_->GetRenderer()->On();
			this->GetRenderer()->Off();
		}

		else
		{
			Charm_->GetRenderer()->Off();
			this->GetRenderer()->On();
		}
	}

	void SetisEquippedUsing(bool _b)
	{
		CharmState_.isEquippedUsing_ = _b;
	}
	

	void SetisUsing(bool _b)
	{
		CharmState_.isUsing_ = _b;
	}
	

};

