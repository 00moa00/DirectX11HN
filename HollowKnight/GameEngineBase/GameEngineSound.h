#pragma once
#include "GameEngineNameObject.h"
#include "ThirdParty/inc/fmod.hpp"
#include "GameEngineFile.h"
#include <map>

class GameEngineSoundHollowKnight;
// ���� :
class GameEngineSound : public GameEngineNameObject
{
public:
	// constrcuter destructer
	GameEngineSound();
	~GameEngineSound();

	// delete Function
	GameEngineSound(const GameEngineSound& _Other) = delete;
	GameEngineSound(GameEngineSound&& _Other) noexcept = delete;
	GameEngineSound& operator=(const GameEngineSound& _Other) = delete;
	GameEngineSound& operator=(GameEngineSound&& _Other) noexcept = delete;

protected:
	bool Load(const std::string& _Path);


private:
	FMOD::Sound* Sound;

	///////////////////////////////////////// �Ŵ�����Ʈ ���� ���
public:
	// �׳� ���� ���1ȸ ����� ���߰ų� �̷��� ���մϴ�.
	static GameEngineSoundHollowKnight SoundPlayControl(const std::string& _Name, unsigned int LoopCount = 0);

	static void SoundPlayOneShot(const std::string& _Name, int LoopCount = 0);
	static void Update();

/// <summary>
/// ///////////////////////////////////// ���ҽ� �Ŵ�����Ʈ
/// </summary>
public:
	static GameEngineSound* FindRessource(const std::string& _Name);
	static GameEngineSound* LoadRessource(const GameEngineFile& _Path);
	static GameEngineSound* LoadRessource(const std::string& _Path);
	static GameEngineSound* LoadRessource(const std::string& _Path, const std::string& _Name);

	static void AllResourcesDestroy();

private:
	static std::map<std::string, GameEngineSound*> AllRes;

};

// ���� ����� �����Ҽ� �ִ� ��ɵ��� �����̴ϴ�.
class GameEngineSound;
class GameEngineSoundHollowKnight 
{
	friend GameEngineSound;

public:
	void Stop();
	void PlaySpeed(float _Speed);
	void Volume(float _Value);

	GameEngineSoundHollowKnight(const GameEngineSoundHollowKnight& _Other);

private:
	GameEngineSound* Sound_;
	FMOD::Channel* ControlHandle_;


	GameEngineSoundHollowKnight(GameEngineSound* Sound, FMOD::Channel* ControlHandle);

public:
	GameEngineSoundHollowKnight();
	~GameEngineSoundHollowKnight();
};