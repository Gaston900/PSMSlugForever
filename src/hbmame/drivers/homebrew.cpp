// Proyecto Shadows Metal Slug Forever
// Copyright-Holders:Gaston90
// Thanks To The Collaborators Who Have Made A Great Contribution To The Project: Remikare And Robbert.

#include "includes/neogeo.h"

/***********************************************************************************************************************************
    In 2010, SNK Playmore, the successor of SNK, released a title catalogue which lists the released
    games (MVS/AES).
    The included title catalogue is the english one.

    Game Title                                                  Genre           Publisher       Date Released (in Japan)
    =================================================================================================================================
    METAL SLUG                                                  Action          Nazca           MVS Cartridge:1996/04/19
                                                                                                NEOGEO ROM-cart:1996/05/24
                                                                                                NEOGEO CD:1996/07/05
    METAL SLUG 2                                                Action          SNK             MVS Cartridge:1998/02/23
                                                                                                NEOGEO ROM-cart:1998/04/02
                                                                                                NEOGEO CD:1998/06/25
    METAL SLUG X                                                Action          SNK             MVS Cartridge:1999/03/19
                                                                                                NEOGEO ROM-cart:1999/05/27
    METAL SLUG 3                                                Action Shooter  SNK             MVS Cartridge:2000/03/23
                                                                                                NEOGEO ROM-cart:2000/06/01
    METAL SLUG 4                                                Action Shooter  SNK Playmore    MVS Cartridge:2002/03/27
                                                                                                NEOGEO ROM-cart:2002/06/13
    METAL SLUG 5                                                Action Shooter  SNK Playmore    MV-0:2003/11/14
                                                                                                NEOGEO ROM-cart:2004/02/19
************************************************************************************************************************************/

/************************************
   Game specific Roms definitions
 ************************************/

#define MSLUG3XE_SFIX_MT_128K \
	NEO_SFIX_MT_128K

#define MSLUG3X_SFIX_MT_128K \
	NEO_SFIX_128K( "3x.s1", CRC(d2af5597) SHA1(7a1c48a65214705327a747b44105cf847a0cba21) )

#define MSLUG3X_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "3x.m1", CRC(0e339fdf) SHA1(65f3c8f551050a798f42da8e8f8d94e51cce7cd1) )

#define MSLUG3X_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "3x.v1", 0x000000, 0x1000000, CRC(67cc9264) SHA1(701758422e1e6c0c0ea0ec15f3b9cd35b299b6ca) )\

#define MSLUG3X_SPRITES \
	ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "3x.c1", 0x000000, 0x800000, CRC(7eb33146) SHA1(c40dcf1358cd408e632e74a200bda596ad738104) )\
	ROM_LOAD16_BYTE( "3x.c2", 0x000001, 0x800000, CRC(a193a88a) SHA1(791884ee5dae0cc2de4889bbe9a24a4db35605f5) )

#define MSLUG3XB_SPRITES \
	ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "3xb.c1", 0x000000, 0x800000, CRC(4a895201) SHA1(eab8d35a2fa141ffdd0997aa71771f20c64dc208) )\
	ROM_LOAD16_BYTE( "3xb.c2", 0x000001, 0x800000, CRC(47c53b38) SHA1(f051068d9a529c91182edd7918e57c4af9f2cdd0) )

#define MSLUG3X0_SFIX_MT_128K \
	NEO_SFIX_128K( "3x0.s1", CRC(87094760) SHA1(cd0d535606c778e2e622447788082d8daf57dffa) )

#define MSLUG3X0_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "3x0.m1", CRC(3d9feec6) SHA1(2e734390d48dc064726a03405ce246bc1d1882d7) )

#define MSLUG3X0_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "3x0.v1", 0x000000, 0x800000, CRC(3fdaec62) SHA1(1902a276d9aec71faf549665658033998e5fecfc) )\

