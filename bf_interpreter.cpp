/**
    COMMANDS for bf language

    > increment data pointer
    < decrement data pointer
    + increment the byte at data pointer
    - decrement the byte at data pointer
    . output(print) byte at data pointer
    , accept one byte of input
    [ if byte at data pointer is 0 , then instead of moving data pointer forward , jump till find ]
    ] if byte at data pointer is non zero then instead of moving forward jump to previous ]

    //anything except these are comments
    in my code implementation even extra ] is comment ;)
*/

#include <iostream> 
#include <fstream>

// edit config.h for getting custom configurations
#include "config.h"

int max_cell_reached=0; //this will hold info abut num of cell occupied 
int data_pointer=0;
char* stack=new char[STACK_SIZE];  //actually people caal it tape but i prefer to call stack




void interactiveModeHelp(){
        std::cout<< "\n\t\t Interactive mode COMMANDS \n "
                << "\t\t === === === === === \n"
                <<"type : \n"
                <<"     "<<EXIT_COMMAND<<" to exit \n\n"
                <<"     "<<CLEAR_COMMAND<<" clears the screen \n\n"
                <<"     "<<RESET_COMMAND<<" resets all cells and move data ptr to 0 \n\n"
                <<"     "<<PRINT_CELL_USED_COMMAND<<" prints number of cells used till now \n\n"
                <<"     "<<INIT_LOGGING_COMMAND <<" [fileName.bf] (without []) logs the commands you enter into filename.bf \n\n"
                <<"     "<<STOP_LOGGING_COMMAND<<" stops logging in file \n\n"
                <<"     "<<PRINT_HELP_COMMAND<<" prints this help info \n\n";
}


void printHelpScreen(){
    std::cout   << "\n\t\t\t*** Welcome to "<<APP_NAME << " VER : "<<APP_VERSION << " ***\n\n"
                << APP_NAME << " built on "  <<__DATE__ << " at " << __TIME__ <<"\n\n"
                << 
                R"HERE(     [USAGE] :
                    -help          : for this menu
                    -v             : for version
                    -f <filename>  : for interpreting a file
                    -i             : for running in interactive mode 
                )HERE"
                << "\n\n";
}

int executeString(std::string& code,int from=0,int firstTime=1){
    //todo: see how can we make it working without firstTime argument 
    int code_len=code.size();
    for(int i=from;i<code_len;i++){
        char instruction=code[i];
        //>
        if(instruction==inc_dat_ptr){
            
            data_pointer++;
            if(data_pointer>max_cell_reached){
                max_cell_reached=data_pointer;
            }

            if(data_pointer>=STACK_SIZE) {
                std::cout << STACK_OVERFLOW << " at index " << i << " data pointer index : "<< data_pointer<< '\n';
                return i;
            }
            continue;
        }
        // <
        if(instruction==dec_dat_ptr){
            data_pointer--;
            if(data_pointer<0){
                std::cout << STACK_OVERFLOW << " But this time in reverse "<<data_pointer<<" index *_*  at index " << i << "\n";
                return i;
            }
            continue;
        }
        //+
        if(instruction==inc_dat_val){
            stack[data_pointer]++;
            continue;
        }
        //-
        if(instruction==dec_dat_val){
            stack[data_pointer]--;
            continue;
        }
        // [
        if(instruction==loop_begin){
            
            
            int ending=0;
            if(stack[data_pointer]==0){
                int bal=0;
                for(ending=i+1;ending<code_len;ending++){
                
                    if(code[ending]==loop_begin)  bal--;
                    if(code[ending]==loop_end) bal++;
                    if(bal==1){    
                        i=ending;
                        break;
                    }
                }
                if (i==code_len-1) return code_len;
                continue;
            }

            while(stack[data_pointer]){
                //the below line resolves a problem of setting the cursor at the end of ***[***]***
                ending=executeString(code,i+1,0); //(recurse) this will help if its in nested loop
            }
            i=ending;
            continue;
        }
        //]
        if(instruction==loop_end){
	    if(!firstTime) {
                return i;
	    }
	    std::cerr<<"ERROR: unexpected ']' at position " << i << std::endl;
	    exit(101);
        }

        //.
        if(instruction==print){
                std::cout<<(char)(stack[data_pointer]); 
            continue;
        }
        //,
        if(instruction==get_input){
            char c;
            std::cin >>c;
            stack[data_pointer]=c;
            continue;
        }
    }
    return code_len;
}

