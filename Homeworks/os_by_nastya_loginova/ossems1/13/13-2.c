#include <signal.h>

int main(void){

    (void)signal(SIGINT, SIG_IGN);
    (void)signal(SIGQUIT, SIG_IGN);
    while(1);
    return 0;

}