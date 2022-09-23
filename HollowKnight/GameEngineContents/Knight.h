#pragma once
#include "MasterActor.h"
#include "KnightSlashEffect.h"
#include "KnightMainLightEffect.h"
#include "KnightDonutLightEffect.h"
#include "KnightSiblingLightEffect.h"
#include "SideDarkEffect.h"
#include "ContentsFontRenderer.h"
#include "KnightStunEffect.h"
#include "LowHealth.h"

#include "KnightFocusEffect.h"

// ���� :
// ����Ʈ ���� : ���� - ����Ʈ�� �¿���
//				����Ʈ - ��� ����ٴ�
//				���� - �������� ����� ����

//				* ����Ʈ�� ��ü �����ɷ� ����

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
	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:
	ContentsFontRenderer* ContentsFontRenderer_;

	bool isKnightPotal_;	// ��Ż�ϰ� ��Ҵ�
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
	bool isGroundWakeUpEnd_;
	bool isWakeUpEnd_;
	bool isSitEnd_;
	bool isDoorEnd_;
	bool isReturnToIdle_;

	bool isRunTurnEnd_;

	bool isTalkingNPC_;

	bool isKnightActtingMove_;
	bool isPressJumppingKey_;
	bool isPossibleDoubleSlash_;
	bool isPossibleDoubleJump_;

	bool isLookMap_;
	bool isRunMode_;

	bool isDeath_;

	bool isInvincibility_;
	bool isKnightBlack_;

	bool isLowHealth_;					//Ż��

	bool isKnihgtStillWall_;

	float KnightJumpPower_;
	float KnightDoubleJumpPower_;
	float KnightRunSpeed_;
	float KnightActtingMoveDirPower_;
	float KnightFallAccel_;
	float JumpAccel_;

	float KnightSlashCollisionTimer_;
	float KnightSlashTimer_;			// ���� ���� üũ Ÿ�̸�
	float KnightLookUpTimer_;
	float KnightLookDownTimer_;
	float KnightDashTimer_;				// �뽬 Ÿ�̸�
	float KnightKnockbackTimer_;		// �˹� Ÿ�̸�
	float KnihgtInvincibilityTimer_;	// ���� ���� �ð�
	float KnihgtInvincibilitingTimer_;	// ���� ���� �ð�
	float KnihgtFocusTimer_;

	float4 ActtingMoveDirection_;	//�ٸ� �ൿ���� �� ������ �ٲ�� �ӽ÷� �ִ� �뵵

	float4 KnockbackDirection_;

	GameEngineStateManager KnightManager_;

	KnightSlashEffect* KnightSlashEffect_;

	KnightMainLightEffect* KnightMainLightEffect_;
	KnightDonutLightEffect* KnightDonutLightEffect_;
	KnightSiblingLightEffect* KnightSiblingLightEffect_;

	SideDarkEffect* SideDarkEffect_;

	KnightStunEffect* KnightStunEffect_;

	KnightFocusEffect* KnightFocusEffect_;			//���� ����Ʈ ������ �����


	GameEngineCollision* Test1_;
	GameEngineCollision* Test2_;

	std::string ChangeLevel_;


public:

	void SetDirInit(float4 _Dir);					// ���� ���ö� �ؽ�ó ����
	void SetKnightisPotal(bool _b);

private:


	bool GetisKnightMove();
	void KnightDirectionCheck();

	void isKnihgtActtingMoveChack();
	void KnightActtingDirectionCheck();
	void KnightIsActtingCheck();


	void KnihgtSlideNegativeRenderer(); //��Ÿ�� ���� ������ ������
	void KnihgtSlidePositiveRenderer(); //��Ÿ�� ���� ������ ������

	void KnightInvincibiliting(float _DeltaTime);


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

	void KnightRunStart(const StateInfo& _Info);
	void KnightRunUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightRunEnd(const StateInfo& _Info);

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

	// ---- ���� ���� ----
	void KnightFocusBurstStart(const StateInfo& _Info);
	void KnightFocusBurstUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightFocusBurstEnd(const StateInfo& _Info);


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

	// ---- ���� �� ----
	void KnightSitStart(const StateInfo& _Info);
	void KnightSitUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightSitEnd(const StateInfo& _Info);

	// ---- NPC ��ȭ ----
	void KnightTalkingStart(const StateInfo& _Info);
	void KnightTalkingUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightTalkingEnd(const StateInfo& _Info);

	void KnightShoppingStart(const StateInfo& _Info);
	void KnightShoppingUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightShoppingEnd(const StateInfo& _Info);

	// ---- ���� ----
	void KnightDoorStart(const StateInfo& _Info);
	void KnightDoorUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightDoorEnd(const StateInfo& _Info);


	// ----  Ÿ�� ���� ----
	void KnightTabletStart(const StateInfo& _Info);
	void KnightTabletUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightTabletEnd(const StateInfo& _Info);

	// ----  Ÿ������ ���� ���� ----

	void KnightTabletReturnToIdleStart(const StateInfo& _Info);
	void KnightTabletReturnToIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void KnightTabletReturnToIdleEnd(const StateInfo& _Info);


	 
	//================================
	//    Bind 
	//================================
	bool KnightVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool KnightVSMonsterAttackCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


	bool KnihgtVSBenchCollision(GameEngineCollision* _This, GameEngineCollision* _Other);
	bool KnihgtVSTabletCollision(GameEngineCollision* _This, GameEngineCollision* _Other);


	bool KnihgtVSNPCCollision(GameEngineCollision* _This, GameEngineCollision* _Other);		//NPC
	bool NPCNextDialogueCollision(GameEngineCollision* _This, GameEngineCollision* _Other); //NPC : ��ȭ�� ����, ��ȭ ����
	bool ShopCloseCollision(GameEngineCollision* _This, GameEngineCollision* _Other);		// ���� �ݱ� ��

	bool KnightVSPotalCollision(GameEngineCollision* _This, GameEngineCollision* _Other);	//��Ż

	bool KnightVSWallCollision(GameEngineCollision* _This, GameEngineCollision* _Other);	//��

	//================================
	//   Getter
	//================================

	KnightMainLightEffect* GetKnightMainLightEffect() const
	{
		return KnightMainLightEffect_;

	}

	KnightDonutLightEffect* GetKnightDonutLightEffect() const
	{
		return KnightDonutLightEffect_;
	}

	KnightSiblingLightEffect* GetKnightSiblingLightEffect() const
	{
		return 	KnightSiblingLightEffect_;
	}
	


}; 

