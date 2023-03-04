/******************************************************************************
//https://leetcode.com/problems/implement-trie-prefix-tree/solutions/632911/help-solution-with-dynamic-allocation-c/
//https://www.enjoyalgorithms.com/blog/introduction-to-trie-data-structure
           
*******************************************************************************/


# include <iostream>
#include <cstddef>
using namespace std;

class trienode
{
private:
	trienode* child[26];
	int n_chars = 26;
	bool word_end;
public:

	trienode()
	{	for (int i = 0; i < 26; i++) 
            child[i] = NULL;
	}
	
	int count_children(trienode* node)
	{
	    int count = 0;
	    for (int i = 0; i < 26; i++) 
	    {
	        if(child[i] != NULL)
	            count++;
	    }
	    return count;
	}
	
	
	bool containskey(char ch)
	{
		return child[ch - 'a']!= NULL;
	}
	
	trienode* get_node(char ch)
	{
		return child[ch-'a'];
	}
	
	void insert_char(char ch, trienode* node)
	{
		child[ch-'a'] = node;
	}
	
	void set_end_of_word(bool)
	{
	word_end = true;
	}
	
	bool is_end_of_word()
	{
		return word_end;
	}
};	


class trie
{
private:
trienode* root;
trienode* searchprefix(string word)
{
	trienode* node = root;
	for (int i=0; i<word.length(); i++)
	{
		char current_char = word.at(i);
		if (node->containskey(current_char))
		{
			node=node->get_node(current_char);
		}
		else
		{
			return NULL;
		}
	}
	return node;
}
public:
	trie()
	{
		root = new trienode();
	}

	void insert(string word)
	{
	    // shoould we check if the word already exists before insertion
		trienode* node = root;
		for (int i=0; i<word.length(); i++)
		{
			char current_char = word.at(i);
			if(!node->containskey(current_char))
			{
				node->insert_char(current_char,new trienode());
			}
			node = node->get_node(current_char);
		}
		node->set_end_of_word(true);
	}
	
	bool search(string word)
	{
		trienode* node = searchprefix(word);
		return node!=NULL && node->is_end_of_word();
	}
	
	bool startswith(string prefix)
	{
		trienode* node = searchprefix(prefix);
		return node!=NULL;
	}
	
	bool trie_delete(string word)
	{
		trienode* node = root;
		int children = 0;
		for(int i=0; i<word.length(); i++)
		{
			char current_char = word.at(i);
			if(!node->containskey(current_char))
				return false;
			else
			{
				node = node->get_node(current_char);
				children = node->count_children(node);
			}			
		}
				
		if(children == 1)
		{
			node = NULL;
			return true;
		}
		if(node->is_end_of_word())
		{
			node->set_end_of_word(false);
			return true;
		}
		else
		{
			node = NULL;
			return true;
		}
			
	}

};

int main()
{
	string word = "annie";
	string wordprefix = "an";
	trie* obj = new trie();
	
	obj->insert(word);
	bool search_result = obj->search(word);
	bool search_prefix_result = obj->startswith(wordprefix);
	bool delete_result = obj->trie_delete(word);
	bool delete_prefix_result = obj->trie_delete(wordprefix);
	
	cout << "search_result:" << search_result << endl;
	cout << "search_prefix_result" << search_prefix_result << endl;
	cout << "delete_result" << delete_result << endl;
	cout << "delete_prefix_result" << delete_prefix_result << endl;
	
	word = "anshi";
	obj->insert(word);
	delete_result = obj->trie_delete(word);
	cout << "delete_result" << delete_result << endl;
	
}
