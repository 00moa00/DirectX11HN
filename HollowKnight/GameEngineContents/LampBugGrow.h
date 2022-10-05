#pragma once
#include "MasterEffect.h"

// ���� :
class LampBugGrow : public MasterEffect
{
public:
	// constrcuter destructer
	LampBugGrow();
	~LampBugGrow();

	// delete Function
	LampBugGrow(const LampBugGrow& _Other) = delete;
	LampBugGrow(LampBugGrow&& _Other) noexcept = delete;
	LampBugGrow& operator=(const LampBugGrow& _Other) = delete;
	LampBugGrow& operator=(LampBugGrow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

