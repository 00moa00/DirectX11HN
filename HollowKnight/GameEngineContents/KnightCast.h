#pragma once

// ���� : �� ������ ��ȥ
// �ݸ��� ���� ���Ϳ� ������ ������ ����Ʈ
// ���� ��Ƶ� �׷���?
class KnightCast
{
public:
	// constrcuter destructer
	KnightCast();
	~KnightCast();

	// delete Function
	KnightCast(const KnightCast& _Other) = delete;
	KnightCast(KnightCast&& _Other) noexcept = delete;
	KnightCast& operator=(const KnightCast& _Other) = delete;
	KnightCast& operator=(KnightCast&& _Other) noexcept = delete;

protected:

private:

};

