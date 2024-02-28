#include "stdafx.h"
#include "GameLogic.h"
#include <ctime>


CGameLogic::CGameLogic()
{
}

CGameLogic::~CGameLogic()
{
}
/**********
[函数名]
[功能]初始化地图
****************/
void CGameLogic::InitMap(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex m_mapSize)
{
	int totalElementNum = (m_mapSize.row - 2)*(m_mapSize.col - 2);
	//地图初始化
	int *randArray=new int[totalElementNum];
	int *randArrayIndex = new int[totalElementNum];
	int elementArray[20] = { 0 };

	//地图位置序列 元素序列
	for (int i = 0; i < 20; i++)
	{
		randArrayIndex[i] = i;
		elementArray[i] = i;	//地图元素为0~19
	}
	for (int i = 20; i < totalElementNum; i++)
	{
		randArrayIndex[i] = i;
	}

	//剩余位置个数  以及剩余元素个数
	int leaveElement = 20;
	int leaveIndex = (m_mapSize.row - 2)*(m_mapSize.col - 2);

	//取出行数个元素

	for (int i = 0; i < m_mapSize.row - 2; i++)
	{
		///取出一个元素
		srand(time(NULL));
		int randNum = rand() % leaveElement;
		int curElement = elementArray[randNum];
		//交换元素
		elementArray[randNum] = elementArray[--leaveElement];

		//取出实际列数个位置
		for (int j = 0; j < m_mapSize.col - 2; j++)
		{
			//取出一个位置
			srand(time(NULL));
			int randLocIndex = rand() % leaveIndex;
			//取出该位置
			int relLocIndex = randArrayIndex[randLocIndex];
			//换掉该位置
			randArrayIndex[randLocIndex] = randArrayIndex[--leaveIndex];

			//将元素放入该位置
			randArray[relLocIndex] = curElement;
		}
	}

	int count = 0;//当前元素位置
	//将得到的序列填入数组中
	for(int i=1;i<m_mapSize.row-1;i++)
		for (int j = 1; j < m_mapSize.col - 1; j++)
		{
			m_anMap[i][j] = randArray[count];
			count++;
		}
	//边缘位置设置为BLANK
	for (int i = 0; i < m_mapSize.col; i++)
	{
		m_anMap[0][i] = BLANK;
		m_anMap[m_mapSize.row - 1][i] = BLANK;
	}
	for (int i = 1; i < m_mapSize.row - 1; i++)
	{
		m_anMap[i][0] = BLANK;
		m_anMap[i][m_mapSize.col - 1] = BLANK;
	}
	delete(randArray);
	delete(randArrayIndex);
	//从中取出列数个图片
		/*
	int anMap[7][8] = { BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,2,0,1,3,2,2,BLANK,BLANK,1,3,2,1,0,0,BLANK,BLANK,1,3,0,3,4,4,BLANK,BLANK,4,4,4,4,4,4,BLANK,BLANK,4,4,4,4,4,4,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK,BLANK};
	for (int i = 0; i < m_mapSize.row; i++)
	{
		for (int j = 0; j < m_mapSize.col; j++)
		{
			m_anMap[i][j] = anMap[i][j];
		}
	}*/
}

