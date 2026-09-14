#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include <assert.h>

Bullet::Bullet(GameObject* parent)
	:GameObject(parent,"Bullet"),hModel_(-1),move_(XMFLOAT3(0,0,0))
{
}

Bullet::~Bullet()
{
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);
	Collider* collider = new SphereCollider({ 0,0,0 }, 0.25f);//半径0.5の球型の当たり判定を作る
	AddCollider(collider);//当たり判定をBulletに追加
}

void Bullet::Update()
{
		//transform_.position_ = transform_.position_ + move_;//弾の進行方向に移動する
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);
		move_.y -= 0.005f;//重力をつける
		XMVECTOR vMove = XMLoadFloat3(&move_);

		vPos = vPos + vMove;//弾の進行方向に移動する

		XMStoreFloat3(&transform_.position_, vPos);//ストア書き込み
		//transform_.position_.y += move_.y;
		//transform_.position_.z += move_.z;
		//if (transform_.position_.z > 50.0f || transform_.position_.z < -50.0f
			//||transform_.position_.x > 50.0f || transform_.position_.x < -50.0f)
		if(transform_.position_.y<-50.0f)//ありえないくらい下に行ったら消す
		{
			KillMe();//弾がある程度遠くに行ったら消す
		}
	}
//弾の弾道を重力つける
//敵を配置（敵もレイキャストして、xz座標ランダで置く）まずは一匹
//当たり判定（コライダーの設置）
XMFLOAT3 velocity_;
float gravity_ = -0.01f;



void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
