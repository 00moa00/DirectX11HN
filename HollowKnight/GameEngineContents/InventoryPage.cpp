#include "PreCompile.h"
#include "InventoryPage.h"
#include "HollowKnightLevel.h"

#include <GameEngineBase/magic_enum.hpp>
#include <GameEngineBase/magic_enum_format.hpp>
#include <GameEngineBase/magic_enum_fuse.hpp>

InventoryPage::InventoryPage() 
{
}

InventoryPage::~InventoryPage() 
{
}

void InventoryPage::Start()
{
	SetPageType(PAGE_TYPE::Inventory);


	// �Ϲ� ������ ��ġ ����
	{
		float MaginX = 0.0f;
		float MaginY = 0.f;
		int SlotNum = 10;

		for (int j = 0; j < 3; ++j)
		{
			for (int i = 0; i < 4; ++i)
			{
				GetLevel<HollowKnightLevel>()->PushItemSlot(SlotNum, { 0 + MaginX, 200.f + MaginY, static_cast<float>(Z_ORDER::UI) });

				MaginX += 70.f;
			}

			MaginX = 0.f;
			MaginY -= 100.f;
			++SlotNum;
		}
	}

	//����Ʈ�� ������������ �����ϴµ�, ��� ���Կ� �� ������ �̸� ���� ���·� ������ ����Ʈ�� �ִ´�

	//���� ������ ���

	{
		float MaginX = 0.0f;
		float MaginY = 0.f;
		int SlotNum = 0;

		for (int i = 0; i < 8; ++i)
		{

			int ValueNum = SlotNum;
			auto ItemEnum = magic_enum::enum_cast<ITEM_LIST>(ValueNum);

			std::string EnumString;

			auto Name = magic_enum::enum_name(ItemEnum.value());
			EnumString = static_cast<std::string>(Name);


			AllItem_.insert({ SlotNum, GetLevel()->CreateActor<ItemSlot>() });
			AllItem_[SlotNum]->CreateItem(EnumString, SlotNum, ItemEnum.value());

			AllItem_[SlotNum]->SetParent(this);
			++SlotNum;
			MaginX += 70.f;
		}

		MaginX = 0.f;
		MaginY -= 100.f;
	

	}




}

void InventoryPage::Update(float _DeltaTime)
{
}

