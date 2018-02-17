/**
 * CSE 100 PA2 SpeechBuilder
 * Author: Jonathan Margoliash
 */

#ifndef DOCUMENT_GENERATOR_HPP
#define DOCUMENT_GENERATOR_HPP

#include <dirent.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <algorithm>
#include "AutocompleteUtils.hpp"

using namespace std;
class Node{
public:
    vector <pair<string, int>> nextWords;
    string word;

    Node(const string & input){
        word = input;
    }

};

class DocumentGenerator
{
public:

vector<Node *> words;

    //Removes unwanted chars from vector
  vector <string> removeUnwanted(vector <string> input){

        vector <string> output = input;

        for(unsigned int i = 0; i<output.size(); ++i){
            for (unsigned int j = 0; j<UNWANTED_CHARACTERS.size(); ++j){

                //If the input string at i is an unwanted character, erase it
                char unwanted = UNWANTED_CHARACTERS[j];
                output[i].erase(std::remove(output[i].begin(),output[i].end(),unwanted),
                    output[i].end());
                
            }
        }
        return output;
    }




 /* Builds a document generator from the documents in the given directory
 * This should open all files in the directory, reads them in, tokenize them into words,
 * and build the datastructure from that stream of words.
 *
 * To tokenize a document:
 * * remove all UNWANTED_CHARACTERS from the document
 * * split it into different tokens based on whitespace (treat all whitespace breaks equally)
 * * additionally split each PUNCTUATION character into its own token (so a single period is a 'word')
 * * from here on, we'll use the word "word" to refer to both strings like "hello" and punctuation strings like "." or ","
 *
 * So, for instance, the short sentence
 * "I like trains. Sally ju^mped over the moon, I think? I. I think."
 * Would be tokenized into ["I", "like", "trains", ".", "Sally",
 *   "jumped", "over", "the", "moon", ",", "I", "think", "?", "I", ".", "I" "think", "."]
 * and the frequencies of the words after "I" would be;
 *  like - 1
 *  think - 2
 *  . - 1
 *
 * You may use the utilities in AutocompleteUtils to help you with this
 * and you may rely on them working.
 * Note however that they do not deal with unwanted characters or split punctuation appropriately.
 * 
 * A few notes:
 * 1) you must treat words with different capitalizatoins differently
 * * (so "foo" and "Foo" are different words, and the frequencies of the words that follow (or precede)
 * * "foo" will be different than the frequencies of the words that follow (or precede) "Foo" )
 * 2) pretend that the first word in the document is preceeded by a periood (That way, it is considered when starting any new sentence)
 */
    DocumentGenerator(const string documentsDirectory) {
        
        //Open directory to build data structure
        DIR * directory = opendir(documentsDirectory.c_str());
        struct dirent* entry;
        vector <string> input;

        //Go entry by entry through the directory
        while((entry = readdir(directory))){

            //Return vector of the words in current document
            string file = documentsDirectory + "/"+entry->d_name;
            input = AutocompleteUtils::getwords(file); 

            //Remove unwanted words
            
            input = removeUnwanted(input);

            for(unsigned int i=0; i<input.size(); ++i){
                //if word is in the structure
                if(find(words.begin(), words.end(), input[i]) != words.end()){

                    //if the next word is in the structure too
                    //only increment the frequency it occurs
                    if(input[i+1] && find(words.begin(), words.end(), input[i+1]) != words.end()){ 
                    
                    }

                    //otherwise, add it to the Node's list, make frequency 1
                    else{
    

                    }
                }
        
                //word is not in structure, we make a new node
                else{
                    
                    //word is last word of document, break loop
                    if(){

                    }

                    //otherwise, look at next word and add to its list, make frequency 1
                    else{

                    }


                }
        
            }

        }

  }

  /**
 * Suppose you're in the middle of generating a document and that you've just added the word prevWord
 * to the document. generateNextWord(prevWord) should generate the next word at random for the document,
 * according to the frequencies of all the words that followed prevWord in the input documents
 *
 * So, for instance, if in all the input documents the word "foo" was followed by the word "bar" twice and "baz" 8 times,
 * then 80% of the time generateNextWord("foo") should return "baz" and 20% of the time you should return "bar".
 * 
 * This method should return punctuation words like "." and "," as if they were any other word.
 * Likewise, it should be able to take punctuation words as input (generateNextWord(","))
 * 
 * You can assume that prevWord is always a word that's present in one of the documents you've read in.
 */
  string generateNextWord(const string prevWord) {
    return ""; //TODO
  }

  /**
 * Generate a document with numWords words in it.
 *
 * See the docs on generateNextWord for a description of what it means to generate a word.
 * After generating all the words - concatenate them all into a single string representing the entire document, and return that string.
 *
 * Notes:
 * The first word you generate should be as if the previous word was '.'
 * Your document should not contain whitespace except for spaces.
 * Your should insert a single space in front of each word except:
 * * Don't insert spaces in front of punctuation marks
 * * Don't insert a space at the start of the document
 * 
 * The document will likely not end at the end of a sentence. That's okay.
 */
  string generateDocument(const int numWords) {
    return "";//TODO
  }

  ~DocumentGenerator() {
    //TODO
  }
  
  //Feel free to put your own code here

private:
    const string PUNCTUATION = ".!,?";
    const string UNWANTED_CHARACTERS = ";:\"~()[]{}\\/^_<>*=&%@$+|`";




  //Feel free to put your own code here
};

#endif //DOCUMENT_GENERATOR_HPP

