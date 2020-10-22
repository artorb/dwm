//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"",  "current_song",			    1,		7},
	{"",  "~/.scripts/kblayout",	    30,		4},
    {"",  "~/.local/bin/statusbar/blevel",	  60,		4},
	//{" ",  "volume_level",						0,		8},
	{"",  "~/.local/bin/statusbar/cpu",	   10,		4},
	{"", "~/.scripts/memory",              	11,		6},
	//{" ",  "~/.local/bin/statusbar/internet",	60,	    17},
	{" ",  "date_time",						    60,		1},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = ' ';
