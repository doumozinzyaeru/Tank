#include "Enemy.h"
#include "Engine/Model.h"
#include "Engine/BoxCollider.h"
#include <assert.h>
#include "Ground.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy"),hModel_(-1)
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	hModel_ = Model::Load("Enemy.fbx");
	
	
	//モデルハンドル、開始フレーム、終了フレーム、アニメーション速度
	Model::SetAnimFrame(hModel_, 1, 100, 0.5f);
	assert(hModel_ >= 0);

	BoxCollider* collider = new BoxCollider({ 0,0,0 }, { 1.0f,2.0f,1.0f });//コライダーを作る
	AddCollider(collider);

	float x = (rand() / RAND_MAX) * 5.0f - 10.0f;
	float z = (rand() / RAND_MAX) * 5.0f - 10.0f;
	SetPosition(x, 0, z);
}

void Enemy::Update()
{
}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}

void Enemy::OnCollision(GameObject* pTarget)
{
	if (pTarget->GetObjectName() == "Bullet")
	{
		KillMe();
	}
}

