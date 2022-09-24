
#include "PreCompile.h"
#include "Grimm.h"
#include "KnightData.h"
#include "HollowKnightLevel.h"
#include "GrimmLevel.h"

#include "FadePink.h"
#include "BossRoarEffect.h"

#include "GrimmFire.h"
#include "GrimmBird.h"
#include "GrimmSpike.h"

void Grimm::GrimmBattleTeleportAppearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("TELEPORT_APPEAR_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	float4 KnightPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();
	//if (ChangeState_ == "BATTLE_AIR_DASH_START")
	//{
	//	if (GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y > -910)
	//	{
	//		SetRamdomPatternIgnoreAir();
	//	}
	//}

	// 텔레포트 나타나면서 팝업 위치를 여기서 정한다.
	auto castType_ = magic_enum::enum_cast<PatternType>(ChangeState_);
	PatternType PatternType_ = castType_.value();


	switch (PatternType_)
	{
	case PatternType::BATTLE_BALLOON_START:
		GetTransform().SetWorldPosition({ MapCenterX_, -700, static_cast<float>(Z_ORDER::Monster)});
		break;
	case PatternType::BATTLE_SLASH_START:
		if (KnightPos.x > MapCenterX_)
		{
			GetTransform().SetWorldPosition({ KnightPos.x - 300.f, -950.f, static_cast<float>(Z_ORDER::Monster) });
			SetMoveDirection(float4::RIGHT);
			GetRenderer()->GetTransform().PixLocalNegativeX();

		}

		else
		{
			GetTransform().SetWorldPosition({ KnightPos.x + 300.f,-950.f, static_cast<float>(Z_ORDER::Monster) });
			SetMoveDirection(float4::LEFT);
			GetRenderer()->GetTransform().PixLocalPositiveX();

		}



		break;
	case PatternType::BATTLE_AIR_DASH_START:

		if (KnightPos.x > MapCenterX_)
		{
			GetTransform().SetWorldPosition({ KnightPos.x - 300.f, -600.f, static_cast<float>(Z_ORDER::Monster) });
			SetMoveDirection(float4::RIGHT);
			//GetRenderer()->GetTransform().PixLocalNegativeX();


		}

		else
		{
			GetTransform().SetWorldPosition({ KnightPos.x + 300.f,-600.f, static_cast<float>(Z_ORDER::Monster) });
			SetMoveDirection(float4::LEFT);
			//GetRenderer()->GetTransform().PixLocalPositiveX();

		}

		break;
	case PatternType::BATTLE_SPIKE_START:

		if (KnightPos.x > MapCenterX_)
		{
			GetTransform().SetWorldPosition({ MapCenterX_ - 400.f, -950.f, static_cast<float>(Z_ORDER::Monster) });
			SetMoveDirection(float4::RIGHT);
			GetRenderer()->GetTransform().PixLocalPositiveX();
		}

		else
		{
			GetTransform().SetWorldPosition({ MapCenterX_ + 400.f,-950.f, static_cast<float>(Z_ORDER::Monster) });
			SetMoveDirection(float4::LEFT);
			GetRenderer()->GetTransform().PixLocalNegativeX();

		}

		break;
	case PatternType::BATTLE_CAST_START:

		if (KnightPos.x > MapCenterX_)
		{
			GetTransform().SetWorldPosition({ MapCenterX_ - 500.f, -950.f, static_cast<float>(Z_ORDER::Monster) });
			SetMoveDirection(float4::RIGHT);
			GetRenderer()->GetTransform().PixLocalNegativeX();

		}

		else
		{
			GetTransform().SetWorldPosition({ MapCenterX_ + 500.f,-950.f, static_cast<float>(Z_ORDER::Monster) });
			SetMoveDirection(float4::LEFT);
			GetRenderer()->GetTransform().PixLocalPositiveX();


		}
		break;
	default:
		break;
	}
	GetRenderer()->On();
	SetMonsterDirection();

}

