#include "PreCompile.h"
#include "Player.h"
#include <GameEngineBase/GameEngineInput.h>
#include <iostream>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineContents/GlobalContentsValue.h>
#include "ScoreTestComponent.h"
#include <GameEngineCore/GameEngineDefaultRenderer.h>
#include <GameEngineCore/GameEngineRenderingPipeLine.h>
#include <GameEngineCore/GameEngineVertexShader.h>
#include <GameEngineCore/GameEngineConstantBuffer.h>
#include <GameEngineCore/GameEngineDevice.h>

Player::Player() 
	: Speed(50.0f)
{
}

Player::~Player() 
{
}

void Player::Start()
{
	if (false == GameEngineInput::GetInst()->IsKey("PlayerLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("PlayerLeft", VK_NUMPAD4);
		GameEngineInput::GetInst()->CreateKey("PlayerRight", VK_NUMPAD6);
		GameEngineInput::GetInst()->CreateKey("PlayerUp", VK_NUMPAD9);
		GameEngineInput::GetInst()->CreateKey("PlayerDown", VK_NUMPAD7);
		GameEngineInput::GetInst()->CreateKey("PlayerForward", VK_NUMPAD8);
		GameEngineInput::GetInst()->CreateKey("PlayerBack", VK_NUMPAD5);
		GameEngineInput::GetInst()->CreateKey("Rot+", VK_NUMPAD1);
		GameEngineInput::GetInst()->CreateKey("Rot-", VK_NUMPAD2);
	}


	GetTransform().SetLocalScale({1, 1, 1});

	ScoreTestComponent* ScoreCom = CreateComponent<ScoreTestComponent>();
	{
		Renderer = CreateComponent<GameEngineDefaultRenderer>();
		Renderer->GetTransform().SetLocalScale({ 100, 100, 100 });
		Renderer->SetPipeLine("Color");
		// 내 맴버변수가 아니라 다른객체의 맴버변수를 사용했다면
		// 이건 터질수 있다.

		Color = { 0.5f, 0.5f, 0.1f, 1.0f };

		Renderer->PipeLineHelper.SetConstantBufferNew("ResultColor", Color);
	}
}

void Player::Update(float _DeltaTime)
{
	if (true == GameEngineInput::GetInst()->IsPress("PlayerLeft"))
	{
		Color.r += 1.0f * _DeltaTime;

		GetTransform().SetWorldMove(GetTransform().GetLeftVector() * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerRight"))
	{
		GetTransform().SetWorldMove(GetTransform().GetRightVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerUp"))
	{
		GetTransform().SetWorldMove(GetTransform().GetUpVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerDown"))
	{
		GetTransform().SetWorldMove(GetTransform().GetDownVector() * Speed * _DeltaTime);
	}

	if (true == GameEngineInput::GetInst()->IsPress("PlayerForward"))
	{
		GetTransform().SetWorldMove(GetTransform().GetForwardVector() * Speed * _DeltaTime);
	}
	if (true == GameEngineInput::GetInst()->IsPress("PlayerBack"))
	{
		GetTransform().SetWorldMove(GetTransform().GetBackVector() * Speed * _DeltaTime);
	}

	//if (true == GameEngineInput::GetInst()->IsPress("Rot+"))
	//{
	//	CurRenderer->GetTransform().SetLocalRotate({ 0.0f, 0.0f, 360.0f * _DeltaTime });
	//}
	//if (true == GameEngineInput::GetInst()->IsPress("Rot-"))
	//{
	//	CurRenderer->GetTransform().SetLocalRotate({ 0.0f, 0.0f, -360.0f * _DeltaTime });
	//}

	// GlobalContentsValue::Actors::TestMonster

	// ChildRenderer->GetTransform().SetWorldPosition({ 150.0f, 100.0f, 30.0f });

}