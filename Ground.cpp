#include "Ground.h"
#include "Engine/Model.h"
#include <assert.h>


Ground::Ground(GameObject* parent)
	:GameObject(parent,"Ground"),hModel_(-1)
{
}

Ground::~Ground()
{
}

void Ground::Initialize()
{
	hModel_ = Model::Load("Ground.fbx");
	assert(hModel_ >= 0);
}

void Ground::Update()
{

}

void Ground::Draw()
{
	//transform_.scale_{1,1,1}

	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Ground::Release()
{
}
