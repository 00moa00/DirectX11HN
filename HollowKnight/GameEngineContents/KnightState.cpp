#include "PreCompile.h"
#include "Knight.h"

void Knight::KnightStillStart(const StateInfo& _Info)
{
	if (_Info.PrevState == "RUN")
	{
		GetRenderer()->ChangeFrameAnimation("RUN_TO_IDLE_ANIMATION");

	}
	else
	{
		GetRenderer()->ChangeFrameAnimation("STILL_ANIMATION");
	}
}

void Knight::KnightStillUpdate(float _DeltaTime, const StateInfo& _Info)
{
	this->isOnGroundCheck(_DeltaTime);

	if (GetisOnGround() == false)
	{
		KnightManager_.ChangeState("FALL");
	}

	// ========== UPDATE ==========

	DoubleSlashTimer(_DeltaTime);

	if (GameEngineInput::GetInst()->IsFree("KnightJump") == true && isPressJumppingKey_ == true)
	{
		isPressJumppingKey_ = false;
	}

	if (GameEngineInput::GetInst()->IsFree("KnightUp") == true)
	{
		KnightLookUpTimer_ = 0.f; // Ÿ�̸� �ʱ�ȭ
	}

	if (GameEngineInput::GetInst()->IsFree("KnightDown") == true)
	{
		KnightLookDownTimer_ = 0.f; // Ÿ�̸� �ʱ�ȭ
	}

	if (GameEngineInput::GetInst()->IsDown("KnightRunMode") == true)
	{
		isRunMode_ = !isRunMode_;
	}

	// ========== ������Ʈ ���� ==========

 	if (GetisKnightMove() == true && isRunMode_ == false)
	{
		KnightManager_.ChangeState("WALK");
	}

	if (GetisKnightMove() == true && isRunMode_ == true)
	{
		KnightManager_.ChangeState("RUN");
	}


	if (GetisOnGround() == false)
	{
		KnightManager_.ChangeState("FALL");
	}



	// ����
	if (GameEngineInput::GetInst()->IsDown("KnightJump") == true && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	// �� ����
	if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsPress("KnightUp") == true)
	{
		KnightManager_.ChangeState("UP_SLASH");
	}

	// �⺻ ����
	if  (GameEngineInput::GetInst()->IsDown("KnightSlash") == true 
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true

		&& isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");
	}

	 //�޺� ����
	if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true 
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
		&& isPossibleDoubleSlash_ == true)
	{
		KnightManager_.ChangeState("DOUBLE_SLASH");
	}

	// �Ʒ� �ٶ󺸱�
	if (GameEngineInput::GetInst()->IsPress("KnightDown") == true )
	{
		LookDownTimerAndChangeState(_DeltaTime);
	}

	// �� �ٶ󺸱�
	if (GameEngineInput::GetInst()->IsPress("KnightUp") == true)
	{
		LookUpTimerAndChangeState(_DeltaTime);
	}

	// �� ����
	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = true;
		//GetRenderer()->ChangeFrameAnimation("MAP_OPEN_ANIMATION");
		KnightManager_.ChangeState("MAP_STILL");

	}

	// �뽬
	if (GameEngineInput::GetInst()->IsDown("KnightDash") == true)
	{
		KnightManager_.ChangeState("DASH");
	}


	// ����
	if (GameEngineInput::GetInst()->IsDown("KnightFocus") == true)
	{
		KnightManager_.ChangeState("FOCUS");
	}
}

void Knight::KnightWalkStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("WALK_ANIMATION");
}

