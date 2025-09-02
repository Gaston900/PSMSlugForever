// Proyecto Shadows Metal Slug Forever
// Copyright-Holders:Gaston90
// Thanks To The Collaborators Who Have Made A Great Contribution To The Project: Robbert.


#include "includes/neogeo.h"


/*************************************
 *
 *  Official sets
 *
 *************************************

    About supported sets:
    =====================

    MVS carts (arcade) were released before the AES carts (home)
    The actual codepath taken depends entirely on the BIOS rom, not the roms in the cartridge, which (with
    a few exceptions) support both codepaths.

    The initial AES releases are therefore later revisions of the game, often with bug fixes over the
    initial MVS releases. It isn't uncommon for later production runs and bootlegs to use these newer sets,
    so all of them are supported in MAME.

    Likewise, because the MVS carts were released first (and were produced in higher numbers and generally
    have a lower cost) it's not uncommon for AES units to operate with converted MVS carts, so, with the
    exception of the sets that specifically lock out the AES mode* these sets are all equally suitable
    for MESS.
    * nitd, kof2001 (initial release has no AES code), and a number of the hacked bootlegs.

    The 'MVS ONLY RELEASE' tagged sets were not officially released for the AES (home) system.
    Information about this can be found at 'The NeoGeo Master List' (unofficial) - http://www.neo-geo.com
    and the official NeoGeo museum - http://neogeomuseum.snkplaymore.co.jp/english/index.php
    Several unofficial 'conversions' of these sets can be found across the internet.
    For completeness sake: Some of these have sets have been released for the CD system.


    M1 (sound driver) rom information:
    ==================================
    . Many 'M1' roms contain mirrored data (64k mirrored or 128k mirrored).
    . Found on several early sets (ID 0001 ~ 0045) and on the last sets (ID 0267 ~ 0272).
    . This caused some confusion and incorrect rom sizes.
    . Minimum 'M1' size is 1mbit, maximum size 4mbit.
    . The remaining 64k 'M1' are marked BAD_DUMP.


    S1 (text layer) rom information:
    ================================
    . All 'S1' roms found on prom are 1mbit.
    . The remainig 64k 'S1' are marked BAD_DUMP.


    MULTI PLAY MODE:
    ================
    The NeoGeo has three games which support MULTI PLAY MODE (Riding Hero / League Bowling / Trash Rally).
    This allows you to 'link' 4 games (MVS) / 2 games (AES) using in game 'Multi-Play' option. To establish
    a link between the carts you have to connect the carts to each other by a communicator cable. The communicatior
    cable is a regular headphone cable with stereo pin jack. It has been reported that you can also 'link' MVS <-> AES.

    All three games use a special PROG board for MULTI PLAY MODE support:
    . Riding Hero    (AES - NEO-AEG PROG-HERO   / MVS NEO-MVS PROG-HERO)
    . League Bowling (AES - NEO-AEG PROG-HERO   / MVS NEO-MVS PROG-HERO)
    . Trash Rally    (AES - NEO-AEG PROG42G-COM / NEO-MVS PROG42G-COM)

    A HD6301V1P MCU on the above boards is used for establishing the 'link'. The MCU has a 4kb internal ROM which
    is not dumped.
    To use the MULTI PLAY MODE on your MVS you have to set the following hardware dips:
    HARD DIP SETTING  4   5   6
    CABINET 1:        OFF OFF ON
    CABINET 2:        OFF ON  ON
    CABINET 3:        ON  OFF ON
    CABINET 4:        ON  ON  ON


    SPHERO SYMPHONY:
    ================
    Several early games have a 'feature' called "sphero symphony". None of the games featuring "sphero symphony"
    uses special hardware. It is something sound based, but what exactly it is (specially arranged samples,
    FM synthesis etc.) is unknown. The AES and MVS releases share the same sound data and driver.

    The AES game-inserts and manuals have an eye-shaped logo with the following text (not to be found on MVS sets):
    sphero
    symphony
    STEREOPHONIC SOUND

    Experience this "LIVE" 3 dimensional sound coming from all around you.

    Games featuring "sphero symphony":
    ID-0006 - Riding Hero
    ID-0007 - Alpha Mission II / ASO II - Last Guardian
    ID-0009 - Ninja Combat
    ID-0010 - Cyber-Lip
    ID-0011 - The Super Spy
    ID-0014 - Mutation Nation
    ID-0017 - Sengoku / Sengoku Denshou
    ID-0018 - Burning Fight
    ID-0020 - Ghost Pilots
    ID-0024 - Last Resort
    ID-0031 - Soccer Brawl
    ID-0033 - Fatal Fury - King of Fighters / Garou Densetsu - shukumei no tatakai
    ID-0034 - Football Frenzy
    ID-0037 - Crossed Swords
    ID-0038 - Thrash Rally
    ID-0039 - King of the Monsters 2 - The Next Thing
    ID-0041 - Baseball Stars 2
    ID-0044 - Art of Fighting / Ryuuko no Ken
    ID-0047 - Fatal Fury 2 / Garou Densetsu 2 - arata-naru tatakai
    ID-0049 - Andro Dunos

*/

