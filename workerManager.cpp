#include "workerManager.h"

WorkerManager::WorkerManager() {

	//1、文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//读文件
	if (!ifs.is_open()) {
		//cout << "文件不存在" << endl;//测试输出

		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化指针为空
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2、文件存在 数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {//如果读到eof说明读到了文件尾部，由情况可为空
		//文件为空
		//cout << "文件为空" << endl;
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化指针为空
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3、文件存在，已经有数据
	int num = this->Get_EmpNum();
	//cout << "职工人数为： " << num << endl;
	this->m_EmpNum = num;
	
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据存到数组中
	init_Emp();

	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "职工编号： " << this->m_EmpArray[i]->m_Id
			<< "姓名： " << this->m_EmpArray[i]->m_Name
			<< "职位： " << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}

//统计文件中的人数
int WorkerManager::Get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME,ios::in);//读文件
	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}

	return num;

}


//展示菜单
void WorkerManager::Show_Menu() {
	cout << "**********************************************" << endl;
	cout << "************欢迎使用职工管理系统**************" << endl;
	cout << "***************0.退出管理程序*****************" << endl;
	cout << "***************1.增加职工信息*****************" << endl;
	cout << "***************2.显示职工信息*****************" << endl;
	cout << "***************3.删除离职职工*****************" << endl;
	cout << "***************4.修改职工信息*****************" << endl;
	cout << "***************5.查找职工信息*****************" << endl;
	cout << "***************6.按照序号排序*****************" << endl;
	cout << "***************7.清空所有数据*****************" << endl;
	cout << "***************8.退出管理程序*****************" << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	

}

void WorkerManager::Exit_System() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}

//添加职工
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工的数量" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		//添加操作
		//计算添加后的空间的大小
		int newSize = this->m_EmpNum + addNum;

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下的数据，拷贝到新空间下
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i <= this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int deptId;

			cout << "请输入第" << i + 1 << "个新职工的编号" << endl;
			cin >> id;

			cout << "请输入第" << i + 1 << "个新职工的姓名" << endl;
			cin >> name;

			cout << "请输入该职工的部门编号"<< endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
			cin >> deptId;

			Worker* worker = NULL;

			switch (deptId)
			{
			case 1:
				worker = new Employee(id, name, deptId);
				break;

			case 2:
				worker = new Manager(id, name, deptId);
				break;

			case 3:
				worker = new Boss(id, name, deptId);
				break;

			default:
				{
					cout << "输入的部门id有误" << endl; 
					system("pause");
					system("cls");
					return;
				}
				break;
			}
			//将创建的职工指针，保存在数组中
			newSpace[this->m_EmpNum + i] = worker;
			
		

		}

		//释放原有空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新的职工人数
		this->m_EmpNum = newSize;
		
		//更新职工不为空的标志
		this->m_FileIsEmpty = false;

		//成功添加后保存到文件中
		this->Save();

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;

	}
	else {
		cout << "输入数据有误" << endl;
	}

	system("pause");
	system("cls");
}

//初始化员工
void WorkerManager::init_Emp() 
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;

	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;

		if (dId == 1)//普通职工
		{
			worker = new Employee(id, name, 1);
		}
		else if (dId == 2)//经理
		{
			worker = new Manager(id, name, 2);
		}
		else if (dId == 3)//老板
		{
			worker = new Boss(id, name, 3);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();
}


//显示职工
void WorkerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}

	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用程序接口
			this->m_EmpArray[i]->showInfo();

		}
	}
	system("pause");
	system("cls");
}

//判断职工是否存在
int WorkerManager::IsExit(int id)
{
	int index = -1;

	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

//删除职工
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		//按照职工编号删除
		cout << "请输入想要删除的职工编号：" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExit(id);

		if (index != -1)//职工存在且删除掉index上的职工
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			cout << "删除成功" << endl;
			this->m_EmpNum--;//更新数组中记录的人员个数
			this->Save();
		}
		else
		{
			cout << "删除失败，未找到该职工" << endl;
		}
		system("pause");
		system("cls");
	}

}

