#pragma once
#include "MasterActor.h"
#include "KnightSlashEffect.h"

// ���� :
class GameEngineTextureRenderer;
class Knight : public MasterActor
{
public:
	// constrcuter destructer
	Knight();
	~Knight();

	// delete Function
	Knight(const Knight& _Other) = delete;
	Knight(Knight&& _Other) noexcept = delete;
	Knight& operator=(const Knight& _Other) = delete;
	Knight& operator=(Knight&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void End() override {}

private:

	bool isSlashEnd_;		// ���� �ִϸ��̼� ����
	bool isDoubleSlashEnd_; // ���� ���� �ִϸ��̼� ����
	bool isUpSlashEnd_;
	bool isDownSlashEnd_;
	bool isDoubleJumpEnd_;
	bool isWalkTurnEnd_;
	bool isMapWalkTurnEnd_;
	bool isFocusEnd_;
	bool isLandEnd_;
	bool isStunEnd_;
	bool isDeathEnd_;
	bool isGroundWakeUp_;
	bool isWakeUp_;

	bool isKnightActtingMove_;
	bool isPressJumppingKey_;
	bool isPossibleDoubleSlash_;
	bool isPossibleDoubleJump_;

	bool isLookMap_;
	bool isRunMode_;
	bool isLowHealth_;

	bool isDeath_;

	float KnightJumpPower_;
	float KnightDoubleJumpPower_;

	float KnightSlashTimer_; // ���� ���� üũ Ÿ�̸�
	float KnightLookUpTimer_;
	float KnightLookDownTimer_;
	float KnightDashTimer_; // �뽬 Ÿ�̸�
	float KnightKnockbackTimer_; // �˹� Ÿ�̸�

	float4 ActtingMoveDirection_; //�ٸ� �ൿ���� �� ������ �ٲ�� �ӽ÷� �ִ� �뵵
	float4 PrevDirection_;

	float4 KnockbackDirection_;

	GameEngineStateManager KnightManager_;
	KnightSlashEffect* KnightSlashEffect_;

	GameEngineCollision* Test1_;
	GameEngineCollision* Test2_;

public:



private:

	bool GetisKnightMove();
	void KnightDirectionCheck();

	void isKnihgtActtingMoveChack();
	void KnightActtingDirectionCheck();
	void KnightIsActtingCheck();


	void KnihgtSlideNegativeRenderer(); //��Ÿ�� ���� ������ ������
	void KnihgtSlidePositiveRenderer(); //��Ÿ�� ���� ������ ������


	void DoubleSlashTimer(float _DeltaTime); //���� ����(�޺�) Ÿ�̸�

	void LookUpTimerAndChangeState(float _DeltaTime);
	void LookDownTimerAndChangeState(float _DeltaTime);

	//================================
	//    State
	//================================

	void Walkking(float _DeltaTime);

	//================================
	//    Bind State
	//================================

	// ---- �⺻ ----
	void KnightStillStart( const StateInfo& _Info);
	void KnightStillUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightWalkStart(const StateInfo& _Info);
	void KnightWalkUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightWalkTurnStart(const StateInfo& _Info);
	void KnightWalkTurnUpdate(float _DeltaTime, const StateInfo& _Info);

	void KnightLookDownStart(const StateInfo& _Info);
	void KnightLookDownUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightLookDownEnd(const StateInfo& _Info);

	void KnightLookUpStart(const StateInfo& _Info);
	void KnightLookUpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightLookUpEnd(const StateInfo& _Info);

	void KnightJumpStart(const StateInfo& _Info);
	void KnightJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightJumpEnd(const StateInfo& _Info);

	void KnightDoubleJumpStart(const StateInfo& _Info);
	void KnightDoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDoubleJumpEnd(const StateInfo& _Info);

	void KnightLandStart(const StateInfo& _Info);
	void KnightLandUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightLandEnd(const StateInfo& _Info);

	void KnightFallStart(const StateInfo& _Info);
	void KnightFallUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightFallEnd(const StateInfo& _Info);

	void KnightDashStart(const StateInfo& _Info);
	void KnightDashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDashEnd(const StateInfo& _Info);

	void KnightFocusStart(const StateInfo& _Info);
	void KnightFocusUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightFocusEnd(const StateInfo& _Info);

	// ---- �޸��� ----
	void KnightRunStart(const StateInfo& _Info);
	void KnightRunUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightRunEnd(const StateInfo& _Info);

	// ---- ���� ----
	void KnightStunStart(const StateInfo& _Info);
	void KnightStunUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightStunEnd(const StateInfo& _Info);

	// ---- ��� ----
	void KnightDeathStart(const StateInfo& _Info);
	void KnightDeathUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDeathEnd(const StateInfo& _Info);

	// ---- ������ ��� ----
	void KnightWakeUpGroundStart(const StateInfo& _Info);
	void KnightWakeUpGroundUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightWakeUpGroundEnd(const StateInfo& _Info);

	// ---- ��� ----
	void KnightWakeUpStart(const StateInfo& _Info);
	void KnightWakeUpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightWakeUpEnd(const StateInfo& _Info);

	// ---- ���� ----
	void KnightSlashStart(const StateInfo& _Info);
	void KnightSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightSlashEnd(const StateInfo& _Info);

	void KnightDoubleSlashStart(const StateInfo& _Info);
	void KnightDoubleSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDoubleSlashEnd(const StateInfo& _Info);

	void KnightUpSlashStart(const StateInfo& _Info);
	void KnightUpSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightUpSlashEnd(const StateInfo& _Info);

	void KnightDownSlashStart(const StateInfo& _Info);
	void KnightDownSlashUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDownSlashEnd(const StateInfo& _Info);


	// ---- ���� ���� ----
	void KnightMapStillStart(const StateInfo& _Info);
	void KnightMapStillUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapStillEnd(const StateInfo& _Info);

	void KnightMapWalkinglStart(const StateInfo& _Info);
	void KnightMapWalkinglUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapWalkinglEnd(const StateInfo& _Info);

	void KnightMapWalkingTurnlStart(const StateInfo& _Info);
	void KnightMapWalkingTurnlUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapWalkingTurnlEnd(const StateInfo& _Info);

	void KnightMapSitLooklStart(const StateInfo& _Info);
	void KnightMapSitLooklUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapSitLooklEnd(const StateInfo& _Info);

	void KnightMapSitWritelStart(const StateInfo& _Info);
	void KnightMapSitWritelUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightMapSitWritelEnd(const StateInfo& _Info);


	// ---- �����̵� ----
	void KnightSlideStart(const StateInfo& _Info);
	void KnightSlideUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightSlideEnd(const StateInfo& _Info);

	void KnightWallJumpStart(const StateInfo& _Info);
	void KnightWallJumpUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightWallJumpEnd(const StateInfo& _Info);


	void KnightWallJumpLandStart(const StateInfo& _Info);
	void KnightWallJumpLandUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightWallJumpLandEnd(const StateInfo& _Info);



	//================================
	//    Bind 
	//================================


	bool KnightVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


}; 

