# PSMETAL SLUG FOREVER
What is PSMSlugForever?

It is called Project Shadow Metal Slug Forever, this project was part of the HBMAME emulator in the year 2018 – 2020.

Afterwards, it has been decided to make the project independent in 2021, providing all kinds of support, repairing all bugs and glitches, correcting incompatibility with the NeoGeo system, etc.

Version 0.224 [HBMAME] is being used as the base system. Users are being offered the pleasure and convenience of being able to play all the Metal Slug game franchises of the "Neo Geo MVS" Arcade system.

Unofficial versions known as "hacks" are also included.

What has been optimized in this version?
---------------------------------------
The NeoGeo systems command was optimized, now it is much more practical to be able to play player 1 and player 2, the arrow command "Up, Down, Left, Right" comes by default, this command is used to move and to perform actions To shoot or jump and throw grenades use the A, S, D, Z key.

Removed the black border on NeoGeo systems, now has full screen.

Removed warning screen.

Removed Startups, Loading, Decryption screen texts.

The Arcade64 “GUI” was modernized with new icons, a custom default configuration has been made.

It is already pre-configured, enforce aspect ratio is disabled, full screen mode and tricks are already enabled by default.

Two new folder sections called “config” and “support” were added that independently group the configurations + extra content, so that everything is kept in order in a single folder.

In the Config folders it is incorporated by:

Audio, Bgfx, Cfg, Comments, Crosshair, Diff, Docs, Folders, Glsl, Gui, Hash, Hlsl, Ini, Inp, Language, Nvram, Plugins, Share, Sta.

In the support folders it is incorporated by:

Artpreview, Artwork, Bosses, Cabinets, Cheat, Cpanel, Ctrlr, Flyers, Gameover, Howto, Icons,
Logo, Manuals, Marquees, Pcb, Roms, Samples, Scores, Select, Snap, Titles, Versus, Video, Cheat.7z, Command.dat, Gameinit.dat, Hiscore.dat, History.dat, Mameinfo.dat, Story. dat and Sysinfo.dat

How to compile
--------------

To be able to compile this version we will need the source codes, for this we will place it in the folder docs/Source Code [HBMame Old]/hbmame-tag224.7z.001, once located we will start to decompress the files it will take a few minutes, once decompressed we will have a folder with the name hbmame-tag224.7z, we will rename it to “src”, now we will paste the remains of the files that we have left “3rdparty, scripts, src and makefile” in the src folder, the system will ask to replace it we will say yes .

Now we will locate the folder where the compiler that we want to use is located, being msys32 or msys64 [This depends on the support that your operating system has, being Windows 32bit or Windows 64Bit]. Now we will paste the “src” folder.

And we will apply this command to start the compilation, this command is for Windows 64Bit system:
```
make PTR64=1 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```
And we will apply this command to start the compilation, this command is for Windows 32Bit system:
```
make PTR64=0 TARGET=mame OSD=winui NOWERROR=1 STRIP_SYMBOLS=1
```

I recommend downloading the compilation tool, whether it is the version msys32 or msys64 that is from the year 2017-12-26, since this version is much more comfortable to compile for this version, especially if it is to compile a version for Windows XP system .

The build tools will be located on the MAMEDEV github website:
https://github.com/mamedev/buildtools/releases

