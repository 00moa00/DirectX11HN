#pragma once
#include "MasterNPC.h"
#include "Shop.h"

// ��ȭ -> prompt
// ���� - > npc

class Iselda : public MasterNPC
{
public:
	// constrcuter destructer
	Iselda();
	~Iselda();

	// delete Function
	Iselda(const Iselda& _Other) = delete;
	Iselda(Iselda&& _Other) noexcept = delete;
	Iselda& operator=(const Iselda& _Other) = delete;
	Iselda& operator=(Iselda&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void CheckDirToKnight() override;
	void StartTalking() override;

public:
	void SetisShop(bool b) override
	{
		if (b == true)
		{
			OpenShop_ = true;
			MapShop_->On();
			MapShop_->SetShopPopup();
			GameEngineSound::SoundPlayOneShot("Iselda_Shop_Open.ogg");
			IseldaManager_.ChangeState("OPEN_SHOP");
		}

		else if (b == false)
		{
			OpenShop_ = false;

			MapShop_->SetShopPopDown();
			GetRenderer()->ChangeFrameAnimation("SHOP_TO_IDLE_ANIMATION");

			//IseldaManager_.ChangeState("IDLE");
		}
	}

private:
	bool ShopToIdleEnd_;
	bool OpenShop_;

	int ShopIndexCount_;
	
	float4 PrevDir_;

	Shop* MapShop_;

	GameEngineStateManager IseldaManager_;

private:
	bool ThisVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


	//================================
	//    Bind State
	//================================
	void IseldaWaitStart(const StateInfo& _Info);
	void IseldaWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void IseldaWaitEnd(const StateInfo& _Info);

	void IseldaIdleStart(const StateInfo& _Info);
	void IseldaIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void IseldaIdleEnd(const StateInfo& _Info);

	void IseldaChangeDirStart(const StateInfo& _Info);
	void IseldaChangeDirUpdate(float _DeltaTime, const StateInfo& _Info);
	void IseldaChangeDirEnd(const StateInfo& _Info);


	void IseldaShopOpenStart(const StateInfo& _Info);
	void IseldaShopOpenUpdate(float _DeltaTime, const StateInfo& _Info);
	void IseldaShopOpenEnd(const StateInfo& _Info);

	void IseldaTalkingStart(const StateInfo& _Info);
	void IseldaTalkingUpdate(float _DeltaTime, const StateInfo& _Info);
	void IseldaTalkingEnd(const StateInfo& _Info);


};

