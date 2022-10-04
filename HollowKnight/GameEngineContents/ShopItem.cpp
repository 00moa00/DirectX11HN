#include "PreCompile.h"

#include "ShopItem.h"

ShopItem::ShopItem() 
{
}

ShopItem::~ShopItem() 
{
}

void ShopItem::Start()
{

	ShopItemState_.Charm_ = CHARM_SLOT::None;
	ShopItemState_.Item_ = ITEM_LIST::NONE;

	ShopItemState_.InInventory_ = false;
}

void ShopItem::Update(float _DeltaTime)
{
}

void ShopItem::CreateShopItem(SHOP_ITEM _Item)
{
	switch (_Item)
	{
	case SHOP_ITEM::Crosslaod_Map:


		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Area_map.png");
		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale()*0.6f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({35,35});

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("200", 
			28, 
			{ 0,0 }, 
			false,
			false, 
			4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({50,0});
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);
		//PriceRenderer_->GetFontRenderer()->SetLeftAndRightSort(LeftAndRightSort::CENTER);
		ShopItemState_.ItemName_ = "������ ������";
		ShopItemState_.ItemInfo_ = "���� ���� �ٷ� �Ʒ��� �ִ� ������ ������ �������� ����. �ڴ��۰� �� �� ���� �ű� �Ʒ��� ���� ���� �־��. �װ��� �����ϰ� �ܷο� ��ҿ����� ������ �λ����̾����.";

		break;
	case SHOP_ITEM::Wayward_Compass:


		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Charm_0.png");
		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.5f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("200",
			28,
			{ 0,0 },
			false,
			false, 4);
		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "�������� ��ħ��";
		ShopItemState_.ItemInfo_ = "���� ��õ�ؿ�! �츮 �Ʒ��� ������ �̷ο��� ���� ã�µ� ������� �����ٸ� �� ������ �� ������.";
		ShopItemState_.Charm_ = CHARM_SLOT::Wayward_Compass;

		break;
	case SHOP_ITEM::Mark_of_Pride:

		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Area_map.png");
		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.6f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("200",
			28,
			{ 0,0 },
			false,
			false, 4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "������ ������";
		ShopItemState_.ItemInfo_ = "���� ���� �ٷ� �Ʒ��� �ִ� ������ ������ �������� ����. �ڴ��۰� �� �� ���� �ű� �Ʒ��� ���� ���� �־��. �װ��� �����ϰ� �ܷο� ��ҿ����� ������ �λ����̾����.";

		break;
	case SHOP_ITEM::Dreamshield:

		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Charm_38.png");
		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.5f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("240",
			28,
			{ 0,0 },
			false,
			false, 4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "��ȯ ����";
		ShopItemState_.ItemInfo_ = "���� ����ȭ�� �� �ִ� ������ ����ϴ� ���� �����̷���.";
		ShopItemState_.Charm_ = CHARM_SLOT::Dreamshield;

		break;

	case SHOP_ITEM::MaskPiece:

		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();
		ItemRenderer_->SetTexture("Heart_Piece_01.png");

		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.6f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("300",
			28,
			{ 0,0 },
			false,
			false, 4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "���� ����";
		ShopItemState_.ItemInfo_ = "�� ���� �����̿�? �׳� � ���� �����̿���. �׷��� ��¼�� ��ſ��� ������������?";
		ShopItemState_.Item_ = ITEM_LIST::Heart_Piece;
		//ShopItemState_.InInventory_ = true;
		break;

	case SHOP_ITEM::Rancid_Egg:
		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();

		ItemRenderer_->SetTexture("Rancid_egg.png");

		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.6f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("300",
			28,
			{ 0,0 },
			false,
			false, 4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "���� ��";
		ShopItemState_.ItemInfo_ = "ī���� �Ʒ����� �̰��� �߰��߾��. ���� �Ʒ� ���㿡 ���� ���� �� � ����ü�� �װ��� ���⿡ ���� �� �и��ؿ�.";
		ShopItemState_.Item_ = ITEM_LIST::Rancid_Egg;

		break;

	case SHOP_ITEM::Acid_armour:
		ItemRenderer_ = CreateComponent<GameEngineUIRenderer>();

		ItemRenderer_->SetTexture("Acid_armour.png");

		ItemRenderer_->GetTransform().SetLocalScale(ItemRenderer_->GetCurTexture()->GetScale() * 0.6f);

		GeoRenderer_ = CreateComponent<GameEngineUIRenderer>();
		GeoRenderer_->SetTexture("Item_Geo.png");
		GeoRenderer_->GetTransform().SetLocalScale({ 35,35 });

		PriceRenderer_ = GetLevel()->CreateActor<ContentsFontRenderer>();
		PriceRenderer_->CreateFontRenderer("300",
			28,
			{ 0,0 },
			false,
			false, 4);

		ItemRenderer_->GetTransform().SetLocalPosition({ -55,0,0 });
		GeoRenderer_->GetTransform().SetLocalPosition({ 25,0,0 });
		PriceRenderer_->GetTransform().SetLocalPosition({ 50,0 });
		PriceRenderer_->SetScreenMove();
		PriceRenderer_->GetFontRenderer()->SetTopAndBotSort(TopAndBotSort::VCENTER);

		ShopItemState_.ItemName_ = "�ƽ����� ����";
		ShopItemState_.ItemInfo_ = "���� �ϳ��� ��� ������ ����. �����ϸ� �ż������� Ư�� �κп��� �߰ߵǴ� Ÿ�� ���� �꼺 �����̷κ��� ��ȣ�մϴ�.";
		ShopItemState_.Item_ = ITEM_LIST::Acid_armour;

		break;

	default:
		break;
	}

	PriceRenderer_->SetParent(this);
}

void ShopItem::SetFontRendererMove()
{
	PriceRenderer_->GetTransform().SetWorldPosition({ PriceRenderer_->GetTransform().GetWorldPosition().x, this->GetTransform().GetWorldPosition().y });
	PriceRenderer_->SetScreenMove();

}

