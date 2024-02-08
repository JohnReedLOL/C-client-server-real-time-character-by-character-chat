/*
	Simple udp server modified from https://www.binarytides.com/programming-udp-sockets-c-linux/
*/
#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <stdbool.h> // bool
#include <unistd.h> // close

#define BUFLEN 2	//Max length of buffer
// #define PORT 8000	//The port on which to listen for incoming data

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv [])
{
    if(argc != 2) {
        die("Wrong number of arguments. This program takes a port number.");
    }
    const int PORT = atoi(argv[1]);
    struct sockaddr_in si_me, si_other;

    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[BUFLEN];

    //create a UDP socket
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }

    printf("Waiting to receive typed characters from another computer... \n");
    bool flag = false;
    //keep listening for data
    while(1)
    {
        fflush(stdout);

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }

        //print details of the client/peer and the data received, but only do it once, if flag is false.
        if(flag == false) {
            printf("Received character from ip address %s . \n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
            flag = true;
        }
        const char input_char = buf[0];
        // const int input_char_as_int = input_char;
        // printf("ASCII code of packet is: %d \n", input_char_as_int);
	if(input_char == 13) {
            putchar('\n');
	} else {
            putchar(input_char);
	}
        if(input_char == 7) {
            printf(" *beep* ");
        }
        //printf("Data: %s\n" , buf);

        /*
         * No need to send back a reply.
        //now reply the client with the same data
        if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        */
    }

    close(s);
    return 0;
}


/*
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
*/
