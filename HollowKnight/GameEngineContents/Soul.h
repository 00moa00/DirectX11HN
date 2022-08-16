#pragma once
#include "MasterUI.h"
// ���� :
class Soul : public MasterUI
{
public:
	// constrcuter destructer
	Soul();
	~Soul();

	// delete Function
	Soul(const Soul& _Other) = delete;
	Soul(Soul&& _Other) noexcept = delete;
	Soul& operator=(const Soul& _Other) = delete;
	Soul& operator=(Soul&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isGrowEnd_;
	bool isShrinkEnd_;

	int SoulLevel_; // ����Ʈ MAK 9 , �������� MAK 6

	GameEngineStateManager SoulManager_;
	GameEngineUIRenderer* EyeRenderer_;
public:
	//================================
	//     Getter
	//================================
	int GetSoulLevel()
	{
		return SoulLevel_;
	}

	//================================
	//     Setter
	//================================
	void GrowSoulLevel()
	{
		if (SoulLevel_ <= 9)
		{
			++SoulLevel_;
			SoulManager_.ChangeState("GROW");
		}
	}
	
	void SetSoulLevel(int _i)
	{
		SoulLevel_ = _i;
	}

	void SetGrowState()
	{
		SoulManager_.ChangeState("GROW");
	}

	void SetIdleState()
	{
		SoulManager_.ChangeState("IDLE");
	}

	void SetShrinkState()
	{
		SoulManager_.ChangeState("SHRINK");
	}

private:
	void SetLevelPosition(int _Level);

	//================================
	//    Bind State
	//================================
	void SoulGrowStart(const StateInfo& _Info);
	void SoulGrowUpdate(float _DeltaTime, const StateInfo& _Info);
	void SoulGrowEnd(const StateInfo& _Info);

	void SoulIdleStart(const StateInfo& _Info);
	void SoulIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void SoulIdleEnd(const StateInfo& _Info);

	void SoulShrinkStart(const StateInfo& _Info);
	void SoulShrinkUpdate(float _DeltaTime, const StateInfo& _Info);
	void SoulShrinkEnd(const StateInfo& _Info);
};

