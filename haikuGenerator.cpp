#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include "Haiku.h"

using namespace std;

void main()
{
	Haiku myHaiku;
	int done = 1;
	srand(time(NULL));
	int randomNum = 0;
	int tempSyllables = 0;
	int syllableGoal = 5;
	string input = "";
	string tempLine = "";

	
	// open file
	ifstream inFile;
	inFile.open("words.txt");

	while (done < 4)
	{
		switch (done)
		{	
			case 1:
			{
				syllableGoal = 5;
				break;
			}
			case 2:
			{
				syllableGoal = 7;
				break;
			}
			case 3:
			{
				syllableGoal = 5;
				break;
			}
		}
		// generate random number between 0 - 60,999 b/c 61000 words/lines
		randomNum = rand() % 60999;

		// get the "randomNumth" line of the file
			for (int i = 0; i < randomNum; i++)
			{
					if (!inFile.eof())
						getline(inFile, input);
			}
			
			// are we are at or under our syllable goal if we add input?
			// yes = add it and update tempSyllables count
			if ((tempSyllables + myHaiku.Syllables(input)) <= syllableGoal)
			{
				tempLine += " " + input;
				tempSyllables += myHaiku.Syllables(input);
			}
			else // no = loop and find another word
			{
				//reset file stream
				inFile.clear();
				inFile.seekg(0, ios::beg);
				continue;
			}

			// are we at our syllable goal?
			if (tempSyllables == syllableGoal)
			{
				done++;
				myHaiku.setHaikuInfo(syllableGoal, tempLine);
				tempLine = "";
				tempSyllables = 0;
				
				//reset file stream
				inFile.clear();
				inFile.seekg(0, ios::beg);
			}

			

			if ( myHaiku._17Syllables(myHaiku.getSyllables()) )
				done = 4;

	}

	myHaiku.Haikuize(cout);

	cout << endl << endl;
	system("pause");

}