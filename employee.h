#pragma once
//普通员工文件
#include <iostream>
#include "worker.h"

using namespace std;

class Employee : public Worker {
public:

	Employee(int id, string name, int dId);
	virtual void showInfo();
	virtual string getDeptName();
};