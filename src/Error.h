#pragma once
#include <iostream>
using namespace std;

class file_illegal_exception : public exception
{
	virtual const char* what() const throw()
	{
		return "�ļ����Ϸ�";
	}
};

class file_nonexist_exception : public exception
{
	virtual const char* what() const throw()
	{
		return "�ļ�������";
	}
};

class para_nonout_exception :public exception 
{
	virtual const char* what() const throw()
	{
		return "������������Ҫ����Ĳ���";
	}
};

class para_undefine_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "��������δ����Ĳ���";
	}
};

class para_conflict_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "�������������ͻ�Ĳ���";
	}
};

class para_form_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "��������t/h��ǵ�����ĸ";
	}
};

class word_circle_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "���ڵ��ʻ�";
	}
};

class word_Nochain_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "�޷��������赥����";
	}
};