#define MSLUG3X0_SPRITES \
	ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "3x0.c1", 0x000000, 0x800000, CRC(e245ad45) SHA1(3c73eae14edc66e74f68460433912ca41a7b2c22) )\
	ROM_LOAD16_BYTE( "3x0.c2", 0x000001, 0x800000, CRC(96bf1209) SHA1(b468010567d59315f304b713b00965cfbfff94e6) )

#define MSLUG3X1_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "3x1.m1", CRC(d603fc58) SHA1(f2458a012edddb872d8bbb4f62ea4d135aa60d63) )

#define MSLUG3X1_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "3x1.v1", 0x000000, 0x800000, CRC(3fe95bc8) SHA1(adb7da80949c7483616311313411ec83d4820c93) )\

#define MSLUG3X1_SPRITES \
	ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "3x1.c1", 0x000000, 0x800000, CRC(4f64aecb) SHA1(5b92ed2d33e79bcacb4af414124c0ff60b5e268a) )\
	ROM_LOAD16_BYTE( "3x1.c2", 0x000001, 0x800000, CRC(c02b2cbb) SHA1(563eb097e097284fe7f09b6b0e2f65fd37814f54) )

#define MSLUG3X2_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "3x2.m1", CRC(c6eace68) SHA1(3fd83b70d9624822159b21b0d5c7d6e80e98deb9) )

#define MSLUG3X2_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "3x2.v1", 0x000000, 0x800000, CRC(95a64a9d) SHA1(01e7732147f068c1f0296ffb0413968b360b6946) )\

#define MSLUG3X2_SPRITES \
	ROM_REGION( 0x800000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "3x2.c1", 0x000000, 0x400000, CRC(9d497f06) SHA1(270d03c8c0be14f4b9bc4e7f72521e192682bb9c) )\
	ROM_LOAD16_BYTE( "3x2.c2", 0x000001, 0x400000, CRC(00482d5f) SHA1(986ee3416f74e6fce8d62c85f1d5219a7135614d) )

#define MSLUG3X3_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "3x3.m1", CRC(c5579de4) SHA1(e7a529439ba8fa68d531afc7d8a95d6f2936289c) )

#define MSLUG3X3_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "3x3.v1", 0x000000, 0x800000, CRC(17934969) SHA1(d7207939a8028eae31361e23739443895fc41e85) )\

#define MSLUG3X3_SPRITES \
	ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "3x3.c1", 0x000000, 0x800000, CRC(9be2f993) SHA1(ce9b7c5ae226f4e9bebc95d1b34affa48693a910) )\
	ROM_LOAD16_BYTE( "3x3.c2", 0x000001, 0x800000, CRC(9f261733) SHA1(6a740972dc9011815614c2d70c10166113e8d4a2) )

#define MSLUG3XE_AUDIO_ENCRYPTED_128K \
	NEO_BIOS_AUDIO_ENCRYPTED_128K( "3xe.m1", CRC(876df5e1) SHA1(a54bd3eb76d9768fec26fbf4153c0a6055df159f) )

#define MSLUG3XE_YMSND \
	ROM_REGION( 0x1000000, "ymsnd", 0 ) \
	ROM_LOAD( "3xe.v1", 0x000000, 0x800000, CRC(5d904213) SHA1(62bf1a832c14203ce913f6ac3dc5df75d141155a) )\
	ROM_LOAD( "3xe.v2", 0x800000, 0x800000, CRC(97cee550) SHA1(b4429e71847ead15b146754f35023efa276253a7) )

#define MSLUG3XE_SPRITES \
    ROM_REGION( 0x1000000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "3xe.c1", 0x000000, 0x800000, CRC(92a89586) SHA1(9d6dca9fd73cdd6d382d26708c632ec01654c050) )\
	ROM_LOAD16_BYTE( "3xe.c2", 0x000001, 0x800000, CRC(18d14a71) SHA1(95e7518091fe5600bd5fb5c90fcec22670bf8910) )

