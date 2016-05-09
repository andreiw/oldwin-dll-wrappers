oldwin-dll-wrappers
===================

An ugly hack.

A bunch of mostly proxy libraries that add missing
symbols seen on later versions of Windows. For
NT 3.51 and NT 4.0.

Mostly doesn't work. Har Har. But I already sunk enough
time into this that I really don't want to randomly
lose this code :-/.

Runs 7za.exe (the command line version of 7zip) on NT 3.51.
Does not run Cygwin (yet? ever?).

Prerequisites
-------------

- NT 3.51 or NT 4.0
- MSVC 4.0 or later

Building
--------

    E:\wrappers> nmake

Using
-----

Using: add the directory with DLLs to your PATH. Patch
       binary using patcher.exe. Pray.

Adjust for your src dir and Windows version.

    E:\wrappers> set PATH=%PATH%:E:\wrappers\nt40
    E:\wrappers> patcher C:\some\path\to\foo.exe
    E:\wrappers> C:\some\path\to\foo.exe

Various
-------

For forwards header generation see http://osdevnotes.blogspot.com/2016/05/easy-creation-of-proxy-dll-pragma.html

Contact Info
------------

andrey.warkentin@gmail.com
