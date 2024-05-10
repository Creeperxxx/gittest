#include "CBasicGame.h"
#include "CGameControl.h"
#include "CGameLogic.h"
#include "global.h"
#include "CGraph.h"

CBasicGame::CBasicGame()
{
	gameMode = 1;
}

void CBasicGame::StartGame()
{
	CGameLogic logic;
	logic.InitLevel1(this->mGraph);
	gameMode = 1;
}

void CBasicGame::StartGame2()
{
	CGameLogic logic;
	logic.InitLevel2(this->mGraph);
	gameMode = 1;
}
void CBasicGame::StartGame3()
{
	CGameLogic logic;
	logic.InitLevel3(this->mGraph);
	gameMode = 1;
}

int CBasicGame::GetElement(int nRow, int nCol)
{
	return this->mGraph.getVex(nRow * mGraph.eCol + nCol);
}

void CBasicGame::SetFirstPoint(int nRow, int nCol)
{
	this->m_svSelFst.row = nRow;
	this->m_svSelFst.col = nCol;
	this->m_svSelFst.index = nRow * mGraph.eCol + nCol;
}

void CBasicGame::SetSecondPoint(int nRow, int nCol)
{
	this->m_svSelSec.row = nRow;
	this->m_svSelSec.col = nCol;
	this->m_svSelSec.index = nRow * mGraph.eCol + nCol;
}

Vertex CBasicGame::getFirstPoint()
{
	return this->m_svSelFst;
}

Vertex CBasicGame::getSecondPoint()
{
	return this->m_svSelSec;
}
bool CBasicGame::Link(stack<Vertex>& path)
{
	if (m_svSelFst.row == m_svSelSec.row &&
		m_svSelFst.col == m_svSelSec.col)
	{
		return false;
	}
	if (mGraph.getVex(m_svSelFst.row * mGraph.eCol + m_svSelFst.col) !=
		mGraph.getVex(m_svSelSec.row * mGraph.eCol + m_svSelSec.col) ||
		mGraph.getVex(m_svSelFst.row * mGraph.eCol + m_svSelFst.col) == BLANK ||
		mGraph.getVex(m_svSelSec.row * mGraph.eCol + m_svSelSec.col) == BLANK)
		return false;
	CGameLogic gameLogic;
	if (gameLogic.IsLink(mGraph, m_svSelFst, m_svSelSec))
	{
		path = gameLogic.getPath();
		gameLogic.Clear(mGraph, m_svSelFst, m_svSelSec);
		//消除棋子
		return true;
	}
	return false;
}

CGraph CBasicGame::getGraph()
{
	return this->mGraph;
}

int CBasicGame::isWin(int nTime)
{
	CGameLogic gameLogic;

	if (nTime <= 0)
	{
		return GAME_LOSE;
	}

	if (gameLogic.isBlank(this->mGraph))
	{
		return GAME_WIN;
	}
	return GAME_PLAY;
}

bool CBasicGame::Help(stack<Vertex>& path, int& row1, int& co1, int& row2, int& col2)
{
	CGameLogic gameLogic;
	if (!gameLogic.isBlank(this->mGraph))
	{
		if (gameLogic.SearchValidPath(mGraph, row1, co1, row2, col2)) {
			path = gameLogic.getPath();
			return true;
		}
	}
	return false;
}


void CBasicGame::ClearMap()
{
	// TODO: 在此处添加实现代码.
	this->mGraph.ClearMap();
}
