#include "pch.h"
#include "CppUnitTest.h"
#include "..\src\core.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1) //n
		{
			char* words[101] = { "element", "heaven", "tab", "teach", "talk" };
			char* answer[101];
			for (int i = 0; i < 101; i++)
			{
				answer[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chains_all(words, 5, answer);

			Assert::AreEqual(l, 5);
			Assert::AreEqual("element tab", answer[0]);
			Assert::AreEqual("element teach heaven", answer[1]);
			Assert::AreEqual("element teach", answer[2]);
			Assert::AreEqual("element talk", answer[3]);
			Assert::AreEqual("teach heaven", answer[4]);
			for (int i = 0; i < 101; i++)
			{
				free(answer[i]);
			}
		}

		TEST_METHOD(TestMethod2) //w
		{
			char* words[101] = { "algebra", "apple", "zoo", "elephant", "under", "fox", "dog", "moon", "leaf", "trick", "pseudopseudohypoparathyroidism"};
			char* answer[101];
			for (int i = 0; i < 101; i++)
			{
				answer[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_word(words, 11, answer, 0, 0, false);

			Assert::AreEqual(l, 4);
			Assert::AreEqual("algebra", answer[0]);
			Assert::AreEqual("apple", answer[1]);
			Assert::AreEqual("elephant", answer[2]);
			Assert::AreEqual("trick", answer[3]);
			for (int i = 0; i < 101; i++)
			{
				free(answer[i]);
			}
		}

		TEST_METHOD(TestMethod3) //m
		{
			char* words[101] = { "bloib", "blf", "adfp", "fllu", "vdfss", "gsdy", "esdah", "newo", "mdfdg", "udsdl", "queen" };
			char* result[101];
			for (int i = 0; i < 101; i++)
			{
				result[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_word_unique(words, 11, result);

			Assert::AreEqual(l, 3);
			Assert::AreEqual("blf", result[0]);
			Assert::AreEqual("fllu", result[1]);
			Assert::AreEqual("udsdl", result[2]);
			for (int i = 0; i < 101; i++)
			{
				free(result[i]);
			}
		}

		TEST_METHOD(TestMethod4) //c
		{
			char* words[101] = { "bloib", "blf", "adfp", "fllu", "vdfss", "gsdy", "esdah", "newo", "mdfdg", "udsdl", "queewewewewewewewewen" };
			char* result[101];
			for (int i = 0; i < 101; i++)
			{
				result[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_char(words, 11, result, 0, 0, 0);

			Assert::AreEqual(l, 2);
			Assert::AreEqual("queewewewewewewewewen", result[0]);
			Assert::AreEqual("newo", result[1]);
			for (int i = 0; i < 101; i++)
			{
				free(result[i]);
			}
		}

		TEST_METHOD(TestMethod5) //h,w
		{
			char* words[101] = { "bloib", "blf", "adfp", "fllu", "vdfss", "gsdy", "esdah", "newo", "mdfdg", "udsdl", "queewewewewewewewewen" };
			char* result[101];
			for (int i = 0; i < 101; i++)
			{
				result[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_word(words, 11, result, 'f', 0, false);

			Assert::AreEqual(l, 2);
			Assert::AreEqual("fllu", result[0]);
			Assert::AreEqual("udsdl", result[1]);
			for (int i = 0; i < 101; i++)
			{
				free(result[i]);
			}
		}

		TEST_METHOD(TestMethod6) //t,w
		{
			char* words[101] = { "bloib", "blf", "adfp", "fllu", "vdfss", "gsdy", "esdah", "newo", "mdfdg", "udsdl", "queewewewewewewewewen" };
			char* result[101];
			for (int i = 0; i < 101; i++)
			{
				result[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_word(words, 11, result, 0, 'u', false);

			Assert::AreEqual(l, 3);
			Assert::AreEqual("bloib", result[0]);
			Assert::AreEqual("blf", result[1]);
			Assert::AreEqual("fllu", result[2]);
			for (int i = 0; i < 101; i++)
			{
				free(result[i]);
			}
		}

		TEST_METHOD(TestMethod7) //r,w
		{
			char* words[101] = { "fddsu", "uasdasf", "ugfl", "laght", "adbon", "tasdu"};
			char* result[101];
			for (int i = 0; i < 101; i++)
			{
				result[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_word(words, 6, result, 0, 0, true);
			Assert::AreEqual(l, 5);
			Assert::AreEqual("fddsu", result[0]);
			Assert::AreEqual("ugfl", result[1]);
			Assert::AreEqual("laght", result[2]);
			Assert::AreEqual("tasdu", result[3]);
			Assert::AreEqual("uasdasf", result[4]);
			for (int i = 0; i < 101; i++)
			{
				free(result[i]);
			}
		}

		TEST_METHOD(TestMethod8) //h, t, c
		{
			char* words[101] = { "asdsn", "adfp", "fllu", "vdfss", "gsdy",  "newo",  "queewewewewewewewewen" };
			char* result[101];
			for (int i = 0; i < 101; i++)
			{
				result[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_char(words, 7, result, 'a', 'o', 0);
			Assert::AreEqual(l, 2);
			Assert::AreEqual("asdsn", result[0]);
			Assert::AreEqual("newo", result[1]);
			for (int i = 0; i < 101; i++)
			{
				free(result[i]);
			}
		}

		TEST_METHOD(TestMethod9) //h, r, w
		{
			char* words[101] = { "fddsu", "ugfl", "laght", "adbon", "tasdu" };
			char* result[101];
			for (int i = 0; i < 101; i++)
			{
				result[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_word(words, 5, result, 'u', 0, true);
			Assert::AreEqual(l, 3);
			Assert::AreEqual("ugfl", result[0]);
			Assert::AreEqual("laght", result[1]);
			Assert::AreEqual("tasdu", result[2]);
			for (int i = 0; i < 101; i++)
			{
				free(result[i]);
			}
		}

		TEST_METHOD(TestMethod10) //h, t, r, w
		{
			char* words[101] = { "fddsu", "ugfl", "laght", "adbon", "tasdu" };
			char* result[101];
			for (int i = 0; i < 101; i++)
			{
				result[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_word(words, 5, result, 'u', 'u', true);
			Assert::AreEqual(l, 3);
			Assert::AreEqual("ugfl", result[0]);
			Assert::AreEqual("laght", result[1]);
			Assert::AreEqual("tasdu", result[2]);
			for (int i = 0; i < 101; i++)
			{
				free(result[i]);
			}
		}
	};
}