void Knight::KnightWalkUpdate(float _DeltaTime, const StateInfo& _Info)
{
	DoubleSlashTimer(_DeltaTime);

	this->KnightDirectionCheck();
	this->isOnGroundCheck(_DeltaTime);
	this->isWallCheck(_DeltaTime);

	if (GetisWall() == true)
	{
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		if (true == GameEngineInput::GetInst()->IsPress("KnightLeft"))
		{

			if (PrevDirection_.CompareInt2D( float4::LEFT) == false)
			{
				PrevDirection_ = float4::LEFT;
				KnightManager_.ChangeState("WALK_TURN");
			}

			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
			PrevDirection_ = float4::LEFT;
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{

			if (PrevDirection_.CompareInt2D(float4::RIGHT) == false)
			{
				PrevDirection_ = float4::RIGHT;
				KnightManager_.ChangeState("WALK_TURN");
			}

			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
			PrevDirection_ = float4::RIGHT;
		}
	}

	else
	{
		KnightManager_.ChangeState("FALL");
	}


	if (GameEngineInput::GetInst()->IsDown("KnightRunMode") == true)
	{
		isRunMode_ = !isRunMode_;
	}

	// ========== ������Ʈ ���� ==========

	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump") )
	{
		isPressJumppingKey_ = false;
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == true)
	{
		KnightManager_.ChangeState("DOUBLE_SLASH");
	}

	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = true;
		GetRenderer()->ChangeFrameAnimation("MAP_OPEN_WALKING_ANIMATION");
		KnightManager_.ChangeState("MAP_WALKING");
	}

	if (GetisKnightMove() == false)
	{
		KnightManager_.ChangeState("STILL");
	}

	// �뽬
	if (GameEngineInput::GetInst()->IsDown("KnightDash") == true)
	{
		KnightManager_.ChangeState("DASH");
	}

	if (isRunMode_ == true)
	{
		KnightManager_.ChangeState("RUN");
	}

}

void Knight::KnightWalkTurnStart(const StateInfo& _Info)
{
	if (PrevDirection_.CompareInt2D(float4::LEFT) == true)
	{
		GetRenderer()->ChangeFrameAnimation("WALK_TURN_RIGHT_ANIMATION");
	}

	if (PrevDirection_.CompareInt2D(float4::RIGHT) == true)
	{
		GetRenderer()->ChangeFrameAnimation("WALK_TURN_LEFT_ANIMATION");
	}
}

void Knight::KnightWalkTurnUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isWalkTurnEnd_ == true)
	{
		isWalkTurnEnd_ = false;

		if (isRunMode_ == true)
		{
			KnightManager_.ChangeState("RUN");
		}

		else if (isRunMode_ == false)
		{
			KnightManager_.ChangeState("WALK");
		}
	}
}



void Knight::KnightLookDownStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("LOOK_DOWN_ANIMATION");
}

void Knight::KnightLookDownUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GameEngineInput::GetInst()->IsFree("KnightDown") == true)
	{
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightLookDownEnd(const StateInfo& _Info)
{
}

void Knight::KnightLookUpStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("LOOK_UP_ANIMATION");

}

void Knight::KnightLookUpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (GameEngineInput::GetInst()->IsFree("KnightUp") == true)
	{
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightLookUpEnd(const StateInfo& _Info)
{
}

void Knight::KnightJumpStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("JUMP_ANIMATION");

	isKnightActtingMove_ = false;
	ActtingMoveDirection_ = float4::ZERO;
	isPressJumppingKey_ = true;
	isPossibleDoubleJump_ = true;

	SetJumpPower({ 0, KnightJumpPower_, 0 });
}

void Knight::KnightJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	DoubleSlashTimer(_DeltaTime);

	if (true == GameEngineInput::GetInst()->IsPress("KnightJump"))
	{
		isKnihgtActtingMoveChack();
		KnightIsActtingCheck();

		isUpBlockCheck(_DeltaTime);
		isOnGroundCheck(_DeltaTime);
		isWallCheck(_DeltaTime);

		ActtingMoveDirection_.Normalize();
		SubJumpPower((float4::UP + -ActtingMoveDirection_ / 2) * GetGravity() * _DeltaTime);


		GetTransform().SetWorldMove(GetJumpPower() * GetJumpSpeed() * _DeltaTime);


		if (GetJumpPower().y <= 0.f || GetisUpBlock() == true || GetisWall() == true)
		{
			KnightManager_.ChangeState("FALL");
		}

		else
		{
			KnightActtingDirectionCheck();
		}


	}

	// ========== ������Ʈ ���� ==========


	// �� ����
	if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsPress("KnightUp") == true)
	{
		KnightManager_.ChangeState("UP_SLASH");
	}

	// �Ʒ� ����
	if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsPress("KnightDown") == true)
	{
		KnightManager_.ChangeState("DOWN_SLASH");
	}

	// �⺻ ����
	if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
		&& GameEngineInput::GetInst()->IsFree("KnightDown") == true

		&& isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");
	}

	//�޺� ����
	if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true
		&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
		&& isPossibleDoubleSlash_ == true)
	{

		KnightManager_.ChangeState("DOUBLE_SLASH");
	}


	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		KnightManager_.ChangeState("FALL");
	}
}

