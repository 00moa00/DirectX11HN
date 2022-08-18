#pragma once
#include "MasterUI.h"

// ���� :
class CharmPage : public MasterUI
{
public:
	// constrcuter destructer
	CharmPage();
	~CharmPage();

	// delete Function
	CharmPage(const CharmPage& _Other) = delete;
	CharmPage(CharmPage&& _Other) noexcept = delete;
	CharmPage& operator=(const CharmPage& _Other) = delete;
	CharmPage& operator=(CharmPage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

