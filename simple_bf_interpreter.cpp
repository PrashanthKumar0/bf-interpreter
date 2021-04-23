//very simplified version of bf_interpreter
#include <iostream>
#include <fstream>
#include <vector> 
//? vector maybe slow 
//  todo: make my own vector 
//! run with exe ./file

#define TAPE_SIZE 300

std::vector<int> stack;

char* TAPE=new char[TAPE_SIZE];
int dp=0;

// std::ofstream of;

const char inc_dat_ptr='>';
const char dec_dat_ptr='<';
const char inc_dat_val='+';
const char dec_dat_val='-';
const char print='.';
const char get_input=',';
const char loop_begin='[';
const char loop_end=']';

// w/o loop
void execute_instruction(const char ch){
    if (ch==inc_dat_ptr) {
        dp++;
        return;
    }
    if (ch==dec_dat_ptr) {
        dp--;
        return;
    }
    if (ch==inc_dat_val) {
        TAPE[dp]+=1;
        return;
    }
    if (ch==dec_dat_val) {
        TAPE[dp]-=1;
        return;
    }
    if (ch==print) {
        std::cout<<TAPE[dp];
        // of<<TAPE[dp];
        return;
    }
    if (ch==get_input) {
        std::cin >> TAPE[dp];
        return;
    }
}

void executeString(std::string& code){
    int code_len=code.size();
    for(int i=0;i<code_len;i++){
        if(code[i]==loop_begin){
            if(TAPE[dp]==0){
                int bal=0;
                int j=i+1;
                for(;j<code_len;j++){
                    if(code[j]==loop_end)    bal++;
                    if(code[j]==loop_begin)    bal--;
                    if(bal==1) break;
                }
                if (j==code_len-1) {
                    std::cerr << " Syntax error on index "<<i; 
                    return;
                }
                i=j;
                continue;
            }
            stack.push_back(i);
            continue;
        }
        if(code[i]==loop_end){
            if(TAPE[dp]!=0){ //if its !0
                i=stack[stack.size()-1];
                continue;
            }
            if(stack.size()) stack.pop_back();
            continue; //or i++?
        }
        execute_instruction(code[i]);
    }
    
}

void executeFile(char* fileName){
    std::ifstream file;
    file.open(fileName);
    // of.open((std::string(fileName)+".out").c_str());
    if(!file){
        std::cerr <<  "ERROR :: FILE < " << fileName << " > NOT FOUND !"<<'\n';
        return;
    }    
    std::string code;
    int valid_brackets=1;
    while(file){
        std::string line;
        std::getline(file,line);
        code+=line;
    }
    file.close();
    std::cout<<"\n\n"<<code<<"\n\n";
    executeString(code);
}

int main(int argc,char** argv){
    if(argc<1) {
        std::cerr<< " Error :: no input file provided ";
        delete [] TAPE;
        // of.close();
        return 1;
    }
    for(int i=0;i<TAPE_SIZE;i++){
        TAPE[i]=0;
    }
    executeFile(*(argv+1));
    // of.close();
    delete [] TAPE;
}