#include "GameAsset.h"

void GameAsset::Awake()
{
	OnAwake();
}
void GameAsset::Update()
{
	OnUpdate();
}

void GameAsset::PostRender()
{
	OnPostRender();
}

void GameAsset::Destroy()
{
	OnDestroy();
}

void GameAsset::OnAwake()
{

}

void GameAsset::OnUpdate()
{

}

void GameAsset::OnPostRender()
{

}

void GameAsset::OnDestroy()
{

}

int GameAsset::GetID()
{
	return m_iAssetID;
}

bool GameAsset::GetDestroyed()
{
	return m_bDestroyed;
}

void GameAsset::SetDetroyed(bool _bDestroy)
{
	m_bDestroyed = _bDestroy;
}

void GameAsset::SetID(int _iSet)
{
	m_iAssetID = _iSet;
}
