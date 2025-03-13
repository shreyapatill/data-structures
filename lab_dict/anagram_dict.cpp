/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>
#include <iostream>

using std::string;
using std::vector;
using std::ifstream;
using std::pair;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    string str;
    ifstream infile( filename );
    if( infile.is_open() ){
        while( getline(infile, str) ){
            string substr = str;
            std::sort(substr.begin(), substr.end());
            dict[substr].push_back(str);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for( auto str : words ){
        string sub_str = str;
        std::sort(sub_str.begin(), sub_str.end());
        dict[sub_str].push_back(str);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string str = word;
    std::sort(str.begin(), str.end());
    if( dict.find(str) == dict.end() || dict.at(str).size() == 1 )
        return vector<string>();
    return dict.at(str);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> vec;
    for( auto v: dict )
        if( v.second.size() > 1 )
            vec.push_back( v.second );
    return vec;
}
