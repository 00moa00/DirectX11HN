#pragma once
#include "GlobalContentsValue.h"

// �����ؾ��ϴ� ������ :		HUD ����(����, ��ȥ), ����, �� �ر�, ������
//							�÷��̾� - ���� ����, ����� ����?

// ����� �������� �����Ǵ� Ŭ������ ������ �־��ְ� ������
// ���ʿ� ������ �������� �ʰ� ������ Ŭ�������� �����°� ȿ�����ϰŰ���.




struct KnightItemData
{
	bool isHas_;
	int ItemCount_;
	ITEM_LIST Item_;
};

struct KnightCharmData
{
	//bool isHas_;
	CHARM_SLOT Charm_;
};


class KnightData
{
private:
	static KnightData* Inst_;

public:
	static KnightData* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	// constrcuter destructer
	KnightData();
	~KnightData();

	// delete Function
	KnightData(const KnightData& _Other) = delete;
	KnightData(KnightData&& _Other) noexcept = delete;
	KnightData& operator=(const KnightData& _Other) = delete;
	KnightData& operator=(KnightData&& _Other) noexcept = delete;

private:
	//================================
	//    �����̵� ������
	//================================
	int AllMask_;			//���� ���� �� �ִ� �ִ� ����
	int CurMask_;			//���� ���� ����
	int CurSoul_;			//���� ��ȥ
	int CharmNotches_;		//������ ���� ĭ ��
	int UsingCharmNotches_; // ���� ������� ���� ĭ ��

	std::vector<KnightCharmData> CharmList_;
	std::vector<KnightItemData> ItemList_;

	bool isKnihgt_;			// �÷��̾ �ִ�. : �ʿ���°Ű��� �Ŀ� ����
	bool isHUD_;			// ��尡 �ִ�. ���� ù ���ۿ��� �ִϸ��̼��� ������ ����


	//================================
	//    �÷���
	//================================
	bool isRefill_;		//���� -> ȸ���ƴ�
	bool isNewMask_;	//���� -> ���� ���嶥
	bool isBreak_;		// ���� -> ������
	bool isDeath_;		//�׾���
	bool isShadow_;		// �׾��� �̹� �׸��ڰ� �ִ�
	bool isGrowSoul_;	// ���͸� ������ ��ȥ�� ����
	bool isSitting_;	// ���ڿ� �ɾ��ִ�.
	bool isSetting_;	//���� ������ ������
	bool isCameraGUI_;	//ī�޶� GUi�� �ִ�

	float4 KnightPosition_;


	//std::map<int, std::string> KnihgtItemList_;

public:

	//================================
	//    ������, ����
	//================================

	bool FindKnightItemList(ITEM_LIST _Item)
	{
		for (std::vector<KnightItemData>::iterator It = ItemList_.begin(); It != ItemList_.end(); ++It)
		{
			if (It->Item_ == _Item)
			{
				return true;
			}
		}

		return false;
	}

	bool FindKnightCharmList(CHARM_SLOT _Charm)
	{
		for (std::vector<KnightCharmData>::iterator It = CharmList_.begin(); It != CharmList_.end(); ++It)
		{
			if (It->Charm_ == _Charm)
			{
				return true;
			}
		}

		return false;
	}

	void PushKnihgtItemList(ITEM_LIST _Item)
	{
		KnightItemData ItemData;
		ItemData.Item_ = _Item;
		//ItemData.ItemCount_ ;

		ItemList_.push_back(ItemData);
	}

	void PushKnihgtCharList(CHARM_SLOT _Charm)
	{
		KnightCharmData CharmData;
		CharmData.Charm_ = _Charm;

		CharmList_.push_back(CharmData);
	}


	//================================
	//    Getter
	//================================
	bool GetisCameraGUI()
	{
		return isCameraGUI_;
	}

	int GetCurSoul()
	{
		return CurSoul_;
	}

	bool GetisHUD()
	{
		return isHUD_;
	}

	bool GetisKnight()
	{
		return isKnihgt_;
	}

	int GetUsingCharmNotches()
	{
		return UsingCharmNotches_;
	}

	bool GetisSetting()
	{
		return isSetting_;
	}

	bool GetisShadow()
	{
		return isShadow_;
	}

	bool GetisSitting()
	{
		return isSitting_;
	}

	int GetAllMask()
	{
		return AllMask_;
	}

	int GetCurMask()
	{
		return CurMask_;
	}

	bool GetisRefill()
	{
		return isRefill_;
	}

	bool GetisNewMask()
	{
		return isNewMask_;
	}

	bool GetisBreak()
	{
		return isBreak_;
	}

	bool GetisDeath()
	{
		return isDeath_;
	}

	bool GetisGrowSoul()
	{
		return isGrowSoul_;
	}

	int GetCharmNotches()
	{
		return CharmNotches_;
	}

	float4 GetKnightPosition()
	{
		return KnightPosition_;
	}


	//================================
	//    Setter
	//================================
	void SetisCameraGUI(bool _b)
	{
		isCameraGUI_ = _b;
	}

	void SetisHUD(bool _b)
	{
		isHUD_ = _b;
	}

	void SetisKnight(bool _b)
	{
		isKnihgt_ = _b;
	}

	//������ �����Ѵ�.
	bool SubUsingCharmNotches(int _i)
	{
		if (CharmNotches_ - UsingCharmNotches_ >= _i)
		{
			UsingCharmNotches_ += _i;
			return true;
		}

		return false;
	}

	// ������ �A��
	void AddUsingCharmNotches(int _i)
	{

		if (UsingCharmNotches_ >= 0)
		{
			UsingCharmNotches_ -= _i;

		}
	}

	void SetKnightPosition(float4 _Pos)
	{
		KnightPosition_ = _Pos;
	}


	void SetisSetting(bool _b)
	{
		isSetting_ = _b;
	}

	void SetisShadow(bool _b)
	{
		isShadow_ = _b;
	}

	void SetisSitting(bool _b)
	{
		isSitting_ = _b;
	}

	void SetAllMask(int _i)
	{
		AllMask_ = _i;
	}

	void SetCurMask(int _i)
	{
		CurMask_ = _i;
	}

	void SetisRefill(bool _b)
	{
		isRefill_ = _b;
	}

	void SetisNewMask(bool _b)
	{
		isNewMask_ = _b;
	}

	void SetisBreak(bool _b)
	{
		isBreak_ = _b;
	}

	void SetisDeath(bool _b)
	{
		isDeath_ = _b;
	}

	void SetisSoulGrow(bool _b)
	{
		isGrowSoul_ = _b;
	}

	void SetCurSoul(int _i)
	{
		CurSoul_ = _i;
	}

};

