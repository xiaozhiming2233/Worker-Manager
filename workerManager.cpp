#include "workerManager.h"

WorkerManager::WorkerManager() {

	//1���ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in);//���ļ�
	if (!ifs.is_open()) {
		//cout << "�ļ�������" << endl;//�������

		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ��ָ��Ϊ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ����� ����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {//�������eof˵���������ļ�β�����������Ϊ��
		//�ļ�Ϊ��
		//cout << "�ļ�Ϊ��" << endl;
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ��ָ��Ϊ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3���ļ����ڣ��Ѿ�������
	int num = this->Get_EmpNum();
	//cout << "ְ������Ϊ�� " << num << endl;
	this->m_EmpNum = num;
	
	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݴ浽������
	init_Emp();

	/*for (int i = 0; i < this->m_EmpNum; i++)
	{
		cout << "ְ����ţ� " << this->m_EmpArray[i]->m_Id
			<< "������ " << this->m_EmpArray[i]->m_Name
			<< "ְλ�� " << this->m_EmpArray[i]->m_DeptId << endl;
	}*/
}

//ͳ���ļ��е�����
int WorkerManager::Get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME,ios::in);//���ļ�
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


//չʾ�˵�
void WorkerManager::Show_Menu() {
	cout << "**********************************************" << endl;
	cout << "************��ӭʹ��ְ������ϵͳ**************" << endl;
	cout << "***************0.�˳��������*****************" << endl;
	cout << "***************1.����ְ����Ϣ*****************" << endl;
	cout << "***************2.��ʾְ����Ϣ*****************" << endl;
	cout << "***************3.ɾ����ְְ��*****************" << endl;
	cout << "***************4.�޸�ְ����Ϣ*****************" << endl;
	cout << "***************5.����ְ����Ϣ*****************" << endl;
	cout << "***************6.�����������*****************" << endl;
	cout << "***************7.�����������*****************" << endl;
	cout << "***************8.�˳��������*****************" << endl;
	cout << "**********************************************" << endl;
	cout << endl;
	

}

void WorkerManager::Exit_System() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}

//���ְ��
void WorkerManager::Add_Emp() {
	cout << "���������ְ��������" << endl;
	int addNum = 0;
	cin >> addNum;

	if (addNum > 0) {
		//��Ӳ���
		//������Ӻ�Ŀռ�Ĵ�С
		int newSize = this->m_EmpNum + addNum;

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ��µ����ݣ��������¿ռ���
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i <= this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int deptId;

			cout << "�������" << i + 1 << "����ְ���ı��" << endl;
			cin >> id;

			cout << "�������" << i + 1 << "����ְ��������" << endl;
			cin >> name;

			cout << "�������ְ���Ĳ��ű��"<< endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
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
					cout << "����Ĳ���id����" << endl; 
					system("pause");
					system("cls");
					return;
				}
				break;
			}
			//��������ְ��ָ�룬������������
			newSpace[this->m_EmpNum + i] = worker;
			
		

		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//�����µ�ְ������
		this->m_EmpNum = newSize;
		
		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;

		//�ɹ���Ӻ󱣴浽�ļ���
		this->Save();

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;

	}
	else {
		cout << "������������" << endl;
	}

	system("pause");
	system("cls");
}

//��ʼ��Ա��
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

		if (dId == 1)//��ְͨ��
		{
			worker = new Employee(id, name, 1);
		}
		else if (dId == 2)//����
		{
			worker = new Manager(id, name, 2);
		}
		else if (dId == 3)//�ϰ�
		{
			worker = new Boss(id, name, 3);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}

	ifs.close();
}


//��ʾְ��
void WorkerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}

	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ó���ӿ�
			this->m_EmpArray[i]->showInfo();

		}
	}
	system("pause");
	system("cls");
}

//�ж�ְ���Ƿ����
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

//ɾ��ְ��
void WorkerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		//����ְ�����ɾ��
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id = 0;
		cin >> id;

		int index = this->IsExit(id);

		if (index != -1)//ְ��������ɾ����index�ϵ�ְ��
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum-1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			cout << "ɾ���ɹ�" << endl;
			this->m_EmpNum--;//���������м�¼����Ա����
			this->Save();
		}
		else
		{
			cout << "ɾ��ʧ�ܣ�δ�ҵ���ְ��" << endl;
		}
		system("pause");
		system("cls");
	}

}

