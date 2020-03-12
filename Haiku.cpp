#include "Haiku.h"
#include <iostream>
#include <fstream>
#include <typeinfo>



Haiku::Haiku()
{
}

Haiku::~Haiku()
{
}

void Haiku::Parse()
{
	ifstream myFile;				// input file
	string input = "";			// holds line from file

	myFile.open("sentences.txt");
	if (myFile.is_open())
	{
		while (myFile.eof() == false)
		{
			getline(myFile, input);


			// PARSE THE INPUT STRING FOR EACH WORD 
			int endPosition = 0;			// holds the value of the position where end of first word is (-- for array position)
			string temp_input1 = input,		// temporary string to find word
				temp_input2 = "",			// temporary string to hold rest of string after a word is extracted from the input
				word = "";					// temporary string to hold a word from the input

			do
			{
				// take in word from input string
				endPosition = temp_input1.find(' ');				// find the end of the word (where space is)

				if (endPosition == -1)								// found last word
				{
					syllables.push_back(Syllables(temp_input1)); 	// add syllables of last word to vector	
					words.push_back(temp_input1);					// add last word to vector


					break;
				}

				temp_input2 = temp_input1.substr(++endPosition);	// store string after first word
				word = temp_input1.erase(--endPosition);			// erase everything after end of word
				temp_input1 = temp_input2;							// restart process

				
				syllables.push_back(Syllables(word));				// add syllables of most recent word to vector
				words.push_back(word);								// add corresponding word to vector

			} while (endPosition != -1);							// loop until last word


		}

		if (myFile.is_open())
			myFile.close();
	}
}

void Haiku::Haikuize(ofstream & _output)
{
	// open output file 
	_output.open("haiku.txt");
	

	// create Line object to output lines
	Line myLine;
	int maxSyllables = 0;
	int wordIndex = 0;
	int tempSyllables = 0;


	// output line  1, 2, 3 of Haiku
	for (int i = 1; i <= 3; i++)
	{
		// reinitializes myLine
		myLine.oneLine = "";		
		myLine.__syllables = 0;
	
		switch (i)
		{
		case 1:
			maxSyllables = 5;
			break;
		case 2:
			maxSyllables = 7;
			break;
		case 3:
			maxSyllables = 5;
			break;
		}

		while (myLine.__syllables != maxSyllables && myLine.__syllables < maxSyllables)
		{
				myLine.oneLine = myLine.oneLine + " " + words.at(wordIndex);

				myLine.__syllables += syllables.at(wordIndex);
				wordIndex++;
		}

		// punctuation
		if (syllables.size() > wordIndex)
			if (syllables.at(wordIndex) == 0)
			{
				myLine.oneLine += " " + words.at(wordIndex);
				wordIndex++;
			}

		_output << left << NoLeadingWhiteSpace(myLine.oneLine)  << endl;
	}

	// output unneeded words (words that didn't make the Haiku)
	if (wordIndex < (words.size() - 1))
	{
		string strTemp = "";

		for (wordIndex; wordIndex < words.size(); wordIndex++)
			strTemp += words.at(wordIndex) + " ";

		_output << endl << left << NoLeadingWhiteSpace(strTemp);
	}

}

void Haiku::Haikuize(ostream & _cout)
{
	// create Line object to output lines
	Line myLine;
	int maxSyllables = 0;
	int wordIndex = 0;
	int tempSyllables = 0;


	// output line  1, 2, 3 of Haiku
	for (int i = 1; i <= 3; i++)
	{
		// reinitializes myLine
		myLine.oneLine = "";
		myLine.__syllables = 0;

		switch (i)
		{
		case 1:
			maxSyllables = 5;
			break;
		case 2:
			maxSyllables = 7;
			break;
		case 3:
			maxSyllables = 5;
			break;
		}

		while (myLine.__syllables != maxSyllables && myLine.__syllables < maxSyllables)
		{
			myLine.oneLine = myLine.oneLine + " " + words.at(wordIndex);

			myLine.__syllables += syllables.at(wordIndex);
			wordIndex++;
		}

		// punctuation
		if (syllables.size() > wordIndex)
			if (syllables.at(wordIndex) == 0 )
			{
				myLine.oneLine += " " + words.at(wordIndex);
				wordIndex++;
			}

		_cout << left << NoLeadingWhiteSpace(myLine.oneLine) << endl;
	}

	// output unneeded words (words that didn't make the Haiku)
	if (wordIndex < (words.size() - 1))
	{
		string strTemp = "";

		for (wordIndex; wordIndex < words.size(); wordIndex++)
			strTemp += words.at(wordIndex) + " ";

		_cout << endl << left << NoLeadingWhiteSpace(strTemp);
	}

}


bool Haiku::_17Syllables(vector<int> _syllables)
{
	int _totalSyllables = 0;

	for (int i = _syllables.size(); i > 0; i--)		// add total syllables in all words in _syllables
	{
		_totalSyllables += _syllables[i - 1];
	}

	if (_totalSyllables >= 17)
		return true;

	return false;
}

