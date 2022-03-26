#include <iostream>
#include <algorithm>

class Core
{
public:
	// ��Ա��������
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
		//����������ĸ�ĵ�����Ϊ�ߣ���¼�ߵ���������Ӧ����
	};
	int getWordLinks(string words[], int wordsSize, char h, char t, int r, string wordLinks[]);
	int getOneLink(Edge* edge[26][26], int r, int bline, vector<vector<int>>& edgeWeight, string sstr, int circle, char t, int isR[], string wordLinks[], int wl);
};
int Core::getWordLinks(string words[], int wordsSize, char h, char t, bool r, string wordLinks[]) {
	//h,t,r��Ҫ���� 
	for (int i = 0; i < wordsSize; i++) {
		wordLinks[i] = words[i];
	}
	return wordsSize;
}
// ��Ա��������
//�õ�����������ɾ�������ӵ��ʣ��ĵ�while
//rֱ���½�boolean�������ж��Ƿ���ʹ���������ĸ�׶��жϣ���ֹ���ֿ�ͷ��β��ĸһ�������
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
				//cout << "���ڵ��ʻ�" << endl;
				throw "���ڵ��ʻ�";
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
			sstr = sstr.erase(0, 2);//ȥ��һ��ʼ�Ŀո�
			//cout << sstr << endl;
			wordLinks[wl] = sstr;
			wl++;
		}
	}
	return wl;
}

int getWordLinks(string words[], int wordsSize, char h, char t, int r, string wordLinks[]) {
	Edge* edge[26][26];
	vector<vector<int>> edgeWeight(26);//��ά���飬��¼������ĸ��ͷ�ĵ��ʸ��������ڲ����Ƿ���������Ĵʣ�����¼��Щ�ʵ�β��ĸ��

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
	//���ϳ�ʼ�����ʶ�ά���飬��������ĸ��ά�����¼��xx��ͷ�ĵ��ʸ���
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
int Core::gen_chain_word(char* words[], int len, char result[], char head, char tail, bool enable_loop) { //��൥��������w 
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
int Core::gen_chains_all(char* words[], int len, char* result[]) { //���ص�������������n 
	int wordLinksSize = gen_chain_char(words, len, result, 0, 0, false);
	return wordLinksSize;
}
int Core::gen_chain_word_unique(char* words[], int len, char result[]) { //����ĸ��ͬ����൥��������m
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
int Core::gen_chain_char(char* words[], int len, char result[], char head, char tail, bool enable_loop) { //�����ĸ������c 
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