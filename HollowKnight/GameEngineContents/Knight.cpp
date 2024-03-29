#include "PreCompile.h"

#include <iostream>

#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>
#include <GameEngineCore/GameEngineTextureRenderer.h>

#include "Knight.h"
#include "MasterMap.h"

#include "KnightData.h"

#include "MasterNPC.h"
#include "RoomPotal.h"
#include "Tablet.h"
#include "Monster.h"
#include "MonsterHitEffect.h"


Knight::Knight()
	:
	KnightManager_(),

	KnightJumpPower_(0.0f),
	KnightRunSpeed_(0.0f),
	KnightFallAccel_(0.0f),

	KnightSlashTimer_(0.0f),
	KnightLookUpTimer_(0.0f),
	KnightLookDownTimer_(0.0f),
	KnightDashTimer_(0.0f),
	KnightSlashCollisionTimer_(0.0f),
	KnihgtInvincibilityTimer_(0.0f),
	KnihgtInvincibilitingTimer_(0.0f),
	KnihgtFocusTimer_(0.0f),
	KnightActtingMoveDirPower_(1.0f),
	JumpAccel_(0.0f),
	KnightDoubleJumpPower_(0.0f),
	KnightFallAccelPower_(0.0f),

	isPossibleDoubleSlash_(false),
	isKnightActtingMove_(false),
	isPressJumppingKey_(false),
	isSlashEnd_(false),
	isDoubleSlashEnd_(false),
	isPossibleDoubleJump_(false),
	isDoubleJumpEnd_(false),
	isUpSlashEnd_(false),
	isDownSlashEnd_(false),
	isLookMap_(false),
	isWalkTurnEnd_(false),
	isRunMode_(false),
	isFocusEnd_(false),
	isLowHealth_(false),
	isLandEnd_(false),
	isStunEnd_(false),
	isDeath_(false),
	isDeathEnd_(false),
	isSitEnd_(false),
	isDoorEnd_(false),
	isRunTurnEnd_(false),
	isCastEnd_(false),
	isSpikeStunEnd_(false),
	isSitBackEnd_(false),
	isOnePunchMode_(false),

	isReturnToIdle_(false),
	isInvincibility_(false),
	isKnightBlack_(false),
	isWakeUpEnd_(false),
	isTalkingNPC_(false),
	isKnihgtStillWall_(false),
	isMapWalkTurnEnd_(false),
	isKnightPotal_(false),
	isGroundWakeUpEnd_(false),
	isKingsPass_(false),
	isIntroLandEnd_(false),
	isKnightSpikeHit_(false),
	isPossibleFallJump_(false),
	isNewMaskEnd_(false),
	isScreamEnd_(false),

	KnightSlashEffect_(nullptr),
	KnightStunEffect_(nullptr),
	SideDarkEffect_(nullptr),
	KnightSiblingLightEffect_(nullptr),
	KnightDonutLightEffect_(nullptr),
	KnightMainLightEffect_(nullptr),
	KnightFocusEffect_(nullptr),
	KnightDoubleJumpEffect_(nullptr),
	KnightCast_(nullptr),
	KnightCastEffect_(nullptr),
	KnightJumpDustEffect_(nullptr),
	KnightDashEffect_(nullptr),
	KnightDoubleJumpParticle_(nullptr),
	DeathLevelChangeFadeOut_(nullptr),
	KnightHatchlingBurst_(nullptr),
	KnightScreamCastEffect_(nullptr),
	KnightInvincibilityEffect_(nullptr),

	ChangeLevel_(""),

	KnockbackDirection_(float4::ZERO)
{
}

Knight::~Knight()
{
}