void Grimm::GrimmBattleTeleportAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (ChangeState_ == "BATTLE_AIR_DASH_START")
	{
		if (GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition().y > -910)
		{
 			SetRamdomPatternIgnoreAir();
			GrimmBattleManager_.ChangeState("BATTLE_TELEPORT_APPEAR");
			return;
		}
	}

	if (isTeleportAppearEnd_ == true)
	{
		isTeleportAppearEnd_ = false;



		GrimmBattleManager_.ChangeState("BATTLE_STUN_BAT");
		return;
	}
}

void Grimm::GrimmBattleTeleportAppearEnd(const StateInfo& _Info)
{
	GetCollision()->On();

}

void Grimm::GrimmBattleTeleportDisappearStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("TELEPORT_DISAPPEAR_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
	GetCollision()->Off();

}

void Grimm::GrimmBattleTeleportDisappearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isTeleportDiappearEnd_ == true)
	{
		isTeleportDiappearEnd_ = false;
		GetRenderer()->Off();

	}
	if (_Info.StateTime > 1.f)
	{
		GrimmBattleManager_.ChangeState("BATTLE_TELEPORT_APPEAR");
		return;

		//_Info.StateTime = 0.f;
	

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


	FireCreateTimer_ = 0.0f;
	GetRenderer()->ChangeFrameAnimation("BALLON_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);
	{
		GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
		GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
		GrimmFire_->SetMoveDir(float4::DOWN, MoveType::Down);
	}

	{
		GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
		GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x ,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
		GrimmFire_->SetMoveDir(float4::DOWN, MoveType::DownRight);
	}

	{
		GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
		GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x ,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
		GrimmFire_->SetMoveDir(float4::DOWN, MoveType::DownLeft);
	}

	{
		GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
		GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2 , -20 });
		GrimmFire_->SetMoveDir(float4::RIGHT, MoveType::Right);
	}

	{
		GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
		GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
		GrimmFire_->SetMoveDir(float4::RIGHT, MoveType::RightDown);
	}

	{
		GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
		GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2 , -20 });
		GrimmFire_->SetMoveDir(float4::RIGHT, MoveType::RightUp);
	}

	{
		GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
		GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
		GrimmFire_->SetMoveDir(float4::LEFT, MoveType::Left);
	}

	{
		GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
		GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
		GrimmFire_->SetMoveDir(float4::LEFT, MoveType::LeftUp);
	}

	{
		GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
		GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2 , -20 });
		GrimmFire_->SetMoveDir(float4::LEFT, MoveType::LeftDown);
	}


}

void Grimm::GrimmBattleBalloonUpdate(float _DeltaTime, const StateInfo& _Info)
{
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::BossActtingShaking);

	FireCreateTimer_ += _DeltaTime;
	if (FireCreateTimer_ > 2.0f)
	{
		FireCreateTimer_ = 0.0f;
		{
			GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
			GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500/2, -20 });
			GrimmFire_->SetMoveDir(float4::DOWN, MoveType::Down);
		}

		{
			GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
			GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x ,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
			GrimmFire_->SetMoveDir(float4::DOWN, MoveType::DownRight);
		}

		{
			GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
			GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x ,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
			GrimmFire_->SetMoveDir(float4::DOWN, MoveType::DownLeft);
		}

		{
			GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
			GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2 , -20 });
			GrimmFire_->SetMoveDir(float4::RIGHT, MoveType::Right);
		}

		{
			GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
			GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
			GrimmFire_->SetMoveDir(float4::RIGHT, MoveType::RightDown);
		}

		{
			GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
			GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2 , -20 });
			GrimmFire_->SetMoveDir(float4::RIGHT, MoveType::RightUp);
		}

		{
			GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
			GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
			GrimmFire_->SetMoveDir(float4::LEFT, MoveType::Left);
		}

		{
			GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
			GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2, -20 });
			GrimmFire_->SetMoveDir(float4::LEFT, MoveType::LeftUp);
		}

		{
			GrimmFire* GrimmFire_ = GetLevel()->CreateActor<GrimmFire>();
			GrimmFire_->GetTransform().SetWorldPosition({ GetTransform().GetWorldPosition().x,  GetTransform().GetWorldPosition().y + 500 / 2 , -20 });
			GrimmFire_->SetMoveDir(float4::LEFT, MoveType::LeftDown);
		}


		
	}

	if (_Info.StateTime > 7.0f)
	{
		SetRamdomPattern();
	}
}

