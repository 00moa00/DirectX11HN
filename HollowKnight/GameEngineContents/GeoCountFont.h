#include <GameEngineCore/CoreMinimal.h>
#include <GameEngineCore/GameEngineFontRenderer.h>

// ���� :
class GeoCountFont : public GameEngineActor
{
public:
	// constrcuter destructer
	GeoCountFont();
	~GeoCountFont();

	// delete Function
	GeoCountFont(const GeoCountFont& _Other) = delete;
	GeoCountFont(GeoCountFont&& _Other) noexcept = delete;
	GeoCountFont& operator=(const GeoCountFont& _Other) = delete;
	GeoCountFont& operator=(GeoCountFont&& _Other) noexcept = delete;

protected:
	void Start()override;
	void Update(float _DeltatTime)override;
	void LevelStartEvent() override;
	void LevelEndEvent() override;

private:

	bool isPossibleCounting_;

	int CurrentNum_;		// �������
	int PrevNum_;			// ������� + ī���� �� ���� < �� ����ϱ� ������ ���� �����
	int CountingNum_;		// ī���� ��


	float CountingTimer_;

	GameEngineFontRenderer* GameEngineFontRenderer_;

	GameEngineStateManager FontStateManager_;

public:
	void CreateFontRenderer(int _Num, float _FontSize, float4 _Position);

public:
	//================================
	//    Setter
	//================================
	void SetCountingFont(int _CoutingNum);
	void SetDisCountingFont(int _CoutingNum);

	//================================
	//    Getter
	//================================
	GameEngineFontRenderer* GetFontRenderer()
	{
		return GameEngineFontRenderer_;
	}

	bool SetPossibleCounting()
	{
		if (FontStateManager_.GetCurStateStateName() == "COUNTUING_IDLE")
		{
			isPossibleCounting_ = true;

		}

		else
		{
			isPossibleCounting_ = false;

		}

		return isPossibleCounting_;
	}

	//================================
	//    Bind State
	//================================
	void FontCountingStart(const StateInfo& _Info);
	void FontCountingUpdate(float _DeltaTime, const StateInfo& _Info);
	void FontCountingEnd(const StateInfo& _Info);

	void FontDisCountingStart(const StateInfo& _Info);
	void FontDisCountingUpdate(float _DeltaTime, const StateInfo& _Info);
	void FontDisCountingEnd(const StateInfo& _Info);

	void FontIdleStart(const StateInfo& _Info);
	void FontIdleUpdate(float _DeltaTime, const StateInfo& _Info);
	void FontIdleEnd(const StateInfo& _Info);

};