//�޸�ְ��
void WorkerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else
	{
		cout << "�������޸�ְ���ı�ţ�" << endl;
		int id;
		cin >> id;

		int ret = this->IsExit(id);
		if (ret != -1)
		{
			//���ҵ���ŵ�ְ��

			delete this->m_EmpArray[ret];
			
			int newId = 0;
			string newName = "";
			int dSelect = 0;

			cout << "�鵽��" << id << "��ְ�����������µ�ְ����" << endl;
			cin >> newId;

			cout << "�������������� " << endl;
			cin >> newName;

			cout << "�������λ" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ϰ�" << endl;

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
				cout << "����ĸ�λ����" << endl;
				break;
			}

			//���µ�������
			this->m_EmpArray[ret] = worker;

			cout << "�޸ĳɹ�" << endl;

			//���浽�ļ���
			this->Save();
		}
		else
		{
			cout << "�޸�ʧ�ܣ����޴���" << endl;
		}
	}
	system("pause");
	system("cls");
}


//����ְ��
void WorkerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ" << endl;
		cout << "1������ְ���ı�Ų���" << endl;
		cout << "2������ְ������������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			//���ձ�Ų�
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >> id;
			int ret = this->IsExit(id);
			if (ret != -1)
			{
				//�ҵ�ְ��
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "���޴���" << endl;
			}
		}
		else if(select == 2)
		{
			//����������
			string name;
			cout << "��������ҵ�������" << endl;
			cin >> name;

			int flag = false;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;

				this->m_EmpArray[i]->showInfo();
				flag = true;
				}
			}
			if (flag == false)
			{
				cout << "���޴���" << endl;
			}
		}
		else
		{
		cout << "�����ѡ������!" << endl;
		}

	}
	system("pause");
	system("cls");
}

//����ְ����Ž�������
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ�Ϊ��!" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ķ�ʽ��" << endl;
		cout << "1����ְ������������" << endl;
		cout << "2����ְ���Ž�������" << endl;

		int select = 0;
		cin >> select;

		if (select == 1 || select == 2)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				int minOrMax = i;//������Сֵ�������ֵ���±�
				for (int j = i + 1; j < this->m_EmpNum; j++)
				{
					if (select == 1)//����
					{
						if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
						{
							minOrMax = j;
						}
					}
					else//����
					{
						if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
						{
							minOrMax = j;
						}
					}
				}
				//�ж�һ��ʼ�϶������ֵ������Сֵ�ǲ���ʵ���ϵ����ֵ����Сֵ�������򽻻�
				if (i != minOrMax)
				{
					Worker* temp = this->m_EmpArray[i];
					this->m_EmpArray[i] = this->m_EmpArray[minOrMax];
					this->m_EmpArray[minOrMax] = temp;
				}
			}
			cout << "����ɹ��������Ľ��Ϊ��" << endl;
			this->Save();//�����Ľ�����浽�ļ���
			this->Show_Emp();
		}
		else
		{
			cout << "��������" << endl;
			system("pause");
			system("cls");
		}

	}
}

//����ļ�
void WorkerManager::Clean_File()
{
	cout << "ȷ�����ȫ��������" << endl;
	cout << "����1��ȷ������" << endl;
	int select = 0;
	cin >> select;
	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc);//ɾ���ļ������´���
		ofs.close();

		if (this->m_EmpArray != NULL)
		{
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ�������Ե�����ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "��ճɹ�" << endl;
	}
	else
	{
		cout << "��ȡ����ղ���" << endl;
	}

	system("pause");
	system("cls");
}


//�����ļ�
void WorkerManager::Save() 
{
	fstream ofs;
	ofs.open(FILENAME, ios::out);//д�ļ��ķ�ʽ���ļ�
	for (int i = 0; i < this->m_EmpNum; i++) 
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	
	//�ر��ļ�
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