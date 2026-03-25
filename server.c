#include <signal.h>
#include <stdio.h>
#include <unistd.h>


void handler (int signum){
    
    unsigned static int len = 0;
    static int bit_len = 35;
    
    static char c = 0;
    static int bit = 0;

    // if (bit_len < 32){
    //     if (signum == SIGUSR1){
    //         len = len << 1;
    //         len++;
    //         bit_len++;
    //     }
    
    //     else if(signum == SIGUSR2){
    //     len = len << 1;
    //     bit_len++;
    // }
    // }

    // if (bit_len == 32){
    //     printf("len = %d et bit_Len = %d\n", len, bit_len);


    // }
    if (bit_len >= 32){
        if (signum == SIGUSR1)
        {
            c = c << 1;
            c++;
            bit++;
        }
        else if (signum == SIGUSR2)
        {
            c = c << 1;
            bit++;
        }
        
        if (bit == 8)
        {
            printf ("%c\n", c);
            c = 0;
            bit = 0;
        }
    }
}

int main (){

    int pid = getpid();
    struct sigaction sa;

    sa.sa_handler = handler;
    sa.sa_flags = SA_SIGINFO;
    
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
    
    printf("PID : %d\n", pid);
    
    while(1){
        pause();
    } 

    

}