#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"
#include "Kusa.h"

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent,"PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);//親をplaysceneにして地面を生成
	Instantiate<Tank>(this);
	Kusa* k = Instantiate<Kusa>(this);
	k->SetPosition(4, 2, 2);
	Enemy*e=Instantiate<Enemy>(this);
	e->SetPosition(2, 2, 2);
	Enemy* e2 = Instantiate<Enemy>(this);
	e2->SetPosition(8, -2, 2);
	Enemy* e3 = Instantiate<Enemy>(this);
	e3->SetPosition(-3, -2, 2);
	Enemy* e4 = Instantiate<Enemy>(this);
	e4->SetPosition(-6, -2, 2);
	Enemy* e5 = Instantiate<Enemy>(this);
	e5->SetPosition(-7, 1, 2);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