void executeFile(std::string fileName){
    std::ifstream file;
    file.open(fileName);
    if(!file){
        std::cout <<  " FILE " << fileName << " NOT FOUND !"<<'\n';
        return;
    }
    
    std::string code;
    while(file){
        std::string line;
        std::getline(file,line);
        code+=line;
    }
    
    executeString(code);
}

void runInteractiveMode(){
    //info
    std::cout   << "\n\t\t\t*** Welcome to "<<APP_NAME << " VER : "<<APP_VERSION << " ***\n\n"
                << APP_NAME << " built on "  <<__DATE__ << " at " << __TIME__ <<"\n\n";
  
    interactiveModeHelp();
  
    std::string code; //this holds code which is going to be in the loop
    int bal=0; //for checking if loops are balanced
    std::string file_path;        
    bool log_in_file=0;
        
    while(1){  //repl
        std::string current_line;
        
        //!powerline
        if(bal==0){
            //if not in loop
            std::cout<<" "<<POWERLINE_DEFAULT<<" ";  
        }else {
            //if in loop
            std::cout<<POWERLINE_IN_LOOP <<"   "<<std::string("  ",(bal<0?0:bal)); //to give nice indentation
        }
 
        getline(std::cin,current_line);
        int line_len=current_line.size();
        
        //!commands execution part

        std::string command;
        for(int i=0;i<line_len;i++){
            if(current_line[i]==COMMAND_PREFIX){
                int sep=i; //seperation between command and argument (for file_path)
                for(sep=i;sep<line_len;sep++){
                    if(current_line[sep]==' ') break;
                }
                command=current_line.substr(i,sep);
                if(sep+1<line_len){
                    file_path=current_line.substr(sep+1,line_len); //not checking for second space because filename may contain spaces
                    break;
                }
                if(command==INIT_LOGGING_COMMAND){ //if no filename is provided use default name
                    file_path=DEFAULT_LOG_FILE_NAME;
                }
            }
        }
        if(command==EXIT_COMMAND)  break;
        if(command==CLEAR_COMMAND) clearScreen();
        if(command==RESET_COMMAND){
            for(int i=0;i<max_cell_reached;i++){
                stack[i]=0;
            }
            std::cout<<"\ncells reset done! \n";
            data_pointer=0;
            max_cell_reached=0;
        }
        if(command==PRINT_CELL_USED_COMMAND)   std::cout<<'\n'<<max_cell_reached<<" cells are used till now\n";
        if(command==PRINT_HELP_COMMAND)   interactiveModeHelp();
        if(command==INIT_LOGGING_COMMAND)   log_in_file=1;
        if(command==STOP_LOGGING_COMMAND)   log_in_file=0;

        //!code interpreter part
        for(int i=0;i<line_len;i++){
            char ch=current_line[i];
            code+=ch;
            if(ch==loop_begin){
                bal++;
                continue;
            }
            if (bal==0) continue; // extra ] is just comment in this interpreter (its not any syntax error)
            if(ch==loop_end){ 
                bal--;
            }
        }
        if(bal==0){  //execute only if loop is balanced                         
            if(log_in_file){
                std::ofstream out_file;
                out_file.open(file_path,std::ios::app);
                out_file<<code<<'\n';
                out_file.close();
            }
            executeString(code);
            code=""; //reset the code
        }
    }
    
    std::cout<<"\n\nExiting " << APP_NAME <<" ... \n\n";
}

int main(int argc,char** argv){
    
    for(int i=0;i<STACK_SIZE;i++){
        stack[i]=0;
    }

    bool fileMode=false;
    for(int i=1;i<argc;i++){
        std::string arg =*(argv+i);
        if(arg=="-h"){
            printHelpScreen();
            delete[] stack;
            return 0;
        }
        if(arg=="-v"){
            std::cout << APP_NAME << " VER: " << APP_VERSION << '\n';
            delete[] stack;
            return 0;
        }
        if(arg=="-f" || fileMode){
            if(fileMode){
                executeFile(*(argv+i));
                std::cout << "\n\nexiting program...\n\n";
                delete[] stack;
                return 0;
            }
            //for first run set it true so that next run takes input as file name
            fileMode=true;
        }
        if(arg=="-i"){
            runInteractiveMode();
            delete[] stack;
            return 0;
        }
    }
    
    printHelpScreen();

    delete[] stack;
    return 0;
}