bool Haiku::isVowel(char _letter, int pos, string _word)
{
	switch (_letter)
	{
	case ('a'):
	case ('A'):
	case ('e'):
	case ('E'):
	case ('i'):
	case ('I'):
	case ('o'):
	case ('O'):
	case ('u'):
	case ('U'):
		return true;					// vowel
	case ('y'):
	case ('Y'):
	{
		if (isVowel(_word[pos + 1], (pos + 1), _word) == true)
			return true;				// vowel

		else
			return false;				// consonant
	}
	default:
		break;
	}

	return false;
}

Word Haiku::Vowels(string _word)
{
	Word myWord;

	for (int i = 0; i < _word.size(); i++)				// loop through the whole word to determine how many vowels and consonants there are
	{
		switch (_word[i])
		{
		case ('a'):
		case ('A'):
		case ('e'):
		case ('E'):
		case ('i'):
		case ('I'):
		case ('o'):
		case ('O'):
		{
			myWord.vowels++;
			myWord.vChar.push_back('v');					// vowel
			continue;								// go up to looping condition
		}

		case ('u'):
		case ('U'):
		{
			if (_word[i - 1] == 'q' || _word[i - 1] == 'Q')			// "QU" or "qu" then it is a consonant not a vowel
			{
				// since "qu" is a single consonant continue in the loop
				continue;
			}

			else
			{
				myWord.vowels++;
				myWord.vChar.push_back('v');								// vowel
			}

			continue;								// go up to looping condition
		}

		case ('y'):
		case ('Y'):
		{
			// if letter following 'y' is a vowel then y is a consonant
			if (isVowel(_word[i + 1], (i + 1), _word) == true)
			{
				myWord.consonants++;
				myWord.vChar.push_back('c');				// consonant
			}
			else
			{
				myWord.vowels++;
				myWord.vChar.push_back('v');				// vowel
			}

			continue;								// go up to looping condition
		}

		default:
		{
			myWord.consonants++;
			myWord.vChar.push_back('c');			// default is it's a consonant
			break;
		}

		} // end of switch
	} // end of for loop

	return myWord;
}

string Haiku::NoLeadingWhiteSpace(string str)
{
	string temp = "";
	int first = 0;				// holds index of first non white space char

		// start adding to temp when you encounter the first non white space char
	for (int j = 0; j < str.length(); j++)
	{
		if (str[j] != 32)
		{
			first = j;

			for (int i = first; i < str.length(); i++)
				temp += str[i];

			break;
		}
	}

	return temp;
}

int Haiku::Syllables(string _word)
{
	int _syllables = 0;
	string temp = "";

	// DATA VALIDATION GET RID OF ALL NON ALPHA CHARS HERE
	for (int i = 0; i < _word.length(); i++)
	{
		temp = onlyAlphaChars(_word);
	}

	if (temp == "")
		return _syllables;		// if temp is blank then _word is punctuation so return 0 syllables

	// stores struct generated from Vowels into oneWord
	Word oneWord = Vowels(temp);
	const int endOfWord = temp.length() - 1;
	//int numLetters = 0;		// numer of letters that have been accounted for



	// add syllables for normal cases
	for (int numLetters = 0; numLetters < oneWord.vChar.size() - 1; numLetters++)
	{
		// more than one consonant
		if (oneWord.consonants > 0)
		{
			if (oneWord.vChar.at(numLetters) == 'c')
			{
				if (oneWord.vChar.at(numLetters + 1) == 'v')
				{
					_syllables++;
					numLetters++;
					continue;
				}
			}

			else if (oneWord.vChar.at(numLetters) == 'v')
			{
				if (oneWord.vChar.at(numLetters + 1) == 'c')
				{
					_syllables++;
					numLetters++;
					continue;
				}
			}

		} // end of if more than one consonant
	} // end of for loop



	if (_syllables <= 0)
		return _syllables = 1;	// default return statement

	return _syllables;
}

string Haiku::onlyAlphaChars(string _word)
{
	string temp = "";
	for (int i = 0; i < _word.size(); i++)
	{
		if ((_word[i] >= 'A' && _word[i] <= 'Z')
			|| (_word[i] >= 'a' && _word[i] <= 'z')
			|| (_word[i] == ' '))				// if not alpha char erase it
			temp += _word[i];
	}

	return temp;
}

vector<int> Haiku::getSyllables()
{
	return syllables;
}

int Haiku::getTotalSyllables()
{
	for (int i = 0; i < syllables.size(); i++)
		totalSyllables += syllables.at(i);

	return totalSyllables;
}

void Haiku::setHaikuInfo(int s, string _line)
{
	syllables.push_back(s);
	words.push_back(_line);
	totalSyllables += s;
}

vector<string> Haiku::getWords()
{
	return words;
}
