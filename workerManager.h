#pragma once//防止头文件重复包含
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

	//显示菜单
	void Show_Menu();

	//退出系统
	void Exit_System();

	//记录职工人数
	int m_EmpNum;

	//职工数组指针
	Worker** m_EmpArray;

	//添加职工
	void Add_Emp();

	//判断文件是否为空的标准
	bool m_FileIsEmpty;

	//统计文件中的人数
	int Get_EmpNum();

	//初始化职工
	void init_Emp();

	//显示职工
	void Show_Emp();

	//判断职工是否存在
	int IsExit(int id);

	//删除职工
	void Del_Emp();

	//修改职工
	void Mod_Emp();

	//查找职工
	void Find_Emp();

	//保存文件
	void Save();

	//按照职工编号进行排序
	void Sort_Emp();

	//清空文件
	void Clean_File();
	

	~WorkerManager();

};
