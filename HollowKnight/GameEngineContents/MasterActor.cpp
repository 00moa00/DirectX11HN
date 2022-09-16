#include "PreCompile.h"
#include "MasterActor.h"

MasterActor::MasterActor() 
	:
	MainRenderer_(nullptr),
	CollisionMap_(nullptr),
	MainCollision_(nullptr),
	GravityY(),
	JumpPower_(),
	CollisionSize_(),
	FallSpeed_(),
	Speed_ (),

	MoveDirection_(float4::ZERO),

	isMove_(true),
	isOnGround_(false),
	isWall_(false),
	isUpBlock_(false)
{
}

MasterActor::~MasterActor() 
{
}

void MasterActor::CreateRendererComponent(float4 _LocalScale, std::string _FileName, int _Index, int _Order)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture(_FileName, _Index);
	MainRenderer_->GetTransform().SetLocalScale({ _LocalScale.x, _LocalScale.y, 1});
	MainRenderer_->SetPivot(PIVOTMODE::BOT);
	//MainRenderer_->GetTransform().SetLocalPosition({ MainRenderer_->GetTransform().GetLocalPosition().x, MainRenderer_->GetTransform().GetLocalPosition().y, 0.1 });
	
}

void MasterActor::CreateRendererComponent(std::string _FileName, int _Index)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture(_FileName, _Index);
	MainRenderer_->GetTransform().SetLocalScale(MainRenderer_->GetCurTexture()->GetScale());

}

void MasterActor::CreateRendererComponent(std::string _FileName)
{
	MainRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	MainRenderer_->SetTexture(_FileName);
	MainRenderer_->GetTransform().SetLocalScale(MainRenderer_->GetCurTexture()->GetScale());
	MainRenderer_->SetPivot(PIVOTMODE::BOT);
}

void MasterActor::CreateCollisionComponent(float4 _LocalScale, int _Order)
{
	MainCollision_ = CreateComponent<GameEngineCollision>();
	MainCollision_->GetTransform().SetLocalScale(_LocalScale);
	MainCollision_->ChangeOrder(_Order);
}



void MasterActor::isPixelCheck(float _DeltaTime, float4 _CheckDir)
{
	//���� ��ġ
	float4 GroundPos = { GetTransform().GetLocalPosition().x ,
	-(GetTransform().GetLocalPosition().y - 2.f ) };



	//float4 GroudCheck = Pos;


	//GroudCheck.y -= 50.f;





	float4 WallPoint = float4::ZERO;
	_CheckDir.Normalize();

	if (_CheckDir.CompareInt2D(float4::RIGHT) == true)
	{
		WallPoint.x = 20.f;
		WallPoint.y = 2.f;
	}

	else if (_CheckDir.CompareInt2D(float4::LEFT) == true)
	{
		WallPoint.x = -20.f;
		WallPoint.y = 2.f;
	}

	else
	{
		WallPoint.x = 0.f;
		WallPoint.y = 0.f;

	}


	float4 WallPos = { GetTransform().GetLocalPosition().x + (  WallPoint.x ),
	-(GetTransform().GetLocalPosition().y + WallPoint.y) };


	float4 GrondColor = GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(GroundPos.ix(), GroundPos.iy());
	float4 WallColor = GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(WallPos.ix(), WallPos.iy());


	while (true)
	{

		float4 CheckPos = { GetTransform().GetLocalPosition().x ,
		-(GetTransform().GetLocalPosition().y + 1.f) };

		float4 CheckColor = GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(CheckPos.ix(), CheckPos.iy());

		if (CheckColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
		{
			GetTransform().SetWorldMove(float4::UP);
			continue;
		}
		else
		{
			break;
		}

	}


	if (GrondColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
	{
		SetisGround(true);
	}
	else
	{
		SetisGround(false);
	}
	if (WallColor.CompareInt4D(float4(0, 0, 1, 1)) == true/* && DirColor.CompareInt2D(float4(1.f, 0, 0, 1.f)) == true*/)
	{
		SetisWall(true);
	}
	else
	{
		SetisWall(false);
	}

}


void MasterActor::isUpBlockCheck(float _DeltaTime)
{



	float4 GetDirPos = { GetTransform().GetLocalPosition().x ,
	-(GetTransform().GetLocalPosition().y ) };

	//GetDirPos.x += GetCenterTop().x;
	GetDirPos.y -= GetCenterTop().y;


	float4 DirColor = GetCollisionMap()->GetCurTexture()->GetPixelToFloat4(GetDirPos.ix(), GetDirPos.iy());



	if (/*CenterColor.CompareInt4D(float4(0, 0, 1, 1)) == true ||*/ DirColor.CompareInt4D(float4(0, 0, 1, 1)) == true)
	{
		SetisUpBlock (true);
	}
	else
	{
		SetisUpBlock(false);
	}
}

float4 MasterActor::GetNextPos(float4 _DeltaTime)
{
	//this->SetMoveDirectionNormalize();

	GetMoveDirection().Normalize();

	return (GetMoveDirection() * _DeltaTime * GetSpeed());
}

float4 MasterActor::GetNextPos(float4 _DeltaTime, float4 Dir)
{
	return (Dir * _DeltaTime * GetSpeed());
}

float4 MasterActor::GetNextPos(float4 _DeltaTime, float _Speed)
{
	return  (float4::DOWN * _Speed * _DeltaTime );
}
