#pragma once
#include "Monster.h"
#include "GrimmBeam.h"
#include "GrimmSpotLight.h"

#include "BossRoomGate.h"

//�� ��������Ʈ ��Ʈ���� ������ ũ�Ⱑ �ٸ��� �ִϸ��̼� �����Ҷ��� ScaleToCutTexture �Ұ�.


enum class EventState
{
	Wait,
	Appear,
	Battle,
	Talking,
	MAX
};


class Grimm : public Monster
{
public:
	// constrcuter destructer
	Grimm();
	~Grimm();

	// delete Function
	Grimm(const Grimm& _Other) = delete;
	Grimm(Grimm&& _Other) noexcept = delete;
	Grimm& operator=(const Grimm& _Other) = delete;
	Grimm& operator=(Grimm&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void SetMonsterHit(int _Damage, float4 _StunDir) override;


private:
	bool isTeleportAppearEnd_;
	bool isTeleportDiappearEnd_;
	bool isPillarEnd_;
	bool isBowEnd_;
	bool isRoarEnd_;

	//bool isTeleportEnd_;

	GrimmBeam* GrimmBeam_;
	GrimmSpotLight* GrimmSpotLight_;
	BossRoomGate* BossRoomGate_;

	EventState EventState_;

	GameEngineStateManager GrimmAppearManager_;
	GameEngineStateManager GrimmManager_;

public:
	void SetEventState(EventState _State)
	{
		EventState_ = _State;
	}

private:
	//================================
	//    Bind State | Appear
	//================================


	void GrimmAppearWaitStart(const StateInfo& _Info);
	void GrimmAppearWaitUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearWaitEnd(const StateInfo& _Info);


	void GrimmAppearTeleportStart(const StateInfo& _Info);
	void GrimmAppearTeleportUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearTeleportEnd(const StateInfo& _Info);

	void GrimmAppearIdle1Start(const StateInfo& _Info);
	void GrimmAppearIdle1Update(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearIdle1End(const StateInfo& _Info);

	void GrimmAppearPillarStart(const StateInfo& _Info);
	void GrimmAppearPillarUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearPillarEnd(const StateInfo& _Info);

	void GrimmAppearPillarLoopStart(const StateInfo& _Info);
	void GrimmAppearPillarLoopUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearPillarLoopEnd(const StateInfo& _Info);
	
	void GrimmAppearIdle2Start(const StateInfo& _Info);
	void GrimmAppearIdle2Update(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearIdle2End(const StateInfo& _Info);

	void GrimmAppearChangeMapStart(const StateInfo& _Info);
	void GrimmAppearChangeMapUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearChangeMapEnd(const StateInfo& _Info);

	void GrimmAppearBowStart(const StateInfo& _Info);
	void GrimmAppearBowUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearBowEnd(const StateInfo& _Info);

	void GrimmAppearRoarStart(const StateInfo& _Info);
	void GrimmAppearRoarUpdate(float _DeltaTime, const StateInfo& _Info);
	void GrimmAppearRoarEnd(const StateInfo& _Info);

	//================================
	//    Bind 
	//================================



};

