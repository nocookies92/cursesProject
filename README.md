#cursesProject a.k.a. SpankWagon
This is an attempt to create a character-tile based game using the curses library.

Yes, it really is called SpankWagon. The credit goes to my friend, a journalism major, who I asked to help me come up with a name and story.

This particlar game uses the pdcurses library to implement curses.h on Windows, and ncurses for Linux.
##Installation

###Unix
Install the ncurses library (`sudo apt-get install ncurses-dev`).
Run `make unix`. The compiled program can be run by the command `./SpankWagon`

###Windows
There are two ways to install this for windows, the easy way, and the hard way. The easy way is to download the .exe from the /bin folder. The hard way is to compile it yourself. I compiled it using MinGW gcc. You also need to install the pdcurses library using the MinGW package installer. Then run `make` on the command line.

##Credits
Programming - Aaron G.

Name - Jason P.
