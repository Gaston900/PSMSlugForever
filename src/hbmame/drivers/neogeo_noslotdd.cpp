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

void neogeo_state::init_garodd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_sma_prot->garou_install_protection(m_maincpu,m_banked_cart);
    m_cmc_prot->neogeo_sfix_decrypt(spr_region, spr_region_size, fix_region, fix_region_size);
}


ROM_START( garoudd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "253dd.p1", 0x000000, 0x800000, CRC(e7c40dfa) SHA1(0d56298eb164e3e09c3b6048e2a7319239aea808) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_512K( "253d.s1", CRC(be2ba1a5) SHA1(e10dd25ba52ebe5caffc66135ba29f6624216b3d) )

	NEO_BIOS_AUDIO_256K( "253.m1", CRC(36a806be) SHA1(90fb44dc0c3fb57946a0f35716056abb84a0f191) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "253.v1", 0x000000, 0x400000, CRC(263e388c) SHA1(11f05feee170370c4bfc5053af79246a6e3de5dc) )
	ROM_LOAD( "253.v2", 0x400000, 0x400000, CRC(2c6bc7be) SHA1(c9c61054ce1a47bf1bf77a31117726b499df24a4) )
	ROM_LOAD( "253.v3", 0x800000, 0x400000, CRC(0425b27d) SHA1(986863c98fc3445487242dcf2ea75b075e7f33ee) )
	ROM_LOAD( "253.v4", 0xc00000, 0x400000, CRC(a54be8a9) SHA1(d7123e79b43e8adfaa5ecadbfcbeb6be890ec311) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD16_BYTE( "253d.c1", 0x0000000, 0x800000, CRC(497be3f2) SHA1(3b4e524ff185db326cdefe115851ce282272fb58) )
	ROM_LOAD16_BYTE( "253d.c2", 0x0000001, 0x800000, CRC(6a9e95ca) SHA1(d9730d2db58edfa660edab5bf0f7fc3ed058bccf) )
	ROM_LOAD16_BYTE( "253d.c3", 0x1000000, 0x800000, CRC(39373d2f) SHA1(8c0307150bc31001605efbe0e38ae74e1e466d5d) )
	ROM_LOAD16_BYTE( "253d.c4", 0x1000001, 0x800000, CRC(4de23f6c) SHA1(b40bce471fb1815037e4c3705f8238e659a13a82) )
	ROM_LOAD16_BYTE( "253d.c5", 0x2000000, 0x800000, CRC(16634ba5) SHA1(e51649efd039270139aa7292a28925e547b2be59) )
	ROM_LOAD16_BYTE( "253d.c6", 0x2000001, 0x800000, CRC(95671ffd) SHA1(803ebeb74fefe88b9aba53cbca103c0e9145abcb) )
	ROM_LOAD16_BYTE( "253d.c7", 0x3000000, 0x800000, CRC(e36ce77f) SHA1(71931559293182749ded13c52d8bac988a3a062f) )
	ROM_LOAD16_BYTE( "253d.c8", 0x3000001, 0x800000, CRC(ddbd1096) SHA1(634cfb61398b3f1b983f7f3966b53f4cc3a78671) )
ROM_END

GAME( 1999, garoudd,     garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garodd,    ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530) (Darksoft)", MACHINE_MECHANICAL )
