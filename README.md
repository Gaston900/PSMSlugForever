# PSMAME PLUS (Metal Slug Forever Special Edition Final)
What is PSMAMEPLUS?

It is called Project Shadow Mame Plus (Metal Slug Forever Special Edition Final), this project was part of the HBMAME emulator in the year 2018 – 2020.

Afterwards, it has been decided to make the project independent in 2021, providing all kinds of support, repairing all bugs and glitches, correcting incompatibility with the NeoGeo system, etc.

Version 0.215 [HBMAME] is being used as the base system. Users are being offered the pleasure and convenience of being able to play all the Metal Slug game franchises of the "Neo Geo MVS" Arcade system.

Unofficial versions known as "hacks" are also included.

What has been optimized in this version?
The command of all the game systems was optimized, now it is much more practical to be able to play, the command of the arrow keys "Up, Down, Left, Right" comes by default, this command is used to be able to move and to take actions For shooting or jumping and throwing grenades, the A, S, D key is used and the rest of the keys are used for certain kinds of games Z, X, C, Q, W, E.

Added custom buttons and auto fire

Removed warning screen.

Removed Startups, Loading, Decryption screen texts.

The Arcade64 “GUI” was modernized with new icons, a custom default configuration has been made.

It is already pre-configured, enforce aspect ratio is disabled, full screen mode and tricks are already enabled by default.

To be able to compile this version we will need the source codes, for this we will place it in the folder docs/Old HBMAME Source Code/hbmame-tag215.7z.001, once located we will start to decompress the files it will take a few minutes, once decompressed we will have a folder with the name hbmame-tag215.7z, we will rename it to “src”, now we will paste the remains of the files that we have left “3rdparty, scripts, src and makefile” in the src folder, the system will ask to replace it we will say yes .

Now we will locate the folder where the compiler that we want to use is located, being msys32 or msys64 [This depends on the support that your operating system has, being Windows 32bit or Windows 64Bit]. Now we will paste the “src” folder.

And we will apply this command to start the compilation, this command is for Windows 64Bit system:

make PTR64=1 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
--------------------------------------------------------------
And we will apply this command to start the compilation, this command is for Windows 32Bit system:

make PTR64=0 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
--------------------------------------------------------------

I recommend downloading the compilation tool, whether it is the version msys32 or msys64 that is from the year 2017-12-26, since this version is much more comfortable to compile for this version, especially if it is to compile a version for Windows XP system .

The build tools will be located on the MAMEDEV github website:
https://github.com/mamedev/buildtools/releases

