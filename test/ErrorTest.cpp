#include "pch.h"
#include "CppUnitTest.h"
#include "..\src\core.h"
#include "..\src\main.h"
#include "Error.h"
#include<iostream>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace ErrorTest
{
	TEST_CLASS(ErrorTest)
	{
	public:
		
		TEST_METHOD(Test_WordCircle_Error)
		{
			char* words[101] = { "fddsu", "uasdasf", "ugfl", "laght", "adbon", "tasdu" };
			char* result[101];
			for (int i = 0; i < 101; i++)
			{
				result[i] = (char*)malloc(sizeof(char) * 601);
			}
			try {
				gen_chain_word(words, 6, result, 0, 0, false);
				Assert::IsTrue(false);
			}
			catch (const char* msg) {
				Assert::AreEqual("存在单词环", msg);
			}
			for (int i = 0; i < 101; i++)
			{
				free(result[i]);
			}
		}
		TEST_METHOD(Test_NonFile_Error) {
			char* words[101] = { "wordlist.exe","-r", "-n", "D:\\grade_three\\wordx.txt" };
			int arg_c = 4;
			try {
				main(arg_c, words);
				Assert::IsTrue(false);
			}
			catch (file_nonexist_exception& e) {
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Test_WrongFile_Error) {
			char* words[101] = { "wordlist.exe","-r", "-n", "D:\\grade_three\\word.md" };
			int arg_c = 4;
			try {
				main(arg_c, words);
				Assert::IsTrue(false);
			}
			catch (file_illegal_exception& e) {
				Assert::IsTrue(true);
			}
		}
		TEST_METHOD(Test_ParaForm_Error) {
			char* words[101] = { "wordlist.exe","-t", "1","-n", "D:\\grade_three\\word.txt" };
			int arg_c = 5;
			try {
				main(arg_c, words);
				Assert::IsTrue(false);
			}
			catch (para_form_exception& e) {
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Test_ParaForm_Error2) {
			char* words[101] = { "wordlist.exe","-t", "mn","-n", "D:\\grade_three\\word.txt" };
			int arg_c = 5;
			try {
				main(arg_c, words);
				Assert::IsTrue(false);
			}
			catch (para_form_exception& e) {
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Test_ParaNout_Error) {
			char* words[101] = { "wordlist.exe","-t","a","-r", "D:\\grade_three\\word.txt" };
			int arg_c = 5;
			try {
				main(arg_c, words);
				Assert::IsTrue(false);
			}
			catch (para_nonout_exception& e) {
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Test_MulOut_Error) {
			char* words[101] = { "wordlist.exe","-w","-n", "D:\\grade_three\\word.txt" };
			int arg_c = 4;
			try {
				main(arg_c, words);
				Assert::IsTrue(false);
			}
			catch (para_conflict_exception& e) {
				Assert::IsTrue(true);
			}
		}

		TEST_METHOD(Test_Nochain_Error)
		{
			char* words[101] = { "abc", "def", "gh", "ijk", "uv", "yz" };
			try {
				handleOutput(words, 6, 'c', 'a', 'z', true);
				Assert::IsTrue(false);
			}
			catch (word_Nochain_exception& e) {
				Assert::IsTrue(true);
			}
		}
	};
}
