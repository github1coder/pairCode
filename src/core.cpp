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
	int getWordLinks(string words[], int wordsSize, char h, char t, int r, string wordLinks[])
};
int Core::getWordLinks(string words[], int wordsSize, char h, char t, bool r, string wordLinks[]) {
	//h,t,r��Ҫ���� 
	for (int i = 0; i < wordsSize; i++) {
		wordLinks[i] = words[i];
	}
	return wordsSize;
}
// ��Ա��������
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