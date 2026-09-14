#include "Tank.h"
#include "Engine/Model.h"
#include <assert.h>
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Engine/Camera.h"
#include "tackHead.h"


namespace
{
	XMVECTOR vFront = { 0,0,1,0 };//タンクの前方向ベクトル
	const float movespeed = 0.1f;
	const float CAM_HEIGHT_BIAS = 0.2f;
	enum CAM_TYPE
	{
		FIXED_CAM,//固定カメラ
		TPS_CAM,//３人称視点カメラ
		TPS_CAMROT,//三人称紫檀カメラ回転
		FPS_CAM,//一人称視点カメラ
		CAM_TYPE_MAX

	};
}

//タンクのボディを表すクラス
Tank::Tank(GameObject* parent)
	:GameObject(parent, "Tank"), hModel_(-1)
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);
	Instantiate<tackHead>(this);
}

void Tank::Update()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード;読み込み
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.position_.y));//Y軸回転行列を作る
	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);//回転行列をベクトルにかけると、回転したベクトルが得られる

	if (Input::IsKeyDown(DIK_C))
	{
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
	}
	switch (camType_)
	{
	case FIXED_CAM:
		SetFixedCam();
		break;
	case TPS_CAM:
	{
		XMFLOAT3 camPos = transform_.position_;//タンクの位置をカメラの位置にする
		camPos.y = camPos.y + 5.0f;//カメラの高さをタンクの位置より高くする
		camPos.z = camPos.z - 13.0f;//カメラの位置をタンクの位置より少し後ろにする
		Camera::SetPosition(camPos);//カメラの位置を設定
		Camera::SetTarget(transform_.position_);//カメラの注視点をタンクの位置にする
	}
		break;
	case TPS_CAMROT:
		//3人称視点回転処理
	{
		XMFLOAT3 camPos;
		XMVECTOR vCAM = { 0.0f,3.0f,-7.0f,0.0f };
		vCAM = XMVector3TransformCoord(vCAM, matRot);//タンクの回転をカメラの位置に反映させる
		XMStoreFloat3(&camPos, vPos + vCAM);
		Camera::SetPosition(camPos);
		Camera::SetTarget(transform_.position_);
	}
		break;
	case FPS_CAM:
		//一人称視点カメラ
		XMFLOAT3 camPos = transform_.position_;
		camPos.y =camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos);//カメラの位置をタンクの位置にする
		XMFLOAT3 camTarget;//カメラの注視点
		XMStoreFloat3(&camTarget, vPos + vMove);
		Camera::SetTarget(camTarget);
		break;
	}



	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 1.0f;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 1.0f;
	}
	Debug::Log("CAMTYPE=");
	Debug::Log(camType_, true);//後のtrueは改行するかどうか
	if (Input::IsKey(DIK_UP))
	{
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード;読み込み
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.position_.y));
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);//回転行列をベクトルにかけると、回転したベクトルが得られる
		vPos = vPos + movespeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);//ストア；書き込み
		
	}
	if (Input::IsKey(DIK_DOWN))
	{
		XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード;読み込み
		XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.position_.y));
		XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);//回転行列をベクトルにかけると、回転したベクトルが得られる
		vPos = vPos - movespeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);//ストア；書き込み
	}
	//レイキャストして、地面に落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は0より下に彫られて作られている
	data.dir = { 0,-1,0 };//真下にレイを飛ばす

	Ground* pGround = (Ground*)FindObject("Ground");
	int hGroundModel = pGround->Getmodelhandle();
	Model::RayCast(hGroundModel, &data);

	if (data.hit == true)
	{
		transform_.position_.y = - data.dist;
		//レイの発射位置から、地面までの距離を引いて、地面にぴったりつける
	}
}
	

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}
