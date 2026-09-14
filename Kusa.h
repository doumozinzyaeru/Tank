#pragma once
#include "Engine/GameObject.h"
class Kusa :
    public GameObject
{
public:
	//コンストラクタ
	Kusa(GameObject* parent);
	~Kusa();
	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	int Getmodelhandle() { return hModel_; }
private:
	int hModel_;

};

