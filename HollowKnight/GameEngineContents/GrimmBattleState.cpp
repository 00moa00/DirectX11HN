
#include "PreCompile.h"
#include "Grimm.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"
#include "GrimmLevel.h"

#include "FadePink.h"
#include "BossRoarEffect.h"



void Grimm::GrimmBattleTeleportAppearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("TELEPORT_APPEAR_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);


	// �ڷ���Ʈ ��Ÿ���鼭 �˾� ��ġ�� ���⼭ ���Ѵ�.
	auto castType_ = magic_enum::enum_cast<PatternType>(ChangeState_);
	PatternType PatternType_ = castType_.value();


	switch (PatternType_)
	{
	case PatternType::BATTLE_BALLOON_START:
		GetTransform().SetWorldPosition({4800,-600, static_cast<float>(Z_ORDER::Monster)});
		break;
	case PatternType::BATTLE_SLASH_START:
		break;
	case PatternType::BATTLE_AIR_DASH_START:
		break;
	case PatternType::BATTLE_SPIKE_START:
		break;
	case PatternType::BATTLE_CAST_START:
		break;
	default:
		break;
	}


}

void Grimm::GrimmBattleTeleportAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (isTeleportAppearEnd_ == true)
	{
		isTeleportAppearEnd_ = false;
		GrimmBattleManager_.ChangeState(ChangeState_);
		return;

	}
}

void Grimm::GrimmBattleTeleportAppearEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleTeleportDisappearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("TELEPORT_DISAPPEAR_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

}

void Grimm::GrimmBattleTeleportDisappearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 1.f)
	{
		//_Info.StateTime = 0.f;
		if (isTeleportDiappearEnd_ == true)
		{
			isTeleportDiappearEnd_ = false;
			GrimmBattleManager_.ChangeState("BATTLE_TELEPORT_APPEAR");
			return;

		}

	}


}
void Grimm::GrimmBattleTeleportDisappearEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleBalloonStartStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("BALLON_START_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

}

void Grimm::GrimmBattleBalloonStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isBllonStartEnd_ == true)
	{
		isBllonStartEnd_ = false;
		GrimmBattleManager_.ChangeState("BATTLE_BALLOON");
	}
}

void Grimm::GrimmBattleBalloonStartEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattleBalloonStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("BALLON_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

}

void Grimm::GrimmBattleBalloonUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 3.0f)
	{
		SetRamdomPattern();
	}
}

void Grimm::GrimmBattleBalloonEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashStartStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("AIR_DASH_START_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattleAirDashStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 2.0f)
	{
		GrimmBattleManager_.ChangeState("BATTLE_AIR_DASH");
		return;
	}
}

void Grimm::GrimmBattleAirDashStartEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleAirDashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("AIR_DASH_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattleAirDashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 2.0f)
	{
		GrimmBattleManager_.ChangeState("BATTLE_AIR_DASH_END");
		return;
	}
}

void Grimm::GrimmBattleAirDashEnd(const StateInfo& _Info)
{

}

void Grimm::GrimmBattleAirDashEndtStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("AIR_DASH_END_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattleAirDashEndtUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 2.0f)
	{
		SetRamdomPattern();

		return;
	}
}

void Grimm::GrimmBattleAirDashEndtEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattleSlashStartStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SLASH_START_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattleSlashStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isSlashStartEnd_ == true)
	{
		isSlashStartEnd_ = false;
		GrimmBattleManager_.ChangeState("BATTLE_SLASH");
	}
}

void Grimm::GrimmBattleSlashStartEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SLASH_SLASH_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattleSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isSlashEnd_ == true)
	{
		isSlashEnd_ = false;
		GrimmBattleManager_.ChangeState("BATTLE_SLASH_UP");
		return;

	}
}

void Grimm::GrimmBattleSlashEnd(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SLASH_UP_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattleSlashUpStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSlashUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isSlashEndEnd_ == true)
	{
		isSlashEndEnd_ = false;
		GrimmBattleManager_.ChangeState("BATTLE_FIRE");
		return;
	}
}

void Grimm::GrimmBattleSlashUpEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattleFireStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleFireUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (_Info.StateTime > 2.0f)
	{
		SetRamdomPattern();
		return;
	}

}

void Grimm::GrimmBattleFireEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattleSpikeStartStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SPRIKE_START_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}


void Grimm::GrimmBattleSpikeStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isSprikeStartEnd_ == true)
	{
		isSprikeStartEnd_ = false;
		GrimmBattleManager_.ChangeState("BATTLE_SPIKE");
		return;
	}
}

void Grimm::GrimmBattleSpikeStartEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattleSpikeStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("SPRIKE_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattleSpikeUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 2.0f)
	{
		SetRamdomPattern();
		return;
	}
}

void Grimm::GrimmBattleSpikeEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattlCastStartStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("CASTS_START_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattlCastStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isCastStartEnd_ == true)
	{
		isCastStartEnd_ = false;
		GrimmBattleManager_.ChangeState("BATTLE_CAST");
		return;
	}
}

void Grimm::GrimmBattlCastStartEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattlCastStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("CAST_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattlCastUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 2.f)
	{
		GrimmBattleManager_.ChangeState("BATTLE_CAST_END");
		return;

	}
}

void Grimm::GrimmBattlCastEnd(const StateInfo& _Info)
{
}

void Grimm::GrimmBattlCastEndStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("CAST_END_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
}

void Grimm::GrimmBattlCastEndUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isCastEndEnd_ == true)
	{
		isCastEndEnd_ = false;
		SetRamdomPattern();
		return;
	}

}

void Grimm::GrimmBattlCastEndEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattlStunStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattlStunUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattlStunEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattlStunBatStart(const StateInfo& _Info)
{
}

void Grimm::GrimmBattlStunBatUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattlStunBatEnd(const StateInfo& _Info)
{
}
