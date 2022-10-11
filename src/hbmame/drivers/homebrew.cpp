// Proyecto Shadows Mame Plus
// copyright-holders:Gaston90

#include "includes/neogeo.h"

 /**********
   HomeBrew
*************/

ROM_START( mslughw ) //mslug5ast
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD32_WORD_SWAP( "268_hw.p1", 0x000000, 0x400000, CRC(1e0506cf) SHA1(f1a20f1f0fc3fd74dd5d258eaf75965eb2b4cd91) )
	ROM_LOAD32_WORD_SWAP( "268_hw.p2", 0x000002, 0x400000, CRC(894cd3dd) SHA1(553f90fce8c04940892bd797dc4f1dddf7276c81) )

	NEO_SFIX_MT_128K

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "268_hw.m1", CRC(876df5e1) SHA1(a54bd3eb76d9768fec26fbf4153c0a6055df159f) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "268_hw.v1", 0x000000, 0x800000, CRC(5d904213) SHA1(62bf1a832c14203ce913f6ac3dc5df75d141155a) )
	ROM_LOAD( "268_hw.v2", 0x800000, 0x800000, CRC(97cee550) SHA1(b4429e71847ead15b146754f35023efa276253a7) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "268_hw.c1", 0x000000, 0x800000, CRC(92a89586) SHA1(9d6dca9fd73cdd6d382d26708c632ec01654c050) )
	ROM_LOAD16_BYTE( "268_hw.c2", 0x000001, 0x800000, CRC(18d14a71) SHA1(95e7518091fe5600bd5fb5c90fcec22670bf8910) )
ROM_END

ROM_START( neopang )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "268_hwneo.p1", 0x000000, 0x080000, CRC(dc5922ee) SHA1(08804fa9894b7e84375300acbdec8ea6829575d0) )

	NEO_SFIX_64K( "268_hwneo.s1", CRC(d78bd9a0) SHA1(17a237166aede98bee27d5b52654414c8a1b071a) )

	NEO_BIOS_AUDIO_128K( "268_hwneo.m1", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

	ROM_REGION( 0x80000, "ymsnd", 0 )
	ROM_LOAD( "268_hwneo.v1", 0x000000, 0x80000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD16_BYTE( "268_hwneo.c1", 0x000000, 0x100000, CRC(62f5405c) SHA1(f9eb8d1838da9953aecf40c3314c608ab655cb8f) )
	ROM_LOAD16_BYTE( "268_hwneo.c2", 0x000001, 0x100000, CRC(e1183030) SHA1(60262d53ab12314db5e5c00a94463500abe3e8b0) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// HomeBrew
GAME( 2022, mslughw,        neogeo,   neogeo_noslot, neogeo,   neogeo_state, init_mslug5hb, ROT0, "CB, Willnie",  "Metal Slug HomeBrew (Mothership Armageddon Easter Egg 2021-06-13)", MACHINE_SUPPORTS_SAVE )
GAME( 2010, neopang,        mslughw,  neogeo_noslot, neogeo,   neogeo_state, init_neogeo,   ROT0, "CeL",          "Metal Slug HomeBrew (Neo Pang)", MACHINE_SUPPORTS_SAVE )
