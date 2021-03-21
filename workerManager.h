#pragma once//��ֹͷ�ļ��ظ�����
#include <iostream>
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
#include <fstream>
#define FILENAME "empFile.txt"
using namespace std;


class WorkerManager {
public:
	WorkerManager();

	//��ʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void Exit_System();

	//��¼ְ������
	int m_EmpNum;

	//ְ������ָ��
	Worker** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//�ж��ļ��Ƿ�Ϊ�յı�׼
	bool m_FileIsEmpty;

	//ͳ���ļ��е�����
	int Get_EmpNum();

	//��ʼ��ְ��
	void init_Emp();

	//��ʾְ��
	void Show_Emp();

	//�ж�ְ���Ƿ����
	int IsExit(int id);

	//ɾ��ְ��
	void Del_Emp();

	//�޸�ְ��
	void Mod_Emp();

	//����ְ��
	void Find_Emp();

	//�����ļ�
	void Save();

	//����ְ����Ž�������
	void Sort_Emp();

	//����ļ�
	void Clean_File();
	

	~WorkerManager();

};
