# C client server real time character-by-character chat
This terminal chat app differs from the usual chat apps in that it allows the other person to see what you are typing as you type it, in real time, rather than after you hit **enter**. It works on Mac, Linux like Ubuntu Linux, and also in the Termux terminal on Android which you can download from the F-Droid open source app store. This terminal app does not work on Window or iPhone by default, although if you are tech-savvy you may be able to figure out a way, for example by using [a-Shell](https://apps.apple.com/us/app/a-shell/id1473805438?platform=iphone) on iPhone. This terminal app has a customization that makes it play a bell noise in the terminal when you hit the "@" character, but the bell noice doesn't play on Android in the Termux terminal. The other person is supposed to type when they hear the bell. Also, if you hit "#" it makes a newline on their end for new paragraphs. To make the C code take each character as it is typed rather than after the user hits **enter** I had to turn on raw mode as described in [this StackOverflow question](https://stackoverflow.com/a/1799024), which causes the Ctrl+C command for terminating the process not work, so you have to close the whole terminal that the client runs on if you want to kill the client. The code is written in 2017 compliant C, C17, and is based off https://www.binarytides.com/programming-udp-sockets-c-linux/ . I compile the code with the gcc compiler.

### Usage:

The server takes a port number to listen on. First compile and run the server in the terminal like so:

```bash
$ gcc server.c -o server
$ ./server 8000
```

The client takes a port number, the port number of the server, and the ip address of the server. Compile and run the client in the terminal like so:

```bash
$ gcc client.c -o client
$ ./client 8000 127.0.0.1
```

In the above example, I used the localhost IP address 127.0.0.1 but you can use any reachable IP address that the server runs on. If the client and server are on the same Wi-Fi network they can connect with each other using a local IP address, which usually starts with "192.168" on home Wi-Fi networks. You can use the included bash script *get_local_ip.sh* to get your local IP address. Note that this real time chat uses UDP sockets instead of TCP sockets so if there are dropped packets they will not be resent. This app is optimized for latency and UDP has less lag than TCP. Note that each device has to run both a client and a server because text only goes in one direction, from the client to the server, so you need both to send text in both directions.
