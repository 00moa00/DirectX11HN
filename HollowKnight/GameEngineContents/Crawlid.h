#pragma once
#include "Monster.h"
// ���� :
class Crawlid : public Monster
{
public:
	// constrcuter destructer
	Crawlid();
	~Crawlid();

	// delete Function
	Crawlid(const Crawlid& _Other) = delete;
	Crawlid(Crawlid&& _Other) noexcept = delete;
	Crawlid& operator=(const Crawlid& _Other) = delete;
	Crawlid& operator=(Crawlid&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineStateManager CrawlidManager_;

	GameEngineRenderer* GameEngineRenderer_;

private:
	//================================
	//    Bind State
	//================================
	void CrawlidStillStart(const StateInfo& _Info);
	void CrawlidStillUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidStillEnd(float _DeltaTime, const StateInfo& _Info);

	void CrawlidWalkStart(const StateInfo& _Info);
	void CrawlidWalkUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidWalkEnd(const StateInfo& _Info);

	void CrawlidFallStart(const StateInfo& _Info);
	void CrawlidFallUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidFallEnd(const StateInfo& _Info);

	void CrawlidTurnStart(const StateInfo& _Info);
	void CrawlidTurnUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidTurnEnd(const StateInfo& _Info);

	void CrawlidStunStart(const StateInfo& _Info);
	void CrawlidStunUpdate(float _DeltaTime, const StateInfo& _Info);
	void CrawlidStunEnd(const StateInfo& _Info);
};

