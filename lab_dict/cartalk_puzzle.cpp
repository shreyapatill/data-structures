/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    /* Your code goes here! */
    string str;
    ifstream infile(word_list_fname);
    if( infile.is_open() ){
        while( getline(infile, str) ){
            if( str.size() == 5 ){
                string str1 = str.substr(1, str.size()-1);
                string str2 = str[0] + str.substr(2, str.size()-1);
                if( d.homophones(str, str1) && d.homophones(str, str2) )
                    ret.push_back(tuple<string, string, string>(str, str1, str2));
            }
        }
    }
    infile.close();
    return ret;
}
