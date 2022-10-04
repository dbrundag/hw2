#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <sstream>
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
	rawWords = convToLower(rawWords);
	//replace punctuation with spaces
	for(unsigned int i=0; i < rawWords.length(); i++)
	{
		if(ispunct(rawWords[i]) != 0)
		{
			rawWords[i] = ' ';
		}
	}

	stringstream ss(rawWords);
	std::string keyword;

	while(ss >> keyword) 
	{
		if(keyword.size() > 1)
		{
			keywords.insert(keyword);
		}
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
