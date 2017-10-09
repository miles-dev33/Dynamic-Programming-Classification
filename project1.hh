///////////////////////////////////////////////////////////////////////////////
// project1.hh
//
// The three algorithms specified in the project 1 requirements
// document, plus helper functions.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once
#include "timer.hh"


#include <algorithm>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// Convenient typedef for a vector of strings.
typedef std::vector<std::string> string_vector;

// Load words from the file at the given path. The words vector is
// cleared, and then each word from the file is added to the
// vector. Returns true on success or fale on I/O error.
bool load_words(string_vector& words, const std::string& path) {
	ifstream inFile("../" + path);
	string line;   //This is the string that is used for reading input from the file to the vector
	words.clear(); //Cleared the words vector before pushing 
	if (!inFile)   //checks if the file was loaded correctly or not
	{
		return false;
	}
	else
	{
		//traverses the file loading all of the words in it into the words vector
		while (inFile)
		{
			getline(inFile, line);
			words.push_back(line);
		}
		words.pop_back();
		inFile.close();
	}

	return true;
}

// Return true if string2 is a mirrored copy of string1, or false
// otherwise. In other words, return true if string1 is the reverse of
// string2. Return false when both strings are equal; by this rule,
// "aaa" is not a mirror of "aaa" even though they are technically the
// reverse of each other. Likewise "" is not a mirror of "". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_mirrored(const std::string& string1, const std::string& string2) {
	// TODO: implement this function, then delete this comment
	int length1 = string1.size() - 1; //length of string 1
	int length2 = string2.size() - 1; //length of string 2
	if (length1 != length2) //if they aren't equal in length then no mirror
	{
		return false;
	}
	else if (string1 == string2) //if they are the same string then no mirror
	{
		return false;
	}
	else //else check if they are mirrors of eachother by checking if both ends of the 
		 //strings are equal by decrementing from the end of one, and incrementing from the 
		 //beggining of the other 
	{

		int i = 0;
		int j = length1;

		while (i <= length1)
		{

			if (string1[i] != string2[j])
			{
				return false;
			}
			i++;
			j--;
		}
	}
	//return true that they are mirrors
	return true;
}

// Return true if alleged_substring can be found as a substring of
// alleged_superstring. For example, "cat" is a substring of
// "catamaran"; "tama" is also a substring of "catamaran". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_substring(const std::string& alleged_substring,
	const std::string& alleged_superstring) {
	// TODO: implement this function, then delete this comment
	int length = alleged_superstring.size() - 1;
	int length2 = alleged_substring.size() - 1;
	int i = 0;
	bool testing = false;
	int k = 0;

	if (alleged_substring == "" && alleged_superstring == "")
	{
		return true;
	}
	else if (alleged_substring == "" && alleged_superstring != "")
	{
		return true;
	}
	else if (alleged_superstring == "" && alleged_substring != "")
	{
		return false;
	}
	else
	{
		for (int i = 0; i < length; i++)
		{
			if (alleged_superstring[i] == alleged_substring[0])
			{
				//making sure that the length of the superstring is greater than the length of the substring
				if (alleged_superstring.substr(i, length - i).size() >= length2)
				{
					k = 0;//to resest the k value so sequences of substrings can be rechecked
					for (int j = 0; j <= length2; j++)
					{
						if (alleged_superstring[i + k] == alleged_substring[j])
						{
							testing = true;
						}
						else
						{
							testing = false;
						}
						k++;
					}
				}
			}

		}
	}

	if (testing)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Return the character that occurs the most times in the given vector
// of strings. The vector must contain at least one character, so that
// the mode is defined. In the event of a tie (i.e. two characters
// have the same count), this function returns the tied character with
// the lesser ASCII code (i.e. the tied character that comes first in
// conventional alphabetical order).
char character_mode(const string_vector& strings) {
	// TODO: implement this function, then delete this comment
	int charArray[256] = { 0 };
	int length = strings.size() - 1;
	string temp;
	int tempLength = 0;
	int count = 0;
	char character;
	int index_biggest = 0;
	for (int i = 0; i <= length; i++)
	{
		temp = strings[i];
		tempLength = strings[i].size() - 1;
		while (count <= tempLength)
		{
			character = temp[count];
			charArray[int(character)]++;
			count++;
		}
		count = 0;//for counting other words. duh.
	}
	for (int i = 0; i < 256; i++)
	{
		if (charArray[index_biggest] < charArray[i])
		{
			index_biggest = i;
		}
	}

	return char(index_biggest);
}

// Return a longest string in the strings vector whose mirror is also
// in the vector. Strings are mirrors of each other in the same sense
// as described above for the is_mirrored(...) function. Either of the
// two mirrored strings may be returned; for example, if the vector
// contains both "cat" and "tac", this function is allowed to return
// either "cat" or "tac". If the vector contains no mirrored strings,
// returns an empty string.
std::string longest_mirrored_string(const string_vector& strings) {
	// TODO: implement this function, then delete this comment

	vector <string> mirrorArray;

	int length = strings.size() - 1;

	for (int i = 0; i < length; i++)
	{
		for (int j = i + 1; j <= length; j++)
		{
			if (is_mirrored(strings[i], strings[j]))
			{

				mirrorArray.push_back(strings[i]);
			}
		}

	}
	int longestIndex = 0;
	int length2 = mirrorArray.size();
	//cout << "length2: " << length2 << endl;

	for (int i = 0; i < length2; i++)
	{
		if (mirrorArray[longestIndex].size() < mirrorArray[i].size())
		{
			longestIndex = i;
		}
	}


	if (length2 == 0)
	{
		return "";
	}
	else
	{
		return mirrorArray[longestIndex];
	}

	return "";
}

// Return a vector of length exactly three, containing the longest
// substring trio from the string vector. A substring trio is three
// non-empty, distinct, strings a, b, and c such that a is a substring
// of b, b is a substring of c. This function returns the substring
// trio with the longest total length of a, b, and c. If the input
// vector does not contain a substring trio, return a vector
// containing exactly three empty strings.
string_vector longest_substring_trio(const string_vector& strings) {
	vector <string> subStringTrio = { "","","" };
	int len = strings.size();
	int best_length = 0;
	int abc_length = 0;
	bool found = false;



	for (int i = 0; i < len; i++)
	{
		cout << "i:" << i << endl;
		for (int j = i + 1; j < len; j++)
		{
			for (int k = j + 1; k < len; k++)
			{
				cout << " strings[i]" << strings[i] << " strings[j]" << strings[j] << " strings[k]" << strings[k] << endl;





				abc_length = strings[i].size() + strings[j].size() + strings[k].size();
				if (((is_substring(strings[i], strings[j]) && is_substring(strings[j], strings[k])) ||
					(is_substring(strings[j], strings[i]) && is_substring(strings[i], strings[k])) &&
					best_length < abc_length))
				{
					subStringTrio[0] = strings[i];
					subStringTrio[1] = strings[j];
					subStringTrio[2] = strings[k];
					best_length = abc_length;
				}
			}
		}
	}
	return subStringTrio;
}
