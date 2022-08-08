#pragma once
#include <GameEngineCore/GameEngineDefaultRenderer.h>


class Tile
{

};

// Ÿ���� ����

// ���� :
class TitleMapRenderer : public GameEngineDefaultRenderer
{
public:
	// constrcuter destructer
	TitleMapRenderer();
	~TitleMapRenderer();

	// delete Function
	TitleMapRenderer(const TitleMapRenderer& _Other) = delete;
	TitleMapRenderer(TitleMapRenderer&& _Other) noexcept = delete;
	TitleMapRenderer& operator=(const TitleMapRenderer& _Other) = delete;
	TitleMapRenderer& operator=(TitleMapRenderer&& _Other) noexcept = delete;

protected:
	std::vector<std::vector<Tile>> Tiles;

private:

};

