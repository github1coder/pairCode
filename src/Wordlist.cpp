#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <regex>
#include <algorithm>
#include <cstring>
#include <Windows.h>

using namespace std;

class MyException {
public:
	MyException(string s, int flag) : str(s), my_flag(flag) { };
public:
	void what() const;  //获取具体的错误信息
private:
	string str;
	int my_flag;
};

void MyException::what() const {
	if (my_flag == 1)
	{
		cout << "参数错误，未定义的参数名：" << str << endl;
	}
	else if (my_flag == 2) {
		cout << str << endl;
	}
	else if (my_flag == 3) {
		cout << "参数错误，以下参数产生输出冲突：" << str << endl;
	}
	else if (my_flag == 5) {
		cout << "参数" << str << "后非单个英文字母" << endl;
	}
}

int getwords(string filePath, char* words[]) {
	int count = 0;
	if (filePath.find(".txt") == filePath.npos) {
		throw MyException("文件不合法", 2);
	}
	ifstream infile;
	infile.open(filePath.c_str(), ios::in);

	if (!infile) {
		throw MyException("文件不存在", 2);
	}
	string data;

	string pattern = "[^a-zA-Z]";
	regex re(pattern);
	string patternblank = "\\s+";
	regex reblank(patternblank);
	string blank = " ";

	while (infile >> data) {
		data = regex_replace(data, re, blank);
		data = regex_replace(data, reblank, blank);
		char* datastr = (char*)data.c_str();
		const char* d = " ";
		char* p;
		p = strtok(datastr, d);
		char* tt;
		while (p)
		{
			if (strlen(p) > 1) {
				p = strlwr(p);
				tt = new char[strlen(p) + 1];
				strcpy(tt, p);
				words[count++] = tt;
			}
			p = strtok(NULL, d);
		}
	}
	infile.close();
	return count;
}

void handleOutput(char* words[], int wordsSize, char type, char h, char t, bool r) {
	HMODULE module = LoadLibrary("..\\bin\\core.dll");
	if (module == NULL) {
		throw "load core.dll failed\n";
		return;
	}
	typedef int (*chain_word)(char* [], int, char* [], char, char, bool);
	typedef int (*chain_all)(char* [], int, char* []);
	typedef int (*chain_word_unique)(char* [], int, char* []);
	typedef int (*chain_char)(char* [], int, char* [], char, char, bool);
	chain_word gen_chain_word;
	chain_all gen_chains_all;
	chain_word_unique gen_chain_word_unique;
	chain_char gen_chain_char;
	gen_chain_word = (chain_word)GetProcAddress(module, "gen_chain_word");
	gen_chains_all = (chain_all)GetProcAddress(module, "gen_chains_all");
	gen_chain_word_unique = (chain_word_unique)GetProcAddress(module, "gen_chain_word_unique");
	gen_chain_char = (chain_char)GetProcAddress(module, "gen_chain_char");
	char* result[20000];

	if (type == 'n') {
		int wordLinksSize = gen_chains_all(words, wordsSize, result);
		if (wordLinksSize == 0) {
			throw MyException("无法构成所需单词链", 2);
		}
		cout << wordLinksSize;
		for (int i = 0; i < wordLinksSize; i++) {
			cout << endl << result[i];
		}
		return;
	}
	const char* fname = ".\\solution.txt";
	ofstream fs;
	fs.open(fname, ios::out);
	if (!fs)
	{
		//创建文件
		ofstream fs(fname);
	}
	if (type == 'w') {
		int wordLinksSize = gen_chain_word(words, wordsSize, result, h, t, r);
		if (wordLinksSize == 0) {
			throw MyException("无法构成所需单词链", 2);
		}
		for (int i = 0; i < wordLinksSize; i++) {
			fs << result[i];
			if (i != wordLinksSize - 1) {
				fs << endl;
			}
		}
	}
	else if (type == 'm') {
		int wordLinksSize = gen_chain_word_unique(words, wordsSize, result);
		if (wordLinksSize == 0) {
			throw MyException("无法构成所需单词链", 2);
		}
		for (int i = 0; i < wordLinksSize; i++) {
			fs << result[i];
			if (i != wordLinksSize - 1) {
				fs << endl;
			}
		}
	}
	else if (type == 'c') {
		int wordLinksSize = gen_chain_char(words, wordsSize, result, h, t, r);
		if (wordLinksSize == 0) {
			throw MyException("无法构成所需单词链", 2);
		}
		for (int i = 0; i < wordLinksSize; i++) {
			fs << result[i];
			if (i != wordLinksSize - 1) {
				fs << endl;
			}
		}
	}
	fs.close();
	return;
}

int main(int argc, char* argv[])
{
	char type = '0'; //n,w,m,c
	char h = '0'; //h
	char t = '0'; //t
	int r = 0; //r
	string wstr = "";//wrongStr用于存不正确的参数
	string rstr = "";//repeatStr用于存重复的有输出参数
	string filePath;
	int paraNum = 0;

	try {
		//处理命令行参数
		for (int count = 1; count < argc; count++) {
			if (argv[count][0] == '-') {
				if (argv[count][1] == 'n' || argv[count][1] == 'w' || argv[count][1] == 'm' || argv[count][1] == 'c') {
					type = argv[count][1];
					paraNum++;
					rstr = rstr + " " + argv[count][1];
					//filePath = argv[++count];
				}
				else if (argv[count][1] == 'h') {
					h = argv[++count][0];
					string m = argv[count];
					if (m.length() != 1) {
						throw MyException("h", 5);
					}
					else if (!(h <= 'z' && h >= 'a' || h <= 'Z' && h >= 'A')) {
						throw MyException("h", 5);
					}
					if (h <= 'Z') {
						h = h - 'A' + 'a';
					}
				}
				else if (argv[count][1] == 't') {
					t = argv[++count][0];
					string m = argv[count];
					if (m.length() != 1) {
						throw MyException("t", 5);
					}
					else if (!(t <= 'z' && t >= 'a' || t <= 'Z' && t >= 'A')) {
						throw MyException("t", 5);
					}
					if (t <= 'Z') {
						t = t - 'A' + 'a';
					}
				}
				else if (argv[count][1] == 'r') {
					r = 1;
				}
				else {
					wstr = wstr + " " + argv[count][1];
				}
			}
			else {
				filePath = argv[count];
			}
		}
		if (wstr.length() != 0) {
			throw MyException(wstr, 1);
		}
		else if (paraNum > 1) {
			throw MyException(rstr, 3);
		}
		else if (paraNum == 0) {
			throw MyException("参数错误，无需要输出的参数", 2);
		}

		//得到单词数组
		char* words[20000];
		int wordsSize = getwords(filePath, words);
		//根据参数处理文件输出 
		handleOutput(words, wordsSize, type, h, t, r);
	}
	catch (MyException& e) {
		e.what();
	}
	catch (const char* msg) {
		cerr << msg << endl;
	}
	return 0;
}
