#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <regex>
#include <algorithm>
using namespace std;
int getwords(string filePath, string words[]) {
	int count = 0;

	ifstream infile;
	infile.open(filePath.c_str(), ios::in);
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
			if (p.size() > 1) {
				transform(p.begin(), p.end(), p.begin(), ::tolower);
				words[count++] = p;
			}
			p = strtok(NULL, d);
		}
	}
	infile.close();
	return count;
}

void handleOutput(string wordLinks[], int wordLinksSize, char type) {
	const char* fname = ".\\solution.txt";
	ofstream fs;
	fs.open(fname, ios::out);
	if (!fs)
	{
		//创建文件
		ofstream fs(fname);
	}
	if (type == 'n') {
		fs << wordLinksSize;
	}
	else if (type == 'w') {
		int maxIndex = -1;
		int maxCount = 0;
		for (int i = 0; i < wordLinksSize; i++) {
			int blankCount = count(wordLinks[i].begin(), wordLinks[i].end(), ' ');
			if (blankCount > maxCount) {
				maxCount = blankCount;
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
			if (flag && blankCount > maxCount) {
				maxCount = blankCount;
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
				len = blankCount;
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

int getWordLinks(string words[], int wordsSize, char h, char t, int r, string wordLinks[]) {  //测试 
	for (int i = 0; i < wordsSize; i++) {
		wordLinks[i] = words[i];
	}
	return wordsSize;
}

int main(int argc, char* argv[])
{
	char type = '0'; //n,w,m,c
	char h = '0'; //h
	char t = '0'; //t
	int r = 0; //r
	string filePath;
	//处理命令行参数
	for (int count = 1; count < argc; count++) {
		if (argv[count][0] == '-') {
			if (argv[count][1] == 'n' || argv[count][1] == 'w' || argv[count][1] == 'm' || argv[count][1] == 'c') {
				type = argv[count][1];
				filePath = argv[++count];
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
		//		else {
		//			filePath = argv[count];
		//		}
	}

	//得到单词数组
	string words[10000];
	int wordsSize = getwords(filePath, words);
	//得到单词链数组 
	string wordLinks[10000];
	int wordLinksSize = getWordLinks(words, wordsSize, h, t, r, wordLinks);
	//根据参数处理文件输出 
	handleOutput(wordLinks, wordLinksSize, type);
	return 0;
}