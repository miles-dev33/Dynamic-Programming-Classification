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
	string line;			//vector read buffer
	words.clear();
	if (!inFile.is_open())
		return false;
	else
	{
		while (inFile)		//file traversal & load loop
		{
			getline(inFile, line);
			words.push_back(line);
		}
		words.pop_back();
		inFile.close();
		return true;
	}
}

// Return true if string2 is a mirrored copy of string1, or false
// otherwise. In other words, return true if string1 is the reverse of
// string2. Return false when both strings are equal; by this rule,
// "aaa" is not a mirror of "aaa" even though they are technically the
// reverse of each other. Likewise "" is not a mirror of "". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_mirrored(const std::string& string1, const std::string& string2) {
	int length1 = string1.size();
	int length2 = string2.size();
	if (length1 != length2)			//non-mirror case
		return false;
	else if (string1 == string2)	//same string case
		return false;
	else							//possible mirror case 
	{
		int i = 0;
		int j = length1 - 1;

		while (i < length1)
		{
			if (string1[i] != string2[j])	//increment from one side and decrement from the other to match
				return false;
			i++;
			j--;
		}
		return true;
	}
}

// Return true if alleged_substring can be found as a substring of
// alleged_superstring. For example, "cat" is a substring of
// "catamaran"; "tama" is also a substring of "catamaran". This
// function should be in-place, meaning that it only examines string1
// and string2 and never creates another string object.
bool is_substring(const std::string& alleged_substring, const std::string& alleged_superstring) {
	int super_len = alleged_superstring.size();
	int sub_len = alleged_substring.size();
	bool substring_exists = false;	//return value control variable
	int k = 0;						//superstring character counter

	if (alleged_substring == "" && alleged_superstring == "")
		return true;
	else if (alleged_substring == "" && alleged_superstring != "")     //subsest logic flow controls
		return true;
	else if (alleged_superstring == "" && alleged_substring != "")
		return false;
	else
	{
		for (int i = 0; i < super_len; i++)
		{
			if (alleged_superstring[i] == alleged_substring[0])						//when the first letter of of substring matches in the superstring
			{
				if (alleged_superstring.substr(i, super_len - i).size() >= sub_len)	//making sure that the length of the superstring is greater than or equal to the length of the substring
				{
					k = 0;															//reset counter for subsequent loop iterations
					for (int j = 0; j < sub_len; j++)
					{
						if (alleged_superstring[i + k] == alleged_substring[j])		//check from first match to end of substring length
							substring_exists = true;
						else
							substring_exists = false;
						k++;
					}
				}
			}
		}
	}

	if (substring_exists)
		return true;
	else
		return false;
}

// Return the character that occurs the most times in the given vector
// of strings. The vector must contain at least one character, so that
// the mode is defined. In the event of a tie (i.e. two characters
// have the same count), this function returns the tied character with
// the lesser ASCII code (i.e. the tied character that comes first in
// conventional alphabetical order).
char character_mode(const string_vector& strings) {
	int charArray[256] = { 0 };
	string word;
	char character;
	int num_words = strings.size();
	int num_chars = 0;
	int index_biggest = 0;
	for (int i = 0; i < num_words; i++)				//loop through every word in the input vector
	{
		word = strings[i];
		num_chars = strings[i].size();
		for (int j = 0; j < num_chars; j++)			//loop through every character for every word
		{
			character = word[j];
			charArray[int(character)]++;			//increment in charArray by ASCII value
		}
	}
	for (int i = 0; i < 256; i++)					//finding the character that occurs the most times
	{
		if (charArray[index_biggest] < charArray[i])
			index_biggest = i;
	}

	return char(index_biggest);						//int to char conversion
}

// Return a longest string in the strings vector whose mirror is also
// in the vector. Strings are mirrors of each other in the same sense
// as described above for the is_mirrored(...) function. Either of the
// two mirrored strings may be returned; for example, if the vector
// contains both "cat" and "tac", this function is allowed to return
// either "cat" or "tac". If the vector contains no mirrored strings,
// returns an empty string.
std::string longest_mirrored_string(const string_vector& strings) {
	vector <string> mirrorArray;
	int vec_len = strings.size();
	int mirror_len = 0;
	int longest_index = 0;
	for (int i = 0; i < vec_len; i++)
	{
		for (int j = i + 1; j < vec_len; j++)								//mirror comparison loops
		{
			if (is_mirrored(strings[i], strings[j]))
				mirrorArray.push_back(strings[i]);							//store mirror when found
		}
	}
	mirror_len = mirrorArray.size();
	for (int i = 0; i < mirror_len; i++)									//longest mirror search loop
	{
		if (mirrorArray[longest_index].size() < mirrorArray[i].size())
			longest_index = i;												//store index of longest mirror
	}
	if (mirror_len == 0)													//when no mirrors are found
		return "";
	else
		return mirrorArray[longest_index];
}

// Return a vector of length exactly three, containing the longest
// substring trio from the string vector. A substring trio is three
// non-empty, distinct, strings a, b, and c such that a is a substring
// of b, b is a substring of c. This function returns the substring
// trio with the longest total length of a, b, and c. If the input
// vector does not contain a substring trio, return a vector
// containing exactly three empty strings.
string_vector longest_substring_trio(const string_vector& strings) {
	vector <string> trio = { "","","" };
	int vec_len = strings.size();
	int longest_trio = 0;
	int trio_length = 0;
	for (int i = 0; i < vec_len; i++)
	{
		for (int j = i + 1; j < vec_len; j++)
		{
			for (int k = j + 1; k < vec_len; k++)			//triply nested for loop for n^3 combinations of substrings
			{
				trio_length = strings[i].size() + strings[j].size() + strings[k].size();
				if (((is_substring(strings[i], strings[j]) && is_substring(strings[j], strings[k])) ||
					(is_substring(strings[j], strings[i]) && is_substring(strings[i], strings[k])) &&
					longest_trio < trio_length))			//true when [i] is a subset of [j] is a subset of [k] OR [j] is a subset of [i] is a subset of [k]
				{											//store trio when true for current loop iteration
					trio[0] = strings[i];
					trio[1] = strings[j];
					trio[2] = strings[k];
					longest_trio = trio_length;
				}
			}
		}
	}
	return trio;
}
