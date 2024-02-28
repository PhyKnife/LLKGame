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
[������]
[����]��ʼ����ͼ
****************/
void CGameLogic::InitMap(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex m_mapSize)
{
	int totalElementNum = (m_mapSize.row - 2)*(m_mapSize.col - 2);
	//��ͼ��ʼ��
	int *randArray=new int[totalElementNum];
	int *randArrayIndex = new int[totalElementNum];
	int elementArray[20] = { 0 };

	//��ͼλ������ Ԫ������
	for (int i = 0; i < 20; i++)
	{
		randArrayIndex[i] = i;
		elementArray[i] = i;	//��ͼԪ��Ϊ0~19
	}
	for (int i = 20; i < totalElementNum; i++)
	{
		randArrayIndex[i] = i;
	}

	//ʣ��λ�ø���  �Լ�ʣ��Ԫ�ظ���
	int leaveElement = 20;
	int leaveIndex = (m_mapSize.row - 2)*(m_mapSize.col - 2);

	//ȡ��������Ԫ��

	for (int i = 0; i < m_mapSize.row - 2; i++)
	{
		///ȡ��һ��Ԫ��
		srand(time(NULL));
		int randNum = rand() % leaveElement;
		int curElement = elementArray[randNum];
		//����Ԫ��
		elementArray[randNum] = elementArray[--leaveElement];

		//ȡ��ʵ��������λ��
		for (int j = 0; j < m_mapSize.col - 2; j++)
		{
			//ȡ��һ��λ��
			srand(time(NULL));
			int randLocIndex = rand() % leaveIndex;
			//ȡ����λ��
			int relLocIndex = randArrayIndex[randLocIndex];
			//������λ��
			randArrayIndex[randLocIndex] = randArrayIndex[--leaveIndex];

			//��Ԫ�ط����λ��
			randArray[relLocIndex] = curElement;
		}
	}

	int count = 0;//��ǰԪ��λ��
	//���õ�����������������
	for(int i=1;i<m_mapSize.row-1;i++)
		for (int j = 1; j < m_mapSize.col - 1; j++)
		{
			m_anMap[i][j] = randArray[count];
			count++;
		}
	//��Եλ������ΪBLANK
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
	//����ȡ��������ͼƬ
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
[������]
[����]�ж��Ƿ��������
****************/
bool CGameLogic::IsLink(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect,LN pNode[MAXLNNUM],Vertex m_mapSize)
{

	if ((sFirstSelect.row == sSecSelect.row) && (sFirstSelect.col == sSecSelect.col))
	{
		return false;
	}//����ѡ��Ϊͬһλ��ͼƬ
	else if (m_anMap[sFirstSelect.row][sFirstSelect.col] != m_anMap[sSecSelect.row][sSecSelect.col])
	{
		return false;
	}
	else
	{
		//���ж�
		if((sFirstSelect.row==sSecSelect.row)||(sFirstSelect.col==sSecSelect.col))
		{
			//һ��ֱ�������ж�
			if (ClearElementByOneLine(m_anMap, sFirstSelect, sSecSelect, pNode))
			{
				return true;
			}
			//����ֱ�������ж�
			else if (ClearElementByThreeLine(m_anMap, sFirstSelect, sSecSelect, pNode,m_mapSize))
			{
				return true;
			}
		}
		else
		{
			//����ֱ�������ж�
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
[������]
[����]���������ͼƬ
****************/
void CGameLogic::Clear(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect)
{
	m_anMap[sFirstSelect.row][sFirstSelect.col] = BLANK;
	m_anMap[sSecSelect.row][sSecSelect.col] = BLANK;
}
/**********
[������]
[����]����
****************/
void CGameLogic::Resort(int m_anMap[MAXMAPROW][MAXMAPCOL],Vertex m_mapSize)
{
	int maxElementNum = (m_mapSize.row - 2)*(m_mapSize.col - 2);
	//����ǰ
	int *beforeSort = new int[maxElementNum];
	int relElementNum = 0;//ʵ��Ԫ������
	
	//���ҵ�ǰ������ʣ��δ����Ԫ��
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

	//���������
	int *afterSort = new int[relElementNum];
	int curStoreLoc = 0;
	//����
	for (int i = 0; i < relElementNum; i++)
	{
		srand(time(NULL));
		int randNum = rand() % (relElementNum-curStoreLoc);

		afterSort[curStoreLoc] = beforeSort[randNum];//����
		//�任ԭ������Ԫ��
		beforeSort[randNum] = beforeSort[relElementNum - curStoreLoc - 1];
		//ָ����һ�洢λ��
		curStoreLoc++;
	}
	int curLoc = 0;
	//�ָ���ͼ
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

	//ɾ������
	delete(beforeSort);
	delete(afterSort);
}
/**********
[������]
[����]��յ�ͼ
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
[������]
[����]�ж�ͬ�������Ƿ������
****************/
bool CGameLogic::LinkInRow(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect)
{
	int nRow = sFirstSelect.row;
	int smallerCol;
	int biggerCol;
	//��֤col1С��col2

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
[������]
[����]�ж�ͬ�������Ƿ������
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
[������]
[����]һ��ֱ������
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
[������]
[����]����ֱ������
****************/
bool CGameLogic::ClearElementByTwoLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM])
{
	Vertex inflexion;

	//��������
	inflexion.row = sFirstSelect.row;
	inflexion.col = sSecSelect.col;
	if ((m_anMap[inflexion.row][inflexion.col] == BLANK) && LinkInRow(m_anMap, sFirstSelect, inflexion) &&  LinkInCol(m_anMap,inflexion, sSecSelect))
	{
		setLNArray(pNode, sFirstSelect, 0);
		setLNArray(pNode, inflexion, 1);
		setLNArray(pNode, sSecSelect, 2);
		return true;
	}
	//��������
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
[������]
[����]����ֱ������
****************/
bool CGameLogic::ClearElementByThreeLine(int m_anMap[MAXMAPROW][MAXMAPCOL], Vertex sFirstSelect, Vertex sSecSelect, LN pNode[MAXLNNUM],Vertex m_mapSize)
{
	//�����յ�
	Vertex inflexionFirst;
	Vertex inflexionSecond;
	/* �޸Ĵ洢�ṹ�����迼�Ǳ�Ե
	//ͬ���Ҵ���Ե
	if ((sFirstSelect.row == sSecSelect.row)&&(sFirstSelect.row==0||(sFirstSelect.row==m_mapSize.row-1)))
	{
		//�ϱ�Ե
		if (sFirstSelect.row == 0)
		{
			inflexionFirst.row = sFirstSelect.row-1;
			inflexionSecond.row = sSecSelect.row - 1;
		}
		//�±�Ե
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
	//ͬ���Ҵ���Ե
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
	//�Ǳ�Ե���  
	//����������һ��� 
	int smallerCol;
	int biggerCol;
	bool startSmall;//����Ƿ������
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
	//���Դ��м仭 
	for (int col = smallerCol + 1; col < biggerCol; col++)
	{
		inflexionFirst.col = col;
		inflexionSecond.col = col;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 1))
		{
			return true;
		}
	}
	if (startSmall)//��·����Ϊ�м� ��� �ұ�
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
		//��·����Ϊ�м� �ұ� ���
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

	//����������»���
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
	//���Դ��м俪ʼ
	for (int row = smallerRow + 1; row < biggerRow; row++)
	{
		inflexionFirst.row = row;
		inflexionSecond.row = row;
		if (setLNArrayF(pNode, sFirstSelect, inflexionFirst, inflexionSecond, sSecSelect, m_anMap, 0))
		{
			return true;
		}
	}
	//���ϵ��� ������
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
[������]
[����]
****************/
void CGameLogic::setLNArray(LN pNode[MAXLNNUM], Vertex sNode,int nIndex)
{
	pNode[nIndex].row = sNode.row;
	pNode[nIndex].col = sNode.col;
	pNode[nIndex].info = true;
}
/**********
[������]
[����]����ֱ������ʱ��װ���Ƿ�������Ӻ���
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