void Knight::KnightJumpEnd(const StateInfo& _Info)
{
	SetJumpPower({ 0, KnightJumpPower_, 0 });

	this->SetisGround(false);
}

void Knight::KnightDoubleJumpStart(const StateInfo& _Info)
{
	isPossibleDoubleJump_ = false;
	isDoubleJumpEnd_ = false;

	GetRenderer()->ChangeFrameAnimation("DOUBLE_JUMP_ANIMATION");

	SetJumpPower({ 0, KnightDoubleJumpPower_, 0 });
}

void Knight::KnightDoubleJumpUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (true == GameEngineInput::GetInst()->IsPress("KnightJump"))
	{
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();
		this->isUpBlockCheck(_DeltaTime);

		ActtingMoveDirection_.Normalize();
		SubJumpPower((float4::UP + -ActtingMoveDirection_ / 2) * GetGravity() * _DeltaTime);

		GetTransform().SetWorldMove(GetJumpPower() * GetJumpSpeed() * _DeltaTime);


		if (isDoubleJumpEnd_ == true || GetisUpBlock() == true)
		{
			KnightManager_.ChangeState("FALL");
		}
	}

	// ========== ������Ʈ ���� ==========

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		KnightManager_.ChangeState("FALL");
	}

}

void Knight::KnightDoubleJumpEnd(const StateInfo& _Info)
{
	//GetRenderer()->GetTransform().SetLocalScale({ 349, 186, 1 });
	//GetRenderer()->SetPivot(PIVOTMODE::BOT);

	this->SetisGround(false);

}

void Knight::KnightLandStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("LAND_ANIMATION");
}

void Knight::KnightLandUpdate(float _DeltaTime, const StateInfo& _Info)
{
	if (isLandEnd_ == true)
	{
		isLandEnd_ = false;
		KnightManager_.ChangeState("STILL");
	}

}

void Knight::KnightLandEnd(const StateInfo& _Info)
{
}

void Knight::KnightFallStart(const StateInfo& _Info)
{
	isKnightActtingMove_ = false;
	ActtingMoveDirection_ = float4::ZERO;
	
	SetMoveDirection(float4::DOWN);

	GetRenderer()->ChangeFrameAnimation("FAll_ANIMATION");
}

