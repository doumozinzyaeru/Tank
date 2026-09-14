#include "Kusa.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
#include "Ground.h"


Kusa::Kusa(GameObject* parent)
	:GameObject(parent,"kusa"),hModel_(-1)
{
}

Kusa::~Kusa()
{
}

void Kusa::Initialize()
{
	hModel_ = Model::Load("kusa.fbx");

	//モデルハンドル、開始フレーム、終了フレーム、アニメーション速度
	Model::SetAnimFrame(hModel_, 1, 180, 0.5f);
	assert(hModel_ >= 0);

	BoxCollider* collider = new BoxCollider({ 0,0,0 }, { 1.0f,2.0f,1.0f });//コライダーを作る
	AddCollider(collider);

}

void Kusa::Update()
{
}

void Kusa::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Kusa::Release()
{
}
