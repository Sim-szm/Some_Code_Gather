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
	unsigned int cur=0;
	int i=0;
	while(cur<this->non_end_flag.size()){
		int sig=1;i=0;
		while(i<content_length){
			if((this->content[i++][0])==(this->non_end_flag[cur])){
				sig=1;
				break;
			}
			sig=-1;
		}
		if(sig==-1){
			std::cout<<"非终结符"<<this->non_end_flag[cur]<<"未使用推导"<<std::endl;
			return false;
		}
		cur++;
	}
	del_left_recursion();i=0;
	while(i<content_length){
		int number=str_sub_num(this->content[i]);
		int flag=0;
		char ch=this->content[i][0];
		int m=0;//直接左递归个数
		for(int p=1;p<=number;p++){
			std::string tmp=get_N_sub_right(p,this->content[i],'|');
			if(ch==tmp[0]){
				flag=1;
				m++;
			}
		}
		if(m==number){
			std::cout<<"每个产生式都是左递归,error !"<<std::endl;
			return false;
		}
		if(flag)
		      del_direct_left_recursion(i);
		i++;
	}
	cur=0;
	while(cur<this->non_end_flag.size()){
		int sig=1;
		int k=0;
		while(k<this->content_length){
			if(this->content[k++][0]==this->non_end_flag[cur]){
				sig=1;
				break;
			}
			sig=-1;
		}	
		if(sig==-1){
			std::cout<<"非终结符"<<this->non_end_flag[cur]<<"未使用推导"<<std::endl;
			return false;
		}
		cur++;
	}
	return true;

}

std::string grammar_analysis::del_char(char ch,std::string src){
	for(unsigned int i=0;i<src.size();i++){
		if(src[i]==ch)
		      src.erase(i,1);
	}
	return src;
}

std::string grammar_analysis::del_repeated_ch(std::string& src){
	unsigned int i=0,j=0;
	for(; i<src.size();i++){
		for(j=i+1;j<src.size();j++){
			if(src[i]==src[j]){
				src.erase(j,1);
			}
		}
	}
	return src;
}

int grammar_analysis::search_char(char ch,std::string& src){
	unsigned int i=0;
	while(i<src.size()){
		if(src[i]==ch)
		      return i;
		i++;
	}
	return -1;
}

int grammar_analysis::str_sub_num(const std::string& src){
	int num=0;
	for(unsigned int i=3;i<src.size();i++){
		if(src[i]=='|')
		      num++;
	}
	return num+1;
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

