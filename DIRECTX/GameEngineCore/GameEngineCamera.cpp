#include "GameEngineCamera.h"
#include "GameEngineRenderer.h"
#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include <GameEngineBase/GameEngineWindow.h>

GameEngineCamera::GameEngineCamera() 
{
	// 윈도우가 여러분들 생각하기 가장 쉬운 비율이라서 여기서 하는거고.
	Size = GameEngineWindow::GetInst()->GetScale();
	Mode = CAMERAPROJECTIONMODE::Orthographic;
	Near = 0.1f;
	Far = 1000.0f;
}

GameEngineCamera::~GameEngineCamera() 
{
}

void GameEngineCamera::Render(float _DeltaTime)
{
	// 랜더하기 전에 
	View.LookAtLH(
		GetActor()->GetTransform().GetLocalPosition(), 
		GetActor()->GetTransform().GetForwardVector(), 
		GetActor()->GetTransform().GetUpVector());

	switch (Mode)
	{
	case CAMERAPROJECTIONMODE::PersPective:
		break;
	case CAMERAPROJECTIONMODE::Orthographic:
		Projection.OrthographicLH(Size.x, Size.y, Near, Far);
		break;
	default:
		break;
	}

	float4 WindowSize = GameEngineWindow::GetInst()->GetScale();

	ViewPort.ViewPort(WindowSize.x, WindowSize.y, 0.0f, 0.0f, 0.0f, 0.0f);


	for (const std::pair<int, std::list<GameEngineRenderer*>>& Group : AllRenderer_)
	{
		float ScaleTime = GameEngineTime::GetInst()->GetDeltaTime(Group.first);
		for (GameEngineRenderer* const Renderer : Group.second)
		{
			Renderer->GetTransform().SetView(View);
			Renderer->GetTransform().SetProjection(Projection);
			Renderer->GetTransform().CalculateWorldViewProjection();
			Renderer->ViewPort = ViewPort;
			Renderer->Render(ScaleTime);
		}
	}
}

void GameEngineCamera::Start()
{
	GetActor()->GetLevel()->PushCamera(this);
}

void GameEngineCamera::PushRenderer(GameEngineRenderer* _Renderer)
{
	AllRenderer_[_Renderer->GetOrder()].push_back(_Renderer);
}