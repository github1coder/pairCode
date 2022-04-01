#pragma once
#include <iostream>
using namespace std;

class file_illegal_exception : public exception
{
	virtual const char* what() const throw()
	{
		return "文件不合法";
	}
};

class file_nonexist_exception : public exception
{
	virtual const char* what() const throw()
	{
		return "文件不存在";
	}
};

class para_nonout_exception :public exception 
{
	virtual const char* what() const throw()
	{
		return "参数错误，无需要输出的参数";
	}
};

class para_undefine_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "参数错误，未定义的参数";
	}
};

class para_conflict_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "参数错误，输出冲突的参数";
	}
};

class para_form_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "参数错误，t/h后非单个字母";
	}
};

class word_circle_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "存在单词环";
	}
};

class word_Nochain_exception :public exception
{
	virtual const char* what() const throw()
	{
		return "无法构成所需单词链";
	}
};