#define NEOPANG_SFIX_64K \
	NEO_SFIX_64K( "neop.s1", CRC(d78bd9a0) SHA1(17a237166aede98bee27d5b52654414c8a1b071a) )

#define NEOPANG_AUDIO_128K \
	NEO_BIOS_AUDIO_128K( "neop.m1", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

#define NEOPANG_YMSND \
	ROM_REGION( 0x80000, "ymsnd", 0 ) \
    ROM_LOAD( "neop.v1", 0x000000, 0x80000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

#define NEOPANG_SPRITES \
	ROM_REGION( 0x200000, "sprites", 0 ) \
	ROM_LOAD16_BYTE( "neop.c1", 0x000000, 0x100000, CRC(62f5405c) SHA1(f9eb8d1838da9953aecf40c3314c608ab655cb8f) )\
	ROM_LOAD16_BYTE( "neop.c2", 0x000001, 0x100000, CRC(e1183030) SHA1(60262d53ab12314db5e5c00a94463500abe3e8b0) )

/****************************
 Decrypter To Encrypted GFX
*******************************/

ROM_START( mslug3xe )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "3xe.p1", 0x000000, 0x400000, CRC(1e0506cf) SHA1(f1a20f1f0fc3fd74dd5d258eaf75965eb2b4cd91) )
	ROM_LOAD32_WORD_SWAP( "3xe.p2", 0x000002, 0x400000, CRC(894cd3dd) SHA1(553f90fce8c04940892bd797dc4f1dddf7276c81) )
	MSLUG3XE_SFIX_MT_128K
	MSLUG3XE_AUDIO_ENCRYPTED_128K
	MSLUG3XE_YMSND
	MSLUG3XE_SPRITES
ROM_END

 /*********
  HomeBrew
************/

ROM_START( mslug3x )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3x.p1", 0x000000, 0x200000, CRC(0d327ddb) SHA1(d4768e4029f0b8f9da3d14f5746d71cf0b5d81aa) )
	MSLUG3X_SFIX_MT_128K
    MSLUG3X_AUDIO_128K
    MSLUG3X_YMSND
    MSLUG3X_SPRITES
ROM_END

ROM_START( mslug3xb )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3xb.p1", 0x000000, 0x200000, CRC(64f596c5) SHA1(22423abd7688ceda121ccdc67505acb37921a563) )
	MSLUG3X_SFIX_MT_128K
    MSLUG3X_AUDIO_128K
    MSLUG3X_YMSND
    MSLUG3XB_SPRITES
ROM_END

ROM_START( mslug3x0 )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3x0.p1", 0x000000, 0x200000, CRC(06967c7f) SHA1(a736ed315a1cb63d25cf8f5d0b5109a7ca4251e9) )
	MSLUG3X0_SFIX_MT_128K
    MSLUG3X0_AUDIO_128K
    MSLUG3X0_YMSND
    MSLUG3X0_SPRITES
ROM_END

ROM_START( mslug3x1 )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3x1.p1", 0x000000, 0x200000, CRC(8cfeada7) SHA1(4a5075fbcfe9c83e641517cde2833946f1f721a0) )
	MSLUG3X0_SFIX_MT_128K
    MSLUG3X1_AUDIO_128K
    MSLUG3X1_YMSND
    MSLUG3X1_SPRITES
ROM_END

ROM_START( mslug3x2 )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3x2.p1", 0x000000, 0x200000, CRC(17510972) SHA1(2a5f255dedaf14e33068b49d809879feeddd5c97) )
	MSLUG3X_SFIX_MT_128K
    MSLUG3X2_AUDIO_128K
    MSLUG3X2_YMSND
    MSLUG3X2_SPRITES
ROM_END

ROM_START( mslug3x3 )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "3x3.p1", 0x000000, 0x200000, CRC(0f7700d7) SHA1(a457f2462969d1e8bdfceefee15bbee24ec7e55f) )
	MSLUG3X_SFIX_MT_128K
    MSLUG3X3_AUDIO_128K
    MSLUG3X3_YMSND
    MSLUG3X3_SPRITES
