// ! edit me to change default behaviour

#if defined(WIN32)
    //// #include <windows.h> //for system("cls"); only     
    void clearScreen(){
        system("cls");
    }
    //powerline ( µ (char)230 cuz λ looks weird in windows default cmd ) 
    #define POWERLINE_DEFAULT ((char)230)  
    #define POWERLINE_IN_LOOP " : "
    
#elif defined(__linux__)
    void clearScreen(){
        // std::cout<<"\033[2j"; //?or 
        system("clear");
    }
    //powerline (λ inspired by garuda linux) 
    #define POWERLINE_DEFAULT "λ"
    #define POWERLINE_IN_LOOP " : "
    
#else
    void clearScreen(){
        std::cout<<"\n unsupported on this platform \n"; //?or system("clear");
    }

    //powerline (λ inspired by garuda linux) 
    #define POWERLINE_DEFAULT "λ"
    #define POWERLINE_IN_LOOP " : "
    
#endif


//todo: add some built in programs

#define APP_NAME "BF_Interpreter"
#define APP_VERSION "0.1 - alpha"


#define STACK_SIZE 500
// 30k is recommended by wikipedia but i think 500 is enough for most cases

//commands in interactive mode
#define COMMAND_PREFIX '@'
#define EXIT_COMMAND "@exit"
#define CLEAR_COMMAND "@clear"
#define RESET_COMMAND "@reset"
#define PRINT_CELL_USED_COMMAND "@cell_used"
#define PRINT_HELP_COMMAND "@help"
#define INIT_LOGGING_COMMAND "@init_log"
#define STOP_LOGGING_COMMAND "@stop_log"

#define DEFAULT_LOG_FILE_NAME "./bf_interpreter.interactive.log.bf"

// i defined stack overflow  xD 
#define STACK_OVERFLOW "ERROR :: YOUR PC EXPLODED BECAUSE STACK OVERFLOWED >_< "







// gems
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

const char inc_dat_ptr='>';
const char dec_dat_ptr='<';
const char inc_dat_val='+';
const char dec_dat_val='-';
const char print='.';
const char get_input=',';
const char loop_begin='[';
const char loop_end=']';

