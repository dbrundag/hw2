#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment
 **/
std::set<std::string> parseStringToWords(string rawWords)
{
	std::set<std::string> keywords;

	//replace punctuation with spaces
	for(unsigned int i=0; i < rawWords.length(); i++)
	{
		if(ispunct(rawWords[i]) != 0)
		{
			rawWords[i] = ' ';
		}
	}

	int end = 0;
	int beg = 0;
	unsigned int iter = 0;

	//identify each word by spaces
	//find all substrings greater than 2 chars and add to set
	//trying to use sliding window tactic
	while(iter < rawWords.length())
	{
		if(rawWords[end] == ' '){
			std::string keyword = rawWords.substr(beg, end - beg);
			if(keyword.length() >=2)
			{
				keywords.insert(keyword);
			}
			beg = end +1;
			end = 0;
			iter++;
			continue;
		}
		end++;
		iter++;
	}
	return keywords;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
