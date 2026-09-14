#include "Saikoro.h"
#include "Engine/Model.h"

Saikoro::Saikoro(GameObject* parent)
	:GameObject(parent, "Saikoro"), hModel_(-1)
{
	hModel_ = Model::Load("saikoro.fbx");
}

Saikoro::~Saikoro()
{
}

void Saikoro::Initialize()
{
	Model::Draw(hModel_);
}

void Saikoro::Update()
{
}

void Saikoro::Draw()
{
}

void Saikoro::Release()
{
}
