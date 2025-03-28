# PSMETAL SLUG FOREVER
What is PSMSlugForever?

It is called Project Shadow Metal Slug Forever, this project was part of the HBMAME emulator in the year 2018 – 2020.

Afterwards, it has been decided to make the project independent in 2021, providing all kinds of support, repairing all bugs and glitches, correcting incompatibility with the NeoGeo system, etc.

Version 0.224 [HBMAME/EKMAME] is being used as the base system. Users are being offered the pleasure and convenience of being able to play all the Metal Slug game franchises of the "Neo Geo MVS/AES", All Lost Media Predecrypted, Decrypter, Encrypte, Earlier And Bootleg, Decrypter Darksoft, Neo SD And Hack.

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

Expand the adpcma rom that can be read to 0x2000000.

Removed the black border on NeoGeo systems, now has full screen.

Removed warning screen.

Removed Startups, Loading, Decryption screen texts.

The Arcade64 "GUI" EKMAME source code has been implemented (By KAZE).

The Arcade64 "GUI" some default settings have been implemented.

It is already pre-configured, enforce aspect ratio is disabled, full screen mode and tricks are already enabled by default.

Two new folder sections called “config” and “support” were added that independently group the configurations + extra content, so that everything is kept in order in a single folder.

In the Config folders it is incorporated by:

Bgfx, Cfg, Comments, Crosshair, Diff, Docs, Folders, Glsl, Gui, Hash, Hlsl, Ini, Inp, Language, Nvram, Plugins, Share, Sta.

In the support folders it is incorporated by:

Artpreview, Artwork, Bosses, Cabinets, Cheat, Cpanel, Ctrlr, Flyers, Gameover, Howto, Icons,
Logo, Manuals, Marquees, Pcb, Roms, Samples, Scores, Select, Snap, Titles, Versus, Video, Cheat.7z, Command.dat, Gameinit.dat, Hiscore.dat, History.dat, Mameinfo.dat, Story. dat and Sysinfo.dat

How to compile
--------------

In order to compile this version we will need the source code, for this we will locate it in the folder docs / Source Code [HBMame] / hbmame-tag224.7z. 001, once located we will begin to unzip the files, it will take a few minutes, once unzipped we will have a folder with the name hbmame-tag224.7z, we will rename it to “src”, Now we will get the latest source code of this Github container once downloaded we will begin to unzip and once finished unzipping we will select the files that we had left in the folder “scripts, src and makefile” we will copy them into the src folder, the system will ask us to replace it we will say yes.

And we will apply this command to start the compilation, this command is for Windows 64Bit system:
```
make PTR64=1 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```
And we will apply this command to start the compilation, this command is for Windows 32Bit system:

The compilation [TOOL](https://github.com/mamedev/buildtools/releases) is suggested to be version msys64 2017-12-26.

