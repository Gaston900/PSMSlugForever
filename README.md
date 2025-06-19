# PSMETAL SLUG FOREVER
What is PSMSlugForever?

It is called Project Shadow Metal Slug Forever, this project was part of the HBMAME emulator in the year 2018 – 2020.

Afterwards, it has been decided to make the project independent in 2021, providing all kinds of support, repairing all bugs and glitches, correcting incompatibility with the NeoGeo system, etc.

Version 0.224 [HBMAME/EKMAME] is being used as the base system.

It allows users to enjoy a unique and distinctive gaming experience, having a great time exploring a wide catalog of different versions of the NeoGeo MVS/AES system.

This project was dedicated with much effort and great care, it was developed with so much passion and with great enthusiasm, with such a deep dedication of interest in preserving the history in the roms that were published since the beginning of the emulation era since 1999 (Predecrypted, Decrypter, Encrypte, Earlier and Bootleg, Darksoft, Neo SD and Hack)

I am only supporting the operating systems, Windows 7, Windows 8, Windows 10 and Windows 11.

What has been optimized in this version?
---------------------------------------
This command will help us have much easier access to the settings:

* To save the game, press the "7" key.
* To load the game, press the "8" key.
* To reset the game, press the "9" key.
* To enter the NeoGeo BIOS, press the "0" key.
* To pause the game, press the "P" key.
* To accelerate the Frames per second (FPS), press the "ALT" key.
* To play in windowed mode, press the "Spacebar" key.
* To accelerate the game by 3x, press the "Backspace" key.

Players 1 and 2 use this controller by default:

* To move, use the arrow keys "Up, Down, Left, Right."
* To perform actions, use the "A, S, D, Z" keys.

Overclocking Default 200%.

The M68000 CPU core has been modified to be compatible with all current types of hack ROMs.

Expand the memory file adpcma rom that can be read to 0x2000000.

The free mod is enabled on the NeoGeo system by pressing the Start button, you don't need to add credits every time you lose.

It has been configured by default that it has 99 Credits in MVS/AES mode.

It supports switching between MVS (Arcade) and AES (Console) mode.

Added custom buttons and autofire.

Removed the black border on NeoGeo systems, now has full screen.

Removed warning screen.

Removed Startups, Loading, Decryption screen texts.

The Arcade64 "GUI" EKMAME source code has been implemented (By KAZE).

The Arcade64 "GUI" some default settings have been implemented.

It is already pre-configured, enforce aspect ratio is disabled, full screen mode and tricks are already enabled by default.

The cheat reference function, if the cloned game does not have a cheat file, it will reference the cheat file of the main ROM.

Supports game list language files.

Two new folder sections called “config” and “support” were added that independently group the configurations + extra content, so that everything is kept in order in a single folder.

In the Config folders it is incorporated by:

Bgfx, Cfg, Comments, Crosshair, Diff, Docs, Folders, Glsl, Gui, Hash, Hlsl, Ini, Inp, Language, Nvram, Plugins, Share, Sta.

In the support folders it is incorporated by:

Artpreview, Artwork, Bosses, Cabinets, Cheat, Cpanel, Ctrlr, Flyers, Gameover, Howto, Icons,
Logo, Manuals, Marquees, Pcb, Roms, Samples, Scores, Select, Snap, Titles, Versus, Video, Cheat.7z, Command.dat, Gameinit.dat, Hiscore.dat, History.dat, Mameinfo.dat, Story. dat and Sysinfo.dat

Added 7 new UI folders by default.

* Metal Slug
* Metal Slug 2
* Metal Slug 3
* Metal Slug 4
* Metal Slug 5
* Metal Slug X
* HomeBrew

How to compile
--------------

In order to compile this version we will need the source code, for this we will locate it in the folder docs / Source Code [HBMame] / hbmame-tag224.7z. 001, once located we will begin to unzip the files, it will take a few minutes, once unzipped we will have a folder with the name hbmame-tag224.7z, we will rename it to “src”, Now we will get the latest source code of this Github container once downloaded we will begin to unzip and once finished unzipping we will select the files that we had left in the folder “scripts, src and makefile” we will copy them into the src folder, the system will ask us to replace it we will say yes.

And we will apply this command to start the compilation, this command is for Windows 64-Bit system:
```
make PTR64=1 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```
And we will apply this command to start the compilation, this command is for Windows 32-Bit system:
```
make PTR64=0 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```

The compilation [TOOL](https://github.com/mamedev/buildtools/releases) is suggested to be version msys64 2017-12-26.

Open Source Software Projects
------------------------------
Although the source code is free to use, please note that the use of this code for any commercial exploitation or use of the project for fundraising purposes is prohibited.
