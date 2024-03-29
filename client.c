/*
	Simple udp client modified from https://www.binarytides.com/programming-udp-sockets-c-linux/
*/
#include<stdio.h>	//printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#include <unistd.h> // close

// #define SERVER "127.0.0.1"
#define BUFLEN 2	//Max length of buffer
// #define PORT 8000	//The port on which to send data

/* Returns 1 if the operating system is Mac and 0 if it is not by using compile time macros. Note that 1 works like "true" in C. */
int isMacOS() {
#ifdef __APPLE__
    return 1;
#else
    return 0;
#endif
}

void die(char *s)
{
    perror(s);
    exit(1);
}

int main(int argc, char *argv [])
{
    if(argc != 3) {
        die("Wrong number of arguments. This program takes a port number and a local ip address.");
    }
    const int PORT = atoi(argv[1]);
    const char * SERVER = argv[2];
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);

    if (inet_aton(SERVER , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    // Turn on raw mode so that putchar doesn't require enter to be pressed to send. See https://stackoverflow.com/a/1799024
    system ("/bin/stty raw");

    printf("Everything you type is being sent to ip address %s . Note that the backspace key does nothing. Press \"@\" to send a beep sound which plays on Linux and Mac laptops. \n", SERVER);
    if( isMacOS() ) {
        printf("Note: the program has detected that your operating system is Mac and is making appropriate adjustments. \n");
    }
    while(1)
    {
        const int ch_integer = getchar();
        char ch = (char) ch_integer;
        message[0] = ch;
        //gets(message);
        // printf(". The ASCII code of the character you just typed is: %d . \n", ch_integer); // This is for debugging.

        if(ch == 3) {
            printf(". You pressed \"Ctrl+C\" which terminates the program. \n");
            close(s);
            exit(0);
        }

        if(ch != 8 && ch != 127) { // Only send if character is not backspace, characters 8 or 127.
            if(ch == '@') {
                printf(". You pressed the \"@\" symbol which sends a bell noise.");
                ch = 7; // Bell noise character
                message[0] = ch;
            }
            if(ch == 13) {
                printf(". You pressed the \"newline\" symbol which sends over the signal to make a new paragraph. ");
            }
            //send the message
            if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == -1) {
                die("sendto()");
            } else {
                // If it is not Mac, print the character that was sent over. Note that without this if statement around the putchar function, the character will appear in the terminal twice on Linux.
                if( isMacOS() ) {
                    putchar(message[0]);
                }
            }
        } else if(ch == 8 || ch == 127) {
            printf(". You pressed the \"backspace\" symbol which unfortunately doesn't work. Nothing was sent over. ");
        } else {
            die("Impossible condition has been executed. Exiting.");
        }

        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);

        /* Note: This client only needs to send data, it does not need to receive data.
        //try to receive some data, this is a blocking call
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }

        // puts(buf);
        // putchar(buf[0]);
        */
    }

    // close(s);
    // return 0;
}


/*
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
*/