/*************************************
 *
 *  Game-specific inits
 *
 *************************************/

void neogeo_state::init_darksoft()
{
	init_neogeo();
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_garoudd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
    m_cmc_prot->cmc42_neogeo_gfx_decrypt(spr_region, spr_region_size, GAROU_GFX_KEY);
    m_sma_prot->garou_install_protection(m_maincpu,m_banked_cart);
}

void neogeo_state::init_garouhdd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
    m_cmc_prot->cmc42_neogeo_gfx_decrypt(spr_region, spr_region_size, GAROU_GFX_KEY);
    m_sma_prot->garouh_install_protection(m_maincpu,m_banked_cart);
}

void neogeo_state::init_kof99dd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
    m_cmc_prot->cmc42_neogeo_gfx_decrypt(spr_region, spr_region_size, KOF99_GFX_KEY);
    m_sma_prot->kof99_install_protection(m_maincpu, m_banked_cart);
}

void neogeo_state::init_kof2000dd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 2;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
    m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, KOF2000_GFX_KEY);
    m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);
	m_sma_prot->kof2000_install_protection(m_maincpu, m_banked_cart);
}

void neogeo_state::init_svcdd()
{
	init_neogeo();
//	m_pvc_prot->svc_px_decrypt(cpuregion, cpuregion_size);
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 3);
	m_sprgen->m_fixed_layer_bank_type = 2;
	m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region,audio_region_size);
	m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, SVC_GFX_KEY);
	m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
	m_pvc_prot->install_pvc_protection(m_maincpu,m_banked_cart);
}

void neogeo_state::init_svcpcbdd()
{
	init_neogeo();

	m_sma_prot->svcpcb_gfx_decrypt(spr_region, spr_region_size);
	m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region,audio_region_size);
	m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, SVC_GFX_KEY);
	m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
	m_sma_prot->svcpcb_s1data_decrypt(fix_region, fix_region_size);
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 3);
	m_sprgen->m_fixed_layer_bank_type = 2;
	m_pvc_prot->install_pvc_protection(m_maincpu,m_banked_cart);
	install_banked_bios();
}

