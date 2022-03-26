#include <iostream>
#include <algorithm>

class Core
{
public:
	// 成员函数声明
	int gen_chain_word(char* words[], int len, char result[], char head, char tail, bool enable_loop);
	int gen_chains_all(char* words[], int len, char result[]);
	int gen_chain_word_unique(char* words[], int len, char result[]);
	int gen_chain_char(char* words[], int len, char result[], char head, char tail, bool enable_loop);
private:
	struct Edge
	{
		int edgeNum = 0;
		int initNum = 0;
		vector<string>edgeWords;
		vector<int>edgeUse;
		//以连接两字母的单词作为边，记录边的数量及相应单词
	};
	int getWordLinks(string words[], int wordsSize, char h, char t, int r, string wordLinks[]);
	int getOneLink(Edge* edge[26][26], int r, int bline, vector<vector<int>>& edgeWeight, string sstr, int circle, char t, int isR[], string wordLinks[], int wl);
};
int Core::getWordLinks(string words[], int wordsSize, char h, char t, bool r, string wordLinks[]) {
	//h,t,r需要更改 
	for (int i = 0; i < wordsSize; i++) {
		wordLinks[i] = words[i];
	}
	return wordsSize;
}
// 成员函数定义
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
				//cout << "存在单词环" << endl;
				throw "存在单词环";
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

				wl = getOneLink(edge, r, n, edgeWeight, sstr, circle + 1, t, isR, wordLinks, wl);
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

int getWordLinks(string words[], int wordsSize, char h, char t, int r, string wordLinks[]) {
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
int Core::gen_chain_word(char* words[], int len, char result[], char head, char tail, bool enable_loop) { //最多单词数量，w 
	String wordLinks[10000];
	int wordLinksSize = getWordLinks(words, len, head, tail, enable_loop, wordLinks);
	int maxIndex = -1;
	int maxCount = 0;
	for (int i = 0; i < wordLinksSize; i++) {
		int blankCount = count(wordLinks[i].begin(), wordLinks[i].end(), ' ');
		if (blankCount + 1 > maxCount) {
			maxCount = blankCount + 1;
			maxIndex = i;
		}
	}
	result = wordLinks[maxIndex];
	return maxCount;
}
int Core::gen_chains_all(char* words[], int len, char* result[]) { //返回单词链的总数，n 
	int wordLinksSize = gen_chain_char(words, len, result, 0, 0, false);
	return wordLinksSize;
}
int Core::gen_chain_word_unique(char* words[], int len, char result[]) { //首字母不同的最多单词数量，m
	String wordLinks[10000];
	int wordLinksSize = getWordLinks(words, len, head, tail, enable_loop, wordLinks);
	int maxIndex = -1;
	int maxCount = 0;
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
	result = wordLinks[maxIndex];
	return maxCount;
}
int Core::gen_chain_char(char* words[], int len, char result[], char head, char tail, bool enable_loop) { //最多字母数量，c 
	String wordLinks[10000];
	int wordLinksSize = getWordLinks(words, len, head, tail, enable_loop, wordLinks);
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
	result = wordLinks[maxIndex];
	return maxCount;
}