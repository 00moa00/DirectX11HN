#pragma once
#include "MasterEffect.h"

// ���� : ���� ���������� ��Ī �ϴ°�
class KnightSlashAttackEffect : public MasterEffect
{
public:
	// constrcuter destructer
	KnightSlashAttackEffect();
	~KnightSlashAttackEffect();

	// delete Function
	KnightSlashAttackEffect(const KnightSlashAttackEffect& _Other) = delete;
	KnightSlashAttackEffect(KnightSlashAttackEffect&& _Other) noexcept = delete;
	KnightSlashAttackEffect& operator=(const KnightSlashAttackEffect& _Other) = delete;
	KnightSlashAttackEffect& operator=(KnightSlashAttackEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

public:
	void EffectOn();

};

