/*
 * =====================================================================================
 *
 *       Filename:  my_wenfa.h
 *        Version:  1.0
 *        Created:  2014年05月08日 11时44分34秒
 *       Revision:  none
 *       Compiler:  clang
 *         Author:  sim szm, xianszm007@gmail.com
 *        Company:  Class 1107 of Computer Science and Technology
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#define M 255

class grammar_analysis{
public:
	grammar_analysis(){
		content= new std::string[M];
		first_set=new std::string[M];
		follow_set=new std::string[M];
		predicted_table=new std::string* [M];
	}
	~grammar_analysis(){
		delete [] content;
		delete [] first_set;
		delete [] follow_set;
		delete [] predicted_table;
	}

	grammar_analysis& push_stack(const std::string&);
	bool next(char,char);
	char pop_stack();
	char get_top_of_analysis_stack();
	char get_current_of_input_stack();
	bool final_print();

	std::string get_first_set(char );
	std::string get_first_set(const std::string& );//str
	std::string get_follow_set(char );
	std::string get_N_sub_right(int cur,const std::string& ,char ch);

	grammar_analysis& del_direct_left_recursion(int cur);
	grammar_analysis& del_left_recursion();

	grammar_analysis& store_first_and_follow();
	grammar_analysis& create_analysis_table();

	int find_non_end_flag_id(char ch);
	bool check_correct();
	std::string del_repeated_ch(std::string& );
	std::string del_char(char ch, std::string src);
	int search_char(char ch,std::string );
	int str_sub_num(const std::string&);
	char random_char(){
		return rand()%25+'A';
	}
private:
	std::string analysis_stack;
	std::string input_stack;

	int content_length;
	std::string end_flag;
	std::string non_end_flag;
	std::string *content;
	std::string end;
	std::string *first_set;
	std::string *follow_set;
	std::string **predicted_table;
public:
	friend std::ostream& operator<<(std::ostream& output ,grammar_analysis& dest);
	friend std::istream& operator>>(std::istream& input ,grammar_analysis& source);
	grammar_analysis(const grammar_analysis&);
	grammar_analysis& operator =(const grammar_analysis& );
};