void Knight::KnightFallUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//isKnihgtActtingMoveChack();
	//KnightActtingDirectionCheck();
	//KnightIsActtingCheck();
	//isWallCheck(_DeltaTime);
	isOnGroundCheck(_DeltaTime);
	//DoubleSlashTimer(_DeltaTime);

	if (GetisOnGround() == true)
	{
		KnightManager_.ChangeState("LAND");
		return;
	}

	else
	{
		GetTransform().SetWorldMove(float4::DOWN * 800 * _DeltaTime);

	}



	//ActtingMoveDirection_.Normalize();

	//if (GetisWall() == true)
	//{
	//	ActtingMoveDirection_ = float4::ZERO;
	//}

	//else if (GetisOnGround() == true)
	//{
	//	KnightManager_.ChangeState("LAND");
	//	return;
	//}

	//else
	//{
	//	GetTransform().SetWorldMove(float4::DOWN/* + ActtingMoveDirection_ / 2*/ * 800 * _DeltaTime);

	//}




	// ========== ������Ʈ ���� ==========


	//// �� ����
	//if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
	//	&& GameEngineInput::GetInst()->IsPress("KnightUp") == true)
	//{
	//	KnightManager_.ChangeState("UP_SLASH");
	//}

	//// �Ʒ� ����
	//if (GameEngineInput::GetInst()->IsPress("KnightSlash") == true
	//	&& GameEngineInput::GetInst()->IsPress("KnightDown") == true)
	//{
	//	KnightManager_.ChangeState("DOWN_SLASH");
	//}

	//// �⺻ ����
	//if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true
	//	&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
	//	&& GameEngineInput::GetInst()->IsFree("KnightDown") == true
	//	&& isPossibleDoubleSlash_ == false)
	//{
	//	KnightManager_.ChangeState("SLASH");
	//}

	////�޺� ����
	//if (GameEngineInput::GetInst()->IsDown("KnightSlash") == true
	//	&& GameEngineInput::GetInst()->IsFree("KnightUp") == true
	//	&& isPossibleDoubleSlash_ == true)
	//{
	//	KnightManager_.ChangeState("DOUBLE_SLASH");
	//}

	////���� ����
	//if (true == GameEngineInput::GetInst()->IsDown("KnightJump") && isPossibleDoubleJump_ == true)
	//{
	//	KnightManager_.ChangeState("DOUBLE_JUMP");
	//}
}

void Knight::KnightFallEnd(const StateInfo& _Info)
{
	if (isKnightActtingMove_ == true)
	{
		SetMoveDirection(ActtingMoveDirection_);
	}
}

void Knight::KnightDashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DASH_ANIMATION");
	KnightDashTimer_ = 0.f;
	SetSpeed(1200.f);

}

void Knight::KnightDashUpdate(float _DeltaTime, const StateInfo& _Info)
{

	KnightDashTimer_ += _DeltaTime;
	//DoubleSlashTimer(_DeltaTime);

	this->KnightDirectionCheck();
	this->isOnGroundCheck(_DeltaTime);
	this->isWallCheck(_DeltaTime);

	if (GetisWall() == true)
	{
		SetMoveDirection(float4::ZERO);
		GetTransform().SetWorldMove(float4::ZERO * GetSpeed() * _DeltaTime);
		//KnightManager_.ChangeState("FALL");
	}

	else if (GetisOnGround() == true)
	{
		GetMoveDirection().Normalize();
		GetTransform().SetWorldMove(GetMoveDirection() * GetSpeed() * _DeltaTime);

	}

	else
	{
		KnightManager_.ChangeState("FALL");
	}


	// ========== ������Ʈ ���� ==========

	//if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	//{
	//	KnightManager_.ChangeState("JUMP");
	//}

	//if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	//{
	//	isPressJumppingKey_ = false;
	//}

	//if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == false)
	//{
	//	KnightManager_.ChangeState("SLASH");
	//}

	//if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == true)
	//{
	//	KnightManager_.ChangeState("DOUBLE_SLASH");
	//}



	if (KnightDashTimer_ > 0.4f)
	{
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightDashEnd(const StateInfo& _Info)
{
	SetSpeed(300.f);
}

void Knight::KnightFocusStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("FOCUS_ANIMATION");
}

void Knight::KnightFocusUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (GameEngineInput::GetInst()->IsFree("KnightFocus") == true)
	{
		KnightManager_.ChangeState("STILL");
	}

	if (isFocusEnd_ == true)
	{
		isFocusEnd_ = false;
		KnightManager_.ChangeState("STILL");
	}

}

void Knight::KnightFocusEnd(const StateInfo& _Info)
{
}

void Knight::KnightRunStart(const StateInfo& _Info)
{
	if (_Info.PrevState == "STILL" || _Info.PrevState == "WALK")
	{
		GetRenderer()->ChangeFrameAnimation("IDLE_TO_RUN_ANIMATION");
	}

	else
	{
		GetRenderer()->ChangeFrameAnimation("RUN_ANIMATION");
	}

}

