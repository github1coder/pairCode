#include "core.h"
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <regex>
#include <algorithm>
#include <cstring>

using namespace std;

struct Edge
{
	int edgeNum = 0;
	int initNum = 0;
	vector<string>edgeWords;
	vector<int>edgeUse;
	//以连接两字母的单词作为边，记录边的数量及相应单词
};


// 成员函数定义
//用迭代器遍历、删减、增加单词，改掉while
//r直接新建boolean数组来判定是否访问过，在首字母阶段判断，防止出现开头结尾字母一样的情况
int getOneLink(Edge* edge[26][26], int r, int bline, vector<vector<int>>& edgeWeight, string sstr, int circle, char t, int isR[], string wordLinks[], int wl) {
	int line = bline;
	isR[line]++;
	vector<int>::iterator eWit;
	sort(edgeWeight[line].begin(), edgeWeight[line].end());
	for (eWit = edgeWeight[line].begin(); eWit != edgeWeight[line].end();) {
		int n = *eWit;
		Edge* e = edge[line][n];
		vector<string>eW = e->edgeWords;
		vector<string>::iterator eWordIt;
		vector<int>::iterator eUit;
		eUit = e->edgeUse.begin();
		for (eWordIt = eW.begin(); eWordIt != eW.end(); eWordIt++) {
			string w = *eWordIt;
			int u = *eUit;
			if (u == 0) {
				if (line != n) {
					if (isR[n] == 1 && r == 0) {
						//cout << "存在单词环" << endl;
						throw"存在单词环";
					}
				}
				else {
					if (isR[n] > 1 && r == 0) {
						//cout << "存在单词环" << endl;
						throw"存在单词环";
					}
				}
				*eUit = 1;
				sstr = sstr + " " + w;

				wl = getOneLink(edge, r, n, edgeWeight, sstr, circle + 1, t, isR, wordLinks, wl);
				*eUit = 0;
				sstr = sstr.substr(0, sstr.length() - w.length());
				sstr = sstr.substr(0, sstr.length() - 1);
				eUit++;
				if (eWit != edgeWeight[line].end())
					eWit++;
			}
			else if (u == 1) {
				eUit++;
				if (eWit != edgeWeight[line].end())
					eWit++;
			}
		}

	}
	isR[line]--;
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

int getWordLinks(char* words[], int wordsSize, char h, char t, int r, string wordLinks[]) {
	Edge* edge[26][26];
	vector<vector<int>> edgeWeight(26);//二维数组，记录各首字母开头的单词个数，便于查找是否存在这样的词，并记录这些词的尾字母。
	if (h != '0' || h != 0) {
		if (!(h <= 'z' && h >= 'a' || h <= 'Z' && h >= 'A')) {
			throw "h后非英语字母";
		}
	}
	if (t != '0' || h != 0) {
		if (!(t <= 'z' && t >= 'a' || t <= 'Z' && t >= 'A')) {
			throw "t后非英语字母";
		}
	}

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

void stringToChars(string wordLink, char* result[]) {
	char* wordLinkstr = (char*)wordLink.c_str();
	const char* d = " ";
	char* p;
	int count = 0;
	p = strtok(wordLinkstr, d);
	char* tt;
	while (p)
	{
		tt = new char[strlen(p) + 1];
		strcpy(tt, p);
		result[count++] = tt;
		p = strtok(NULL, d);
	}
}

int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) { //最多单词数量，w 
	string wordLinks[20000];
	int r = enable_loop ? 1 : 0;
	int wordLinksSize = getWordLinks(words, len, head, tail, r, wordLinks);
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
		stringToChars(wordLinks[maxIndex], result);
	}
	return maxCount;
}

int gen_chains_all(char* words[], int len, char* result[]) { //返回单词链的总数，n 
	string wordLinks[20000];
	int wordLinksSize = getWordLinks(words, len, 0, 0, false, wordLinks);
	char* tt;
	for (int i = 0; i < wordLinksSize; i++) {
		tt = new char[strlen(wordLinks[i].c_str()) + 1];
		strcpy(tt, wordLinks[i].c_str());
		result[i] = tt;
	}
	return wordLinksSize;
}

int gen_chain_word_unique(char* words[], int len, char* result[]) { //首字母不同的最多单词数量，m
	string wordLinks[20000];
	int wordLinksSize = getWordLinks(words, len, 0, 0, false, wordLinks);
	int maxIndex = -1;
	int maxCount = 0;
	int blankCount;
	for (int i = 0; i < wordLinksSize; i++) {
		blankCount = 0;
		bool flag = true;
		bool blank = true;
		int fletter[26] = { 0 };
		string wordLink = wordLinks[i];
		for (int j = 0; j < wordLink.size(); j++) {
			if (blank) {
				blank = false;
				int index = wordLink[j] <= 90 ? wordLink[j] + 32 - 97 : wordLink[j] - 97;
				if (fletter[index] != 0) {
					flag = false;
					break;
				}
				else {
					fletter[index] = 1;
				}
			}
			else if (wordLink[j] == ' ') {
				blank = true;
				blankCount++;
			}
		}
		if (flag && blankCount + 1 > maxCount) {
			maxCount = blankCount + 1;
			maxIndex = i;
		}
	}
	if (maxIndex >= 0) {
		stringToChars(wordLinks[maxIndex], result);
	}
	return maxCount;
}

int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) { //最多字母数量，c 
	string wordLinks[20000];
	int r = enable_loop ? 1 : 0;
	int wordLinksSize = getWordLinks(words, len, head, tail, r, wordLinks);
	int maxIndex = -1;
	int maxCount = 0;
	int maxlen = 0;
	for (int i = 0; i < wordLinksSize; i++) {
		int blankCount = count(wordLinks[i].begin(), wordLinks[i].end(), ' ');
		int len = wordLinks[i].size() - blankCount;
		if (len > maxlen) {
			maxlen = len;
			maxCount = blankCount + 1;
			maxIndex = i;
		}
	}
	if (maxIndex >= 0) {
		stringToChars(wordLinks[maxIndex], result);
	}
	return maxCount;
}
