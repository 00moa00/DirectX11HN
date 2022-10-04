#pragma once
#include "GlobalContentsValue.h"

#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/magic_enum_format.hpp>
#include <GameEngineBase/magic_enum_fuse.hpp>
// �����ؾ��ϴ� ������ :		HUD ����(����, ��ȥ), ����, �� �ر�, ������
//							�÷��̾� - ���� ����, ����� ����?

// ����� �������� �����Ǵ� Ŭ������ ������ �־��ְ� ������
// ���ʿ� ������ �������� �ʰ� ������ Ŭ�������� �����°� ȿ�����ϰŰ���.

enum class LevelList
{
	KingsPassLevel1,
	KingsPassLevel2,
	KingsPassLevel3,
	KingsPassLevel4,

	CrossroadsLevel1,
	CrossroadsLevel2,
	CrossroadsLevel3,
	CrossroadsLevel4,
	CrossroadsLevel5,
	CrossroadsLevel6,
	CrossroadsLevel7,

	DirtmouthLevel1,
	DirtmouthLevel2,
	DirtmouthLevel3,

	GrimmDirtmouthLevel1,
	GrimmDirtmouthLevel2,
	GrimmDirtmouthLevel3,

	GrimmmLevel,


	SlyShopLevel,
	MapShopLevel,

	DirtmouthStationLevel,

