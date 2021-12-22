#pragma once
#include <vector>
#include <string>
#include "../Util/Singleton.h"

class ColiderComponent;
class ColiderManager : public Singleton<ColiderManager>
{
public:
	void AddColider(ColiderComponent* col);
	ColiderComponent* FindColider(const std::wstring& tag);

	void CheckToMouse(ColiderComponent* col);
	void CheckToColider(ColiderComponent* col);
private:
	std::vector<ColiderComponent*> m_vecCols;
};