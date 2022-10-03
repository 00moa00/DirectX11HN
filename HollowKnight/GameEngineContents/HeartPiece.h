#pragma once
#include <GameEngineCore/CoreMinimal.h>


// ���� ���� ���� ���� ������ ���� �ִϸ��̼� ó��
// ���� �ð� ������ ���İ��� �������鼭 Off
// fsm ���� ����� �Ⱦ if������ ó���ߴµ� �׳� fsm���� �������� ��
class HeartPiece : public GameEngineActor
{
public:
	// constrcuter destructer
	HeartPiece();
	~HeartPiece();

	// delete Function
	HeartPiece(const HeartPiece& _Other) = delete;
	HeartPiece(HeartPiece&& _Other) noexcept = delete;
	HeartPiece& operator=(const HeartPiece& _Other) = delete;
	HeartPiece& operator=(HeartPiece&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isNewMask_;		// ����ũ�� ���� ��������
	bool isCompleteMask_;	// ����ũ�� �ϼ� ������

	bool isFleurAppeerEnd_;

	bool isLevel1End_;
	bool isLevel2End_;
	bool isLevel3End_;
	bool isLevel4End_;
	bool isFuseEnd_;

	float Alpha_;

	GameEngineUIRenderer* FleurRenderer_;
	GameEngineUIRenderer* MaskRenderer_;
	GameEngineUIRenderer* FlashRenderer_;

public:
	void SetNewMaskPiece();

};

