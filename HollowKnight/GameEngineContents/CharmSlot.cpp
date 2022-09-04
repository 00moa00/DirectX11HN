#include "PreCompile.h"
#include "CharmSlot.h"

CharmSlot::CharmSlot() 
	:
	Charm_(nullptr)
{
}

CharmSlot::~CharmSlot() 
{
}

void CharmSlot::Start()
{
}

void CharmSlot::Update(float _Deltatime)
{
}

void CharmSlot::CreateCharmSlot(std::string _SlotName, std::string _CharmFilePath, CharmState _CharmState, CHARM_SLOT _slot)
{
	// ���� ����
	CreateRendererComponent({68,68,1}, "charm_backboard.png");

	//���� ����
	CharmState_.SlotNum_ = _CharmState.SlotNum_;
	CharmState_.KnihgistHas_ = _CharmState.KnihgistHas_;
	CharmState_.isUsing_ = _CharmState.isUsing_;
	CharmState_.isEquippedSlot_ = false;
	CharmState_.isEquippedSlotUsing_ = false;
	CharmState_.CharmFilePath_ = _CharmFilePath;
	CharmState_.CharmName_ = _SlotName;
	CharmState_.UsingSlotNum_ = static_cast<int>(_slot);

	//����
	Charm_ = GetLevel()->CreateActor<Charm>();
	Charm_->CreateCharm(_SlotName, _CharmFilePath, { 131, 128, 1 });

	Charm_->SetParent(this);

	SetPointerSize(Charm_->GetRenderer()->GetCurTexture()->GetScale());

	//���� ĭ ����
	switch (_slot)
	{
	case CHARM_SLOT::Wayward_Compass:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "�������� ��ħ��");
		SetInfo( "������ ���� ������ �����ڿ��� ��ġ�� �ӻ迩 ����ڰ� �ڽ��� ���� ��ġ�� ��Ȯ�� �ľ��� �� �ְ� �մϴ�.");

		break;
	case CHARM_SLOT::Gathering_Swarm:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "�������� ����");
		SetInfo( "������ �����ڸ� ����ٴϸ�, ��ģ ������ �����ɴϴ�.�ƹ��� ����� ���̶� ����� ���� �ߵ��� ���ϴ� �̵鿡�� �����մϴ�.");

	break;	
	case CHARM_SLOT::Stalwart_Shell:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "ưư�� ������");
		SetInfo( "�ּ��ڵ��� ���� ����κ��� �� ���� ��ȥ�� ����� ���� ����մϴ�. ������� ���� ������ �� ��� ��ȥ�� ���� ������ŵ�ϴ�.");

	break;	
	case CHARM_SLOT::Soul_Catcher:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "��ȥ ������");
		SetInfo( "���� ����ִ� ����ü�κ��� ��ȥ�� ����� �� ���Ǵ� ������ �ּ����� ����. ������� ���� ������ �� ��� ��ȥ�� ���� ũ�� ������ŵ�ϴ�.");

		break;	
	case CHARM_SLOT::Shaman_Stone:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "�ּ����� ��");
		SetInfo( "�ּ����� ���� ���� ������ ��� �ִٰ� �մϴ�. �ֹ��� ���� �������� ������ �� ���� ���ظ� ���մϴ�.");

		break;

	case CHARM_SLOT::Soul_Eater:
		CharmState_.SlotCount_ = 4;
		SetInfoName( "��ȥ ������");
		SetInfo( "���� ����ִ� ����ü�κ��� ��ȥ�� ����� �� ���Ǵ� ������ �ּ����� ����. ������� ���� ������ �� ��� ��ȥ�� ���� ũ�� ������ŵ�ϴ�.");

		break;
	case CHARM_SLOT::Dashmaster:
		CharmState_.SlotCount_ = 4;
		SetInfoName( "��� ������");
		SetInfo( "'��ø�����'��� �˷��� ������ ������ ����� �ϰ� �ֽ��ϴ�. �����ڴ� �� ���� ��ø� �һӸ� �ƴ϶� �Ʒ��ε� ��ø� �� �� �ֽ��ϴ�. �ִ��� ���� �ֺ��� ���ƴٴϰ� �;��ϴ� �̵鿡�� �̻����Դϴ�.");

		break;
	case CHARM_SLOT::Thorns_of_Agony:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "������ ���õ���");
		SetInfo( "�������� ������ �����ϸ� �ֺ��� ä���� �մϴ�. ���ظ� ������ �ֺ��� ���鿡�� ���ظ� ������ ���ð� ���� ������ �ڶ󳳴ϴ�.");

		break;
	case CHARM_SLOT::Fury_of_the_Fallen:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "�������� �г�");
		SetInfo( "���� �̵鿡 ���� �г�� �������� ��¡�մϴ�. ������ ��������� �� �������� ���� �����մϴ�.");

		break;
	case CHARM_SLOT::Fragile_Heart:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "����� ����");
		SetInfo( "�������� ü���� �������� �� ���� ���ظ� �ߵ� �� �ְ� �մϴ�. �� ������ ���ؼ� �����ڰ� ������ �����ϴ�.");

		break;
	case CHARM_SLOT::Fragile_Greed:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "����� Ž��");
		SetInfo( "�����ڰ� ���� ����ġ�� �� ���� ������ �������ݴϴ�. �� ������ ���ؼ� �����ڰ� ������ �����ϴ�.");

		break;
	case CHARM_SLOT::Fragile_Strength:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "����� �� ");
		SetInfo( "�����ڸ� ���ϰ� �ϰ�, ������� ������ ������ �ջ��� ������ŵ�ϴ�. �� ������ ���ؼ� �����ڰ� ������ �����ϴ�.");

		break;
	case CHARM_SLOT::Spell_Twister:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "�ֹ� ȸ����");
		SetInfo( "�ֹ��� �θ��� �� �ʿ��� ��ȥ ����� ���Դϴ�.");

		break;
	case CHARM_SLOT::Steady_Body:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "��鸲 ���� �ڼ�");
		SetInfo( "������� ���� ������ �� �����ڰ� �ڷ� ���� �и��� �ʰ� �մϴ�. �������� ���·� ��� ������ �� �� �ְ� �մϴ�.");

		break;
	case CHARM_SLOT::Heavy_Blow:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "������ Ÿ��");
		SetInfo( "���� ������ ������� ����������ϴ�. �������� ����� ���� �������� ���� ������ �޾��� �� �� �ָ� �з����� �մϴ�.");

		break;
	case CHARM_SLOT::Quick_Slash:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "���� ����");
		SetInfo( "�Բ� ���ص� �ҿ����ϰ� ������ ������κ��� �¾���ϴ�. ����� ������ �ֵѷ����⸦ �����մϴ�. �����ڴ� ������� �ξ� �� ������ �� �� �ֽ��ϴ�.");

		break;
	case CHARM_SLOT::Longnail:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "��ٶ� ���");
		SetInfo( "�������� ��� ������ �������� �ָ��� ���� ������ �� �ְ� �մϴ�.");

		break;
	case CHARM_SLOT::Mark_of_Pride:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "������ ǥ��");
		SetInfo( "�縶�� ������ �ڽŵ��� �����ϴ� �̿��� �ݴϴ�. �������� ��� ������ ũ�� �������� �ָ��� ���� ������ �� �ְ� �մϴ�.");

		break;
	case CHARM_SLOT::Baldur_Shell:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "�ߴ� ������");
		SetInfo( "��ȥ�� �����ϸ鼭 ������ ������� �����ڸ� ��ȣ�մϴ�. ������� ������ �ƴϸ� �ʹ� ���� �ջ��� ����ϸ� ����� �μ����ϴ�.");

		break;
	case CHARM_SLOT::Flukenest:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "���� ����");
		SetInfo( "���� ����� ���忡�� �¾ ����ִ� ����. ������ ���� �ֹ��� ���������� �Ʊ� ���� ������ �ٲߴϴ�.");

		break;
	case CHARM_SLOT::Defenders_Crest:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "��ȣ����� ����");
		SetInfo( "�ż������� ���� ���� �漺������ ��翡�� ������ ��Ư�� ����. ������ ������������ ������ ����޽��ϴ�. �����ڰ� ������ ������ �����ϰ� �մϴ�.");

		break;
	case CHARM_SLOT::Glowing_Womb:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "������ ����");
		SetInfo( "�������� ��ȥ�� ���� ������ ź����Ű�� �� ����մϴ�. ������ �԰ų� ����� ������ ������, �θ� ��ȣ�ϱ� ���� �ڽ��� ����մϴ�.");

		break;
	case CHARM_SLOT::Quick_Focus:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "��� ����");
		SetInfo( "���� ��� �����ϰ� �ִ� ����. ��ȥ ������ �ӵ��� �������� �����ڰ� ���ظ� �� ���� ġ���� �� �ְ� �մϴ�.");

		break;
	case CHARM_SLOT::Deep_Focus:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "���� ����");
		SetInfo( "���� �Ⱓ�� ���� ���� �ȿ� �ڿ������� ������ ����. �ֺ� ����κ��� ��ȥ�� ������ϴ�.�����ڴ� �� ���� �ӵ��� ��ȥ�� ����������, ġ�� ȿ���� �� �谡 �˴ϴ�.");

		break;
	case CHARM_SLOT::Lifeblood_Heart:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "������ ����");
		SetInfo( "������ �������� ���� ������ �ϴ� ����ִ� ���� ��� �ֽ��ϴ�. �޽��� �� �� �����ڴ� ����� �ջ����κ��� ��ȣ�ϴ� �������� ���õ˴ϴ�.");

		break;
	case CHARM_SLOT::Lifeblood_Core:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "������ ��");
		SetInfo( "������ �������� �긮�� ����ִ� ���� ��� �ֽ��ϴ�. �޽��� �� �� �����ڴ� ���� �ջ����κ��� ��ȣ�ϴ� �������� ���õ˴ϴ�.");

		break;
	case CHARM_SLOT::Jonis_Blessing:
		CharmState_.SlotCount_ = 4;
		SetInfoName( "������ �ູ");
		SetInfo( "ģ���� �̱����� ������ �ູ. ��ü ��ü�� �Ķ� �������� ��ȭ��ŵ�ϴ�. �����ڴ� �� �ǰ��� �����⸦ ������ �� ���� �ջ��� �ߵ� �� ������, ��ȥ�� �����Ͽ� �����θ� ġ���� ���� �����ϴ�.");

		break;
	case CHARM_SLOT::Grubsong:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "�ֹ��� �뷡 ");
		SetInfo( "�ع�� �ֹ����� ���縦 ��� �ֽ��ϴ�. ���ظ� ���� �� ��ȥ�� ����ϴ�.");

		break;
	case CHARM_SLOT::Grubberflys_Elegy:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "�ֹ������� �ְ�");
		SetInfo( "���� ���� �ܰ�� �Ѿ �ֹ����� ���縦 ��� �ֽ��ϴ�. ���⿡ �ż��� ���� ���� ä��ϴ�. �������� ü���� ������ �� ������κ��� �Ͼ� �߰ſ� �������� �߻��մϴ�.");

		break;
	case CHARM_SLOT::Hiveblood:
		CharmState_.SlotCount_ = 4;
		SetInfoName( "������ ����");
		SetInfo( "������ ���� ���� ������ ������ Ȳ�ݻ� ���. �ð��� ������ ���� �������� ��ó�� ġ���Ͽ� ��ȥ�� �������� �ʰ� ü���� ��ã�� �� �ְ� �մϴ�.");

		break;
	case CHARM_SLOT::Spore_Shroom:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "���� ����");
		SetInfo( "����ִ� ������ ������ �����Ǿ� �ֽ��ϴ�. ��ȥ�� ����Ǹ� ���ڸ� �Ѹ��ϴ�. ��ȥ�� ������ �� ���������� ������ ���ظ� ������ ���ڸ� �����մϴ�.");

		break;
	case CHARM_SLOT::Sharp_Shadow:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "��ī�ο� �׸���");
		SetInfo( "�׸��ڸ� ġ������ ����� �ٲٴ� ������ �ֹ��� ��� �ֽ��ϴ�. �׸��� ��ø� ����� �� �������� ���� ��ī�ο����� ������ ���ظ� �����ϴ�.");

		break;
	case CHARM_SLOT::Shape_of_Unn:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "����� ����");
		SetInfo( "������ ������ ����� ������ �巯���ϴ�. ��ȥ�� �����ϴ� ���� �����ڴ� ���ο� ���¸� ���ϸ�, ���� ���ϱ� ���� �����Ӱ� ������ �� �ֽ��ϴ�.");

		break;
	case CHARM_SLOT::Nailmasters_Glory:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "�������� ����");
		SetInfo( "�������� ����, ���, ��ȸ�� ��� �ֽ��ϴ�. �������� ��� ��� ���޵��� �������� �ڽ��� ���� �� ���� �����ϰ� ����� �� ���� ������ �� �ְ� �մϴ�.");

		break;
	case CHARM_SLOT::Dream_Wielder:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "���� ����");
		SetInfo( "��ȯ�� ����� �ֵθ��� ������ �����ϴ� �̵��� ���� ������� ����. �����ڰ� ��ȯ�� ����� �� ���� �����ϰ� ���� ������ �� �� ���� ��ȥ�� ������ �� �ְ� �մϴ�.");

		break;
	case CHARM_SLOT::Kingsoul:
		CharmState_.SlotCount_ = 5;
		SetInfoName( "���� ��ȥ");
		SetInfo( "õõ�� ��ȥ�� ȸ���Ѵ�. ������� ���� ���� �� �� �ְ� �ȴ�.");

		break;
	case CHARM_SLOT::Sprintmaster:
		CharmState_.SlotCount_ = 1;
		SetInfoName( "���ָ�����");
		SetInfo( "���ָ����Ͷ�� �˷��� �̻��� ������ ����� �ϰ� �ִ� ����. �������� �̵��ӵ��� �������Ѽ� ������ ���ϰų� �����ڸ� �߿��� �� �ְ� �����ݴϴ�.");

		break;
	case CHARM_SLOT::Weaversong:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "���� ���� �뷡");
		SetInfo( "�ڽ��� �������� ���ư� ���� �̵��� �ۺ� �뷡�� ����ִ� ������� ¥���� ����. �ܷο� �����ڿ��� ģ���� ��ȣ�ڰ� �Ǿ��� ���縦 ��ȯ�մϴ�.");

		break;
	case CHARM_SLOT::Dreamshield:
		CharmState_.SlotCount_ = 3;
		SetInfoName( "��ȯ����");
		SetInfo( "���� ����ȭ�� �� �ִ� ������ ����ϴ� ���� ����. �����ڸ� ����ٴϸ� �����ִ� ���и� �����մϴ�.");

		break;
	case CHARM_SLOT::Grimmchild:
		CharmState_.SlotCount_ = 2;
		SetInfoName( "�׸��� ����");
		SetInfo( "�׸� �ش��� �ǽĿ� ������ �̵��� ���ϴ� ����. �����ڴ� �׸��� �������� ã�Ƴ��� �Ҳ��� �����ؾ� �մϴ�. �������� ���� �Ҳ��� �������� ������ ǥ�õ˴ϴ�.");

		break;
	default:
		break;
	}

	//GetRenderer()->SetParent(this);

}