void Grimm::GrimmBattleBalloonEnd(const StateInfo& _Info)
{
	GetLevel<HollowKnightLevel>()->GetMainCameraManager()->ChangeCameraMove(CameraMode::TargetInRoomMove);

}

void Grimm::GrimmBattleAirDashStartStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("AIR_DASH_START_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);


	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();

	}

	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{

		GetRenderer()->GetTransform().PixLocalPositiveX();

	}

	AirDashDest_ = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();

	float4 KnihgtVec = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();
	float4 GrimmVec = float4({ GetTransform().GetWorldPosition().x, -925 }) - GetTransform().GetWorldPosition();

	GrimmVec.Normalize();
	KnihgtVec.Normalize();

	float4 Ro ;
	
	Ro = float4::DotProduct3D(GrimmVec, AirDashDest_);

	AirDashRotation_ = (Ro.x * GameEngineMath::PI / 180.f);



	AirDashDest_ = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
	AirDashDest_ = float4::NormalizeReturn(AirDashDest_);


}

void Grimm::GrimmBattleAirDashStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isDashStartEnd_ == true)
	{
		isDashStartEnd_ = false;
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
	GetRenderer()->GetTransform().PixLocalPositiveX();

	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{
		//GetRenderer()->GetTransform().PixLocalNegativeX();
		AirDashRotation_ = -AirDashRotation_;

	}

	GetRenderer()->GetTransform().SetWorldRotation({ 0,0,AirDashRotation_ });
}

void Grimm::GrimmBattleAirDashUpdate(float _DeltaTime, const StateInfo& _Info)
{

	float4 CurrentPos = GetTransform().GetWorldPosition();

	float4 Move = AirDashDest_ * 2000.f * _DeltaTime;

	GetTransform().SetWorldMove(Move);
	this->isPixelCheck(_DeltaTime, float4::ZERO);

	if (GetisOnGround() == true)
	{
		//int a = 0;
		GrimmBattleManager_.ChangeState("BATTLE_AIR_DASH_END");
		return;
	}
}

void Grimm::GrimmBattleAirDashEnd(const StateInfo& _Info)
{
	GetRenderer()->GetTransform().SetWorldRotation({ 0,0,0 });
}

void Grimm::GrimmBattleAirDashEndtStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("AIR_DASH_END_ANIMATION");
	GetRenderer()->ScaleToCutTexture(0);

	if (GetMoveDirection().CompareInt2D(float4::RIGHT))
	{
		GetRenderer()->GetTransform().PixLocalNegativeX();

	}

	if (GetMoveDirection().CompareInt2D(float4::LEFT))
	{

		GetRenderer()->GetTransform().PixLocalPositiveX();

	}
}

