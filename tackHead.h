#pragma once
#include "Engine/GameObject.h"

class tackHead :
    public GameObject
{
public:
	//コンストラクタ
	tackHead(GameObject* parent);
	~tackHead();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
private:
	int hModel_;//タンクモデルのハンドル
	XMFLOAT3 move_;//弾の進行方向
};

