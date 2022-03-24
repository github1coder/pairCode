#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <regex>
#include <algorithm>
#include <cstring>

using namespace std;
int getwords(string filePath, string words[]) {
	int count = 0;
	if (filePath.find(".txt")) {
		throw "文件不合法";
	}
	ifstream infile;
	infile.open(filePath.c_str(), ios::in);
	
	if (!infile) {
		throw "文件不存在";
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
		while (p)
		{
			if (strlen(p) > 1) {
				p = strlwr(p);
				words[count++] = p;
			}
			p = strtok(NULL, d);
		}
	}
	infile.close();
	return count;
}

void handleOutput(string wordLinks[], int wordLinksSize, char type) {
	if (type == 'n') {
		cout << wordLinksSize;
		for (int i = 0; i < wordLinks.size(); i++) {
			cout << endl << wordLinks[i];
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
		int maxIndex = -1;
		int maxCount = 0;
		for (int i = 0; i < wordLinksSize; i++) {
			int blankCount = count(wordLinks[i].begin(), wordLinks[i].end(), ' ');
			if (blankCount + 1 > maxCount) {
				maxCount = blankCount + 1;
				maxIndex = i;
			}
		}
		if (maxIndex >= 0) {
			for (int i = 0; i < wordLinks[maxIndex].size(); i++) {
				if (wordLinks[maxIndex][i] != ' ') {
					if (wordLinks[maxIndex][i] >= 65 && wordLinks[maxIndex][i] <= 90) {  //大写字母 
						fs << wordLinks[maxIndex][i] + 32;
					}
					else {
						fs << wordLinks[maxIndex][i];
					}
				}
				else fs << endl;
			}
		}
	}
	else if (type == 'm') {
		int maxIndex = -1;
		int maxCount = 0;
		int blankCount;
		for (int i = 0; i < wordLinksSize; i++) {
			blankCount = 0;
			bool flag = true;
			bool blank = true;
			int fletter[26] = { 0 };
			string wordLink = wordLinks[i];
			for (int j = 0; j < wordLink.size(); i++) {
				if (blank) {
					blank = false;
					int index = wordLink[i] <= 90 ? wordLink[i] + 32 - 97 : wordLink[i] - 97;
					if (fletter[index] != 0) {
						flag = false;
						break;
					}
					else {
						fletter[index] = 1;
					}
				}
				else if (wordLink[i] == ' ') {
					blank = false;
					blankCount++;
				}
			}
			if (flag && blankCount + 1 > maxCount) {
				maxCount = blankCount + 1;
				maxIndex = i;
			}
		}
		if (maxIndex >= 0) {
			for (int i = 0; i < wordLinks[maxIndex].size(); i++) {
				if (wordLinks[maxIndex][i] != ' ') {
					if (wordLinks[maxIndex][i] >= 65 && wordLinks[maxIndex][i] <= 90) {  //大写字母 
						fs << wordLinks[maxIndex][i] + 32;
					}
					else {
						fs << wordLinks[maxIndex][i];
					}
				}
				else fs << endl;
			}
		}
	}
	else if (type == 'c') {
		int maxIndex = -1;
		int maxCount = 0;
		for (int i = 0; i < wordLinksSize; i++) {
			int blankCount = count(wordLinks[i].begin(), wordLinks[i].end(), ' ');
			int len = wordLinks[i].size() - blankCount;
			if (len > maxCount) {
				maxCount = len;
				maxIndex = i;
			}
		}
		if (maxIndex >= 0) {
			for (int i = 0; i < wordLinks[maxIndex].size(); i++) {
				if (wordLinks[maxIndex][i] != ' ') fs << wordLinks[maxIndex][i];
				else fs << endl;
			}
		}
	}
	fs.close();
	return;
}

struct Edge
{
	int edgeNum = 0;
	int initNum = 0;
	vector<string>edgeWords;
	vector<int>edgeUse;
	//以连接两字母的单词作为边，记录边的数量及相应单词
};
//用迭代器遍历、删减、增加单词，改掉while
//r直接新建boolean数组来判定是否访问过，在首字母阶段判断，防止出现开头结尾字母一样的情况
int getOneLink(Edge* edge[26][26], int r, int bline, vector<vector<int>>& edgeWeight, string sstr, int circle, char t, int isR[], string wordLinks[], int wl) {
	int line = bline;
	int eNum = edgeWeight[line].size();
	int iNum = eNum;
	isR[line] = 1;
	vector<int>::iterator eWit;
	sort(edgeWeight[line].begin(), edgeWeight[line].end());
	for (eWit = edgeWeight[line].begin(); eWit != edgeWeight[line].end(); eWit++) {
		int n = *eWit;
		Edge* e = edge[line][n];
		if (line != n) {
			if (isR[n] == 1 && r == 0) {
				cout << "存在单词环" << endl;

			}
		}
		vector<string>eW = e->edgeWords;
		vector<string>::iterator eWordIt;
		vector<int>::iterator eUit;
		eUit = e->edgeUse.begin();
		for (eWordIt = eW.begin(); eWordIt != eW.end(); eWordIt++) {
			string w = *eWordIt;
			int u = *eUit;
			if (u == 0) {
				*eUit = 1;
				sstr = sstr + " " + w;

				wl=getOneLink(edge, r, n, edgeWeight, sstr, circle + 1, t, isR, wordLinks, wl);
				*eUit = 0;
				sstr = sstr.substr(0, sstr.length() - w.length() - 1);
			}
		}

	}
	isR[line] = 0;
	if (circle > 1) {
		if (t <= 'z' && t >= 'a') {
			if (sstr[sstr.length() - 1] == t) {
				sstr = sstr.erase(0, 2);
				//cout << sstr << endl;
				wordLinks[wl] = sstr;
				wl++;
			}
		}
		else {
			sstr = sstr.erase(0, 2);//去掉一开始的空格
			//cout << sstr << endl;
			wordLinks[wl] = sstr;
			wl++;
		}
	}
	return wl;
}

int getWordLinks(string words[], int wordsSize, char h, char t, int r, string wordLinks[]) {  //测试 
	Edge* edge[26][26];
	vector<vector<int>> edgeWeight(26);//二维数组，记录各首字母开头的单词个数，便于查找是否存在这样的词，并记录这些词的尾字母。

	for (int i = 0; i < 26; i++) {
		for (int j = 0; j < 26; j++) {
			Edge* e = new Edge;
			edge[i][j] = e;
		}
	}
	for (int i = 0; i < wordsSize; i++) {
		string str = words[i];
		char begin = str[0];
		int len = str.length();
		char end = str[len - 1];
		Edge* e = edge[begin - 'a'][end - 'a'];
		e->edgeWords.push_back(str);
		e->edgeNum++;
		e->initNum++;
		e->edgeUse.push_back(0);
		edgeWeight[begin - 'a'].push_back(end - 'a');
	}
	//以上初始化单词二维数组，设置首字母二维数组记录以xx开头的单词个数
	int isR[26] = { 0 };
	int wl = 0;
	if (h <= 'z' && h >= 'a') {
		wl = getOneLink(edge, r, h - 'a', edgeWeight, " ", 0, t, isR, wordLinks, 0);
	}
	else {
		for (int i = 0; i < 26; i++) {
			if (!edgeWeight[i].empty()) {
				wl = getOneLink(edge, r, i, edgeWeight, " ", 0, t, isR, wordLinks, wl);
			}
		}
	}
	return wl;
}

int main(int argc, char* argv[])
{
	char type = '0'; //n,w,m,c
	char h = '0'; //h
	char t = '0'; //t
	int r = 0; //r
	string filePath;
	try {
		//处理命令行参数
		for (int count = 1; count < argc; count++) {
			if (argv[count][0] == '-') {
				if (argv[count][1] == 'n' || argv[count][1] == 'w' || argv[count][1] == 'm' || argv[count][1] == 'c') {
					type = argv[count][1];
					//filePath = argv[++count];
				}
				else if (argv[count][1] == 'h') {
					h = argv[++count][0];
				}
				else if (argv[count][1] == 't') {
					t = argv[++count][0];
				}
				else if (argv[count][1] == 'r') {
					r = 1;
				}
			}
			else {
				filePath = argv[count];
			}
		}

		//得到单词数组
		string words[10000];
		int wordsSize = getwords(filePath, words);
		//得到单词链数组 
		string wordLinks[10000];
		int wordLinksSize = getWordLinks(words, wordsSize, h, t, r, wordLinks);
		//根据参数处理文件输出 
		handleOutput(wordLinks, wordLinksSize, type);
	}	catch (const char* msg) {
		cerr << msg << endl;
	}
	return 0;
}