void Grimm::GrimmBattleAirDashEndtUpdate(float _DeltaTime, const StateInfo& _Info)
{

	//SetMonsterDirection();
	this->isPixelCheck(_DeltaTime, GetMoveDirection());

	// ======== Crawlid VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Grimm::MonsterVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}


	if (GetisWall() == false)
	{
		GetTransform().SetWorldMove(GetMoveDirection() * 1600.f * _DeltaTime);

	}

	else
	{
		GetTransform().SetWorldMove(float4::ZERO * 1000.f * _DeltaTime);

	}


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
	//SetMonsterDirection();
	//this->isPixelCheck(_DeltaTime, GetMoveDirection());

	// ======== Monster VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Grimm::MonsterVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}


	if (GetisWall() == false)
	{
		float4 Move = GetMoveDirection() * 2000.f * _DeltaTime;
		GetTransform().SetWorldMove(Move);
	}


	if (GetisWall() == true)
	{
		//int a = 0;
		GrimmBattleManager_.ChangeState("BATTLE_SLASH_UP");
		return;
	}

	//if (_Info.StateTime > 0.3f)
	//{
	//	isSlashEnd_ = false;
	//	GrimmBattleManager_.ChangeState("BATTLE_SLASH_UP");
	//	return;

	//}

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
	// ======== Monster VS WallColl ========
	if (GetWallCollision()->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Wall, CollisionType::CT_OBB2D,
		std::bind(&Grimm::MonsterVSWallCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		SetisCollWall(true);
	}
	else
	{
		SetisCollWall(false);

	}


	if (GetisWall() == false)
	{
		float4 Move = float4::UP * 1000.f * _DeltaTime;
		GetTransform().SetWorldMove(Move);
	}



	if (GetisWall() == true)
	{
		//int a = 0;
		GrimmBattleManager_.ChangeState("BATTLE_FIRE");
		return;
	}

	if (GetTransform().GetWorldPosition().y > -600)
	{
		isSlashEndEnd_ = false;
		SetRamdomPattern();		
		return;
	}
}

void Grimm::GrimmBattleSlashUpEnd(const StateInfo& _Info)
{
}


void Grimm::GrimmBattleFireStart(const StateInfo& _Info)
{
	GetRenderer()->Off();
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



	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 5350,-1000,static_cast<float>(Z_ORDER::Object) });
	}

	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 5200,-1000,static_cast<float>(Z_ORDER::Object) });
	}

	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 5050,-1000,static_cast<float>(Z_ORDER::Object) });
	}

	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 4900,-1000,static_cast<float>(Z_ORDER::Object) });
	}

	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 4750,-1000,static_cast<float>(Z_ORDER::Object) });
	}

	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 4600,-1000,static_cast<float>(Z_ORDER::Object) });
	}

	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 4450,-1000,static_cast<float>(Z_ORDER::Object) });
	}

	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 4300,-1000,static_cast<float>(Z_ORDER::Object) });
	}

	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 4150,-1000,static_cast<float>(Z_ORDER::Object) });
	}

	{
		GrimmSpike* GrimmSpike_ = GetLevel()->CreateActor<GrimmSpike>();
		GrimmSpike_->GetTransform().SetWorldPosition({ 4000,-1000,static_cast<float>(Z_ORDER::Object) });
	}
}


void Grimm::GrimmBattleSpikeStartUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (_Info.StateTime > 1.f)
	{
		isSprikeStartEnd_ = false;
		GrimmBattleManager_.ChangeState("BATTLE_SPIKE");
		return;
	}
	//if (isSprikeStartEnd_ == true)
	//{

	//}

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
	if (_Info.StateTime > 1.0f)
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

	GrimmBird* GrimmBird_ = GetLevel()->CreateActor<GrimmBird>();
	GrimmBird_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y, -20 });

	float4 Dir_ = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
	GrimmBird_->SetMoveDir(Dir_.NormalizeReturn());


}

void Grimm::GrimmBattlCastUpdate(float _DeltaTime, const StateInfo& _Info)
{
	BirdCreateTimer_ += _DeltaTime;



	if (BirdCreateTimer_ < 0.2f)
	{		
		BirdDir_ = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition() - GetTransform().GetWorldPosition();
	}

	if (BirdCreateTimer_ > 0.8f)
	{
		BirdCreateTimer_ = 0.0f;
		GrimmBird* GrimmBird_ = GetLevel()->CreateActor<GrimmBird>();
		GrimmBird_->GetTransform().SetWorldPosition({ this->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y, -20 });
		
		
		
		
		GrimmBird_->SetMoveDir(BirdDir_.NormalizeReturn());

	}

	


	if (_Info.StateTime > 3.f)
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
	for (int i = 0; i < 10; ++i)
	{
		GrimmStunBatList_.push_back(GetLevel()->CreateActor<GrimmStunBat>());
		float X = GameEngineRandom::MainRandom.RandomFloat(4400.f, 5200.f);
		float Y = GameEngineRandom::MainRandom.RandomFloat(-890.f, -700.f);


		GrimmStunBatList_.back()->GetTransform().SetWorldPosition({ X, Y, static_cast<float>(Z_ORDER::Monster)});


	}
}

void Grimm::GrimmBattlStunBatUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Grimm::GrimmBattlStunBatEnd(const StateInfo& _Info)
{
}

bool Grimm::MonsterVSWallCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
