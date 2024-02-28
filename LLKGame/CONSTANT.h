#pragma once
//��Ϸ��ͼ��ʼ��
#define MAXMAPROW 18     
#define MAXMAPCOL 24	 //��ͼΪ16*22  ��ԵΪ��λ�� ����Ϊ2�ı���

#define ELEMENTWIDTH 40 //��Ϸͼ���
#define ELEMENTHEIGHT 40 //��Ϸͼ����
#define STARTTOPLOC 50		//��ϷԪ�س�ʼ����λ�þ���涥�˳���
#define STARTLEFTLOC 50		//��ϷԪ�س�ʼ����λ�þ�������λ��
//��Ϸ�Ѷ�
#define EASY 1
#define MEDIUM 2
#define DIFFICULT 3
//��Ϸ�����Ѷȵ�ͼ��С
#define EASYMAPROW 8
#define EASYMAPCOL 10 //�򵥵�ͼΪ6*8
#define MEDIUMMAPROW 12
#define MEDIUMMAPCOL 16 //�м���ͼΪ10*14
#define DIFFICULTMAPROW 18
#define DIFFICULTMAPCOL 24//�߼���ͼΪ16*22
//���������ʱ������
#define MAXLNNUM 4  //������ʱ������������ʼ�ڵ������յ�  ��������ĸ��� ����ʱʹ��

//�հ�Ԫ��
#define BLANK -1		//Ԫ���Ѿ�����

//�û������Ӧ����
#define SELECTBLANK 1 //����հ�Ԫ��
#define FIRSTSELECT 2 //�ǿհ�Ԫ����Ϊ��һ��ѡ��
#define CLEARSELECT 3 //�ڶ���ѡ�������������
#define CLEARSELECTUSETOOL 4 //ʹ�õ��߽�������
#define RESELECT 5 //�ڶ���ѡ�������㲻������

//��ʱ��
#define PLAY_TIMER_ID 1   //��ʱ��ID

//��Ϸ״̬
#define GAME_GOING 1 //��Ϸ���ڽ�����
#define GAME_PAUSE 2 //��Ϸ��ͣ

//��Ϸ��Ҫ����
#define GAME_MAIN_FRAME 0  //������
#define GAME_MODEL_BASE 1 //����ģʽ
#define GAME_MODEL_EASY 2 //����ģʽ
#define GAME_MODEL_LEVEL 3 //�ؿ�ģʽ

//��ʾ���
#define TIPS_GET 1 //�ɹ������ʾ
#define TIPS_NOTFIND 2 //û�пɴ�·��
#define TIPS_SCORENOTENOUGH 3//���ֲ���

//�ļ����
#define RANKFILEPATH _T("file\\score.txt")  //������Ϣ·��
#define CONFIGFILEPATH _T("file\\config.ini") //������Ϣ·��

#define MAXRANKMES 1000 //�����Ϣ����
#define MAXFILEPATHLENGTH 32 //���·������

#define DEFAULTELEMENT _T("source\\element\\smile.bmp") 
#define DEFAULTMASK _T("source\\element\\smile_mask.bmp")
#define DEFAULTPICTURE _T("source\\theme\\theme0.bmp")
#define DEFAULTMUSIC _T("source\\music\\default.wav")

//���а�
#define MAXRANKLEVEL 10//���а��������