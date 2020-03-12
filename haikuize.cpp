///*
//Name:		Deron Washington II
//Class:		CECS 282
//Instructor:	Minhthong Nguyen
//Purpose:	Examine a line of English text and
//			"haikuize" it
//*/
//
//#include <iostream>									// console i/o
//#include <string>									// string library
//#include <fstream>									// file i/o
//#include <vector>									// vector container
//#include "Haiku.h"
//
//using namespace std;								// standard namespaces
//
//void main()
//{
//	Haiku myHaiku;
//	ofstream myOutput;
//
//	myHaiku.Parse();
//
//	// if 17 syllables in the input then make a Haiku
//	if (  myHaiku._17Syllables( myHaiku.getSyllables() ) == true  ) 
//	{
//		myHaiku.Haikuize(myOutput);
//	}
//
//	else   // can't make Haiku
//	{
//		for (auto const & input : myHaiku.getWords())
//			myOutput << endl << input + " ";
//	}
//
//	// close output file
//	if (myOutput.is_open())
//			myOutput.close();
//
//	cout << "Check file entitled haiku.txt ";
//	printf("\n \n");					// new line before closing 
//	system("pause");					// pause before closing the program
//}
//
//
//
