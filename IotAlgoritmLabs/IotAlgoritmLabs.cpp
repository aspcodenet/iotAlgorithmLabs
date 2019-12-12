// IotAlgoritmLabs.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
#include <fstream>
#include <iterator>
#include <sstream> 

using namespace std;

void Lab1()
{
	vector<char> v;
	for (char ch = 'a'; ch != 'z'; ch++)
		v.push_back(ch);

	sort(begin(v), end(v));

	for_each(begin(v), end(v), [](char ch) {
		cout << ch << ',';
		});

	cout << endl;

	sort(begin(v), end(v), std::greater<char>());

	for_each(begin(v), end(v), [](char ch) {
		cout << ch << ',';
		});

}

void Lab2()
{
	ifstream infile(".\\Cars.txt", ios::in);
	vector<string> cars;
	string line;
	while (getline(infile, line))
		if(!line.empty())
			cars.push_back(line);
	
	sort(begin(cars), end(cars), [] (string line1, string line2){
		return line2.length() > line1.length();
		});

	for (string c : cars)
		cout << c << endl;
}

void Lab3()
{
	ifstream infile(".\\birds.txt", ios::in);
	vector<string> birds;
	string line;
	while (getline(infile, line))
		if (!line.empty())
			birds.push_back(line);

	int antal = count_if(begin(birds), end(birds), [](string birdname) {
		if (birdname[0] == 'B' || birdname[0] == 'b') return true;
		return false;
		//return (birdname[0] == 'B' || birdname[0] == 'b');
		});

	cout << "Börjar på B " << antal << endl;

	antal = count_if(begin(birds), end(birds), [](string birdname) {
		return ((birdname[0] == 'D' || birdname[0] == 'd') || birdname.length() > 10);
		});
	cout << "Börjar på D  eller mer än 10 tecken " << antal << endl;

}


void Lab4()
{
	ifstream infile(".\\birds.txt", ios::in);
	vector<string> birds;
	string line;
	while (getline(infile, line))
		birds.push_back(line);

	bool b = any_of(begin(birds), end(birds), [](string birdname) {
		return (birdname.find("kad") != string::npos);
		});
	cout << "Innehåller kad " << b << endl;




	vector<string> mellanslag;
	copy_if(begin(birds), end(birds),back_inserter(mellanslag),
		[](string birdname) {
			return (birdname.find(' ') != string::npos);
		});
	for (string s : mellanslag)
		cout << s << endl;

	//Alt 2 lambda with captures
	//for_each(begin(birds), end(birds), 
	//	[&mellanslag](string birdname) {
	//		if ((birdname.find(' ') != string::npos))
	//			mellanslag.push_back(birdname);
	//	});


}


void Lab5()
{
	ifstream infile(".\\birds.txt", ios::in);
	vector<string> birds;
	string line;
	while (getline(infile, line))
		if (!line.empty())
			birds.push_back(line);

	transform(begin(birds), end(birds), begin(birds), [](string& str) {
			std::transform(str.begin(), str.end(), str.begin(), ::toupper);	
			return str;
		});

	for (string s : birds)
		cout << s << endl;

}


std::vector<std::string> split(const std::string& s, char delimiter)
{
	std::vector<std::string> tokens;
	std::string token;
	std::istringstream tokenStream(s);
	while (std::getline(tokenStream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

void Lab6()
{
	ifstream infile(".\\iso.txt", ios::in);
	vector<string> words;
	string line;
	while (getline(infile, line))
		if (!line.empty())
		{
			for (string s : split(line, ' '))
				if(s.length() > 0)
					words.push_back(s);
		}

	sort(begin(words), end(words));

	words.erase(unique(words.begin(), words.end()), words.end());
	//Alt...  set<string> s( words.begin(), words.end() );
	// words = s;

	for (string s : words)
		cout << s << endl;


	sort(begin(words), end(words), [](string s1, string s2) {
		if (s1.length() == s2.length())
			return s1 < s2;
		return s1.length() < s2.length();
		});
	for (string s : words)
		cout << s << endl;


	int antal = count_if(begin(words), end(words), [](string word) {
		return word.length() > 5;
		}
	);
	cout << (float)antal / (float)words.size();


	vector<string> badWords = {
		"and", "but", "do", "if", "in", "is", "its", "not", "of", "or" , "that", "the", "to"
	};

	cout << words.size() << endl;
	words.erase(remove_if(begin(words), end(words), [badWords] (string word){
		bool ret = find(begin(badWords), end(badWords), word) != badWords.end();
		return ret;
		}),end(words));

	auto iterator = remove_if(begin(words), end(words), [badWords](string word) {
		bool ret = find(begin(badWords), end(badWords), word) != badWords.end();
		return ret;
		});
	words.erase(iterator, end(words));


	cout << words.size() << endl;

}


int main()
{
	Lab1();
	Lab2();
	Lab3();
	Lab4();
	Lab5();
	Lab6();
	return 0;
}
