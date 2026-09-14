#include "tackHead.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include <assert.h>
#include "Bullet.h"

tackHead::tackHead(GameObject* parent)
	:GameObject(parent, "tackHead"), hModel_(-1)
{
}

tackHead::~tackHead()
{
}

void tackHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);
}

void tackHead::Update()
{
	if (Input::IsKey(DIK_P))
	{
		transform_.rotate_.y += 1.0f;
	}
	if (Input::IsKey(DIK_O))
	{
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKey(DIK_SPACE))
	{
		const float BULLET_SPEED = 0.2f;//弾のスピードを設定
		XMFLOAT3 canonTop = Model::GetBonePosition(hModel_, "Top");
		XMFLOAT3 canonRoot = Model::GetBonePosition(hModel_, "Root");
		XMVECTOR vTop = XMLoadFloat3(&canonTop);
		XMVECTOR vRoot = XMLoadFloat3(&canonRoot);
		XMVECTOR vMove = XMVectorSubtract(vTop, vRoot);
		vMove = 0.2f * vMove;//弾のスピードを設定
		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);

		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());//親をタンクにして弾
		pBullet->setmoveVector(move);
		pBullet->SetPosition(canonTop);//弾の位置を砲台の先端にする
	}
}

void tackHead::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void tackHead::Release()
{
}

