MusicBox-C-Client
=================

MusicBox C++ Client

C++ dynamic library + app example for https://github.com/giko/Musicbox_server
Using https://github.com/zaphoyd/websocketpp with VSC++ fixes.
Unix versions comin...

Prerequisites:
	1) Boost need to be installed
	2) Compile boost libraries with static-linking 
		(.\b2 --toolset=msvc-11.0 runtime-link=static)
	3) Set $(BOOSTROOT) to your boost home

Everything else should work out of box.