	KingsPassGrimmOpenLevel

};

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
	int AllMask_;							//���� ���� �� �ִ� �ִ� ����
	int CurMask_;							//���� ���� ����
	int CurSoul_;							//���� ��ȥ
	int CharmNotches_;						//������ ���� ĭ ��
	int UsingCharmNotches_;					// ���� ������� ���� ĭ ��

	int HitDamage_;							// ���� ������

	int MaskPieceCount_;					// ���� ���� ����

	std::vector<KnightCharmData> CharmList_;
	std::vector<KnightItemData> ItemList_;

	bool isKnihgt_;							// �÷��̾ �ִ�. : �ʿ���°Ű��� �Ŀ� ����
	bool isHUD_;							// ��尡 �ִ�. ���� ù ���ۿ��� �ִϸ��̼��� ������ ����

	float MaxSkew;							// unit is degrees angle.
	float MaxSway;							// unit is pixels in screen space.
	float SeedShiftingFactor;

	bool isOverlayflag_;					//�������� �÷���
	bool SavedPaletteInit_;					//�ȷ�Ʈ...�ε� ��� �����

	float4 OverlayColor_;					//�������� �÷�

	float4 MainLightMulColor_;				//���� ����Ʈ �÷�
	float4 MainLightPlusColor_;				//���� ����Ʈ �÷��� �÷�

	float4 SlibingLightMulColor_;
	float4 SlibingLightPlusColor_;

	float4 DounutLightMulColor_;
	float4 DounutLightPlusColor_;

	BlendMode MainLighBlend_;
	BlendMode SlibingLighBlend_;
	BlendMode DounutLighBlend_;

	std::string PrevLevel_;
	std::string CurrentLevel_;
	std::vector<std::string> AllLevelNameList_;

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
	bool isEffectGUI_;
	bool isRevive_;		//�÷��̾ �ٽ� �¾��		: ����ÿ� �����
	bool isBossBattle_;
	bool isIntroFallEvent_;
	bool isUseSoul_;
	bool isDeathLevelChange_;

	bool isGrimmOpen_;

	bool isAddNewMask_;	// ���� �رݵƴ�.

	float4 KnightPosition_;
	//float4 CurDir_;


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

	std::vector<KnightItemData> GetKnightItemData()
	{
		return ItemList_;
	}
	bool GetisAddNewMask() const
	{
		return isAddNewMask_;
	}

	int GetMaskPieceCount() const
	{
		return MaskPieceCount_;
	}

	bool GetisGrimmOpen() const
	{
		return isGrimmOpen_;
	}

	bool GetisDeathLevelChange() const
	{
		return isDeathLevelChange_;
	}

	bool GetisisUseSoul() const
	{
		return isUseSoul_;
	}

	bool GetisIntroFallEvent()
	{
		return isIntroFallEvent_;
	}

	bool GetisBossBattle() const
	{
		return isBossBattle_;
	}

	int GetHitDamage() const
	{
		return HitDamage_;
	}

	std::string& GetPreLevel()
	{
		return PrevLevel_;
	}

	std::string& GetCurrentLevel()
	{
		return CurrentLevel_;
	}

	BlendMode GetMainLightBlend()
	{
		return MainLighBlend_;
	}

	BlendMode GetSlibingLightBlend()
	{
		return SlibingLighBlend_;
	}

	BlendMode GetDounutLightBlend()
	{
		return DounutLighBlend_;
	}


	float4 GetKnihgtMainLightMulColor()
	{
		return MainLightMulColor_;
	}

	float4 GetKnihgtMainLightPlusColor()
	{
		return MainLightPlusColor_;
	}

	float4 GetKnihgtSlibingLightMulColor()
	{
		return SlibingLightMulColor_;
	}

	float4 GetKnihgtSlibingLightPlusColor()
	{
		return SlibingLightPlusColor_;
	}

	float4 GetKnihgtDounutLightMulColor()
	{
		return DounutLightMulColor_;
	}

	float4 GetKnihgtDounutLightPlusColor()
	{
		return DounutLightPlusColor_;
	}

	bool GetSavedPaletteInit()
	{
		return SavedPaletteInit_;
	}

	bool GetOverlayFlag()const
	{
		return isOverlayflag_;
	}

	float4 GetOverlayColor()
	{
		return OverlayColor_;
	}

	float GetMaxSkew() const
	{
		return MaxSkew;
	}


	float GetMaxSway() const
	{
		return MaxSway;
	}


	float GetSeedshiftingFactor() const
	{
		return SeedShiftingFactor;
	}


	bool GetisEffectGUI()
	{
		return isEffectGUI_;
	}

	bool GetisRevive()
	{
		return isRevive_;
	}


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
	void AddMaskPieceCount()
	{
		++MaskPieceCount_;
		if (MaskPieceCount_ > 4)
		{
			MaskPieceCount_ = 0;
		}
	}

	void SetisAddNewMask(bool _b)
	{
		isAddNewMask_ = _b;
	}

	void SetMaskPieceCount(int _i)
	{
		MaskPieceCount_ = _i;
	}

	void SetisGrimmOpen(bool _b)
	{
		isGrimmOpen_ = _b;
	}

	void SetisDeathLevelChange(bool _b)
	{
		isDeathLevelChange_ = _b;
	}

	void SetisUseSoul(bool _b)
	{
		isUseSoul_ = _b;
	}

	void SetisIntroFallEvent(bool _b)
	{
		isIntroFallEvent_ = _b;
	}

	void SetisBossBattle(bool _b)
	{
		isBossBattle_ = _b;
	}

	void SetHitDamage(int _i)
	{
		HitDamage_ = _i;
	}


	void PushLevelNameList(std::string _Name)
	{
		AllLevelNameList_.push_back(_Name);
	}


	void SetCurrentLevel(std::string _Level)
	{
		PrevLevel_ = CurrentLevel_;

		std::string UpperName = GameEngineString::ToUpperReturn(_Level);

		CurrentLevel_ = UpperName;
	}

	void SetMainLightBlend(BlendMode _Mode)
	{
		MainLighBlend_ = _Mode;
	}

	void SetSlibingLightBlend(BlendMode _Mode)
	{
		SlibingLighBlend_ = _Mode;
	}

	void SetDounutLightBlend(BlendMode _Mode)
	{
		DounutLighBlend_ = _Mode;
	}

	void SetKnihgtMainLightMulColor(float4 _f4)
	{
		MainLightMulColor_ = _f4;
	}

	void SetKnihgtMainLightPlusColor(float4 _f4)
	{
		MainLightPlusColor_ = _f4;
	}

	void SetKnihgtSlibingLightMulColor(float4 _f4)
	{
		SlibingLightMulColor_ = _f4;
	}

	void SetKnihgtSlibingLightPlusColor(float4 _f4)
	{
		SlibingLightPlusColor_ = _f4;
	}

	void SetKnihgtDounutLightMulColor(float4 _f4)
	{
		DounutLightMulColor_ = _f4;
	}

	void SetKnihgtDounutLightPlusColor(float4 _f4)
	{
		DounutLightPlusColor_ = _f4;
	}


	void SetSavedPaletteInit(bool _b)
	{
		SlibingLightMulColor_ = _b;
	}

	void SetOverlayflag(bool _b)
	{
		isOverlayflag_ = _b;
	}

	void SetOverlayColor(float4 _f)
	{
		OverlayColor_ = _f;
	}


	void SetMaxSkew(float _f)
	{
		MaxSkew = _f;
	}


	void SetMaxSway(float _f)
	{
		MaxSway = _f;
	}


	void SetSeedshiftingFactor(float _f) 
	{
		SeedShiftingFactor = _f;
	}



	void SetisRevive(bool _b)
	{
		isRevive_ = _b;
	}

	void SetisEffectGUI(bool _b)
	{
		isEffectGUI_ = _b;
	}

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

	void SetAddAllMask()
	{
		++AllMask_;
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

