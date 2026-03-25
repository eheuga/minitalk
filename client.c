#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char* str){
    int i = 0;

    while (str[i])
        i++;

    return (i);
}

int main (int ac, char **av){

    int i = 0;
    int j;
    unsigned int mask;
    if (ac != 3){
        return (0);
    }
    
    // int len = ft_strlen(av[2]);

    // mask = 1 << 31;
    // while (mask){

    //     sleep(3);
    //     if ((len & mask) == mask)
    //         kill(atoi(av[1]), SIGUSR1);
    //     else
    //         kill(atoi(av[1]), SIGUSR2);

    //     mask = mask >> 1;
    // }

    usleep(100);
    unsigned char c = av[2][0];
    while (av[2][i]){
        
        j = 0;
        mask = 128;
        while (j < 8)
        {
                usleep(100 );
                if ((av[2][i] & mask) == mask)
                    kill(atoi(av[1]), SIGUSR1);
                else
                    kill(atoi(av[1]), SIGUSR2);
            
                // printf("mask = %d\n", mask);
                // printf("c = %d\n", c);
                mask = mask >> 1;    
                j++;
            }
        
        i++;
    }

}