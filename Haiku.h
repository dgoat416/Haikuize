#ifndef _HAIKU
#define _HAIKU


#include <string>
#include <vector>
using namespace std;

// Word data type
struct Word
{
public:
	vector<char> vChar;									// holds whether each character is a vowel or a consonant
	int vowels = 0;
	int consonants = 0;
};

// Line data type
struct Line
{
	int __syllables = 0;
	string oneLine = "";
};


class Haiku
{
public:
	Haiku();
	~Haiku();

	/*
	Parses input and stores words in <words vector>
	*/
	void Parse();

	/*
	Outputs a Haiku using an ofstream object
	*/
	void Haikuize(ofstream & _oFile);

	/*
	Outputs a Haiku using an ostream object
	*/
	void Haikuize(ostream & _cout);

	/*
Determines if the user input has 17 or > syllables
If there are 17 syllables then the input can
be made into a haiku, otherwise it can't
@param _input = original input string from user
@return
		- true = there are >= 17 syllables
		- false = there are < 17 syllables
*/
	bool _17Syllables(vector<int> _syllables);


	/*
Determines if a letter is a vowel or not
@param = _letter is a letter that you want to determine is a vowel or not
@return
		- true = _letter is a vowel
		- false = _letter is a consonant
*/
	bool isVowel(char _letter, int pos, string _word);

	/*
Determines whether characters in _word is a vowel or not
@param _word is a word from the user input
@return a struct (by value)
*/
	Word Vowels(string _word);


	/**
	 * Gets rid of leading white space in a string
	 * @param str is a string that should have white
	 *  space chars to get rid of
	 * @return temp which is the string with no leading whitespace
	 */
	string NoLeadingWhiteSpace(string str);


	/*
Determines how many syllables are in a word
@param _word = word to find syllables for
@return number of syllables in one word(the string parameter)
*/
	int Syllables(string _word);

/*
Converts the parameter string to only alphabetical 
characters
@param _word = word to return a only alphabetical
version of
@return the only alphabetical version of _word
*/
	string onlyAlphaChars(string _word);

	/*
	Accessor function to return vector<int> syllables
	@return private member variable syllables
	*/
	vector<int> getSyllables();

	/*
	Accessor function to return vector<int> syllables
	@return private member variable syllables
	*/
	int getTotalSyllables();

	/*
	Mutator function to set private member variables
	@param int s =  changes private member variable syllables
	@param string _word =  changes private member variable words
	*/
	void setHaikuInfo(int s, string _word);

	/*
	Accessor function to return vector<string> words
	@return private member variable words
	*/
	vector<string> getWords();


private:
	vector<string> words;
	vector<int> syllables;
	int totalSyllables = 0;
};

#endif