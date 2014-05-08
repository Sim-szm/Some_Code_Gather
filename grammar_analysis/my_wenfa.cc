/*
 * =====================================================================================
 *
 *       Filename:  my_wenfa.cc
 *        Version:  1.0
 *        Created:  2014年05月08日 13时36分01秒
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
#include "my_wenfa.h"

int grammar_analysis::find_non_end_flag_id(char ch){
	for(int i=0;i<content_length;i++){
		if(content[i]==ch){
			return i;
		}
	}
	return -1;
}

bool grammar_analysis::check_correct(){

}

std::string grammar_analysis::del_char(char ch,std::string src){

}

std::string grammar_analysis::del_repeated_ch(std::string& src){

}

int grammar_analysis::search_char(char ch,std::string& src){

}

int grammar_analysis::str_sub_num(const std::string& src){

}


grammar_analysis::grammar_analysis(const grammar_analysis& src){
	end_flag=src.end_flag;
	non_end_flag=src.non_end_flag;
	end=src.end;
	content_length=src.content_length;
	content=new std::string[M];
	first_set=new std::string[M];
	follow_set=new std::string[M];
	predicted_table=new std::string* [M];
	for(int i=0;i<content_length;i++){
		content[i]=src.content[i];
	}
	store_first_and_follow();
	create_analysis_table();
	
}

grammar_analysis& grammar_analysis::operator=(const grammar_analysis& src){
	end_flag=src.end_flag;
	non_end_flag=src.non_end_flag;
	end=src.end;
	content_length=src.content_length;
	content=new std::string[M];
	first_set=new std::string[M];
	follow_set=new std::string[M];
	predicted_table=new std::string* [M];
	for(int i=0;i<content_length;i++){
		content[i]=src.content[i];
	}
	store_first_and_follow();
	create_analysis_table();
	return *this;
}

grammar_analysis& grammar_analysis::push_stack(const std::string& src){

}

bool grammar_analysis::next(char ch,char cur){

}

char grammar_analysis::pop_stack(){

}

char grammar_analysis::get_top_of_analysis_stack(){

}

char grammar_analysis::get_current_of_input_stack(){

}

bool grammar_analysis::final_print(){

}

std::string grammar_analysis::get_first_set(char ch){

}

std::string grammar_analysis::get_str_first_set(const std::string& src){

}

std::string grammar_analysis::get_follow_set(char ch){

}

std::string grammar_analysis::get_N_sub_right(int cur,const std::string& src,char ch){

}

grammar_analysis& grammar_analysis::del_direct_left_recursion(int cur){

}

grammar_analysis& grammar_analysis::del_left_recursion(){

}

grammar_analysis& grammar_analysis::store_first_and_follow(){

}

grammar_analysis& grammar_analysis::create_analysis_table(){

}

