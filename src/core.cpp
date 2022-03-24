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
	int getWordLinks(string words[], int wordsSize, char h, char t, int r, string wordLinks[])
};
int Core::getWordLinks(string words[], int wordsSize, char h, char t, bool r, string wordLinks[]) {
	//h,t,r需要更改 
	for (int i = 0; i < wordsSize; i++) {
		wordLinks[i] = words[i];
	}
	return wordsSize;
}
// 成员函数定义
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