/**********
[函数名]
[功能]判断是否可以连接
****************/
bool CGameLogic::IsLink(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect,LN pNode[MAXLNNUM],Vertex m_mapSize)
{

	if ((sFirstSelect.row == sSecSelect.row) && (sFirstSelect.col == sSecSelect.col))
	{
		return false;
	}//两次选择为同一位置图片
	else if (m_anMap[sFirstSelect.row][sFirstSelect.col] != m_anMap[sSecSelect.row][sSecSelect.col])
	{
		return false;
	}
	else
	{
		//简化判断
		if((sFirstSelect.row==sSecSelect.row)||(sFirstSelect.col==sSecSelect.col))
		{
			//一条直线消子判断
			if (ClearElementByOneLine(m_anMap, sFirstSelect, sSecSelect, pNode))
			{
				return true;
			}
			//三条直线消子判断
			else if (ClearElementByThreeLine(m_anMap, sFirstSelect, sSecSelect, pNode,m_mapSize))
			{
				return true;
			}
		}
		else
		{
			//两条直线消子判断
			if (ClearElementByTwoLine(m_anMap, sFirstSelect, sSecSelect, pNode))
			{
				return true;
			}
			else if (ClearElementByThreeLine(m_anMap, sFirstSelect, sSecSelect, pNode,m_mapSize))
			{
				return true;
			}
		}	
			return false;
	}
}
/**********
[函数名]
[功能]清除可连接图片
****************/
void CGameLogic::Clear(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect)
{
	m_anMap[sFirstSelect.row][sFirstSelect.col] = BLANK;
	m_anMap[sSecSelect.row][sSecSelect.col] = BLANK;
}
/**********
[函数名]
[功能]重排
****************/
void CGameLogic::Resort(int m_anMap[MAXMAPROW][MAXMAPCOL],Vertex m_mapSize)
{
	int maxElementNum = (m_mapSize.row - 2)*(m_mapSize.col - 2);
	//排序前
	int *beforeSort = new int[maxElementNum];
	int relElementNum = 0;//实际元素数量
	
	//查找当前数组中剩余未消除元素
	for (int i = 1; i < m_mapSize.row - 1; i++)
	{
		for (int j = 1; j < m_mapSize.col; j++)
		{
			if (m_anMap[i][j] != BLANK)
			{
				beforeSort[relElementNum++] = m_anMap[i][j];
			}
		}
	}

	//重新排序后
	int *afterSort = new int[relElementNum];
	int curStoreLoc = 0;
	//重排
	for (int i = 0; i < relElementNum; i++)
	{
		srand(time(NULL));
		int randNum = rand() % (relElementNum-curStoreLoc);

		afterSort[curStoreLoc] = beforeSort[randNum];//重排
		//变换原数组中元素
		beforeSort[randNum] = beforeSort[relElementNum - curStoreLoc - 1];
		//指向下一存储位置
		curStoreLoc++;
	}
	int curLoc = 0;
	//恢复地图
	for (int i = 1; i < m_mapSize.row - 1; i++)
	{
		for (int j = 1; j < m_mapSize.col - 1; j++)
		{
			if (m_anMap[i][j] != BLANK)
			{
				m_anMap[i][j] = afterSort[curLoc];
				curLoc++;
			}
		}
	}

	//删除数组
	delete(beforeSort);
	delete(afterSort);
}
/**********
[函数名]
[功能]清空地图
****************/
void CGameLogic::EmptyMap(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex mapSize)
{
	for(int i=1;i<mapSize.row-1;i++)
		for (int j = 1; j < mapSize.col - 1; j++)
		{
			m_anMap[i][j] = BLANK;
		}
}
/**********
[函数名]
[功能]判断同行两点是否可连接
****************/
bool CGameLogic::LinkInRow(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect)
{
	int nRow = sFirstSelect.row;
	int smallerCol;
	int biggerCol;
	//保证col1小于col2

	if (sFirstSelect.col < sSecSelect.col)
	{ 
		smallerCol = sFirstSelect.col;
		biggerCol = sSecSelect.col;
	}
	else
	{
		smallerCol = sSecSelect.col;
		biggerCol = sFirstSelect.col;
	}

	for (int i = smallerCol + 1; i < biggerCol; i++)
	{
		if (m_anMap[nRow][i] != BLANK)
		{
			return false;
		}
	}
	return true;
}
/**********
[函数名]
[功能]判断同行两点是否可连接
****************/
bool CGameLogic::LinkInCol(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect)
{
	int nCol = sFirstSelect.col;
	int smallerRow;
	int biggerRow;
	if (sFirstSelect.row < sSecSelect.row)
	{
		smallerRow = sFirstSelect.row;
		biggerRow = sSecSelect.row;
	}
	else
	{
		smallerRow = sSecSelect.row;
		biggerRow = sFirstSelect.row;
	}

	for (int row = smallerRow + 1; row < biggerRow; row++)
	{
		if (m_anMap[row][nCol] != BLANK)
		{
			return false;
		}
	}
	return true;
}
/**********
[函数名]
[功能]一条直线消子
****************/
bool CGameLogic::ClearElementByOneLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM])
{
	if (sFirstSelect.row == sSecSelect.row)
	{
		if (LinkInRow(m_anMap, sFirstSelect, sSecSelect))
		{
			setLNArray(pNode, sFirstSelect, 0);
			setLNArray(pNode, sSecSelect, 1);
			return true;
		}
	}
	if (sFirstSelect.col == sSecSelect.col)
	{
		if (LinkInCol(m_anMap, sFirstSelect, sSecSelect))
		{
			setLNArray(pNode, sFirstSelect, 0);
			setLNArray(pNode, sSecSelect, 1);
			return true;
		}
	}
	return false;
}

