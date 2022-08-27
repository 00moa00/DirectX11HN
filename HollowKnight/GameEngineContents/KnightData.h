#pragma once

//struct KnihgtHasItem
//{
//	int ItemSlotNum_;
//	std::string _Name;
//};
//
//


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
	int AllMask_;
	int CurMask_;
	int CharmNotches_; //������ ���� ĭ ��
	int UsingCharmNotches_; // ���� ������� ���� ĭ ��

	bool isRefill_;
	bool isNewMask_;
	bool isBreak_;

	bool isDeath_;

	bool isShadow_;

	bool isGrowSoul_; // ���͸� ������ ��ȥ�� ����]

	bool isSitting_; // ���ڿ� �ɾ��ִ�.

	bool isSetting_; //���� ������ ������

	std::map<int, std::string> KnihgtItemList_;

public:

	//================================
	//    Getter
	//================================

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

	//================================
	//    Setter
	//================================

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
		UsingCharmNotches_ -= _i;
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

};