void Knight::KnightRunUpdate(float _DeltaTime, const StateInfo& _Info)
{
	DoubleSlashTimer(_DeltaTime);

	this->KnightDirectionCheck();
	this->isOnGroundCheck(_DeltaTime);
	this->isWallCheck(_DeltaTime);

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

			if (PrevDirection_.CompareInt2D(float4::LEFT) == false)
			{
				PrevDirection_ = float4::LEFT;
				KnightManager_.ChangeState("WALK_TURN");
			}

			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
			PrevDirection_ = float4::LEFT;
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{

			if (PrevDirection_.CompareInt2D(float4::RIGHT) == false)
			{
				PrevDirection_ = float4::RIGHT;
				KnightManager_.ChangeState("WALK_TURN");
			}

			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
			PrevDirection_ = float4::RIGHT;
		}
	}


	else
	{
		KnightManager_.ChangeState("FALL");
	}


	// ========== ������Ʈ ���� ==========

	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == false)
	{
		KnightManager_.ChangeState("SLASH");
	}

	if (true == GameEngineInput::GetInst()->IsDown("KnightSlash") && isPossibleDoubleSlash_ == true)
	{
		KnightManager_.ChangeState("DOUBLE_SLASH");
	}

	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = true;
		GetRenderer()->ChangeFrameAnimation("MAP_OPEN_WALKING_ANIMATION");
		KnightManager_.ChangeState("MAP_WALKING");
	}

	if (GetisKnightMove() == false)
	{
		KnightManager_.ChangeState("STILL");
	}

	// �뽬
	if (GameEngineInput::GetInst()->IsDown("KnightDash") == true)
	{
		KnightManager_.ChangeState("DASH");
	}
}

void Knight::KnightRunEnd(const StateInfo& _Info)
{
}

void Knight::KnightSlashStart(const StateInfo& _Info)
{
	isPossibleDoubleSlash_ = false;
	KnightSlashTimer_ = 0.f;
	GetRenderer()->ChangeFrameAnimation("SLASH_ANIMATION");
	KnightSlashEffect_->SetAnimationSlash();
}

void Knight::KnightSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	KnightDirectionCheck();
	isOnGroundCheck(_DeltaTime);
	isWallCheck(_DeltaTime);

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

	// �����߿� �����Ѵٸ� �ִϸ��̼��� ���� ������ ���� ������Ʈ�� �̵��ϸ� �ȵȴ�. => ���� : �ִϸ��̼� ó��
	// �׷��� ������ ���⼭ �߷�ó���� ���� �ϴ���
	else if (GetisOnGround() == false && GetisWall() == false)
	{
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();
	
		DoubleSlashTimer(_DeltaTime);

		ActtingMoveDirection_.Normalize();

		if (GetisWall() == true)
		{
			ActtingMoveDirection_ = float4::ZERO;
		}

		GetTransform().SetWorldMove((GetFallDownDirection() + ActtingMoveDirection_ / 2) * GetGravity() * GetFallSpeed() * _DeltaTime);

		if (isSlashEnd_ == true)
		{
			KnightManager_.ChangeState("FALL");

		}

	}

	KnightSlashEffect_->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());


	// ========== ������Ʈ ���� ==========

	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}


	//�ִϸ��̼��� ������ 
	if (isSlashEnd_ == true)
	{
		isSlashEnd_ = false;
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightSlashEnd(const StateInfo& _Info)
{
	isPossibleDoubleSlash_ = true;
}

void Knight::KnightDoubleSlashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DOUBLE_SLASH_ANIMATION");
	KnightSlashEffect_->SetAnimationDoubleSlash();
}

void Knight::KnightDoubleSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{
	KnightSlashEffect_->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());

	//�ִϸ��̼��� ������ 
	if (isDoubleSlashEnd_ == true)
	{
		isDoubleSlashEnd_ = false;
		KnightManager_.ChangeState("STILL");
	}

}

