/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Author: Jonathan Margoliash
 *  Modified from code authored by: Jor-el Briones, Christine Alvarado
 */

#ifndef AUTOCOMPLETE_HPP
#define AUTOCOMPLETE_HPP

#include <vector>
#include <string>
#include <utility>
using namespace std;

/**
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie.
 */

//Node class to implement ternary trie.
class Node{

public:
    Node * center;
    Node * left;
    Node * right;
    char data;
    unsigned int frequency;
    bool leaf;

//Constructor for Node, set to null or 0, assign char data
    Node(const char & d){
        data = d;
        frequency = 0;
        leaf = false;
        center = left = right = nullptr;
    }
};

//This is a helper that is used to sort in PredictCompletions. It sorts first 
//by frequency, then by alphabetical order.
bool checkFrequency(pair<string, unsigned int> p1, pair<string, unsigned int> p2){

    if(p1.second==p2.second){   //if same frequency
        
      
        if(p1.first.compare(p2.first)<0)    //use string::compare STL function
            return true;                    
        else
            return false;   
    }
    
    //If not same frequency, return true to use p1 first or false to use p2
    return p1.second > p2.second;

}

class Autocomplete
{
public:

    //Gives access to root node of trie
    Node * root; 

  /* 
  Build the Autocomplete structure, calls help from "insert" helper function.
  */
    Autocomplete(const vector<string> words) {
  
        root = 0;   //Initialize root to 0 to start building.

        //For all the words in the vector, insert them into trie
        for (unsigned int i = 0; i<words.size(); ++i){
            insert(words[i]);
        }
    }

    /* Print out contents of tree - uses inorder traversal to print contents
     * in order. Has recursive helper function traverse.
     */
    void print(){
        string empty;
        traverse(empty, root);  
    }

  /* Return up to 10 of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than 10 legal completions, this
   * function returns a vector with as many completions as possible.
   * Otherwise, 10 completions should be returned.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the 10 most frequent completions
   * of the prefix)
   * If you need to choose between two or more completions which have the same frequency,
   * choose the one that comes first in alphabetical order.
   *
   * Inputs: prefix. The prefix to be completed. Must be of length >= 1.
   * Return: the vector of completions
   */
    vector<string> predictCompletions(const string prefix) {

        //Check if prefix is size 0. If it is, return vector of size 0.
        if(prefix.size()==0){
            return vector<string>();
        }
        //Nodes to move through trie
        Node * parent;
        Node * curr = root;

        //Pump through nodes until we have found entire prefix.
        for (unsigned int i = 0; i<prefix.size(); ++i){
            if(curr){

                parent = curr;
                    
                //curr = input at i, keep traversing down
                if(curr->data == prefix[i]){
                    curr= curr->center;
                }

                //curr > input at i, go left
                else if(curr->data > prefix[i]){
                    if(curr->left){
                        curr = curr->left;
                    }
                    else{
                        return vector<string>(); 
                    }
                    --i;
                }

                //curr < input at i, go right
                else{
                    if(curr->right){
                        curr = curr->right;
                    }
                    else{
                        return vector<string>();
                    }
                    --i;
                }                    
            }
        }

        //Param for helper function.
        vector<pair<string, unsigned int>> pairs;
       
        //Edge Case: for when prefix = a word node
        if(parent->leaf && parent->data==prefix[prefix.size()-1]){
            std::pair <std::string, unsigned int> insert (prefix, parent->frequency);
            pairs.push_back(insert);
        }

        //Call recursive helper to iterate through tree.
        predictHelper(&pairs, curr, prefix);

        //Sort the list using our own sorting function to sort by frequency
        sort(pairs.begin(), pairs.end(), checkFrequency);

        //Shorten the list after sorting.
        vector<string> output;
        if(pairs.size()>10){
            for(unsigned int i = 0; i<10; ++i){
                output.push_back(pairs[i].first);
            }
        }
    
        //If list is <10, just copy those elements without trimming the list
        else{
            for(unsigned int i = 0; i<pairs.size(); ++i){
                output.push_back(pairs[i].first);
            }
     
        }

        return output;
    }

