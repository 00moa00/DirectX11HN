#pragma once
#include <GameEngineCore/CoreMinimal.h>


// �� �������� �ִϸ��̼��� �ִ�.
// �ٴڿ� ������ �ִϸ��̼� ����ϰ� �״´�
// ����Ʈ �� -> ���� ��Ҿ��� �� ������. 
// ����Ʈ ���� -> ���� ������� ������ �ʰ�(�ȼ��浹�� ���� �ʰ�), �������� �۾�����. 
class MonsterHitParticle : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterHitParticle();
	~MonsterHitParticle();

	// delete Function
	MonsterHitParticle(const MonsterHitParticle& _Other) = delete;
	MonsterHitParticle(MonsterHitParticle&& _Other) noexcept = delete;
	MonsterHitParticle& operator=(const MonsterHitParticle& _Other) = delete;
	MonsterHitParticle& operator=(MonsterHitParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	bool isImpact_;

	float Scale_;
	float Speed_;

	std::vector<GameEngineTextureRenderer*> ParticleList_;
	std::vector<float4> DirList_;
	std::vector<float4> InitDir_;
	std::vector<float4> InitScale_;
	std::vector<bool> isEndMove_;

	std::vector<float4> StartDirList_;

private:
	void isPixelCheck(float _DeltaTime);

public:
	void SetDir(float4 _Dir);
	void SetTexWhite();
	void SetisImpact(bool _b);
};

