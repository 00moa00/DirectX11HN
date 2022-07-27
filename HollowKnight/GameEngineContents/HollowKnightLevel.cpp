#include "PreCompile.h"
#include "HollowKnightLevel.h"
#include "GlobalContentsValue.h"
#include <GameEngineCore/GameEngineCameraActor.h>
HollowKnightLevel::HollowKnightLevel() 
	:
	MasterMap_(nullptr),
	Knight_(nullptr),
	MainCameraPosition_()
{
}

HollowKnightLevel::~HollowKnightLevel() 
{
}

void HollowKnightLevel::CraateMasterMapActor()
{
	MasterMap_ = CreateActor<MasterMap>();

}

void HollowKnightLevel::CreateKnightActor()
{
	Knight_ = CreateActor<Knight>();

}

void HollowKnightLevel::CameraMoveWindowLimit()
{

	//ī�޶� ���ٸ�
	if (GetMainCameraActor() == nullptr)
	{
		return;
	}

	//ī�޶�� �÷��̾ ���󰣴�.
	GetMainCameraActorTransform().SetLocalPosition(Knight_->GetTransform().GetLocalPosition());
	MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();

	//ī�޶��� ��ġ - ������ �������� x�� 0�̶��
	if ( 0 > MainCameraPosition_.x - GameEngineWindow::GetInst()->GetScale().hix() )
	{
		MainCameraPosition_.x = 0 + GameEngineWindow::GetInst()->GetScale().hix();
		GetMainCameraActorTransform().SetLocalPosition(MainCameraPosition_);
	}

	if (MainMapSize_.x < MainCameraPosition_.x + GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition_.x = MainMapSize_.x - GameEngineWindow::GetInst()->GetScale().hix();
		GetMainCameraActorTransform().SetLocalPosition(MainCameraPosition_);
	}



	if (0 < MainCameraPosition_.y + GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition_.y = 0 - GameEngineWindow::GetInst()->GetScale().hiy();
		GetMainCameraActorTransform().SetLocalPosition(MainCameraPosition_);
	}


	if (-MainMapSize_.y > MainCameraPosition_.y - GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition_.y = -(MainMapSize_.y - GameEngineWindow::GetInst()->GetScale().hiy());
		GetMainCameraActorTransform().SetLocalPosition(MainCameraPosition_);
	}

}

void HollowKnightLevel::SetMainMapSize(float4 _MapSize)
{
	MainMapSize_ = _MapSize;

}

