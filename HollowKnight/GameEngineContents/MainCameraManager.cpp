#include "PreCompile.h"
#include "MainCameraManager.h"

MainCameraManager::MainCameraManager() 
{
}

MainCameraManager::~MainCameraManager() 
{
}


void MainCameraManager::MainCameraMoveLimitWindow(float4 _TargetPos, float4 _MapSize)
{
	//ī�޶� ���ٸ�
	if (GetLevel()->GetMainCameraActor() == nullptr)
	{
		return;
	}

	//ī�޶�� �÷��̾ ���󰣴�.
	//GetMainCameraActorTransform().SetLocalPosition(Knight_->GetTransform().GetLocalPosition());
	//MainCameraPosition_ = GetMainCameraActorTransform().GetLocalPosition();


	float4 CurrentPos = GetLevel()->GetMainCameraActorTransform().GetWorldPosition();
	float4 DestPos = _TargetPos;
	float4 MoveCamera = float4::Lerp(CurrentPos, DestPos, GameEngineTime::GetDeltaTime() * 10.f);



	GetLevel()->GetMainCameraActorTransform().SetWorldPosition({ MoveCamera.x,MoveCamera.y,  -1800.0f });
	float4 MainCameraPosition = GetLevel()->GetMainCameraActorTransform().GetLocalPosition();

	//ī�޶��� ��ġ - ������ �������� x�� 0�̶��
	if (0 > MainCameraPosition.x - GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = 0 + GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

	if (_MapSize.x < MainCameraPosition.x + GameEngineWindow::GetInst()->GetScale().hix())
	{
		MainCameraPosition.x = _MapSize.x - GameEngineWindow::GetInst()->GetScale().hix();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

	if (0 < MainCameraPosition.y + GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = 0 - GameEngineWindow::GetInst()->GetScale().hiy();
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}

	if (-_MapSize.y > MainCameraPosition.y - GameEngineWindow::GetInst()->GetScale().hiy())
	{
		MainCameraPosition.y = -(_MapSize.y - (GameEngineWindow::GetInst()->GetScale().hiy()));
		GetLevel()->GetMainCameraActorTransform().SetWorldPosition(MainCameraPosition);
	}
}

