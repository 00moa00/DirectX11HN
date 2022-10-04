#include "PreCompile.h"
#include "Sly.h"

#include "HollowKnightLevel.h"
Sly::Sly() 
	:
	OpenShop_(false),

	ShopIndexCount_(0),

	PrevDir_(),

	MapShop_(nullptr)
{
}

Sly::~Sly() 
{
}

void Sly::Start()
{
	SetNPCName("������");

	SetNPCType(NPC_TYPE::Shop);

	GetTransform().SetWorldPosition({ 1176.f, -861.f, static_cast<int>(Z_ORDER::NPC) });
	CreateNameFontRenderer();
	CreatePromptSet();

	PromptSet* ShopPromptSet_ = GetLevel()->CreateActor<PromptSet>();
	ShopPromptSet_->CreatePrompSet(PromptSetType::TALK);
	ShopPromptSet_->SetParent(this);
	ShopPromptSet_->GetTransform().SetLocalPosition({ -220.f, 220.f });
	//ShopPromptSet_->GetCollision()->GetTransform().SetLocalPosition({ 0.f, -300.f });
	ShopPromptSet_->GetCollision()->GetTransform().SetLocalScale({ 200.f, 100.f });

	GetPromptSet()->GetTransform().SetLocalPosition({ 50.f, 220.f });
	//GetPromptSet()->GetCollision()->GetTransform().SetLocalPosition({ 0, -300.f });
	GetPromptSet()->GetCollision()->GetTransform().SetLocalScale({ 280.f, 100.f });

	CreateCollisionComponent(float4{ 600, 120, 1 }, static_cast<int>(COLLISION_ORDER::NPC));

	CreateDialogueSet();

	GetDialogueSet()->PushDialogue("�� �ǳ��� ���� ���԰� ���� �� ������.�ణ�� ������ ��������.");
	GetDialogueSet()->PushDialogue("�Ƹ� ���� ������ �ȱ� �����ؾ� �ϳ�...�ƴϸ� �װ� �� �������̷���?��.������ ������� ���迡���� ��� ���� �����ؿ�.");

	GetDialogueSet()->SetDialogueOff();

	CreateRendererComponent("Sly_town_idle0000-Sheet.png", 0);
	GetRenderer()->SetPivot(PIVOTMODE::BOT);

	GetRenderer()->CreateFrameAnimationCutTexture("IDLE_ANIMATION", FrameAnimation_DESC("Sly_town_idle0000-Sheet.png", 0, 5, 0.100f));
	GetRenderer()->CreateFrameAnimationCutTexture("CHANGE_DIR_ANIMATION", FrameAnimation_DESC("Sly_turn_left_to_right0000-Sheet.png", 0, 2, 0.100f));


	{
		std::vector<unsigned int> CustomAni;

		for (int i = 2; i > -1; --i)
		{
			CustomAni.push_back(i);
		}

		GetRenderer()->CreateFrameAnimationCutTexture("CHANGE_RETURN_DIR_ANIMATION", FrameAnimation_DESC("Sly_turn_left_to_right0000-Sheet.png", CustomAni, 0.100f, false));
	}
	GetRenderer()->CreateFrameAnimationCutTexture("RIGHT_IDLE", FrameAnimation_DESC("Sly_turn_left_to_right0000-Sheet.png", 2, 2, 0.100f, false));

	GetRenderer()->SetScaleModeImage();
	GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");

	GetRenderer()->AnimationBindEnd("CHANGE_DIR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("RIGHT_IDLE");

		});

	GetRenderer()->AnimationBindEnd("CHANGE_RETURN_DIR_ANIMATION", [=](const FrameAnimation_DESC& _Info)
		{
			GetRenderer()->ChangeFrameAnimation("IDLE_ANIMATION");

		});



	MapShop_ = GetLevel()->CreateActor<Shop>();
	MapShop_->SetShopType(SHOP_TYPE::Sly_Shop);
	MapShop_->CreateFigurehead(SHOP_TYPE::Sly_Shop);
	MapShop_->GetTransform().SetWorldPosition({ 400, 0 });

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::MaskPiece);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(0);
	MapShop_->GetShopItemList().back()->SetItemInfo("�� ���� �����̿�? �׳� �� ū � ���� �����̿���.�׷��� ��¼�� ����� �װ��� ����� �� �������� �����.");

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::MaskPiece);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(1);
	MapShop_->GetShopItemList().back()->SetItemInfo("�̰��� �� �ϳ� �߰��߾��.�ڼ��� ���� �ű⿡ ���� ���� ���� ������ �־��.");

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::MaskPiece);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(2);
	MapShop_->GetShopItemList().back()->SetItemInfo("��� �̰͵��� �����ϴ� �� ����? ����� ���� ������.���� �� �ϳ��� â���� �߰��߰ŵ��.");

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::MaskPiece);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(3);
	MapShop_->GetShopItemList().back()->SetItemInfo("�˰� ���� �� ������ �ϳ� �� ���� �־����. ��¥ ������ ������!");

	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Rancid_Egg);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(4);


	MapShop_->GetShopItemList().push_back(GetLevel()->CreateActor<ShopItem>());
	MapShop_->GetShopItemList().back()->CreateShopItem(SHOP_ITEM::Acid_armour);
	MapShop_->GetShopItemList().back()->SetParent(MapShop_);
	MapShop_->GetShopItemList().back()->SetSlideItemIndex(5);

	MapShop_->SetItemListPosition();
	MapShop_->Off();

	SlyManager_.CreateStateMember("IDLE"
		, std::bind(&Sly::SlyIdleUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Sly::SlyIdleStart, this, std::placeholders::_1)
		, std::bind(&Sly::SlyIdleEnd, this, std::placeholders::_1));


	SlyManager_.CreateStateMember("CHANGEDIR"
		, std::bind(&Sly::SlyChangeDirUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Sly::SlyChangeDirStart, this, std::placeholders::_1)
		, std::bind(&Sly::SlyChangeDirEnd, this, std::placeholders::_1));


	SlyManager_.CreateStateMember("SHOP_OPEN"
		, std::bind(&Sly::SlyShopOpenUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Sly::SlyShopOpenStart, this, std::placeholders::_1)
		, std::bind(&Sly::SlyShopOpenEnd, this, std::placeholders::_1));


	SlyManager_.CreateStateMember("TALKING"
		, std::bind(&Sly::SlyTalkingUpdate, this, std::placeholders::_1, std::placeholders::_2)
		, std::bind(&Sly::SlyTalkingStart, this, std::placeholders::_1)
		, std::bind(&Sly::SlyTalkingEnd, this, std::placeholders::_1));


	SlyManager_.ChangeState("IDLE");


}