void Knight::KnightDoubleSlashEnd(const StateInfo& _Info)
{
	isPossibleDoubleSlash_ = false;
}

void Knight::KnightUpSlashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("UP_SLASH_ANIMATION");
	KnightSlashEffect_->SetAnimationUpSlash();
}

void Knight::KnightUpSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{

	//KnightSlashEffect_->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());


	KnightDirectionCheck();
	isOnGroundCheck(_DeltaTime);
	isWallCheck(_DeltaTime);

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

	// �����߿� �����Ѵٸ� �ִϸ��̼��� ���� ������ ���� ������Ʈ�� �̵��ϸ� �ȵȴ�. => ���� : �ִϸ��̼� ó��
	// �׷��� ������ ���⼭ �߷�ó���� ���� �ϴ���
	else if (GetisOnGround() == false && GetisWall() == false)
	{
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();

		DoubleSlashTimer(_DeltaTime);

		ActtingMoveDirection_.Normalize();

		if (GetisWall() == true)
		{
			ActtingMoveDirection_ = float4::ZERO;
		}

		GetTransform().SetWorldMove((GetFallDownDirection() + ActtingMoveDirection_ / 2) * GetGravity() * GetFallSpeed() * _DeltaTime);

		if (isUpSlashEnd_ == true)
		{
			KnightManager_.ChangeState("FALL");

		}

	}

	KnightSlashEffect_->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());


	// ========== ������Ʈ ���� ==========

	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}


	//�ִϸ��̼��� ������ 
	if (isUpSlashEnd_ == true)
	{
		isUpSlashEnd_ = false;
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightUpSlashEnd(const StateInfo& _Info)
{
}

void Knight::KnightDownSlashStart(const StateInfo& _Info)
{
	GetRenderer()->ChangeFrameAnimation("DOWN_SLASH_ANIMATION");
	KnightSlashEffect_->SetAnimationDownSlash();
}

void Knight::KnightDownSlashUpdate(float _DeltaTime, const StateInfo& _Info)
{

	KnightDirectionCheck();
	isOnGroundCheck(_DeltaTime);
	isWallCheck(_DeltaTime);

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

	// �����߿� �����Ѵٸ� �ִϸ��̼��� ���� ������ ���� ������Ʈ�� �̵��ϸ� �ȵȴ�. => ���� : �ִϸ��̼� ó��
	// �׷��� ������ ���⼭ �߷�ó���� ���� �ϴ���
	else if (GetisOnGround() == false && GetisWall() == false)
	{
		isKnihgtActtingMoveChack();
		KnightActtingDirectionCheck();
		KnightIsActtingCheck();

		DoubleSlashTimer(_DeltaTime);

		ActtingMoveDirection_.Normalize();

		if (GetisWall() == true)
		{
			ActtingMoveDirection_ = float4::ZERO;
		}

		GetTransform().SetWorldMove((GetFallDownDirection() + ActtingMoveDirection_ / 2) * GetGravity() * GetFallSpeed() * _DeltaTime);

		if (isDownSlashEnd_ == true)
		{
			KnightManager_.ChangeState("FALL");

		}

	}

	KnightSlashEffect_->GetTransform().SetWorldPosition(this->GetTransform().GetWorldPosition());


	// ========== ������Ʈ ���� ==========

	if (true == GameEngineInput::GetInst()->IsPress("KnightJump") && isPressJumppingKey_ == false)
	{
		KnightManager_.ChangeState("JUMP");
	}

	if (true == GameEngineInput::GetInst()->IsFree("KnightJump"))
	{
		isPressJumppingKey_ = false;
	}


	//�ִϸ��̼��� ������ 
	if (isDownSlashEnd_ == true)
	{
		isDownSlashEnd_ = false;
		KnightManager_.ChangeState("STILL");
	}
}

void Knight::KnightDownSlashEnd(const StateInfo& _Info)
{
}

void Knight::KnightMapStillStart(const StateInfo& _Info)
{
	if (_Info.PrevState == "STILL")
	{
		GetRenderer()->ChangeFrameAnimation("MAP_OPEN_ANIMATION");

	}

	if (_Info.PrevState == "MAP_WALKING")
	{
		GetRenderer()->ChangeFrameAnimation("MAP_STILL_ANIMATION");
	}
}

void Knight::KnightMapStillUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = false;
		KnightManager_.ChangeState("STILL");
	}

	if (GetisKnightMove() == true)
	{
		//GetRenderer()->ChangeFrameAnimation("MAP_WALKING_ANIMATION");
		KnightManager_.ChangeState("MAP_WALKING");
	}


}

