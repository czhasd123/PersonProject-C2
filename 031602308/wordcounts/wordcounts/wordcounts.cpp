#include "pch.h"
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include<string>
#include<fstream>
#include<iostream>
#include<sstream>
using namespace std;
bool cmp(const pair<string, int> &p1, const pair<string, int> &p2)
{
	return p1.second > p2.second;
}//定义一个sort的比较模式，从大到小排序 
char *temp = new char[10000000];
int CountLines(char *filename)
{
	ifstream ReadFile;
	int n = 0;
	char line[512];
	string temp;
	ReadFile.open(filename, ios::in);
	if (ReadFile.fail())
	{
		return 0;
	}
	else
	{
		while (getline(ReadFile, temp))
		{
			if (temp.empty()) continue;
			n++;
		}
		return n;
	}
	ReadFile.close();
}//统计文本行数 

int Countcharacters(char *filename)
{
	ifstream ReadFile;
	int m = 0;
	char characters;
	ReadFile.open(filename);
	ReadFile >> noskipws;
	if (ReadFile.fail())
	{
		return 0;
	}
	else
	{
		while (!ReadFile.eof())
		{
			ReadFile >> characters;
			m++;
		}
		return m - 1;
	}
	ReadFile.close();
}//统计文本字数 
int main(int argc, char *argv[]) {
	int sum = 0;
	int i = 0;
	int j = 0;
	long int n = 0;
	int m = 0;
	int number;
	char c;
	cout << "characters:" << Countcharacters(argv[1]) << endl;
	cout << "lines:" << CountLines(argv[1]) << endl;
	map<string, int> words;//用map存储单词及其数量
	map<string, int> ::iterator l_it;
	ifstream ReadFile;
	char characters;
	ReadFile.open(argv[1]);
	ReadFile >> noskipws;
	if (ReadFile.fail())
	{
		return 0;
	}
	else
	{
		while (!ReadFile.eof())
		{
			ReadFile >> characters;
			temp[n] = characters;
			n++;
		}
	}
	ReadFile.close();
	char x[10];
	for (j = 0; j < n; j++)
	{
		if (temp[j] >= 'A'&&temp[j] <= 'Z')
		{
			temp[j] += 32;
		}
	}
	int  flag = 0, k = 0;
	for (i = 0; i < n; i++)
	{
		if (!((temp[i] >= 48 && temp[i] <= 57) || (temp[i] >= 97 && temp[i] <= 122)))//跳过非字母和非数字字符 
			continue;
		else
		{
			for (j = 0; j < 4 && i < n; j++)
			{
				if (!((temp[i] >= 48 && temp[i] <= 57) || (temp[i] >= 97 && temp[i] <= 122)))
					break;
				x[j] = temp[i++];//temp中存入四个非空格字符
			}
			if (j == 4)
			{
				for (m = 0; m < 4; m++)
				{
					if (x[m] < 97 || x[m]>122)
					{
						flag = 1;
						break;//判断这四个字符是否都是字母
					}
				}
				if (flag == 0)//四个字符都是字母的情况，判断为一个单词
				{
					char *w = new char[100];//存放单词 
					for (m = 0; m < 4; m++)
					{
						w[k++] = x[m];//temp中字符存入w
					}
					while (((temp[i] >= 48 && temp[i] <= 57) || (temp[i] >= 97 && temp[i] <= 122)) && i < n)//继续存入单词剩余字符
					{
						w[k++] = temp[i++];
					}
					w[k] = '\0';
					string wr;
					wr = w;
					l_it = words.find(wr);
					if (l_it == words.end())
					{
						words.insert(pair<string, int>(wr, 1));//未找到单词，插入单词并设定频次为1 
					}
					else
					{
						++l_it->second;
					}
					delete[]w;
					k = 0;
				}
				else
				{
					flag = 0;
					j = 0;
				}
			}
		}
	}
	vector<pair<string, int> > arr;
	for (map<string, int>::iterator it = words.begin(); it != words.end(); ++it)
	{
		arr.push_back(make_pair(it->first, it->second));
	}//将map的单个单词及数目存入vector容器并进行字典排序 
	sort(arr.begin(), arr.end(), cmp);//value排序 
	for (map<string, int>::iterator it = words.begin(); it != words.end(); ++it)
	{
		sum = sum + it->second;
	}
	cout << "words:" << sum << endl;
	ofstream out("result.txt");
	out << "characters:" << Countcharacters(argv[1]) << endl;
	out << "lines:" << CountLines(argv[1]) << endl;
	out << "words:" << sum << endl;
	//输出到result文本 
	i = 0;
	for (vector<pair<string, int> >::iterator it = arr.begin(); it != arr.end(); ++it)
	{
		cout << "<" << it->first << ">" << ":" << it->second << endl;
		out << "<" << it->first << ">" << ":" << it->second << endl;
		i++;
		if (i == 10)
		{
			break;
		}
	}
	i = 0;

	return 0;
}