ROM_END

ROM_START( neopang )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "neop.p1", 0x000000, 0x080000, CRC(dc5922ee) SHA1(08804fa9894b7e84375300acbdec8ea6829575d0) )
	NEOPANG_SFIX_64K
    NEOPANG_AUDIO_128K
    NEOPANG_YMSND
    NEOPANG_SPRITES
ROM_END

/*    YEAR   NAME             PARENT       MACHINE     INPUT                           INIT        MONITOR COMPANY           FULLNAME FLAGS */
// Metal Slug (TAOENWEN Neo Geo Hack Converted C, V, M, S & P Decrypter To Encrypte)
GAME( 2022, mslug3xe,         mslug3x,  neogeo_noslot, neogeo,     neogeo_state,    init_mslug5hb,   ROT0, "CB, Willnie",     "Metal Slug HomeBrew (Mothership Armageddon Easter Egg Beta 2022-01-10)(Encrypted C)", MACHINE_SUPPORTS_SAVE ) /* Encrypted GFX */

/*    YEAR   NAME             PARENT       MACHINE     INPUT                           INIT        MONITOR COMPANY           FULLNAME FLAGS */
// HomeBrew
GAME( 2022, mslug3x,          neogeo,   neogeo_noslot, neogeo,     neogeo_state,    init_neogeo,     ROT0, "CB, Willnie",     "Metal Slug HomeBrew (Mothership Armageddon Easter Egg Final Release 2022-02-03)", MACHINE_SUPPORTS_SAVE )// Metal Slug 3X (Complete Collection)
GAME( 2022, mslug3xb,         mslug3x,  neogeo_noslot, neogeo,     neogeo_state,    init_neogeo,     ROT0, "CB, Willnie",     "Metal Slug HomeBrew (Mothership Armageddon Easter Egg Beta 2022-01-10)", MACHINE_SUPPORTS_SAVE )// Metal Slug 3X (Complete Collection)
GAME( 2020, mslug3x0,         mslug3x,  neogeo_noslot, neogeo,     neogeo_state,    init_neogeo,     ROT0, "CB, Willnie",     "Metal Slug HomeBrew (Mothership Armageddon Easter Egg Demo 0 2020-01-20)", MACHINE_SUPPORTS_SAVE )// Metal Slug 3X (Complete Collection)
GAME( 2020, mslug3x1,         mslug3x,  neogeo_noslot, neogeo,     neogeo_state,    init_neogeo,     ROT0, "CB, Willnie",     "Metal Slug HomeBrew (Mothership Armageddon Easter Egg Demo 1 2020-04-14)", MACHINE_SUPPORTS_SAVE )// Metal Slug 3X (Complete Collection)
GAME( 2020, mslug3x2,         mslug3x,  neogeo_noslot, neogeo,     neogeo_state,    init_neogeo,     ROT0, "CB, Willnie",     "Metal Slug HomeBrew (Mothership Armageddon Easter Egg Demo 2 2020-04-16)", MACHINE_SUPPORTS_SAVE )// Metal Slug 3X (Complete Collection)
GAME( 2021, mslug3x3,         mslug3x,  neogeo_noslot, neogeo,     neogeo_state,    init_neogeo,     ROT0, "CB, Willnie",     "Metal Slug HomeBrew (Mothership Armageddon Easter Egg Demo 3 2021-08-21)", MACHINE_SUPPORTS_SAVE )// Metal Slug 3X (Complete Collection)
GAME( 2010, neopang,          mslug3x,  neogeo_noslot, neogeo,     neogeo_state,    init_neogeo,     ROT0, "CeL",             "Metal Slug HomeBrew (Neo Pang)", MACHINE_SUPPORTS_SAVE )


