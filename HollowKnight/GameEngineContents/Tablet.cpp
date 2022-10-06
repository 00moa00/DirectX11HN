#include "PreCompile.h"
#include "Tablet.h"
#include "GlobalContentsValue.h"

Tablet::Tablet() 
	:
	isOpenDialogue_(false),

	Alpha_(0.0f),

	BackRenderer_(nullptr),
	LightRenderer_(nullptr),

	Collision_(nullptr),
	PromptSet_(nullptr),
	TabletDialogue_(nullptr)

{
}

Tablet::~Tablet() 
{
}

void Tablet::Start()
{
	TabletManager_.CreateStateMember("IDLE"
		, std::bind(&Tablet::TabletIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tablet::TabletIdleStart, this, std::placeholders::_1)
		, std::bind(&Tablet::TabletIdleEnd, this, std::placeholders::_1));

	TabletManager_.CreateStateMember("APPEAR"
		, std::bind(&Tablet::TabletAppearUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Tablet::TabletAppearStart, this, std::placeholders::_1)
		, std::bind(&Tablet::TabletAppearEnd, this, std::placeholders::_1));

	TabletManager_.ChangeState("IDLE");
}

void Tablet::Update(float _DeltaTime)
{
	TabletManager_.Update(_DeltaTime);
}

void Tablet::CreateTablet(std::string _BackFilePath, std::string _LightFilePath, float4 _CollSize, TabletType _TabletType)
{
	BackRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	BackRenderer_->SetTexture(_BackFilePath);
	BackRenderer_->GetTransform().SetLocalScale(BackRenderer_->GetCurTexture()->GetScale());
	BackRenderer_->SetPivot(PIVOTMODE::BOT);

	LightRenderer_ = CreateComponent<GameEngineTextureRenderer>();
	LightRenderer_->SetTexture(_LightFilePath);
	LightRenderer_->GetTransform().SetLocalScale(LightRenderer_->GetCurTexture()->GetScale());
	LightRenderer_->SetPivot(PIVOTMODE::BOT);
	LightRenderer_->GetPixelData().MulColor.a = 0.0f;

	LightRenderer_->Off();

	Collision_ = CreateComponent<GameEngineCollision>();
	Collision_->GetTransform().SetLocalScale(_CollSize);
	Collision_->ChangeOrder(COLLISION_ORDER::Tablet);

	PromptSet_ = GetLevel()->CreateActor<PromptSet>();
	PromptSet_->CreatePrompSet(PromptSetType::SEARCH);
	PromptSet_->SetParent(this);
	PromptSet_->GetTransform().SetLocalPosition({0, 350});
	PromptSet_->GetCollision()->GetTransform().SetLocalPosition({0, -350});

	TabletDialogue_ = GetLevel()->CreateActor<TabletDialogue>();

	switch (_TabletType)
	{
	case TabletType::FocusSpell:
		SpellFocusInfo_ = GetLevel()->CreateActor<SpellFocusInfo>();
		SpellFocusInfo_->SetSpellFocusInfoOff();

		TabletDialogue_->PushDialogue("����� �����, ��ŵ��� ���� ���Ѵ�.\n�츮 �Ͽ��̱⿡ ������ ���� �ִ�.��ȥ�� ������ �޸� ���� ���� �̷� �� �ִ�.", 0);

		break;
	case TabletType::Tu_Story:
		TabletDialogue_->PushDialogue("����� �����, ��ŵ��� ���� ���Ѵ�.\n�̰� �ʸӿ� �հ� â������ ���� ���� �ȴ�.�� ��踦 �ǳʹٸ�, �츮�� ���� �ؼ��϶�.", 100);
		TabletDialogue_->PushDialogue("�������� ������ ����, ������ �ձ��� ����϶�.\n�ż�����", 100);
		TabletDialogue_->GetArrow()->GetTransform().SetLocalPosition({0,-50});
		PromptSet_->GetTransform().SetLocalPosition({ 0, 450 });

		break;
	default:
		break;
	}


}

void Tablet::TabletDialogueOn()
{
	TabletDialogue_->On();
	TabletDialogue_->SetDialogueOn();

	if (SpellFocusInfo_ != nullptr)
	{
		SpellFocusInfo_->SetSpellFocusInfoOn();
	}


	isOpenDialogue_ = true;
	PromptSet_->Off();
	GameEngineSound::SoundPlayOneShot("Lore_Tablet_activate_temp.ogg");
}

void Tablet::TabletDialogueOff()
{
	TabletDialogue_->Off();

	TabletDialogue_->SetDialogueOff();
	if (SpellFocusInfo_ != nullptr)
	{
		SpellFocusInfo_->SetSpellFocusInfoOff();
	}
	isOpenDialogue_ = false;
	PromptSet_->On();

}

void Tablet::TabletIdleStart(const StateInfo& _Info)
{
}

void Tablet::TabletIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	Alpha_ -= _DeltaTime * 0.7f;
	LightRenderer_->GetPixelData().MulColor.a = Alpha_;

	if (Alpha_ <= 0.0f)
	{
		Alpha_ = 0.0f;
	}

	if (Collision_->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Tablet::TabletVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == true
		)
	{
		TabletManager_.ChangeState("APPEAR");
		return;
	}
}

void Tablet::TabletIdleEnd(const StateInfo& _Info)
{
}

void Tablet::TabletAppearStart(const StateInfo& _Info)
{
	LightRenderer_->On();
	//GameEngineSound::SoundPlayOneShot("ui_button_confirm.ogg", 0.1f);

}

void Tablet::TabletAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{

	Alpha_ += _DeltaTime * 0.7f;
	LightRenderer_->GetPixelData().MulColor.a = Alpha_;

	if (Alpha_ >= 1.0f)
	{
		Alpha_ = 1.0f;
	}

	if (Collision_->IsCollision(CollisionType::CT_OBB2D, COLLISION_ORDER::Knight, CollisionType::CT_OBB2D,
		std::bind(&Tablet::TabletVSKnightCollision, this, std::placeholders::_1, std::placeholders::_2)) == false
		)
	{
		TabletManager_.ChangeState("IDLE");
		return;
	}


}

void Tablet::TabletAppearEnd(const StateInfo& _Info)
{
	//Alpha_ = 1.0f;
}

void Tablet::TabletOnDialougueStart(const StateInfo& _Info)
{
}

void Tablet::TabletOnDialougueUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Tablet::TabletOnDialougueEnd(const StateInfo& _Info)
{
}

void Tablet::TabletOffDialougueStart(const StateInfo& _Info)
{
}

void Tablet::TabletOffDialougueUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Tablet::TabletOffDialougueEnd(const StateInfo& _Info)
{
}

bool Tablet::TabletVSKnightCollision(GameEngineCollision* _This, GameEngineCollision* _Other)
{
	return true;
}
