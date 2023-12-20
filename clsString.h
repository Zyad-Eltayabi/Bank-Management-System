#pragma once
#include<iostream>
#include <vector>
using namespace std;
class clsString
{
private:
	string _Value;
public:
	clsString()
	{
		_Value = "";
	}
	clsString(string Value)
	{
		_Value = Value;
	}
	void SetString(string Value)
	{
		_Value = Value;
	}
	string GetString()
	{
		return _Value;
	}
	__declspec(property(put = SetString, get = GetString)) string Value;

	static int CountWordsInString(string S1)
	{
		string delim = " "; // delimiter
		short pos = 0;
		string sWord; // define a string variable
		int Counter = 0;
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				Counter++;
			}
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
		{
			Counter++;
		}
		return Counter;
	}
	int CountWordsInString()
	{
		return CountWordsInString(_Value);
	}
	static string UpperAllLetters(string YourString)
	{
		for (int i = 0; i < YourString.length(); i++)
		{
			YourString[i] = toupper(YourString[i]);
		}
		return YourString;
	}
	string UpperAllLetters()
	{
		return UpperAllLetters(_Value);
	}
	static string LowerAllLetters(string YourString)
	{
		for (int i = 0; i < YourString.length(); i++)
		{
			YourString[i] = tolower(YourString[i]);
		}
		return YourString;
	}
	string LowerAllLetters()
	{
		return LowerAllLetters(_Value);
	}
	static short CountCapitalLetters(string& ReadString)
	{
		short Count = 0;
		for (short i = 0; i < ReadString.length(); i++)
		{
			if (ReadString[i] != ' ')
			{
				if (isupper(ReadString[i]))
				{
					Count++;
				}
			}
		}
		return Count;
	}
	short CountCapitalLetters()
	{
		return  CountCapitalLetters(_Value);
	}
	static short CountSmallLetters(string& ReadString)
	{
		short Count = 0;
		for (short i = 0; i < ReadString.length(); i++)
		{
			if (ReadString[i] != ' ')
			{
				if (islower(ReadString[i]))
				{
					Count++;
				}
			}
		}
		return Count;
	}
	short CountSmallLetters()
	{
		return CountSmallLetters(_Value);
	}
	static int CountCharacterRepetition(string& UserString, char& Letter)
	{
		int Counter = 0;
		for (char& L : UserString)
		{
			if (Letter == L)
				Counter++;
		}
		return Counter;
	}
	int CountCharacterRepetition(char Letter)
	{
		return  CountCharacterRepetition(_Value, Letter);
	}
	static bool CheckTheLetterIsVowel(char Letter)
	{
		Letter = tolower(Letter);
		return ((Letter == 'a') || (Letter == 'e') || (Letter == 'i') || (Letter == 'o') || (Letter == 'u'));
	}
	static int CountVowelNumbersInString(string StringFromUser)
	{
		int Counter = 0;
		for (char& L : StringFromUser)
		{
			if (CheckTheLetterIsVowel(L))
				Counter++;
		}
		return Counter;
	}
	int CountVowelNumbersInString()
	{
		return CountVowelNumbersInString(_Value);
	}
	static void PrintVowelLettersInString(string StringFromUser)
	{
		int Counter = 0;
		for (char& L : StringFromUser)
		{
			if (CheckTheLetterIsVowel(L))
				cout << "  " << L;
		}
	}
	void PrintVowelLettersInString()
	{
		PrintVowelLettersInString(_Value);
	}
	static void PrintEachWordInString(string S1)
	{
		string delim = " "; // delimiter
		cout << "\nYour string wrords are: \n\n";
		short pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos); // store the word
			if (sWord != "")
			{
				cout << sWord << endl;
			}
			S1.erase(0, pos + delim.length()); /* erase() until
			positon and move to next word. */
		}
		if (S1 != "")
		{
			cout << S1 << endl; // it print last word of the string.
		}
	}
	void PrintEachWordInString()
	{
		PrintEachWordInString(_Value);
	}
	static vector <string> SplitString(string S1, string delim)
	{
		vector <string> vTokens;
		short pos = 0;
		string sWord; // define a string variable
		// use find() function to get the position of the delimiters
		while ((pos = S1.find(delim)) != std::string::npos)
		{
			sWord = S1.substr(0, pos);
			if (sWord != "")
			{
				vTokens.push_back(sWord);
			}
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
		{
			vTokens.push_back(S1);

		}
		return vTokens;
	}
	vector <string> SplitString(string delim)
	{
		return SplitString(_Value,delim);
	}
	static string JoinString(vector <string> Names, string Delim)
	{
		string FullName = "";
		for (string& name : Names)
		{
			FullName = FullName + name + Delim;
		}
		return FullName;
	}
	static string ReverseString(string UserString)
	{
		string Words = "";
		for (short i = UserString.length() - 1; i >= 0; i--)
		{
			if (UserString[i] == ' ')
			{
				Words = Words + UserString.substr(i + 1, UserString.length()) + " ";
				UserString.erase(i, UserString.length());
			}
		}
		return Words + UserString;
	}
	string ReverseString()
	{
		return ReverseString(_Value);
	}
	static string ReplaceWordsInString(string UserString, string word1, string word2)
	{
		short pos = UserString.find(word1);

		while (pos != std::string::npos)
		{
			UserString = UserString.replace(pos, word1.length(), word2);
			pos = UserString.find(word1);
		}
		return UserString;
	}
	string ReplaceWordsInString(string word1, string word2)
	{
		return ReplaceWordsInString(_Value, word1, word2);
	}
	static string RemovePunctuationCharacters(string Words)
	{
		string RemovePunctuation = "";
		for (short i = 0; i < Words.length(); i++)
		{
			if (!ispunct(Words[i]))
			{
				RemovePunctuation += Words[i];
			}
		}
		return RemovePunctuation;
	}
	string RemovePunctuationCharacters()
	{
		return RemovePunctuationCharacters(_Value);
	}



};