void Knight::KnightMapStillEnd(const StateInfo& _Info)
{
}

void Knight::KnightMapWalkinglStart(const StateInfo& _Info)
{
	if (_Info.PrevState == "MAP_STILL")
	{
		GetRenderer()->ChangeFrameAnimation("MAP_WALKING_ANIMATION");
	}

	if (_Info.PrevState == "MAP_WALKING_TURN")
	{
		GetRenderer()->ChangeFrameAnimation("MAP_WALKING_ANIMATION");
	}
}

void Knight::KnightMapWalkinglUpdate(float _DeltaTime, const StateInfo& _Info)
{
	this->KnightDirectionCheck();
	this->isOnGroundCheck(_DeltaTime);
	this->isWallCheck(_DeltaTime);

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

			if (PrevDirection_.CompareInt2D(float4::LEFT) == false)
			{
				PrevDirection_ = float4::LEFT;
				KnightManager_.ChangeState("MAP_WALKING_TURN");
			}

			GetTransform().SetWorldMove(float4::LEFT * GetSpeed() * _DeltaTime);
			PrevDirection_ = float4::LEFT;
		}


		if (true == GameEngineInput::GetInst()->IsPress("KnightRight"))
		{

			if (PrevDirection_.CompareInt2D(float4::RIGHT) == false)
			{
				PrevDirection_ = float4::RIGHT;
				KnightManager_.ChangeState("MAP_WALKING_TURN");
			}

			GetTransform().SetWorldMove(float4::RIGHT * GetSpeed() * _DeltaTime);
			PrevDirection_ = float4::RIGHT;
		}
	}


	else
	{
		isLookMap_ = false;
		KnightManager_.ChangeState("FALL");
	}


	// ========== ������Ʈ ���� ==========


	if (GetisKnightMove() == false)
	{
		KnightManager_.ChangeState("MAP_STILL");
	}

	if (GameEngineInput::GetInst()->IsDown("KnightLookMap") == true)
	{
		isLookMap_ = false;
		KnightManager_.ChangeState("WALK");

	}
}

void Knight::KnightMapWalkinglEnd(const StateInfo& _Info)
{
}

void Knight::KnightMapWalkingTurnlStart(const StateInfo& _Info)
{
	if (PrevDirection_.CompareInt2D(float4::LEFT) == true)
	{
		GetRenderer()->ChangeFrameAnimation("MAP_WALKING_TURN_RIGHT_ANIMATION");
	}

	if (PrevDirection_.CompareInt2D(float4::RIGHT) == true)
	{
		GetRenderer()->ChangeFrameAnimation("MAP_WALKING_TURN_LEFT_ANIMATION");
	}
}

void Knight::KnightMapWalkingTurnlUpdate(float _DeltaTime, const StateInfo& _Info)
{

	if (isMapWalkTurnEnd_ == true)
	{
		isMapWalkTurnEnd_ = false;
		KnightManager_.ChangeState("MAP_WALKING");
	}
}

void Knight::KnightMapWalkingTurnlEnd(const StateInfo& _Info)
{
}

void Knight::KnightMapSitLooklStart(const StateInfo& _Info)
{
}

void Knight::KnightMapSitLooklUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Knight::KnightMapSitLooklEnd(const StateInfo& _Info)
{
}

void Knight::KnightMapSitWritelStart(const StateInfo& _Info)
{
}

void Knight::KnightMapSitWritelUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Knight::KnightMapSitWritelEnd(const StateInfo& _Info)
{
}

