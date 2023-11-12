# Sharingan
## A Linux Keylogger Malware

<p align="center">
 <img src="https://external-content.duckduckgo.com/iu/?u=https%3A%2F%2Fthumbs.gfycat.com%2FNiceRequiredGrunion-size_restricted.gif&f=1&nofb=1&ipt=17c223d47e58a2fdfa49fc2a3b7a351be620f0081dc3b0ab7de98abfd90e55df&ipo=images">
 
</p>

<p align="center">I do not own this content.  All credits go to its rightful owner</p>


## Disclaimer
Don't use this for malicious purposes use it to educate yourself and learn more about the world of computers.  If you do though use it for malicious intent I hold no responsiblity for your actions be warned cyber crime is really serious and can  land you behind bars for a while.

## Project Overview and Purpose
I'm really interested in the idea of becoming a red teamer, that will be creating and employing various TTPs.  On that journey I wanted to get my hands dirty actually developing tools and this is the first beginner project meant to give me experience working with C and also interfacing with the linux kernel and devices.  I'd say this was a very informative experience and have compiled a list of key concepts I've learned along the way ...

    1. In Linux keystrokes are identifiable through the use of event files 
    2. How to use and create Makefiles
    3. How to use and create my own systemd service
    4. Developing with C/C++ using multiple files

This particular keylogger will track files after conducting keyboard detection and will attempt to communicate with an external server which you can setup within the main code before compilation.  There will also be a local log file where the files will be written to. Do note that this will be located in the /tmp directory so it will be removed upon restart.

I hope to continue on this journey and continue to make more tools and I hope you all will enjoy the journey along the way with me.  As a great man once said

"The most important step is the next one. Always the next one." - Dhalinar Kholin From the Stormlight Archive Series

## Installation Instructions

### Prequisites

Before downloading and attempting to install this program you need to make sure you are...

    1. deploying it on a linux based operating system
    2. that you have the gcc compiler installed
    3. finally that the make utility is also installed
    4. if you plan on cloning the repo you will also want to have git installed

Most linux systems ship with gcc by default and you can verify it with the command 

```
gcc -version
```

If not installed you can install both gcc and make via your distros package manager fairly easily.

### Installation

Moving on to the actual installation process you'll want to start off by cloning this repository or downloading it. You can clone the repo with the command 
```
git clone https://github.com/sKannanaikal/sharingan.git
```

Once installed you will want to change to the directory and simply run the make command from there the installation process will occur and you will have the keylogger up and running.
```
cd sharingan && make
```

Before you start this program you will want to setup a Server for the keylogger to communicate with you can create on the fly with netcat just run the command on your own computer and this will open a listening server on port 80 on all interfaces on your system and redirect all output to the file labelled keystrokes.
```
nc -lvp 80 > keystrokes
```

However given that this utility has a network communication component to it you will likely have to edit it for use you can do this by entering the main.c file and changing the value of SERVER and PORT on lines 37 and 38 respectively in the main.c file before running the make command.


## Issues and Disadvantages
These are some issues I'm aware of and hope to rework later on...

    1. Does not support multiple keyboards typing at once
    2. Is not exactly discrete
    3. Requires root privs (unfortunately keyloggers in linux requqire root privlieges at minimum given how the operating system is set up as far as I know)

## Closing Thoughts
I would really appreciate any helpful tips on improving this and your thoughts on the program.
