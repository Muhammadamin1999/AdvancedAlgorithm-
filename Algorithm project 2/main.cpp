
#include <iostream>
#include <vector>
#include <fstream>
#include "AVL.cpp"
#include "HashMap.cpp"
#include "Trie.cpp"
#include <chrono>
using namespace std;

void build_linearList_dic(vector<string>& list, vector<string>& my_dictionary);
void checkWords(vector<string>& list, vector <string>& my_words);
void lowerCaseString(string& str);

void build_bbst_dic(AVL<string, string>& bbst , vector<string>&  my_dictionary);
void checkWords(AVL<string, string>& bbst, vector<string>& my_words);

const int M = 355;
const int S = 356;

struct MyKeyHash {
    unsigned long operator()(const string& str) const
    {
         int h = 0, len = str.length();
	    for (int i = 0; i < len; i++)
	        h = ((h * S) % M + str[i]) % M;

    return h;
    }
};
void build_hmap_dic(HashMap<string, string, MyKeyHash>& hmap, vector<string>&  my_dictionary);
void checkWords(HashMap<string, string, MyKeyHash>& hmap, vector<string>&  my_words);

void build_trie_dic(Trie& trie, vector<string>&  my_dictionary);
void checkWords(Trie& trie, vector<string>& my_words);

vector<string> read_data(ifstream &fileStream);




int main()
{
    string filename;
    
    ifstream file("english_words.txt");
    vector <string> my_dictionary = read_data(file);
    
    string fileNames[11] = {"100.txt", "1000.txt", "2000.txt", "3000.txt", "4000.txt", "5000.txt", "6000.txt", "7000.txt", "8000.txt", "9000.txt", "10000.txt"};
    
	for(int i  = 0; i < 11; i++){
		
		cout << endl <<"FOR " << fileNames[i] << " " << endl;
		
		filename = fileNames[i];
		
		cout << "\n\n----------------------------Linear List---------------------------------\n\n";
	    vector<string> linear_List = my_dictionary;
	    auto start = chrono::steady_clock::now();
	    build_linearList_dic(linear_List, my_dictionary);
	    auto end = chrono::steady_clock::now();
	    cout << "Elapsed time for dictionary read: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
	    
	    
	    // words to check file
	    ifstream words_file(filename);
	    
	    vector <string> my_words = read_data(words_file);
	    
	    start = chrono::steady_clock::now();
		checkWords(linear_List, my_words);
		end = chrono::steady_clock::now();
		cout << "Elapsed time for words check: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
	    
	
	   	cout << "\n\n----------------------------BBST---------------------------------\n\n";
		AVL<string, string> bbst;
	    start = chrono::steady_clock::now();
	    build_bbst_dic(bbst,my_dictionary);
	    end = chrono::steady_clock::now();
	    
	    cout << "Elapsed time for dictionary read: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
	
	    start = chrono::steady_clock::now();
		checkWords(bbst, my_words);
		end = chrono::steady_clock::now();
		cout << "Elapsed time for words check: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
	    
	    cout << "\n\n----------------------------HashMap---------------------------------\n\n";
	    
		
		
		HashMap<string, string, MyKeyHash> hmap;
		start = chrono::steady_clock::now();
		build_hmap_dic(hmap, my_dictionary);
		end = chrono::steady_clock::now();
		cout << "Elapsed time for dictionary read: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
	    
		
	    start = chrono::steady_clock::now();
	    checkWords(hmap, my_words);
	    end = chrono::steady_clock::now();
	  	cout << "Elapsed time for words check: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
	
	    cout << "\n\n----------------------------Trie---------------------------------\n\n";
	    Trie trie;
	    start = chrono::steady_clock::now();
		build_trie_dic(trie, my_dictionary);
		end = chrono::steady_clock::now();
		cout << "Elapsed time for dictionary read: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
	
		start = chrono::steady_clock::now();
		checkWords(trie, my_words);
		end = chrono::steady_clock::now();
		cout << "Elapsed time for words check: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;
		
	}
    
   

    return 0;
}

vector<string> read_data(ifstream &fileStream){
    vector <string> dictionary;
    string word;
    
    while (fileStream >> word)
	{
 		dictionary.push_back(word);
 	}
 	return dictionary;
}

void build_linearList_dic(vector<string>& list, vector<string>& my_dictionary){
	for(string dword : my_dictionary){
		list.push_back(dword);
	}
}

void checkWords(vector<string>& list, vector<string>& my_words)
{
    bool found;

	for(string mword : my_words){
		
		found = false;
    	lowerCaseString(mword);

	    for (string wrd : list)
	    {
	        if (wrd.compare(mword) == 0)
	        {
	            found = true;
	            break;
	        }
	
	        
	    }
	    if (!found)
        {
            cout << mword << " not found!" << endl;

        }
		
	}
}

void lowerCaseString(string& str)
{
    char temp[100];
    int y = 0;
    for (int x=0; x < str.length(); x++)
    {
        if ((str[x] >= 'a' && str[x] <= 'z') || (str[x] >= 'A' && str[x] <= 'Z')) {
            temp[y] = tolower(str[x]);
            y++;
        }
    }
    temp[y] = '\0';

    str.assign(temp);
}

void build_bbst_dic(AVL<string, string>& bbst , vector<string>&  my_dictionary)
{
    
    for(string s : my_dictionary){
        bbst.insert(s, s);
    }
	
}

void checkWords(AVL<string, string>& bbst, vector<string>& my_words)
{

    bool found;
	
	 
    for(string mword : my_words){
    	found = false;
        lowerCaseString(mword);

        string* result = bbst.search(mword);

        if (result == nullptr)
        {
            cout << mword << " not found!" << endl;
        }
	}
        
}


void build_hmap_dic(HashMap<string, string, MyKeyHash>& hmap, vector<string>&  my_dictionary)
{
	for(string dicw : my_dictionary){
		hmap.put(dicw, dicw);
	}	
	
}

void checkWords(HashMap<string, string, MyKeyHash>& hmap, vector<string>&  my_words)
{	
	bool found;

	for(string mword : my_words){
		
		found = false;
    	lowerCaseString(mword);

	   
    	string value;
    	found = hmap.get(mword, value);
    	
        if (value.compare(mword) == 0)
        {
        	found = true;
        }
	        
	    
	    if (!found)
        {
            cout << mword << " not found!" << endl;

        }
	}
}
  	

void build_trie_dic(Trie& trie, vector<string>&  my_dictionary)
{

    for (string s : my_dictionary)
    {
        lowerCaseString(s);
        trie.insert(s);
    }
}

void checkWords(Trie& trie, vector<string>& my_words)
{
    
    bool found;

    for(string mword : my_words){
    	found = false;
        lowerCaseString(mword);

        if (!trie.search(mword))
        {
            cout << mword << " not found!" << endl;
        }
	}
        
    
}
