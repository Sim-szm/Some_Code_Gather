#include <iostream>      
#include <string.h>   
#include <stdlib.h>
#define WORD_MAX 256
using namespace std;   
const int num_chars = 26;   
class Trie {   
public:   
     Trie();   
     Trie(Trie& tr);   
	 ~Trie(  );
     int trie_search(const char* word, char* entry );   
     int insert(const char* word, const char* entry);     
protected:   
     struct Trie_node   
     {   
         char* data;   
           Trie_node* branch[num_chars];   
           Trie_node();   
     };   
        
       Trie_node* root;   
};   
Trie::~Trie(  ){

}
Trie::Trie_node::Trie_node()    
{   
      data = NULL;   
    for (int i=0; i<num_chars; ++i)    
          branch[i] = NULL;   
}   
Trie::Trie( ):root(NULL)   {}
int Trie::trie_search(const char* word, char* entry )     
{   
    int position = 0;   
    char char_code;   
      Trie_node *location = root;   
    while( location!=NULL && *word!=0 )    
    {   
        if (*word>='A' && *word<='Z')    
              char_code = *word-'A';   
        else if (*word>='a' && *word<='z')    
              char_code = *word-'a';   
        else return 0;   
          location = location->branch[char_code];   
          position++;   
          word++;   
    }   
    if ( location != NULL && location->data != NULL )    
   {   
        strcpy(entry,location->data);   
        return 1;   
    }   
    else return 0;   
}   
int Trie::insert(const char* word, const char* entry)    
{   
    int result = 1, position = 0;   
    char char_code;
    if ( root == NULL ) 
	  root = new Trie_node;    

      Trie_node *location = root;   

    while( location!=NULL && *word!=0 )   
    {   
        if (*word>='A' && *word<='Z')    
              char_code = *word-'A';   
        else if (*word>='a' && *word<='z')    
              char_code = *word-'a';   
        else
		  return 0;   

        if( location->branch[char_code] == NULL )    
              location->branch[char_code] = new Trie_node;   

          location = location->branch[char_code];   
          position++;   
          word++;   
    } 

    if (location->data != NULL)   
          result = 0;

    else {   
          location->data = new char[strlen(entry)+1];   
        strcpy(location->data, entry);   
    }

    return result;   
}   

int main()   
{   
      Trie t;   
	  int flag=1;
	  char *word;
      char entry[WORD_MAX]; 
	 // char text_line[WORD_MAX];

      t.insert("lucky", "幸运");    
      t.insert("love","爱情");   
      t.insert("fanstic","奇妙的");    
      t.insert("abandon","沉沦");   
      t.insert("like","喜欢");    
      t.insert("snake","蛇");   
      t.insert("sacrifice","祭奠");    
      t.insert("this", "这个"); 
	  cout<<"please input which word to fing :\n( if you want to stop serach input : $ ) "<<endl;
	  cin>>word;
	  while(flag) {
		  if( strncmp( word,"$",1 ) ==0){
			  cout<<"game over !"<<endl;
			  flag=0;
			   break;
		}

        if (t.trie_search(word, entry)) {

			cout<<"<"<<word<<">"<<" was found. meaning: "<<entry<<endl;   
	    } else {
		cout<<"this word not find\n";
		}
		cout<<"please input which word to fing : "<<endl;
		cin>>word;
	  }
	  cout<<"**********************************"<<endl;
    return ( 0 );
}  

