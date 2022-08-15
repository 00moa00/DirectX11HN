#include "PreCompile.h"
#include "HUD.h"
#include "KnightData.h"

HUD::HUD() 
	:
	VesselFrame_(nullptr),

	MaskesAppearEnd_(false),

	MaskesSize_(0),
	CurMask_(0),
	MakesAppearCount_(0),
	MaskAppearTimer_(0.f),

	HUDManager_()
{
}

HUD::~HUD() 
{
}

void HUD::Start()
{
	VesselFrame_ = GetLevel() ->CreateActor<VesselFrame>();
	VesselFrame_ -> GetTransform().SetLocalPosition({ -(GameEngineWindow::GetInst()->GetScale().hx() - 70.f), GameEngineWindow::GetInst()->GetScale().hy() - 50.f, -100 });

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size()-1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100});

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ - ((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });

	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });

	CurMask_ = Maskes_.size() - 1;

	KnightData::GetInst()->SetAllMask(CurMask_);
	KnightData::GetInst()->SetCurMask(CurMask_);

	HUDManager_.CreateStateMember("MASK_APPEAR"
		, std::bind(&HUD::MaskAppearUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&HUD::MaskAppearStart, this, std::placeholders::_1), std::bind(&HUD::MaskAppearEnd, this, std::placeholders::_1));

	HUDManager_.CreateStateMember("IDLE"
		, std::bind(&HUD::HUDIdleUpdate, this, std::placeholders::_1, std::placeholders::_2), std::bind(&HUD::HUDIdleStart, this, std::placeholders::_1), std::bind(&HUD::HUDIdleEnd, this, std::placeholders::_1));

	HUDManager_.ChangeState("MASK_APPEAR");

}

void HUD::Update(float _DeltaTime)
{
	HUDManager_.Update(_DeltaTime);
}

void HUD::NewMask()
{
	Maskes_.push_back(GetLevel()->CreateActor<Mask>());
	Maskes_.back()->GetTransform().SetWorldPosition({ -((GameEngineWindow::GetInst()->GetScale().hx() - 200.f) - ((Maskes_.size() - 1) * 60)), GameEngineWindow::GetInst()->GetScale().hy() - 55, -100 });
	MaskesSize_ = Maskes_.size();

	
	Maskes_[MaskesSize_-1]->SetNewAppearState();
	KnightData::GetInst()->SetAllMask(MaskesSize_);
}

void HUD::RefillMask()
{
	// ���� �� + �̹� ä���� ���� �ڿ��� ���� ä���
	for (int i = 0; i < MaskesSize_; ++i)
	{
		if (Maskes_[i]->GetisBroken() == true)
		{
			Maskes_[i]->SetisRefill();
			CurMask_ = i;

			KnightData::GetInst()->SetCurMask(CurMask_);
			return;
		}
	}
}

void HUD::BreakMask()
{
	// ���� �ڿ� �ִ� ���� ���� ��´�
	for (int i = Maskes_.size()-1; i >= 0; --i)
	{
		if (Maskes_[i]->GetisIdle() == true)
		{
			Maskes_[i]->SetisBroken();
			CurMask_ = i;

			KnightData::GetInst()->SetCurMask(CurMask_);
			return;
		}
	}
}

void HUD::AllRefillMask()
{
	for (int i = 0; i < MaskesSize_; ++i)
	{
		Maskes_[i]->SetisRefill();
	}
	KnightData::GetInst()->SetCurMask(MaskesSize_);
}

void HUD::SetAppearAnimation()
{

}

void HUD::MaskAppearStart(const StateInfo& _Info)
{
	MaskesSize_ = Maskes_.size();
}

void HUD::MaskAppearUpdate(float _DeltaTime, const StateInfo& _Info)
{
	MaskAppearTimer_ += _DeltaTime;

	if (MaskAppearTimer_ > 0.3f )
	{
		MaskAppearTimer_ = 0.0f;

		//������ ���鵵 ��¦! �ϱ� ���ؼ�.
		if (MakesAppearCount_ == Maskes_.size())
		{
			HUDManager_.ChangeState("IDLE");
		}
		else
		{
			//Maskes_[MakesAppearCount_]->SetisIdle();p
			Maskes_[MakesAppearCount_]->SetAppearState();
			++MakesAppearCount_;
		}
	}
}

void HUD::MaskAppearEnd(const StateInfo& _Info)
{
	MakesAppearCount_ = 0;

	for (int i = 0; i < MaskesSize_; ++i)
	{
		//Maskes_[i]->SetisIdle();
		Maskes_[i]->SetIdleState();
	}
}

void HUD::HUDIdleStart(const StateInfo& _Info)
{
}

void HUD::HUDIdleUpdate(float _DeltaTime, const StateInfo& _Info)
{
	//����
	if (KnightData::GetInst()->GetisRefill() == true)
	{
		RefillMask();
		KnightData::GetInst()->SetisRefill(false);
	}

	//����
	if (KnightData::GetInst()->GetisBreak() == true)
	{
		BreakMask();
		KnightData::GetInst()->SetisBreak(false);
	}

	// ����Ʈ ����
	if (KnightData::GetInst()->GetisDeath() == true)
	{
		KnightData::GetInst()->SetisDeath(false);

		for (int i = 0; i < MaskesSize_; ++i)
		{
			Maskes_[i]->SetIdleState();
		}
		KnightData::GetInst()->SetCurMask(MaskesSize_-1);

		//HUDManager_.ChangeState("MASK_APPEAR");

	}

}

void HUD::HUDIdleEnd(const StateInfo& _Info)
{

}
