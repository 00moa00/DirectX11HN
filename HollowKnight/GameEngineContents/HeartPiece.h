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

	float CompletAlpha_;
	float CompletScale_;

	float4 CompleteInitScale_;

	GameEngineUIRenderer* FleurRenderer_;
	GameEngineUIRenderer* MaskRenderer_;
	GameEngineUIRenderer* FlashRenderer_;

	GameEngineUIRenderer* CompleteMaskRenderer_;

	GameEngineStateManager HeartManager_;


public:
	void SetNewMaskPiece();

private:
	void HeartIdleStart(const StateInfo& _Info);
	void HeartIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void HeartIdleEnd(const StateInfo& _Info);

	void HeartWhiteStart(const StateInfo& _Info);
	void HeartWhiteUpdate(float _DeltaTime, const StateInfo& _Info);
	void HeartWhiteEnd(const StateInfo& _Info);

	void HeartMovingStart(const StateInfo& _Info);
	void HeartMovingUpdate(float _DeltaTime, const StateInfo& _Info);
	void HeartMovingEnd(const StateInfo& _Info);

	void HeartNewMaskStart(const StateInfo& _Info);
	void HeartNewMaskUpdate(float _DeltaTime, const StateInfo& _Info);
	void HeartNewMaskEnd(const StateInfo& _Info);
};