void CharmSlot::CreateEquippedCharmSlot( CharmState _CharmState)
{
	// ���� ����
	CreateRendererComponent({ 38, 38,1 }, "charm_cost.png");

	//���� ����
	CharmState_.SlotNum_ = _CharmState.SlotNum_;
	CharmState_.SlotCount_ = _CharmState.SlotCount_;
	CharmState_.KnihgistHas_ = _CharmState.KnihgistHas_;
	CharmState_.isUsing_ = _CharmState.isUsing_;
	CharmState_.isEquippedSlot_ = true;
	CharmState_.isEquippedSlotUsing_ = false;


	//����
	Charm_ = GetLevel()->CreateActor<Charm>();
	//Charm_->CreateCharm(_SlotName, _CharmFilePath, { 131, 128, 1 });

	Charm_->SetParent(this);

	SetPointerSize({ 38 , 38, 1});

}

void CharmSlot::CreateCopyCharm(GameEngineUIRenderer* _RenderData, std::string _SlotName, std::string _FilePath)
{


	CharmState_.CharmFilePath_ = _FilePath;
	CharmState_.CharmName_ = _SlotName;

	Charm_->CreateCharm(_SlotName, _FilePath, { 131, 128, 1 });
	SetPointerSize(Charm_->GetRenderer()->GetCurTexture()->GetScale());

}


void CharmSlot::CharmSetMoveLeft()
{

}