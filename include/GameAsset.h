#pragma once
#include <memory>
#include <vector>

class GameAsset
{
public:

	void Awake();
	void Update();
	void PostRender();
	void Destroy();

	int GetID();
	bool GetDestroyed();
	void SetDetroyed(bool _bDestroy);
protected:
	int m_iAssetID;
	bool m_bDestroyed;

	virtual void OnAwake();
	virtual void OnUpdate();
	virtual void OnPostRender();
	virtual void OnDestroy();
	void SetID(int _iSet);
};