/**********
[函数名]
[功能]两条直线消子
****************/
bool CGameLogic::ClearElementByTwoLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM])
{
	Vertex inflexion;

	//横向连线
	inflexion.row = sFirstSelect.row;
	inflexion.col = sSecSelect.col;
	if ((m_anMap[inflexion.row][inflexion.col] == BLANK) && LinkInRow(m_anMap, sFirstSelect, inflexion) &&  LinkInCol(m_anMap,inflexion, sSecSelect))
	{
		setLNArray(pNode, sFirstSelect, 0);
		setLNArray(pNode, inflexion, 1);
		setLNArray(pNode, sSecSelect, 2);
		return true;
	}
	//纵向连线
	inflexion.row = sSecSelect.row;
	inflexion.col = sFirstSelect.col;
	if ((m_anMap[inflexion.row][inflexion.col] == BLANK) && LinkInCol(m_anMap, sFirstSelect, inflexion) &&  LinkInRow(m_anMap, inflexion, sSecSelect))
	{
		setLNArray(pNode, sFirstSelect, 0);
		setLNArray(pNode, inflexion, 1);
		setLNArray(pNode, sSecSelect, 2);
		return true;
	}
	return false;
}
/**********
[函数名]
[功能]三条直线消子
****************/
bool CGameLogic::ClearElementByThreeLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM],Vertex m_mapSize)
{
	//两个拐点
	Vertex inflexionFirst;
	Vertex inflexionSecond;
	/* 修改存储结构后无需考虑边缘
	//同行且处边缘
	if ((sFirstSelect.row == sSecSelect.row)&&(sFirstSelect.row==0||(sFirstSelect.row==m_mapSize.row-1)))
	{
		//上边缘
		if (sFirstSelect.row == 0)
		{
			inflexionFirst.row = sFirstSelect.row-1;
			inflexionSecond.row = sSecSelect.row - 1;
		}
		//下边缘
		else if(sFirstSelect.row==m_mapSize.row-1)
		{
			inflexionFirst.row = sFirstSelect.row + 1;
			inflexionSecond.row = sSecSelect.row + 1;
		}
		inflexionFirst.col = sFirstSelect.col;
		inflexionSecond.col = sSecSelect.col;

		setLNArray(pNode, sFirstSelect, 0);
		setLNArray(pNode, inflexionFirst, 1);
		setLNArray(pNode, inflexionSecond, 2);
		setLNArray(pNode, sSecSelect, 3);
		return true;
	}
	//同列且处边缘
	if ((sFirstSelect.col == sSecSelect.col) && (sFirstSelect.col == 0 || sFirstSelect.col == m_mapSize.col - 1))
	{
		if (sFirstSelect.col == 0)
		{
			inflexionFirst.col = -1;
			inflexionSecond.col = -1;
		}
		else if (sFirstSelect.col == m_mapSize.col - 1)
		{
			inflexionFirst.col = m_mapSize.col;
			inflexionSecond.col = m_mapSize.col;
		}
		inflexionFirst.row = sFirstSelect.row;
		inflexionSecond.row = sSecSelect.row;
		setLNArray(pNode, sFirstSelect, 0);
		setLNArray(pNode, inflexionFirst, 1);
		setLNArray(pNode, inflexionSecond, 2);
		setLNArray(pNode, sSecSelect, 3);
		return true;
	}
	*/
	//非边缘情况  
	//从起点向左右画线 
	int smallerCol;
	int biggerCol;
	bool startSmall;//起点是否在左边
	if (sFirstSelect.col > sSecSelect.col)
	{
		smallerCol = sSecSelect.col;
		biggerCol = sFirstSelect.col;
		startSmall = false;
	}
	else
	{
		smallerCol = sFirstSelect.col;
		biggerCol = sSecSelect.col;
		startSmall = true;
	}
	
	inflexionFirst.row = sFirstSelect.row;
	inflexionSecond.row = sSecSelect.row;
	//试试从中间画 
	for (int col = smallerCol + 1; col < biggerCol; col++)
	{
		inflexionFirst.col = col;
		inflexionSecond.col = col;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
		{
			return true;
		}
	}
	if (startSmall)//线路次序为中间 左边 右边
	{
		for (int col = smallerCol - 1; col >= 0; col--)
		{
			inflexionFirst.col = col;
			inflexionSecond.col = col;
			if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
			{
				return true;
			}
		}
		for (int col = biggerCol + 1; col < m_mapSize.col; col++)
		{
			inflexionFirst.col = col;
			inflexionSecond.col = col;
			if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
			{
				return true;
			}
		}
	}
	else
	{
		//线路次序为中间 右边 左边
		for (int col = biggerCol + 1; col < m_mapSize.col; col++)
		{
			inflexionFirst.col = col;
			inflexionSecond.col = col;
			if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
			{
				return true;
			}
		}
		for (int col=smallerCol-1;col>=0;col--)
		{
			inflexionFirst.col = col;
			inflexionSecond.col = col;
			if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
			{
				return true;
			}
		}
	}

	//从起点向上下画线
	int smallerRow;
	int biggerRow;
	if (sFirstSelect.row > sSecSelect.row)
	{
		smallerRow = sSecSelect.row;
		biggerRow = sFirstSelect.row;
	}
	else
	{
		smallerRow = sFirstSelect.row;
		biggerRow = sSecSelect.row;
	}

	inflexionFirst.col = sFirstSelect.col;
	inflexionSecond.col = sSecSelect.col;
	//试试从中间开始
	for (int row = smallerRow + 1; row < biggerRow; row++)
	{
		inflexionFirst.row = row;
		inflexionSecond.row = row;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 0))
		{
			return true;
		}
	}
	//从上到下 优先上
	for (int row = smallerRow - 1; row >= 0; row--)
	{
		inflexionFirst.row = row;
		inflexionSecond.row = row;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 0))
		{
			return true;
		}
	}
	for (int row = biggerRow+1; row<m_mapSize.row; row++)
	{
		inflexionFirst.row = row;
		inflexionSecond.row = row;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 0))
		{
			return true;
		}
	}
	return false;
}
/**********
[函数名]
[功能]
****************/
void CGameLogic::setLNArray(LN pNode[MAXLNNUM], Vertex sNode,int nIndex)
{
	pNode[nIndex].row = sNode.row;
	pNode[nIndex].col = sNode.col;
	pNode[nIndex].info = true;
}
/**********
[函数名]
[功能]三条直线消子时封装的是否可以消子函数
****************/
bool CGameLogic::setLNArrayF(LN pNode[MAXLNNUM], Vertex v1, Vertex v2, Vertex v3, Vertex v4, int m_anMap[MAXMAPROW][MAXMAPCOL],int nStatus)
{
	if(nStatus==0)
	{ 	
		if ((m_anMap[v2.row][v2.col] == BLANK) && (m_anMap[v3.row][v3.col] == BLANK) && LinkInCol(m_anMap, v1,v2) && LinkInRow(m_anMap, v2,v3) && LinkInCol(m_anMap, v3,v4))
		{
			setLNArray(pNode, v1, 0);
			setLNArray(pNode, v2, 1);
			setLNArray(pNode, v3, 2);
			setLNArray(pNode, v4, 3);
			return true;
		}
	}
	else if (nStatus == 1)
	{
		if ((m_anMap[v2.row][v2.col] == BLANK) && (m_anMap[v3.row][v3.col] == BLANK) && LinkInRow(m_anMap, v1, v2) && LinkInCol(m_anMap, v2, v3) && LinkInRow(m_anMap, v3, v4))
		{
			setLNArray(pNode, v1, 0);
			setLNArray(pNode, v2, 1);
			setLNArray(pNode, v3, 2);
			setLNArray(pNode, v4, 3);
			return true;
		}
	}

	return false;
}