void Sly::Update(float _DeltaTime)
{
	CheckDirToKnight();
	SlyManager_.Update(_DeltaTime);
}

void Sly::CheckDirToKnight()
{
	float4 KnightPos = GetLevel<HollowKnightLevel>()->GetKnight()->GetTransform().GetWorldPosition();
	float4 DirPos = KnightPos - this->GetTransform().GetWorldPosition();
	DirPos.Normalize();

	if (DirPos.x > 0.0f)
	{
		SetMoveDirection(float4::RIGHT);

		if (PrevDir_.CompareInt2D(float4::RIGHT) == false)
		{
			GetRenderer()->ChangeFrameAnimation("CHANGE_DIR_ANIMATION");

			//IseldaManager_.ChangeState("CHANGE_DIR");
			//return;
		}

		PrevDir_ = float4::RIGHT;

		//GetRenderer()->GetTransform().PixLocalNegativeX();
	}

	else if (DirPos.x < 0.0f)
	{
		SetMoveDirection(float4::LEFT);

		if (PrevDir_.CompareInt2D(float4::LEFT) == false)
		{
			GetRenderer()->ChangeFrameAnimation("CHANGE_RETURN_DIR_ANIMATION");

			//IseldaManager_.ChangeState("CHANGE_DIR");
			//return;
		}

		PrevDir_ = float4::LEFT;
	}
}

void Sly::SlyIdleStart(const StateInfo& _Info)
{
}

void Sly::SlyIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Sly::SlyIdleEnd(const StateInfo& _Info)
{
}

void Sly::SlyChangeDirStart(const StateInfo& _Info)
{
}

void Sly::SlyChangeDirUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Sly::SlyChangeDirEnd(const StateInfo& _Info)
{
}

void Sly::SlyShopOpenStart(const StateInfo& _Info)
{
}

void Sly::SlyShopOpenUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Sly::SlyShopOpenEnd(const StateInfo& _Info)
{
}

void Sly::SlyTalkingStart(const StateInfo& _Info)
{
}

void Sly::SlyTalkingUpdate(float _DeltaTime, const StateInfo& _Info)
{
}

void Sly::SlyTalkingEnd(const StateInfo& _Info)
{
}