ROM_START( garoudd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x900000, CRC(eb2d1ea5) SHA1(6a64235c77a1263094d4ef9aa49300842e582222) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_512K( "srom", CRC(be2ba1a5) SHA1(e10dd25ba52ebe5caffc66135ba29f6624216b3d) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(36a806be) SHA1(90fb44dc0c3fb57946a0f35716056abb84a0f191) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(123d8987) SHA1(cecf4d70ba84f3d8b1180ac2707e168f5b219a0f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(21d6b54a) SHA1(6ce50711c4edf206fe123a489b8c61cbcab50b97) )
ROM_END

ROM_START( garouhdd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x900000, CRC(29e85d59) SHA1(b2935e57cb1420b6514ab83d86f36fea658fec3a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_512K( "srom", CRC(be2ba1a5) SHA1(e10dd25ba52ebe5caffc66135ba29f6624216b3d) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(36a806be) SHA1(90fb44dc0c3fb57946a0f35716056abb84a0f191) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(123d8987) SHA1(cecf4d70ba84f3d8b1180ac2707e168f5b219a0f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(21d6b54a) SHA1(6ce50711c4edf206fe123a489b8c61cbcab50b97) )
ROM_END

ROM_START( garouhadd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promha", 0x000000, 0x900000, CRC(308b0e02) SHA1(1c9fe760ce6b4e4bbc8d26b570b50f8a026149b2) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_512K( "srom", CRC(be2ba1a5) SHA1(e10dd25ba52ebe5caffc66135ba29f6624216b3d) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(36a806be) SHA1(90fb44dc0c3fb57946a0f35716056abb84a0f191) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(123d8987) SHA1(cecf4d70ba84f3d8b1180ac2707e168f5b219a0f) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(21d6b54a) SHA1(6ce50711c4edf206fe123a489b8c61cbcab50b97) )
ROM_END

ROM_START( kof99dd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x900000, CRC(bdd7be09) SHA1(a37a5d10efa458f88385b0ec56d195ecca4332c4) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1b0133fe) SHA1(7f8e743bc0c8384dec12ca7007d32b23fef8875d) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0xe00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xe00000, CRC(1fc7c930) SHA1(2d043636eeee0530f552fababa0d7d61336d647d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(8f856c98) SHA1(8bae1814c8e7b4b519bdc07c09b1a8b3491e0f48) )
ROM_END

ROM_START( kof99edd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prome", 0x000000, 0x900000, CRC(e3b48e65) SHA1(c5fce036a792db9ce30458795a7c0942c678c706) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1b0133fe) SHA1(7f8e743bc0c8384dec12ca7007d32b23fef8875d) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0xe00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xe00000, CRC(1fc7c930) SHA1(2d043636eeee0530f552fababa0d7d61336d647d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(8f856c98) SHA1(8bae1814c8e7b4b519bdc07c09b1a8b3491e0f48) )
ROM_END

ROM_START( kof99hdd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x900000, CRC(57d67f28) SHA1(8e1be82337555217ce8c36b038a88f6f0afda868) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1b0133fe) SHA1(7f8e743bc0c8384dec12ca7007d32b23fef8875d) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0xe00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xe00000, CRC(1fc7c930) SHA1(2d043636eeee0530f552fababa0d7d61336d647d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(8f856c98) SHA1(8bae1814c8e7b4b519bdc07c09b1a8b3491e0f48) )
ROM_END

ROM_START( kof99kdd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x900000, CRC(83411cfd) SHA1(47c5dec3c6c00e21e96664dd558c3d401eeabde3) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1b0133fe) SHA1(7f8e743bc0c8384dec12ca7007d32b23fef8875d) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0xe00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xe00000, CRC(1fc7c930) SHA1(2d043636eeee0530f552fababa0d7d61336d647d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(8f856c98) SHA1(8bae1814c8e7b4b519bdc07c09b1a8b3491e0f48) )
ROM_END

ROM_START( kof2000dd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x900000, CRC(396aeed7) SHA1(0f0bad158b10855c32369d4ca6e5504ea4b611b6) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_512K( "srom.s1", CRC(38901d4d) SHA1(c7684f66ab4ed577094da6ae143477c9df28d1fe) )

	NEO_BIOS_AUDIO_ENCRYPTED_256K( "m1rom", CRC(4b749113) SHA1(2af2361146edd0ce3966614d90165a5c1afb8de4) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(fe16ee57) SHA1(405cca65759258193e982b252c359d998a3f4919) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(82004ca6) SHA1(e37c5f6fa248ba9d11c46f117b5722f3895e455f) )
ROM_END

ROM_START( svcpcbdd )
	ROM_REGION( 0x2000000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom.p1", 0x000000, 0x2000000, CRC(7db9c3bb) SHA1(ff60a425657eebdb799bcde2fe3fdf27dcfef11a) )

	NEO_SFIX_MT_512K

	ROM_REGION16_BE( 0x80000, "mainbios", 0 )
	/* this contains both an ASIA and JAPAN bios, HARDDIP3 on the PCB selects which to use */
	ROM_LOAD16_WORD_SWAP( "sp-4x.sp1", 0x00000, 0x80000, CRC(b4590283) SHA1(47047ed5b6062babc0a0bebcc30e4b3f021e115a) )

	ROM_REGION( 0x80000, "audiocrypt", 0 )
	ROM_LOAD( "269.m1", 0x00000, 0x80000, CRC(f6819d00) SHA1(d3bbe09df502464f104e53501708ac6e2c1832c6) )
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "269.v1", 0x000000, 0x800000, CRC(c659b34c) SHA1(1931e8111ef43946f68699f8707334c96f753a1e) )
	ROM_LOAD( "269.v2", 0x800000, 0x800000, CRC(dd903835) SHA1(e58d38950a7a8697bb22a1cc7a371ae6664ae8f9) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "269c.c1", 0x0000000, 0x2000000, CRC(1b608f9c) SHA1(4e70ad182da2ca18815bd3936efb04a06ebce01e) )
	ROM_LOAD( "269c.c2", 0x2000000, 0x2000000, CRC(5a95f294) SHA1(6123cc7b20b494076185d27c2ffea910e124b195) )
ROM_END

GAME( 1999, garoudd,    garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garoudd,    ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530) (Darksoft)", MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, garouhdd,   garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garouhdd,   ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530 ~ NGH-2530) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, garouhadd,  garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garoudd,    ROT0, "SNK", "Garou - Mark of the Wolves (NGH-2530) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99dd,    kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGM-2510) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99edd,   kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Earlier) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99hdd,   kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGH-2510) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX, crashes going into attract demo */
GAME( 1999, kof99kdd,   kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Korean release) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 2000, kof2000dd,  kof2000,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2000dd,  ROT0, "SNK", "The King of Fighters 2000 (NGM-2570 ~ NGH-2570) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 2003, svcpcbdd,   svcpcb,   neogeo_noslot,   dualbios, neogeo_state, init_svcpcbdd,   ROT0, "SNK Playmore", "SNK vs. Capcom - SVC Chaos (JAMMA PCB, set 1) (Darksoft)", MACHINE_MECHANICAL ) // not a clone of neogeo because it's NOT a neogeo cart.
