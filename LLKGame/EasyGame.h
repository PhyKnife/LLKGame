#pragma once
#include "GameControl.h"
class CEasyGame :
	public CGameControl
{
public:
	CEasyGame();
	~CEasyGame();
	int getTips();
	bool resortMap();
	void setUseTool();
	int getScore();
};

