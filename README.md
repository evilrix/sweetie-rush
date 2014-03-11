sweetie-rush
============

A prototype/concept for a game similar to "Candy Crush".

TODO:

There are some known issues that need fixing:

* Currently, there is no scoring mechanism (boo!)
* The game is meant to only last for 1 minute
* New matches generated by "drops" are not handled
* The randomization of sweeties relies on the poor RNG of the CRT
* The game-board matching code is a little hacky
* There are almost certainly still dragons in the matching code
* No logic exists to ensure that there'll always be a legal move
* Images are loaded at runtime rather than being embedded as a resource

Requirements:
* Visual Studio 2013 (the code base is C++11 and won't build with older, non-standard versions)
* SDL and SDL Image libraries
* Doxygen if you want to create the API docs (see inline doxygen commentary)

The code is written in ANSI C++ compatible with the C++11 standard. Whilst it was written using Visual Studio 2013, is should, with very few modifications, build and run on any platform using a C++11 complient compiler.
