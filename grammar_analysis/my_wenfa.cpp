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
#include "my_wenfa.h"

int grammar_analysis::find_non_end_flag_id(char ch){
	for(int i=0;i<content_length;i++){
		if(content[i][0]==ch){
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

int grammar_analysis::search_char(char ch,std::string src){
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
	if(src.empty())
	      return *this;
	std::string tmp=src;
	tmp.replace(tmp.begin(),tmp.end(),tmp.rbegin(),tmp.rend());
	analysis_stack.append(tmp);
	return *this;
}

bool grammar_analysis::next(char ch,char cur){
	if(search_char(ch,end_flag)!=-1){
		if(ch==cur){
			pop_stack();
			input_stack.erase(0,1);
			return true;
		}else{
			return false;
		}
	}
	return false;
}

char grammar_analysis::pop_stack(){
	char ch=this->analysis_stack[this->analysis_stack.size()-1];
	this->analysis_stack.erase(this->analysis_stack.size()-1,1);
	return ch;
}

char grammar_analysis::get_top_of_analysis_stack(){
	return this->analysis_stack[this->analysis_stack.size()-1];
}

char grammar_analysis::get_current_of_input_stack(){
	return this->input_stack[0];
}

bool grammar_analysis::final_print(){

}

std::string grammar_analysis::get_first_set(char ch){
	std::string x="";
	if(search_char(ch,this->end_flag)!=-1){
		x.append(1,ch);  //x as a end_flag !
	}
	else if(search_char(ch,this->non_end_flag)!=-1){
		int i=find_non_end_flag_id(ch);
		if(i!=-1){
			std::string wp=this->content[i];
			unsigned int k=3;
			while(k<wp.size()){
				if(wp[k-1]=='|' || k==3){
					if(search_char(wp[k],this->end_flag)!=-1||wp[k]=='^'){
						x.append(1,wp[k]);
					}else{
						if(k==3 || wp[k+1]=='|' || k==wp.size()-1){
							x+=get_first_set(wp[k]);
						}else{
							std::string tmp=get_first_set(wp[k-1]);
							if(search_char('^',tmp)!=-1){
								x+=get_first_set(wp[k]);
							}
						}
					}
					k++;
				}else{
					k++;
				}
			}
		}
	}
	return x;
}

std::string grammar_analysis::get_first_set(const std::string& src){
	return get_first_set(src[0]);
}

std::string grammar_analysis::get_follow_set(char ch){
	std::string x;
	if(search_char(ch,non_end_flag)!=-1){
		if(!find_non_end_flag_id(ch))
		      x+="@";
		int i=0;
		while(i<content_length){
			std::string wp=content[i];
			unsigned int k=3;
			char cgr=content[i][0];
			while(k<wp.size()){
				while(wp[k]==k){
					if(k<wp.size()-1 && wp[k+1]!='|'){
						std::string tmp=del_char('^',get_first_set(wp[k+1]));
						if(x.find(tmp)==std::string::npos){
							x+=tmp;
						}
						if(search_char('^',get_first_set(wp[k+1]))!=-1){
							if(x!=get_follow_set(cgr))
							      x+=get_follow_set(cgr);
						}
					}else if(k==wp.size()-1){
						if(x.find(get_follow_set(cgr))==std::string::npos){
							x+=get_follow_set(cgr);
						}
					}
					k++;
				}
				k++;
			}
			i++;
		}
	}
	x=del_repeated_ch(x);
	return del_repeated_ch(x);
}

std::string grammar_analysis::get_N_sub_right(int cur,const std::string& src,char ch='|'){
	std::string x;
	int flag[M];
	int len=1;
	if(cur>int(src.size()))
	      return x;
	for(unsigned int k=3;k<src.size();k++){
		if(src[k]==ch){
			flag[len++]=k;
		}
	}
	for(unsigned int k=flag[cur-1]+1;k<src.size();k++){
		if(src[k]==ch)
		      break;
		else
		      x.append(1,src[k]);
	}
	x=del_repeated_ch(x);
	return del_repeated_ch(x);
}

grammar_analysis& grammar_analysis::del_direct_left_recursion(int cur){
		int n=str_sub_num(content[cur]);
		char ch=random_char();
		char l_end=content[cur][0];
		int sig=0;
		for(int k=1;k<=n;k++){
			std::string tmp=get_N_sub_right(k,content[cur],'|');
			if(l_end==tmp[0])
			      sig=1;
			if(del_char(l_end,tmp).empty()){
				std::cout<<"无穷推导"<<std::endl;
				exit(0);
			}
		}
		if(sig==0)
		      return *this;
		std::cout<<"direct recursion "<<std::endl;
		if(non_end_flag.size()>=26){
			exit(0);
		}
		while(true){
			if(search_char(ch,non_end_flag)==-1)
			      break;
			else
			      ch=random_char();
		}
		non_end_flag.append(1,ch);
		std::string tmp,next;
		tmp+=l_end;tmp+="->";
		next+=ch;next+="->";
		for(int k=1;k<=n;k++){
			std::string t=get_N_sub_right(k,content[cur],'|');
			if(l_end==t[0]){
				t.erase(0,1);t+=ch;
				next+=t;next+='|';
			}else{
				if(t=="^") t.clear();
				t+=ch;
				tmp+=t;tmp+='|';

			}
		}
		next+='^';
		tmp.erase(tmp.size()-1,1);
		content[cur]=tmp;
		content_length+=1;
		content[content_length]=end;
		//insert
		for(int j=content_length-1;j>cur;j--){
			content[j]=content[j-1];
		}
		content[cur+1]=next;
		return *this;
}

grammar_analysis& grammar_analysis::del_left_recursion(){
	for(unsigned int i=1;i<non_end_flag.size();i++){
		for(unsigned int j=0;j<i;j++){
			char A_i=content[i][0];//get Ai
			char A_j=content[j][0];//get Aj
			std::string Ai_str=content[i];
			int A_i_n=str_sub_num(Ai_str); //Ai sub_num
			std::string update; //recond update
			update+=A_i;
			update+="->";
			for(int k=1;k<A_i_n;k++){
				std::string tmp=get_N_sub_right(k,Ai_str,'|');
				std::string Ai_t; // new sub
				if(tmp[0]==A_j){  //Ai->Aj
					std::string Aj_str=content[j];
					int A_j_n=str_sub_num(Aj_str);
					for(int p=1;p<=A_i_n;p++){
						std::string j_tmp=get_N_sub_right(p,Aj_str,'|');
						std::string i_tmp=tmp;
						tmp.replace(0,1,j_tmp);
						Ai_t+=i_tmp;
						Ai_t+='|';
					}
					Ai_t.erase(Ai_t.size()-1,1);//last '|'
				}
				else
				      Ai_t=tmp;
				update+=Ai_t;
				update+='|';
			}
			update.erase(update.size()-1,1);
			content[i]=update;
		}
	}
	return *this;
}

grammar_analysis& grammar_analysis::store_first_and_follow(){
	unsigned int i=0;
	while(i<non_end_flag.size()){
		first_set[i]=get_first_set(non_end_flag[i]);
		follow_set[i]=get_follow_set(non_end_flag[i]);
		i++;
	}
	return *this;
}

grammar_analysis& grammar_analysis::create_analysis_table(){
	for(unsigned int i=0;i<this->non_end_flag.size();i++){
		predicted_table[i]=new std::string[M];
	}
	for(unsigned int i=0;i<this->non_end_flag.size();i++){
		std::string tmp=content[i];
		int m=search_char(tmp[0],this->non_end_flag);
		int n=str_sub_num(tmp);
		for(int k=1;k<=n;k++){
			std::string tmp_s=get_N_sub_right(k,tmp);
			std::string first_t=get_first_set(tmp_s);//right part sub_set
			for(unsigned int j=0;j<first_t.size();j++){
				int pos=search_char(first_t[j],end_flag);
				if(pos!=-1){
					predicted_table[m][pos]=tmp_s;
				}
			}

			if(search_char('^',first_t)!=-1 || tmp_s[0]=='^'){
				std::string follow_t=get_follow_set(tmp[0]);
				for(unsigned int j=0;j<follow_t.size();j++){
					int po_t=search_char(follow_t[j],end_flag);
					if(po_t==-1)
					      po_t=(int)(this->end_flag.size());
					predicted_table[m][po_t]=tmp_s;

				}
			}
		}
	}
	return *this;
}
int main(int argc,char *argv[]){
	//.....
	return 0;
}
