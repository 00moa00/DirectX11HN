#pragma once
#include "MasterPage.h"

// ���� : ����ȭ ����
class MapPage : public MasterPage
{
public:
	// constrcuter destructer
	MapPage();
	~MapPage();

	// delete Function
	MapPage(const MapPage& _Other) = delete;
	MapPage(MapPage&& _Other) noexcept = delete;
	MapPage& operator=(const MapPage& _Other) = delete;
	MapPage& operator=(MapPage&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