//修改职工
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "请输入修改职工的编号：" << endl;
		int id;
		cin >> id;

		int ret = this->IsExit(id);
		if (ret != -1)
		{
			//查找到编号的职工

			delete this->m_EmpArray[ret];
			
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "查到：" << id << "号职工，请输入新的职工号" << endl;
			cin >> newId;

			cout << "请输入新姓名： " << endl;
			cin >> newName;

			cout << "请输入岗位" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、老板" << endl;

			cin >> dSelect;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 1);
				break;
			case 3:
				worker = new Boss(newId, newName, 1);
				break;

			default:
				cout << "输入的岗位有误" << endl;
				break;
			}

			//更新到数组中
			this->m_EmpArray[ret] = worker;

			cout << "修改成功" << endl;

			//保存到文件中
			this->Save();
		}
		else
		{
			cout << "修改失败，查无此人" << endl;
		}
	}
	system("pause");
	system("cls");
}


//查找职工
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空" << endl;
	}
	else
	{
		cout << "请输入查找的方式" << endl;
		cout << "1、按照职工的编号查找" << endl;
		cout << "2、按照职工的姓名查找" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//按照编号查
			int id;
			cout << "请输入查找的职工编号：" << endl;
			cin >> id;
			int ret = this->IsExit(id);
			if (ret != -1)
			{
				//找到职工
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "查无此人" << endl;
			}
		}
		else if(select == 2)
		{
			//按照姓名查
			string name;
			cout << "请输入查找的姓名：" << endl;
			cin >> name;

			int flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
				cout << "查找成功！该职工信息如下：" << endl;

				this->m_EmpArray[i]->showInfo();
				flag = true;
				}
			}
			if (flag == false)
			{
				cout << "查无此人" << endl;
			}
		}
		else
		{
		cout << "输入的选项有误!" << endl;
		}

	}
	system("pause");
	system("cls");
}

//按照职工编号进行排序
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或为空!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序的方式：" << endl;
		cout << "1、按职工号升序排序" << endl;
		cout << "2、按职工号降序排序" << endl;

		int select = 0;
		cin >> select;

		if (select == 1 || select == 2)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				int minOrMax = i;//声明最小值或者最大值的下标
				for (int j = i + 1; j < this->m_EmpNum; j++)
				{
					if (select == 1)//升序
					{
						if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
						{
							minOrMax = j;
						}
					}
					else//降序
					{
						if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
						{
							minOrMax = j;
						}
					}
				}
				//判断一开始认定的最大值或者最小值是不是实际上的最大值或最小值，不是则交换
				if (i != minOrMax)
				{
					Worker* temp = this->m_EmpArray[i];
					this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
					this->m_EmpArray[minOrMax] = temp;
				}
			}
			cout << "排序成功！排序后的结果为：" << endl;
			this->Save();//排序后的结果保存到文件中
			this->Show_Emp();
		}
		else
		{
			cout << "输入有误" << endl;
			system("pause");
			system("cls");
		}

	}
}

//清空文件
void WorkerManager::Clean_File()
{
	cout << "确定清空全部数据吗？" << endl;
	cout << "输入1来确定操作" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc);//删除文件后重新创建
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//删除堆区的每个职工对象
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区对的数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功" << endl;
	}
	else
	{
		cout << "已取消清空操作" << endl;
	}

	system("pause");
	system("cls");
}


//保存文件
void WorkerManager::Save() 
{
	fstream ofs;
	ofs.open(FILENAME, ios::out);//写文件的方式打开文件
	for (int i = 0; i < this->m_EmpNum; i++) 
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	
	//关闭文件
	ofs.close();

}


WorkerManager::~WorkerManager() 
{
	if (this->m_EmpArray != NULL) 
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}