#pragma once
#include <GameEngineCore/GameEngineGUI.h>

class GameEngineTextureRenderer;
class MetaSpriteWindow : public GameEngineGUIWindow
{
public:
    MetaSpriteWindow();
    ~MetaSpriteWindow();

    MetaSpriteWindow(const MetaSpriteWindow& _Other) = delete;
    MetaSpriteWindow(MetaSpriteWindow&& _Other) noexcept = delete;
    MetaSpriteWindow& operator=(const MetaSpriteWindow& _Other) = delete;
    MetaSpriteWindow& operator=(MetaSpriteWindow&& _Other) noexcept = delete;

    GameEngineDirectory MetaDir;
    GameEngineTexture* TargetTexture;

protected:
    void Initialize(class GameEngineLevel* _Level) override;
    void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
    std::string CurMetaFolder_;
    std::string CurAtlasFolder_;

    std::string CurMetaFile_;
    std::string CurAtlasFile_;

    void MetaFileButton();
    void AtlasFileButton();

    //void MetaFileButton();
    //void AtlasFileButton();

};