void Knight::Start()
{

	//================================
	//    Initialize
	//================================
	SetMoveDirection(float4::RIGHT);
	SetSpeed(300.f);
	SetisMove(true);
	SetGravity(200.f);
	SetJumpSpeed(11.f);
	SetCollisionSize({ 0, 0, 0 });
	SetFallSpeed(150);

	KnightData::GetInst()->SetHitDamage(1);

	CreateCollisionComponent(float4{ 60, 120, 1 }, static_cast<int>(COLLISION_ORDER::Knight));
	CreateWallCollisionComponent(float4{ 20, 20, 1 });

	GetCollision()->GetTransform().SetWorldPosition({ 0, 120 / 2, static_cast<float>(Z_ORDER::Knight) });

	CreateRendererComponent(float4{ 349, 186, 1 }, "Knight_idle_still_020000-Sheet.png", 8, static_cast<int>(RENDERORDER::Knight));



	GetRenderer()->GetTransform().PixLocalNegativeX();

	GetTransform().SetWorldPosition({ 500,-4000,static_cast<float>(Z_ORDER::Knight) });

	KnightSlashEffect_ = GetLevel()->CreateActor<KnightSlashEffect>();
	KnightMainLightEffect_ = GetLevel()->CreateActor<KnightMainLightEffect>();
	KnightDonutLightEffect_ = GetLevel()->CreateActor<KnightDonutLightEffect>();
	KnightSiblingLightEffect_ = GetLevel()->CreateActor<KnightSiblingLightEffect>();
	KnightStunEffect_ = GetLevel()->CreateActor<KnightStunEffect>();

	KnightStunEffect_->StunEffectOff();

	KnightDoubleJumpEffect_ = GetLevel()->CreateActor<KnightDoubleJumpEffect>();
	KnightCast_ = GetLevel()->CreateActor<KnightCast>();
	KnightCastEffect_ = GetLevel()->CreateActor<KnightCastEffect>();
	KnightJumpDustEffect_ = GetLevel()->CreateActor<KnightJumpDustEffect>();
	KnightDashEffect_ = GetLevel()->CreateActor<KnightDashEffect>();
	KnightDoubleJumpParticle_ = GetLevel()->CreateActor<KnightDoubleJumpParticle>();
	KnightHatchlingBurst_ = GetLevel()->CreateActor<KnightHatchlingBurst>();
	KnightScreamCastEffect_ = GetLevel()->CreateActor<KnightScreamCastEffect>();
	KnightScreamParticle_ = GetLevel()->CreateActor<KnightScreamParticle>();
	KnightInvincibilityEffect_ = GetLevel()->CreateActor<KnightInvincibilityEffect>();

	KnightDoubleJumpEffect_->Off();
	KnightScreamParticle_->Off();

	KnightSlashEffect_->SetParent(this);
	KnightSlashEffect_->SetAnimationStill();

	KnightSlashEffect_->GetCollision()->Off();
	KnightMainLightEffect_->SetParent(this);
	KnightDonutLightEffect_->SetParent(this);
	KnightSiblingLightEffect_->SetParent(this);
	KnightDoubleJumpEffect_->SetParent(this);
	KnightCast_->SetParent(this);
	KnightCastEffect_->SetParent(this);
	KnightStunEffect_->SetParent(this);
	KnightDashEffect_->SetParent(this);
	KnightScreamCastEffect_->SetParent(this);
	//KnightHatchlingBurst_->SetParent(this);
	KnightInvincibilityEffect_->SetParent(this);

	KnightMainLightEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Light) });
	KnightDonutLightEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Dount_Light) });
	KnightSiblingLightEffect_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x, GetTransform().GetWorldPosition().y, static_cast<float>(Z_ORDER::Small_Light) });
	KnightJumpPower_ = 120.f;
	KnightDoubleJumpPower_ = 100.f;
	KnightRunSpeed_ = 400.f;
	KnightActtingMoveDirPower_ = 2.0f;
	KnightFallAccel_ = 0.0f;

	isRunMode_ = true;

	//================================
	//    CreateKey
	//================================

	if (false == GameEngineInput::GetInst()->IsKey("KnightLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("KnightLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("KnightRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("KnightUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("KnightDown", VK_DOWN);

		GameEngineInput::GetInst()->CreateKey("KnightRunMode", 'R');
		GameEngineInput::GetInst()->CreateKey("KnightOnePunchMode", 'P');

		GameEngineInput::GetInst()->CreateKey("KnightLookMap", VK_TAB);
		GameEngineInput::GetInst()->CreateKey("KnightDash", VK_SHIFT);
		GameEngineInput::GetInst()->CreateKey("KnightFocus", 'Q');
		GameEngineInput::GetInst()->CreateKey("KnightCast", 'S');
		GameEngineInput::GetInst()->CreateKey("KnightScreamCast", 'A');

		GameEngineInput::GetInst()->CreateKey("KnightSlash", 'C');
		GameEngineInput::GetInst()->CreateKey("KnightTalking", 'Z');
		GameEngineInput::GetInst()->CreateKey("KnightClose", 'Z');

		GameEngineInput::GetInst()->CreateKey("KnightSit", 'T');

		GameEngineInput::GetInst()->CreateKey("KnightJump", VK_SPACE);

		GameEngineInput::GetInst()->CreateKey("OnOffSettingPage", 'I');


	}


	//================================
	//    Create Animation
	//================================

	// ---- 기본 ----
	GetRenderer()->CreateFrameAnimationCutTexture("STILL_ANIMATION", FrameAnimation_DESC("Knight_idle_still_020000-Sheet.png", 0, 8, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("SLAH_STILL_ANIMATION", FrameAnimation_DESC("Knight_idle_still_020000-Sheet.png", 0, 8, 0.100f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("JUMP_ANIMATION", FrameAnimation_DESC("Knight_jump_01-Sheet.png", 0, 5, 0.120f, true));
	

	
	GetRenderer()->CreateFrameAnimationCutTexture("DOUBLE_JUMP_ANIMATION", FrameAnimation_DESC("Knight_double_jump_v020000-Sheet.png", 0, 7, 0.040f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("FALL_ANIMATION", FrameAnimation_DESC("Knight_fall_01-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("FALL_LOOP_ANIMATION", FrameAnimation_DESC("Knight_fall_01-Sheet.png", 3, 5, 0.100f, true));

	GetRenderer()->CreateFrameAnimationCutTexture("LAND_ANIMATION", FrameAnimation_DESC("Knight_land0000-Sheet.png", 0, 2, 0.080f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("WALK_ANIMATION", FrameAnimation_DESC("Knight_walk0000-Sheet.png", 0, 7, 0.100f));

	GetRenderer()->CreateFrameAnimationCutTexture("WALK_TURN_LEFT_ANIMATION", FrameAnimation_DESC("Knight_turn000-Sheet.png", 0, 1, 0.080f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("WALK_TURN_RIGHT_ANIMATION", FrameAnimation_DESC("Knight_turn000-Sheet.png", 0, 1, 0.080f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("RUN_TURN_ANIMATION", FrameAnimation_DESC("Knight_idle_to_run0000-Sheet.png", 0, 4, 0.120f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("LOOK_DOWN_ANIMATION", FrameAnimation_DESC("Knight_look_down0000-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("LOOK_UP_ANIMATION", FrameAnimation_DESC("Knight_look_up0000-Sheet.png", 0, 5, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DASH_ANIMATION", FrameAnimation_DESC("Knight_dash_v020000-Sheet.png", 0, 11, 0.070f, false));


	GetRenderer()->CreateFrameAnimationCutTexture("LOW_HEALTH_ANIMATION", FrameAnimation_DESC("Knight_idle_low_health000-Sheet.png", 0, 9, 0.100f));

	// ---- 스턴 ----
	GetRenderer()->CreateFrameAnimationCutTexture("STUN_ANIMATION", FrameAnimation_DESC("Knight_stun0000-Sheet.png", 0, 4, 0.070f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SPIKE_STUN_ANIMATION", FrameAnimation_DESC("Knight_spike_death000-Sheet.png", 0, 7, 0.070f, false));

	// ---- 죽음 ----
	GetRenderer()->CreateFrameAnimationCutTexture("DEATH_ANIMATION", FrameAnimation_DESC("Knight_death_anim0000-Sheet.png", 0, 13, 0.100f, false));


	// ---- 달리기 ----
	GetRenderer()->CreateFrameAnimationCutTexture("RUN_ANIMATION", FrameAnimation_DESC("Knight_run0000-Sheet.png", 0, 7, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_TO_RUN_ANIMATION", FrameAnimation_DESC("Knight_idle_to_run0000-Sheet.png", 0, 4, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("RUN_TO_IDLE_ANIMATION", FrameAnimation_DESC("Knight_run_to_idle000-Sheet.png", 0, 5, 0.100f, false));

	// ---- 지도 보기 ----
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_OPEN_ANIMATION", FrameAnimation_DESC("Knight_idle_map0000-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_STILL_ANIMATION", FrameAnimation_DESC("Knight_idle_map0000-Sheet.png", 2, 8, 0.100f));

	GetRenderer()->CreateFrameAnimationCutTexture("MAP_OPEN_WALKING_ANIMATION", FrameAnimation_DESC("Knight_walk_map0000-Sheet.png", 0, 1, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_WALKING_ANIMATION", FrameAnimation_DESC("Knight_walk_map0000-Sheet.png", 2, 9, 0.100f));

	GetRenderer()->CreateFrameAnimationCutTexture("MAP_WALKING_TURN_RIGHT_ANIMATION", FrameAnimation_DESC("Knight_walk_map_turn0000-Sheet.png", 0, 0, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_WALKING_TURN_LEFT_ANIMATION", FrameAnimation_DESC("Knight_walk_map_turn0000-Sheet.png", 1, 1, 0.100f, false));

	GetRenderer()->CreateFrameAnimationCutTexture("MAP_SIT_WRITE_ANIMATION", FrameAnimation_DESC("Knight_sit_map_write0000-Sheet.png", 0, 3, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("MAP_SIT_LOOK_ANIMATION", FrameAnimation_DESC("Knight_sit_map_look0026-Sheet.png", 0, 3, 0.100f));

	// ---- 공격 ----
	GetRenderer()->CreateFrameAnimationCutTexture("SLASH_ANIMATION", FrameAnimation_DESC("Knight_slash_left_longer0000-Sheet.png", 0, 5, 0.07f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DOUBLE_SLASH_ANIMATION", FrameAnimation_DESC("Knight_slash_left_longer0000-Sheet.png", 6, 10, 0.07f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("UP_SLASH_ANIMATION", FrameAnimation_DESC("Knight_up_slash0000-Sheet.png", 0, 4, 0.07f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("DOWN_SLASH_ANIMATION", FrameAnimation_DESC("Knight_down_slash_v02000-Sheet.png", 0, 4, 0.07f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("CAST_ANIMATION", FrameAnimation_DESC("Knight_cast_v030002-Sheet.png", 0, 11, 0.060f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SCREAM_CAST_ANIMATION", FrameAnimation_DESC("Knight_scream_cast_lvl_020000-Sheet.png", 0, 8, 0.060f, false));

	// ---- 새로운 마스크 ----
	GetRenderer()->CreateFrameAnimationCutTexture("NEW_MASK_START_ANIMATION", FrameAnimation_DESC("Knight_cast0003-Sheet.png", 0, 2, 0.060f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("NEW_MASK_CAST_ANIMATION", FrameAnimation_DESC("Knight_cast0003-Sheet.png", 3, 8, 0.060f, true));
	GetRenderer()->CreateFrameAnimationCutTexture("NEW_MASK_END_ANIMATION", FrameAnimation_DESC("Knight_cast0003-Sheet.png", 9, 9, 0.100f, false));

	// ---- 기상 ----
	GetRenderer()->CreateFrameAnimationCutTexture("WAKEUP_GROUND_ANIMATION", FrameAnimation_DESC("Knight_wake_up_ground0000-Sheet.png", 0, 20, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("WAKEUP_ANIMATION", FrameAnimation_DESC("Knight_wake0000-Sheet.png", 0, 4, 0.100f, false));

	{
		std::vector<unsigned int>CustomAni;

		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);
		CustomAni.push_back(7);

		for (int i = 7; i < 21; ++i)
		{
			CustomAni.push_back(i);
		}


		GetRenderer()->CreateFrameAnimationCutTexture("INTRO_LAND_ANIMATION", FrameAnimation_DESC("Knight_wake_up_ground0000-Sheet.png", CustomAni, 0.120f, false));
	}
	// ---- 탈진 ----
	//GetRenderer()->CreateFrameAnimationCutTexture("LOW_HEALTH_ANIMATION", FrameAnimation_DESC("Knight_idle_low_health000-Sheet.png", 0, 9, 0.100f));

	// ---- 슬라이드 ----
	GetRenderer()->CreateFrameAnimationCutTexture("SLIDE_ANIMATION", FrameAnimation_DESC("Knight_wall_slide0000-Sheet.png", 0, 3, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("WALL_JUMP_ANIMATION", FrameAnimation_DESC("Knight_wall_jump0000-Sheet.png", 0, 2, 0.100f));

	// ---- 의자 ----
	GetRenderer()->CreateFrameAnimationCutTexture("SIT_ANIMATION", FrameAnimation_DESC("Knight_sit0000-Sheet.png", 0, 4, 0.070f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SIT_IDLE_ANIMATION", FrameAnimation_DESC("Knight_sit0000-Sheet.png", 3, 3, 0.100f));

	{
		std::vector<unsigned int>BackAni;

		for (int i = 4; i > -1; --i)
		{
			BackAni.push_back(i);
		}

		GetRenderer()->CreateFrameAnimationCutTexture("SIT_BACK_ANIMATION", FrameAnimation_DESC("Knight_sit0000-Sheet.png", BackAni, 0.070f, false));
	}

	// ---- 문 들어가기 ----
	GetRenderer()->CreateFrameAnimationCutTexture("DOOR_ANIMATION", FrameAnimation_DESC("Knight_into_door0000-Sheet.png", 0, 9, 0.100f, false));
	GetRenderer()->CreateFrameAnimationCutTexture("SEE_ANIMATION", FrameAnimation_DESC("Knight_into_door0000-Sheet.png", 0, 2, 0.100f, false));

	{
		std::vector<unsigned int>BackAni;

		for (int i = 2; i > -1; --i)
		{
			BackAni.push_back(i);
		}
		GetRenderer()->CreateFrameAnimationCutTexture("SEE_RETURN_ANIMATION", FrameAnimation_DESC("Knight_into_door0000-Sheet.png", BackAni, 0.070f, false));
	}

	// ---- 집중 ----

	GetRenderer()->CreateFrameAnimationCutTexture("FOCUS_ANIMATION", FrameAnimation_DESC("Knight_focus_v020000-Sheet.png", 0, 11, 0.140f, false));


	GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");
	//================================
	//    Create Bind Animation
	//================================
	{

		GetRenderer()->AnimationBindEnd("SLAH_STILL_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				GetRenderer()->ChangeFrameAnimation("FAll_ANIMATION");
			});

		GetRenderer()->AnimationBindEnd("SIT_BACK_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isSitBackEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("SCREAM_CAST_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isScreamEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("NEW_MASK_START_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				GetRenderer()->ChangeFrameAnimation("NEW_MASK_CAST_ANIMATION");
			});

		GetRenderer()->AnimationBindEnd("NEW_MASK_END_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isNewMaskEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("SPIKE_STUN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isSpikeStunEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("CAST_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isCastEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("INTRO_LAND_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isIntroLandEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("FALL_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				GetRenderer()->ChangeFrameAnimation("FALL_LOOP_ANIMATION");
			});

		GetRenderer()->AnimationBindEnd("SEE_RETURN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isReturnToIdle_ = true;
			});

		GetRenderer()->AnimationBindEnd("RUN_TURN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isRunTurnEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("SIT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				GetRenderer()->ChangeFrameAnimation("SIT_IDLE_ANIMATION");
			});

		GetRenderer()->AnimationBindEnd("SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isSlashEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("DOUBLE_SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isDoubleSlashEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("DOUBLE_JUMP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				GetRenderer()->ChangeFrameAnimation("JUMP_ANIMATION");
				isDoubleJumpEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("UP_SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isUpSlashEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("DOWN_SLASH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isDownSlashEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("MAP_OPEN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				GetRenderer()->ChangeFrameAnimation("MAP_STILL_ANIMATION");
			});

		GetRenderer()->AnimationBindEnd("MAP_OPEN_WALKING_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				GetRenderer()->ChangeFrameAnimation("MAP_WALKING_ANIMATION");
			});

		GetRenderer()->AnimationBindEnd("MAP_WALKING_TURN_RIGHT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isMapWalkTurnEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("MAP_WALKING_TURN_LEFT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isMapWalkTurnEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("WALK_TURN_RIGHT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isWalkTurnEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("WALK_TURN_LEFT_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isWalkTurnEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("IDLE_TO_RUN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				GetRenderer()->ChangeFrameAnimation("RUN_ANIMATION");
			});

		GetRenderer()->AnimationBindEnd("RUN_TO_IDLE_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");
			});

		GetRenderer()->AnimationBindEnd("FOCUS_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isFocusEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("LAND_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isLandEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("STUN_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isStunEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("DEATH_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isDeathEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("WAKEUP_GROUND_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isGroundWakeUpEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("WAKEUP_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isWakeUpEnd_ = true;
			});

		GetRenderer()->AnimationBindEnd("DOOR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
			{
				isDoorEnd_ = true;
			});
	}

	//================================
	//    Create State
	//================================
	 
	// ---- 기본 ----
	KnightManager_.CreateStateMember("STILL"
		, std::bind(&Knight::KnightStillUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightStillStart, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("WALK"
		, std::bind(&Knight::KnightWalkUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWalkStart, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("WALK_TURN"
		, std::bind(&Knight::KnightWalkTurnUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWalkTurnStart, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("LOOK_UP"
		, std::bind(&Knight::KnightLookUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightLookUpStart, this, std::placeholders::_1), std::bind(&Knight::KnightLookUpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("LOOK_DOWN"
		, std::bind(&Knight::KnightLookDownUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightLookDownStart, this, std::placeholders::_1), std::bind(&Knight::KnightLookDownEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("FOCUS"
		, std::bind(&Knight::KnightFocusUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightFocusStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightFocusEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("SLASH_JUMP"
		, std::bind(&Knight::KnightUpSlashJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightUpSlashJumpStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightUpSlashJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("JUMP"
		, std::bind(&Knight::KnightJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightJumpStart, this, std::placeholders::_1), std::bind(&Knight::KnightJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DOUBLE_JUMP"
		, std::bind(&Knight::KnightDoubleJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDoubleJumpStart, this, std::placeholders::_1), std::bind(&Knight::KnightDoubleJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("LAND"
		, std::bind(&Knight::KnightLandUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightLandStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightLandEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("INTRO_LAND"
		, std::bind(&Knight::KnightIntroLandUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightIntroLandStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightIntroLandEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("FALL"
		, std::bind(&Knight::KnightFallUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Knight::KnightFallStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightFallEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("INTRO_FALL"
		, std::bind(&Knight::KnightIntroFallUpdate, this, std::placeholders::_1, std::placeholders::_2),
		std::bind(&Knight::KnightIntroFallStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightIntroFallEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DASH"
		, std::bind(&Knight::KnightDashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("FOCUS_BURST"
		, std::bind(&Knight::KnightFocusBurstUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightFocusBurstStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightFocusBurstEnd, this, std::placeholders::_1));

	// ---- 공격 ----
	KnightManager_.CreateStateMember("SLASH"
		, std::bind(&Knight::KnightSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightSlashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DOUBLE_SLASH"
		, std::bind(&Knight::KnightDoubleSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDoubleSlashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDoubleSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("UP_SLASH"
		, std::bind(&Knight::KnightUpSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightUpSlashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightUpSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("DOWN_SLASH"
		, std::bind(&Knight::KnightDownSlashUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDownSlashStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDownSlashEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("CAST"
		, std::bind(&Knight::KnightCastUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightCastStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightCastEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("SCREAM_CAST"
		, std::bind(&Knight::KnightScreamCastUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightScreamCastStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightScreamCastEnd, this, std::placeholders::_1));

	// ----스턴 ----
	KnightManager_.CreateStateMember("STUN"
		, std::bind(&Knight::KnightStunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightStunStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightStunEnd, this, std::placeholders::_1));

	// ---- 사망 ----
	KnightManager_.CreateStateMember("DEATH"
		, std::bind(&Knight::KnightDeathUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDeathStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDeathEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("WAKE_UP"
		, std::bind(&Knight::KnightWakeUpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWakeUpStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightWakeUpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("GROUND_WAKE_UP"
		, std::bind(&Knight::KnightWakeUpGroundUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWakeUpGroundStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightWakeUpGroundEnd, this, std::placeholders::_1));

	// ---- 달리기 ----
	KnightManager_.CreateStateMember("RUN"
		, std::bind(&Knight::KnightRunUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightRunStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightRunEnd, this, std::placeholders::_1));


	// ---- 지도 보기 ----
	KnightManager_.CreateStateMember("MAP_STILL"
		, std::bind(&Knight::KnightMapStillUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapStillStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapStillEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_WALKING"
		, std::bind(&Knight::KnightMapWalkinglUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapWalkinglStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapWalkinglEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_WALKING_TURN"
		, std::bind(&Knight::KnightMapWalkingTurnlUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapWalkingTurnlStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapWalkingTurnlEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_SIT_LOOK"
		, std::bind(&Knight::KnightMapSitLooklUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapSitLooklStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapSitLooklEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("MAP_SIT_WRITE"
		, std::bind(&Knight::KnightMapSitWritelUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightMapSitWritelStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightMapSitWritelEnd, this, std::placeholders::_1));

	// ---- 슬라이드 ----
	KnightManager_.CreateStateMember("SLIDE"
		, std::bind(&Knight::KnightSlideUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightSlideStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightSlideEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("WALL_JUMP"
		, std::bind(&Knight::KnightWallJumpUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWallJumpStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightWallJumpEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("WALL_JUMP_LAND"
		, std::bind(&Knight::KnightWallJumpLandUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightWallJumpLandStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightWallJumpLandEnd, this, std::placeholders::_1));

	// ---- 의자 ----
	KnightManager_.CreateStateMember("SIT"
		, std::bind(&Knight::KnightSitUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightSitStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightSitEnd, this, std::placeholders::_1));

	// ---- NPC 대화 ----
	KnightManager_.CreateStateMember("TALKING"
		, std::bind(&Knight::KnightTalkingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightTalkingStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightTalkingEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("SHOPPING"
		, std::bind(&Knight::KnightShoppingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightShoppingStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightShoppingEnd, this, std::placeholders::_1));

	// ---- 문 들어가기 ----
	KnightManager_.CreateStateMember("DOOR"
		, std::bind(&Knight::KnightDoorUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightDoorStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightDoorEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("SEE"
		, std::bind(&Knight::KnightTabletUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightTabletStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightTabletEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("SEE_RETURN_TO_IDLE"
		, std::bind(&Knight::KnightTabletReturnToIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightTabletReturnToIdleStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightTabletReturnToIdleEnd, this, std::placeholders::_1));

	KnightManager_.CreateStateMember("NEW_MASK"
		, std::bind(&Knight::KnightNewMaskEventUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Knight::KnightNewMaskEventStart, this, std::placeholders::_1)
		, std::bind(&Knight::KnightNewMaskEventEnd, this, std::placeholders::_1));

	KnightManager_.ChangeState("STILL");
}

void Knight::Update(float _DeltaTime)
{
	KnightManager_.Update(_DeltaTime);
	KnightData::GetInst()->SetKnightPosition(this->GetTransform().GetWorldPosition());

}

void Knight::LevelStartEvent()
{
	KnightManager_.ChangeState("STILL");


	if (KnightData::GetInst()->GetisIntroFallEvent() == false)
	{
		std::string EnumString;
		auto PrevName = magic_enum::enum_name(LevelList::KingsPassLevel1);
		EnumString = static_cast<std::string>(PrevName);

		std::string UpperName = GameEngineString::ToUpperReturn(EnumString);
		if (GetLevel()->GetNameConstRef() == UpperName)
		{
			KnightManager_.ChangeState("INTRO_FALL");
		}
	}

	if (KnightData::GetInst()->GetisDeathLevelChange() == true)
	{
		KnightData::GetInst()->SetisDeathLevelChange(false);
		GetTransform().SetLocalPosition({ 4611, -3127, static_cast<float>(Z_ORDER::Knight) });
		KnightManager_.ChangeState("SIT");

	}

	isKnightPotal_ = false;

	if (DeathLevelChangeFadeOut_ != nullptr)
	{
		if (DeathLevelChangeFadeOut_->GetDeathflag() == true)
		{
			DeathLevelChangeFadeOut_->Death();
			DeathLevelChangeFadeOut_ = nullptr;
		}
	}

	KnightData::GetInst()->SetisIntroFallEvent(true);

}

void Knight::LevelEndEvent()
{
}




void Knight::SetDirInit(float4 _Dir)
{
	SetMoveDirection(_Dir);

	if (_Dir.CompareInt2D(float4::LEFT))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
		KnightSlashEffect_->SetEffectDirection(float4::LEFT);
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalPositiveX();
		//KnightSlashEffect_->GetCollision()->GetTransform().PixLocalPositiveX();

		this->SetMoveDirection(float4::LEFT);
	}

	if (_Dir.CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		KnightSlashEffect_->SetEffectDirection(float4::RIGHT);

		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalNegativeX();
		//KnightSlashEffect_->GetCollision()->GetTransform().PixLocalNegativeX();


		this->SetMoveDirection(float4::RIGHT);
	}
}

void Knight::SetKnightisPotal(bool _b)
{
	isKnightPotal_ = _b;
}

void Knight::SetKnightState(std::string _StateName)
{
	KnightManager_.ChangeState(_StateName);
}

bool Knight::GetisKnightMove()
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		return true;
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		return true;
	}

	//if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	//{
	//	return true;
	//}

	//if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	//{
	//	return true;
	//}

	return false;
}

void Knight::isKnihgtActtingMoveChack()
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		isKnightActtingMove_ = true;
	}

	else if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		isKnightActtingMove_ = true;
	}


	else
	{
		isKnightActtingMove_ = false;

	}

}

void Knight::KnightDirectionCheck()
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalPositiveX();
		KnightSlashEffect_->SetEffectDirection(float4::LEFT);

		GetWallCollision()->GetTransform().SetLocalPosition({-10, 50});
		//KnightSlashEffect_->GetCollision()->GetTransform().PixLocalPositiveX();

		this->SetMoveDirection(float4::LEFT);
	}

	if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalNegativeX();
		KnightSlashEffect_->SetEffectDirection(float4::RIGHT);

		//KnightSlashEffect_->GetCollision()->GetTransform().PixLocalNegativeX();
		GetWallCollision()->GetTransform().SetLocalPosition({ 10, 50 });

		this->SetMoveDirection(float4::RIGHT);
	}

	//if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	//{
	//	this->SetMoveDirection(float4::DOWN);
	//}

	//if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	//{
	//	this->SetMoveDirection(float4::UP);
	//}
}

void Knight::KnightActtingDirectionCheck()
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalPositiveX();
		ActtingMoveDirection_ = float4::LEFT;
	}

	else if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
		KnightSlashEffect_->GetRenderer()->GetTransform().PixLocalNegativeX();

		ActtingMoveDirection_ = float4::RIGHT;
	}

	else
	{
		ActtingMoveDirection_ = float4::ZERO;

	}

	//if (true == GameEngineInput::GetInst()->IsPress("KnightDown"))
	//{
	//	//ActtingMoveDirection_ = float4::DOWN;
	//}

	//if (true == GameEngineInput::GetInst()->IsPress("KnightUp"))
	//{
	//	//ActtingMoveDirection_ = float4::UP;
	//}
}

void Knight::KnihgtSlideNegativeRenderer()
{
	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
	}

	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
	}

}

void Knight::KnihgtSlidePositiveRenderer()
{
	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();
	}

	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		GetRenderer()->GetTransform().PixLocalPositiveX();
	}
}

void Knight::KnightInvincibiliting(float _DeltaTime)
{
	KnihgtInvincibilitingTimer_ += _DeltaTime;
	KnihgtInvincibilityTimer_ += _DeltaTime;


	if (KnihgtInvincibilityTimer_ > 1.f)
	{
		KnihgtInvincibilityTimer_ = 0.0f;
		isInvincibility_ = false;
		GetRenderer()->GetPixelData().MulColor.r = 1.f;
		GetRenderer()->GetPixelData().MulColor.g = 1.f;
		GetRenderer()->GetPixelData().MulColor.b = 1.f;
	}

	if (KnihgtInvincibilitingTimer_ > 0.1f)
	{
		isKnightBlack_ = !isKnightBlack_;
		KnihgtInvincibilitingTimer_ = 0.0f;
	}
	if (isKnightBlack_ == true && isInvincibility_ == true)
	{
		GetRenderer()->GetPixelData().MulColor.r = 1.f;
		GetRenderer()->GetPixelData().MulColor.g = 1.f;
		GetRenderer()->GetPixelData().MulColor.b = 1.f;
	}

	else if (isKnightBlack_ == false && isInvincibility_ == true)
	{
		GetRenderer()->GetPixelData().MulColor.r = 0.f;
		GetRenderer()->GetPixelData().MulColor.g = 0.f;
		GetRenderer()->GetPixelData().MulColor.b = 0.f;
	}

}

void Knight::KnightIsActtingCheck()
{
	if (false == GameEngineInput::GetInst()->IsPress("KnightLeft")
		&& false == GameEngineInput::GetInst()->IsPress("KnightRight")
		&& false == GameEngineInput::GetInst()->IsPress("KnightDown")
		&& false == GameEngineInput::GetInst()->IsPress("KnightUp"))
	{
		ActtingMoveDirection_ = float4::ZERO;
	}
}

void Knight::Walkking(float _DeltaTime)
{
	KnightDirectionCheck();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());
	//this->isWallCheck(_DeltaTime);

	if (GetisWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{
			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{
			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
		}
	}


	else
	{
		KnightManager_.ChangeState("FALL");
	}

}

void Knight::DoubleSlashTimer(float _DeltaTime)
{
	if (isPossibleDoubleSlash_ == true)
	{
		KnightSlashTimer_ += _DeltaTime;

		if (KnightSlashTimer_ > 0.5f)
		{
			KnightSlashTimer_ = 0.f;
			isPossibleDoubleSlash_ = false;
		}
	}
}

void Knight::LookUpTimerAndChangeState(float _DeltaTime)
{
	KnightLookUpTimer_ += _DeltaTime;

	if (KnightLookUpTimer_ > 0.5f)
	{
		KnightLookUpTimer_ = 0.f;
		KnightManager_.ChangeState("LOOK_UP");
	}
}

void Knight::LookDownTimerAndChangeState(float _DeltaTime)
{

	KnightLookDownTimer_ += _DeltaTime;

	if (KnightLookDownTimer_ > 0.5f)
	{
		KnightLookDownTimer_ = 0.f;
		KnightManager_.ChangeState("LOOK_DOWN");
	}
}

bool Knight::KnightVSMonsterCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (isInvincibility_ == false)
	{
		MasterActor* DyMonster_ = dynamic_cast<MasterActor*>(_Other->GetActor());
		MonsterHitEffect* Effect = GetLevel()->CreateActor<MonsterHitEffect>();

		Effect->GetTransform().SetWorldPosition({ DyMonster_->GetTransform().GetWorldPosition().x,  DyMonster_->GetTransform().GetWorldPosition().y + (DyMonster_->GetRenderer()->GetTransform().GetWorldScale().y / 4) , static_cast<float>(Z_ORDER::Effect) });

		if (DyMonster_ != nullptr)
		{
			KnockbackDirection_ = DyMonster_->GetMoveDirection();

			Monster* Monster_ = dynamic_cast<Monster*>(_Other->GetActor());

			if (Monster_->GetMonsterType() == MonsterType::Spike)
			{
				isKnightSpikeHit_ = true;
			}

		}

		return true;
	}

	else
	{
		return false;
	}
}

bool Knight::KnightVSMonsterAttackCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (isInvincibility_ == false && _Other != nullptr)
	{
		MasterEffect* Attack = dynamic_cast<MasterEffect*>(_Other->GetActor());
		MonsterHitEffect* Effect = GetLevel()->CreateActor<MonsterHitEffect>();
		if (Effect != nullptr && Attack != nullptr )
		{
			Effect->GetTransform().SetWorldPosition({ _Other->GetTransform().GetWorldPosition().x,  _Other->GetTransform().GetWorldPosition().y + (Attack->GetCollision()->GetTransform().GetWorldScale().y / 4) , static_cast<float>(Z_ORDER::Effect) });
		}

		//if(_This->)

		return true;
	}
	else
	{
		return false;
	}
}

bool Knight::KnihgtVSBenchCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}

bool Knight::KnihgtVSTabletCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	Tablet* Tablet_ = dynamic_cast<Tablet*>(_Other->GetActor());
	if (Tablet_ != nullptr)
	{
		if (Tablet_->GetisOpenDialogue() == false && KnightManager_.GetCurStateStateName() != "SEE")
		{
			if (GameEngineInput::GetInst()->IsDown("KnightUp") == true)
			{
				Tablet_->TabletDialogueOn();
				return true;
			}
		}

		if (Tablet_->GetisOpenDialogue() == true && KnightManager_.GetCurStateStateName() == "SEE")
		{
			if (GameEngineInput::GetInst()->IsDown("KnightUp") == true)
			{

				if (Tablet_->GetTabletDialogue()->GetDialougueFull() == true)
				{
					Tablet_->TabletDialogueOff();
					KnightManager_.ChangeState("SEE_RETURN_TO_IDLE");
				}

				else 
				{
					Tablet_->GetTabletDialogue()->SetNextDialogue();
				}
			}
		}
	}

	return true;
}

bool Knight::KnihgtVSNPCCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	MasterNPC* NPC = dynamic_cast<MasterNPC*>(_Other->GetActor());

	if (NPC != nullptr)
	{

		if (true == GameEngineInput::GetInst()->IsDown("KnightUp"))
		{
			if (NPC->GetNPCType() == NPC_TYPE::Shop)
			{
				NPC->GetMoveDirection().Normalize();
				if (NPC->GetMoveDirection().x < 0)
				{
					NPC->SetisShop(true);
					KnightManager_.ChangeState("SHOPPING");
					//NPC->SetisShop(true);
				}

				else if (NPC->GetMoveDirection().x > 0)
				{
					NPC->SetisTalking(true);
					NPC->StartTalking();
					NPC->GetDialogueSet()->SetDialogueOn();
					KnightManager_.ChangeState("TALKING");
				}

			}

			else if (NPC->GetNPCType() == NPC_TYPE::Normal)
			{
				KnightManager_.ChangeState("TALKING");
				NPC->SetisTalking(true);
				NPC->StartTalking();
				NPC->GetDialogueSet()->SetDialogueOn();
				isTalkingNPC_ = true;
			}
		}
	}

	return true;
}

bool Knight::NPCNextDialogueCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	MasterNPC* NPC = dynamic_cast<MasterNPC*>(_Other->GetActor());

	if (NPC != nullptr)
	{
		if (true == GameEngineInput::GetInst()->IsDown("KnightTalking"))
		{
			if (NPC->GetDialogueSet()->GetDialougueFull() == true)
			{
				NPC->GetDialogueSet()->SetDialogueOff();
				NPC->SetisTalking(false);
				KnightManager_.ChangeState("STILL");
				//return;
			}
			else
			{
				NPC->GetDialogueSet()->SetNextDialogue();

			}
		}
	}

	return true;
}

bool Knight::ShopCloseCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (GameEngineInput::GetInst()->IsDown("KnightClose") == true)
	{
		MasterNPC* NPC = dynamic_cast<MasterNPC*>(_Other->GetActor());

		if (NPC != nullptr)
		{
			NPC->SetisShop(false);
			KnightManager_.ChangeState("STILL");
		}
	}

	return false;
}

bool Knight::KnightVSPotalCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	if (GameEngineInput::GetInst()->IsDown("KnightUp") == true)
	{
		RoomPotal* Potal = dynamic_cast<RoomPotal*>(_Other->GetActor());


		POTAL_TYPE FindType = Potal->GetPotalType();

		switch (FindType)
		{
		case POTAL_TYPE::Sly_Shop:
			ChangeLevel_ = "SlyShopLevel";

			break;
		case POTAL_TYPE::Map_Shop:
			ChangeLevel_ = "MapShopLevel";

			break;

		case POTAL_TYPE::Dirt:
			ChangeLevel_ = "DirtmouthLevel2";

			break;

		case POTAL_TYPE::Grimm_Dirt:
			ChangeLevel_ = "GrimmDirtmouthLevel2";

			break;

		case POTAL_TYPE::Grimm_Tent:
			ChangeLevel_ = "GrimmLevel";

			break;

		default:
			break;
		}

		KnightManager_.ChangeState("DOOR");
	}

	return true;
}

bool Knight::KnightVSWallCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
	//SetisWall(true);
}




//bool Knight::CheckMapCollision()
//{
//
//	std::vector<GameEngineTextureRenderer*> MapCollTexture = GetLevel<MasterMap>()->GetCollisionMap();
//
//	for (std::vector<GameEngineTextureRenderer*>::iterator Start = MapCollTexture.begin(); Start != MapCollTexture.end(); ++Start)
//	{
//		MapCollisionColor_.push_back((*Start)->GetCurTexture()-> GetPixel(GetTransform().GetWorldPosition().ix(), -GetTransform().GetWorldPosition().iy()));
//
//		if (false == MapCollisionColor_.begin()->CompareInt4D(float4::ZERO))
//		{
//			int a = 0;
//		}
//
//		return true;
//	}
//
//	return true;
//
//}
