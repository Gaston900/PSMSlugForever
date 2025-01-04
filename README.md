# PSMETAL SLUG FOREVER
What is PSMSlugForever?

It is called Project Shadow Metal Slug Forever, this project was part of the HBMAME emulator in the year 2018 – 2020.

Afterwards, it has been decided to make the project independent in 2021, providing all kinds of support, repairing all bugs and glitches, correcting incompatibility with the NeoGeo system, etc.

Version 0.224 [HBMAME/EKMAME] is being used as the base system. Users are being offered the pleasure and convenience of being able to play all the Metal Slug game franchises of the "Neo Geo MVS/AES", All Lost Media Predecrypted, Decrypter, Earlier And Bootleg, Decrypter Darksoft, Neo SD And Hack.

What has been optimized in this version?
---------------------------------------
The NeoGeo systems command was optimized, now it is much more practical to be able to play player 1 and player 2, the arrow command "Up, Down, Left, Right" comes by default, this command is used to move and to perform actions To shoot or jump and throw grenades use the A, S, D, Z key.

Removed the black border on NeoGeo systems, now has full screen.

Removed warning screen.

Removed Startups, Loading, Decryption screen texts.

The Arcade64 "GUI" EKMAME source code has been implemented (By KAZE).

The Arcade64 "GUI" new icons have been implemented (By KOF2112).

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
```
make PTR64=0 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```

The compilation [TOOL](https://github.com/mamedev/buildtools/releases) is suggested to be version msys64 2017-12-26.

