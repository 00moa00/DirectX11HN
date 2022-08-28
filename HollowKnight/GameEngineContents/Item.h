#pragma once
#include "MasterUI.h"
#include"GlobalContentsValue.h"





// ���� : ������ ���Թ�ȣ 0~9 ���� ������. 10~ 29 �Ϲ� ������. 30~ 33 �Ǹ� ������
// ���� �����۰�, �Ǹ� �������� ��ġ ����
// �Ϲ� �������� ������ ������ ItemSlot�� ���Ƽ� ��������� ���ڸ��� �ִ´� 
// �Ϲ� ������ �߿��� �Һ� ������ �������� �ִµ�
// ������ 0�� �Ǹ� �ش� �������� �ڿ� �ִ� ������ ������ key���� ����.
// ���� ������ �ش� �������� ���� �������� �Ѵ�.

class Item : public MasterUI
{
public:
	// constrcuter destructer
	Item();
	~Item();

	// delete Function
	Item(const Item& _Other) = delete;
	Item(Item&& _Other) noexcept = delete;
	Item& operator=(const Item& _Other) = delete;
	Item& operator=(Item&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

public:
	void CreateItem(std::string _Name, ITEM_LIST _Item);



};