  /* Destructor */
  ~Autocomplete() {
    deleteAllNodes(root); 
  }

private:

    //Recursive helper for Autocomplete(); inserts words one at a time.
    void insert(const string word){

        if(!root){   //this is first insertion        
            root = new Node(word[0]);   //Make root node
            Node * curr = root;         //curr pointer to iterate through

            for(unsigned int i = 1; i<word.size(); ++i){
                curr->center = new Node(word[i]);
                curr = curr->center;
            }

            //Set fields for leaf node
            ++curr->frequency;
            curr->leaf = true;

            return;
        }

        //words that are not the first insertion
        else{
            
            Node * parent;
            Node * curr = root;

            for(unsigned int i = 0; i<word.size(); ++i){

                //If curr exists, keep traversing the tree
                if(curr){

                    parent = curr;
                    
                    //curr = input at i, keep traversing down
                    if(curr->data == word[i]){
                        curr= curr->center;
                    }

                    //curr > input at i, go left
                    else if(curr->data > word[i]){

                        //If the correct node is already there, travel
                        if(curr->left){
                            curr = curr->left;
                        }

                        //If the correct node isn't already there, make one
                        else{
                            curr->left = new Node(word[i]);
                            curr = curr->left;
                        }
                            --i;
                    }

                    //curr < input at i, go right
                    else{

                        //If the correct node is already there, travel
                        if(curr->right){
                            curr = curr->right;
                        }

                        //If the correct node isn't already there, make one
                        else{
                            curr->right = new Node(word[i]);
                            curr = curr->right;
                        }
                            --i;
                    }
                    
                }

                //curr doesnt exist, so we must make new nodes going down to
                //insert the word
                else{
                    //center condition
                        parent->center = new Node(word[i]);
                        parent = parent->center;
                        curr = parent->center;
                }
            }
        //Set leaf and frequency
        parent->leaf = true;
        ++parent->frequency;
        }

    }

    //Recursive helper for the print function. Pretty much only used to help
    //debug.
    void traverse(string prefix, Node * curr){
        
        //If curr==null, do nothing
        if (curr){
            
            //For ordering, go left first
            traverse(prefix, curr->left);

            //If this is a leaf node (word), then print the contents to cout
            if (curr->leaf){
                cout<<prefix;
                cout<<curr->data<<"\n";
                cout<<curr->frequency<<"\n";
            }

            //Go center, add data to the string as you go
            traverse(prefix+curr->data, curr->center);

            //Go right
            traverse(prefix, curr->right);
        }
    }

    //Helper function for predict words, adds them to *pairs as a new prediction
    //is found in a subtree. The Node that the code starts travelling at is one
    //past the prefix, so it follows everynode in the subtree.
    void predictHelper(vector<pair<string, unsigned int>> * pairs, Node * curr, string prefix){

        //Go left first
        if (curr){
            predictHelper(pairs, curr->left, prefix);

            //If its a word, add it to the vector
            if(curr->leaf){
               std::pair <std::string, unsigned int> insert (prefix+curr->data, curr->frequency);
               pairs->push_back(insert);
            }
            
            //Go center, add data to the string
            if(curr->center)
                predictHelper(pairs, curr->center, prefix+curr->data);

            //Go right
            predictHelper(pairs, curr->right, prefix);
        }
    }

    //Helper function for the destructor, follows same basic traversal
    void deleteAllNodes(Node * curr){
        if (curr){
            if(curr->left)
                deleteAllNodes(curr->left);
    
            if(curr->center)
                deleteAllNodes(curr->center);

            if(curr->right)
                deleteAllNodes(curr->right);

            delete curr;
        }
    }
    

  //you may add your own code here

};

#endif // AUTOCOMPLETE_HPP
