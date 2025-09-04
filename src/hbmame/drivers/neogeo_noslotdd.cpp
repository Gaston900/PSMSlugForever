// Proyecto Shadows Metal Slug Forever
// Copyright-Holders:Gaston90
// Thanks To The Collaborators Who Have Made A Great Contribution To The Project: Remikare and Robbert.


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

void neogeo_state::init_ct2k3sadd()
{
	init_neogeo();
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_bootleg_prot->decrypt_ct2k3sa(spr_region, spr_region_size, audiocpu_region,audio_region_size);
	m_bootleg_prot->patch_ct2k3sa(cpuregion, cpuregion_size);
}

void neogeo_state::init_ct2k3spdd()
{
	init_neogeo();
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_bootleg_prot->decrypt_ct2k3sp(spr_region, spr_region_size, audiocpu_region,audio_region_size, fix_region, fix_region_size);
	m_bootleg_prot->patch_cthd2003(m_maincpu,m_banked_cart, cpuregion, cpuregion_size);
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

/*************************************
    Game specific input definitions
 *************************************/
 
INPUT_PORTS_START( mjneogeodd )
	PORT_INCLUDE( neogeo )

	PORT_MODIFY("DSW")
	PORT_DIPNAME( 0x04, 0x00, DEF_STR( Controller ) ) PORT_DIPLOCATION("SW:3")
	PORT_DIPSETTING(    0x04, DEF_STR( Joystick ) )
	PORT_DIPSETTING(    0x00, "Mahjong Panel" )
INPUT_PORTS_END


ROM_START( 2020bbdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(d396c9cb) SHA1(47ba421d14d05b965a8d44e7475b227a208e5a07) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7015b8fc) SHA1(8c09bc3e6c62e0f7c9557c1e10c901be325bae7f) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(4cf466ec) SHA1(6a003b53c7a4af9d7529e2c10f27ffc4e58dcda5) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(5b021231) SHA1(3a751461f02f9b865686c6a403b38c7c82eda992) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(46546a10) SHA1(3e70485a8e5c97b3db449de8942633135f10dbb0) )
ROM_END

ROM_START( 2020bbadd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x080000, CRC(c59be3dd) SHA1(4fbd462c1c18e85a252c58b04b54fd3b82b46cb0) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7015b8fc) SHA1(8c09bc3e6c62e0f7c9557c1e10c901be325bae7f) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(4cf466ec) SHA1(6a003b53c7a4af9d7529e2c10f27ffc4e58dcda5) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(5b021231) SHA1(3a751461f02f9b865686c6a403b38c7c82eda992) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(46546a10) SHA1(3e70485a8e5c97b3db449de8942633135f10dbb0) )
ROM_END

ROM_START( 2020bbhdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x080000, CRC(12d048d7) SHA1(ee0d03a565b11ca3bee2d24f62ff46a85ef18d90) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7015b8fc) SHA1(8c09bc3e6c62e0f7c9557c1e10c901be325bae7f) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(4cf466ec) SHA1(6a003b53c7a4af9d7529e2c10f27ffc4e58dcda5) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(5b021231) SHA1(3a751461f02f9b865686c6a403b38c7c82eda992) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(46546a10) SHA1(3e70485a8e5c97b3db449de8942633135f10dbb0) )
ROM_END

ROM_START( 3countbdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(ffbdd928) SHA1(05b24655ca32723661adc5509b450824deb0c176) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(c362d484) SHA1(a3c029292572842feabe9aa8c3372628fb63978d) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(7eab59cb) SHA1(5ae4107457e091f73960bfba39b589ae36d51ca3) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(26f79226) SHA1(1cfd98233be1129a3610b2670587b584e982ddb0) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(fb5fc62d) SHA1(cac6855889b4bf7c4a174da3655205333a50e3be) )
ROM_END

ROM_START( alpham2dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0xa0000, CRC(5415d8c0) SHA1(ffd756203e6d646323966ed2f679bea6b08ba962) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(85ec9acf) SHA1(39a11974438ad36a2cc84307151b31474c3c5518) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(28dfe2cd) SHA1(1a1a99fb917c6c8db591e3be695ce03f843ee1df) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(e609b3ad) SHA1(fcc46f5bb0891e6b71a0d59ce8f781bbb16d8288) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(b134d93e) SHA1(cbde742ecba6ceb1b895f0fa4394bc4b2e9a145b) )
ROM_END

ROM_START( alpham2pdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promp", 0x000000, 0x100000, CRC(8c6d3c17) SHA1(aea233dcdaa78e212dd154f2c664d3fa31927f9b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromp", CRC(efc9ae2e) SHA1(a594826b0082fe5a13191673e8d9aa42517230f5) )

	NEO_BIOS_AUDIO_128K( "m1romp", CRC(5976b464) SHA1(ec824567ecc3579f6d86c9d9385710cbaeef16a3) )

	ROM_REGION( 0x380000, "ymsnd", 0 )
	ROM_LOAD( "vroma0p", 0x000000, 0x380000, CRC(9f08b300) SHA1(9156945c2a07d538c4212043b01ac5a09df451ea) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0p", 0x0000000, 0x400000, CRC(d61a52ec) SHA1(cd642e668d1851c2f9fe4ff41d436b73ce40caf7) )
ROM_END

ROM_START( androdundd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(be2b36b8) SHA1(f43338db54d49c58f5ea8df6d300c3775940a15b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6349de5d) SHA1(bcc44b9576d7bedd9a39294530bb66f707690c72) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(edd2acf4) SHA1(c4ee6ba834d54b9fc5a854dbc41a05877e090371) )

	ROM_REGION( 0x100000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x100000, CRC(ce43cb89) SHA1(47f82e077abb6efc6b1b0490412ae147d5d2acef) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x200000, CRC(00ffc911) SHA1(fce0fc1b2d6e25b9823e688a09625734f5a617b3) )
ROM_END

ROM_START( aodkdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(a3f82b1c) SHA1(9ae52f9e6048d23a7310b6077cec89867e14c54b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(96148d2b) SHA1(47725a8059346ebe5639bbdbf62a2ac8028756a9) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(5a52a9d1) SHA1(ef913a9a55d29d5dd3beab1ce6039d64ce9b1a5b) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(e8ab7c8a) SHA1(ec44609d05c3a90f16316ce1f3ef06a87decca9d) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(a07d45d0) SHA1(eafc4069eeb897c663d15caf00bd5f1661ecb485) )
ROM_END

ROM_START( aofdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(ca9f7a6d) SHA1(4d28ef86696f7e832510a66d3e8eb6c93b5b91a1) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(89903f39) SHA1(a04a0c244a5d5c7a595fcf649107969635a6a8b6) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0987e4bb) SHA1(8fae4b7fac09d46d4727928e609ed9d3711dbded) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(8bff8c7b) SHA1(b9f393953928615b1b3f28822eb4e458a8e54aba) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(624dab7f) SHA1(21b51b28136c8060a49957bde9e350c8fdef4d43) )
ROM_END

ROM_START( aof2dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(a3b1d021) SHA1(ee42f3ca4516226b0088d0303ed28e3ecdabcd71) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8b02638e) SHA1(aa4d28804ca602da776948b5f223ea89e427906b) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(f27e9d52) SHA1(dddae733d87ce7c88ad2580a8f64cb6ff9572e67) )

	ROM_REGION( 0x500000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x500000, CRC(d28ad285) SHA1(ad1e38b3426022bf5a58ced71410d3c2e4da1a7a) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(1609a135) SHA1(5820c0fcff70fdc1f6a861dda5c75203d2854542) )
ROM_END

ROM_START( aof2add )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(a7a76f05) SHA1(6b1ee737d9cc39a7c7ce426a63fedaed4669db9c) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8b02638e) SHA1(aa4d28804ca602da776948b5f223ea89e427906b) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(f27e9d52) SHA1(dddae733d87ce7c88ad2580a8f64cb6ff9572e67) )

	ROM_REGION( 0x500000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x500000, CRC(d28ad285) SHA1(ad1e38b3426022bf5a58ced71410d3c2e4da1a7a) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(1609a135) SHA1(5820c0fcff70fdc1f6a861dda5c75203d2854542) )
ROM_END

ROM_START( aof3dd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x300000, CRC(ad005661) SHA1(e30fd1bd6230671d9a83fef7e5a865896d69fb3a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(cc7fd344) SHA1(2c6846cf8ea61fb192ba181dbccb63594d572c0e) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(cb07b659) SHA1(940b379957c2987d7ab0443cb80c3ff58f6ba559) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(c8e41f27) SHA1(d8225928ac3bb10121f12b9b3b016f35c24d3b7c) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1c00000, CRC(f5492b63) SHA1(d8b9993244be0db8e82479f4d0aa63359779a45a) )
ROM_END

ROM_START( aof3kdd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x300000, CRC(c0760964) SHA1(e8df6a1dfd61d0bc533ea2e957e8e10d087a317b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(cc7fd344) SHA1(2c6846cf8ea61fb192ba181dbccb63594d572c0e) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(cb07b659) SHA1(940b379957c2987d7ab0443cb80c3ff58f6ba559) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(c8e41f27) SHA1(d8225928ac3bb10121f12b9b3b016f35c24d3b7c) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1c00000, CRC(f5492b63) SHA1(d8b9993244be0db8e82479f4d0aa63359779a45a) )
ROM_END

ROM_START( b2bdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(7687197d) SHA1(4bb9cb7819807f7a7e1f85f1c4faac4a2f8761e8) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(44e5f154) SHA1(b3f80051789e60e5d8c5df0408f1aba51616e92d) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(6da739ad) SHA1(cbf5f55c54b4ee00943e2a411eeee4e465ce9c34) )

	ROM_REGION( 0x100000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x100000, CRC(50feffb0) SHA1(00127dae0130889995bfa7560bc4b0662f74fba5) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(61b410e2) SHA1(c0d15ed197a45d86f73d4ec1c0f70c0e1dd31580) )
ROM_END

ROM_START( bakatonodd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(1c66b6fa) SHA1(6c50cc452971c46c763ae0b2def95792671a1798) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(f3ef4485) SHA1(c30bfceed7e669e4c97b0b3ec2e9f4271e5b6662) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(f1385b96) SHA1(e7e3d1484188a115e262511116aaf466b8b1f428) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(5c3b339b) SHA1(79e1c46c83ea5976525f157b6b7b797e5d3f7327) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(eec21a1f) SHA1(a44563ae95fee325de631b57af3f1101f202b818) )
ROM_END

ROM_START( bangbeadd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(08b6b530) SHA1(59554a0a869020f55493d6c589830a0a8a9ab11f) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(bb50fb2d) SHA1(7372939f328fb5e7d09c16985e09ae8c34702b0c) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(85668ee9) SHA1(7d3f51710cf90c097cd3faaeeef10ceb85cbb3e8) )

	ROM_REGION( 0x500000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x500000, CRC(0091e1f2) SHA1(c970a5312954af2452ab086dbf409362869e02a4) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(2a25e064) SHA1(a86a476ba3f91c885edde28268de8a9b69899c7c) )
ROM_END

ROM_START( bjourneydd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(6a2f6d4a) SHA1(b8ca548e56f1c7abcdce415ba7329e0cf698ee13) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(843c3624) SHA1(dbdf86c193b7c1d795f8c21f2c103c1d3e18abbe) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(8e1d4ab6) SHA1(deabc11ab81e7e68a3e041c03a127ae28d0d7264) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(75797499) SHA1(2a9af826de786f906aaf31506af8a0133af7f820) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(60366331) SHA1(8065f86a92a5b498fbe45d5b65eb8e199a756115) )
ROM_END

ROM_START( bjourneyhdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x100000, CRC(62cbe7b2) SHA1(f9a8fd98702c623ae793804ba50d09751e3fee4c) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(843c3624) SHA1(dbdf86c193b7c1d795f8c21f2c103c1d3e18abbe) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(8e1d4ab6) SHA1(deabc11ab81e7e68a3e041c03a127ae28d0d7264) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(75797499) SHA1(2a9af826de786f906aaf31506af8a0133af7f820) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(60366331) SHA1(8065f86a92a5b498fbe45d5b65eb8e199a756115) )
ROM_END

ROM_START( blazstardd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x300000, CRC(635b1487) SHA1(409cd3c54e183725c3dff0b6a6a0aebb531eb6a9) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(d56cb498) SHA1(420ce56431dc7f3f7de84fcbc8c0a17b5eab205e) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(d31a3aea) SHA1(e23abfeb23052f0358edcf2c83401025fe632511) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x800000, CRC(79544c10) SHA1(c2820b1c7b324deea5e2fdddec9e47daae88c9be) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(56d83a8c) SHA1(a6a7d87e711dd7cd754dacf34c510073d042b166) )
ROM_END

ROM_START( breakersdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(96dcd0e4) SHA1(24b61c07ea49d41c382e25c969afdbf8e041aae8) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(076fb64c) SHA1(c166038128d7004f69932141f83b320a35c2b4ca) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(3951a1c1) SHA1(1e6442a7ea82ada9503d71045dd93e12bd05254f) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x800000, CRC(c1cd8b16) SHA1(f407f0c59f90d7c86cd2aca9807c14dfcc814eff) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(ef488dd3) SHA1(52a2ab1d94e0447e587039a5aa6b7d558b4edc4c) )
ROM_END

ROM_START( breakrevdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(d72cf10d) SHA1(58076ec4b1d9b23e0f8e5a3971c9bcd2b807ea9c) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(e7660a5d) SHA1(1cd54964ba60b245ea57d9daf0e27b572b815d21) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(00f31c66) SHA1(8488598415c9b74bce00e05b31d96e3d1625c20d) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x800000, CRC(41d0e3c4) SHA1(d82c03e9ced3e4fd7a68020e2788f5720e65fede) )

	ROM_REGION( 0x1800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1800000, CRC(484b3489) SHA1(836aa9091de68644641867e276bbd5f767c23e1b) )
ROM_END

ROM_START( bstarsdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(c100b5f5) SHA1(4cea9f29ad67288c3eccfa4cf961ee9782e49165) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1a7fd0c6) SHA1(3fc701b7afddab369ddf9dedfbc5e1aaf80b8af3) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(4ecaa4ee) SHA1(50abfb8eed6cb4887393089f9ccc76f306ef69b5) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(1a4532fe) SHA1(a59ab1721d609006a91296ffa74f039836fe8381) )

	ROM_REGION( 0x100000, "ymsnd.deltat", 0 )
    ROM_LOAD( "vroma1", 0x000000, 0x080000, CRC(04a733d1) SHA1(84159368c0f6de2c3b8121227201cd3422455cf6) )
	
	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(71f8eb10) SHA1(779958dd7696bff57c58722252452341f39a5fa7) )
ROM_END

ROM_START( bstarshdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x080000, CRC(3bc7790e) SHA1(50b2fffb1278151bb4849fbe1f8cb23916019815) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1a7fd0c6) SHA1(3fc701b7afddab369ddf9dedfbc5e1aaf80b8af3) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(4ecaa4ee) SHA1(50abfb8eed6cb4887393089f9ccc76f306ef69b5) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(1a4532fe) SHA1(a59ab1721d609006a91296ffa74f039836fe8381) )

	ROM_REGION( 0x100000, "ymsnd.deltat", 0 )
    ROM_LOAD( "vroma1", 0x000000, 0x080000, CRC(04a733d1) SHA1(84159368c0f6de2c3b8121227201cd3422455cf6) )
	
	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(71f8eb10) SHA1(779958dd7696bff57c58722252452341f39a5fa7) )
ROM_END

ROM_START( bstars2dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(523567fd) SHA1(f1e81eb4678f586b214ea102cde6effea1b0f768) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(015c5c94) SHA1(f1c60cd3dc54986b39f630ef3bf48f68c68695dc) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(15c177a6) SHA1(3f4abed635102f9bc8b44809750828c82e79b44f) )

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(5e70d959) SHA1(cd6c271d2862903177db69222cbdc99f6b09df78) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(e8615dd1) SHA1(3fdb453acb537b7f6c14b14a85d01b904bba44db) )
ROM_END

ROM_START( burningfdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(4092c8db) SHA1(df194a4ad2c35e0e18bc053ff9284183444a4666) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6799ea0d) SHA1(ec75ef9dfdcb0b123574fc6d81ebaaadfba32fb5) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0c939ee2) SHA1(57d580d3279e66b9fe66bbcc68529d3384a926ff) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(1018b733) SHA1(26ef911a0afff0eb3b7bc528d9bb4aa77dfeb5a4) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(7d63dc96) SHA1(b0a308ce23df248d7a5ff9e6bf71425a47ceec82) )
ROM_END

ROM_START( burningfhdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x080000, CRC(ddffcbf4) SHA1(c646c4bbdb4e9b32df76c90f582ccd69fcc9f8e7) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6799ea0d) SHA1(ec75ef9dfdcb0b123574fc6d81ebaaadfba32fb5) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0c939ee2) SHA1(57d580d3279e66b9fe66bbcc68529d3384a926ff) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(1018b733) SHA1(26ef911a0afff0eb3b7bc528d9bb4aa77dfeb5a4) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(7d63dc96) SHA1(b0a308ce23df248d7a5ff9e6bf71425a47ceec82) )
ROM_END

ROM_START( burningfpdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promp", 0x000000, 0x100000, CRC(39673258) SHA1(5b924fef3b98c153830c2fcf1ce1ea78c8dc4ce6) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromp", CRC(f3d130e8) SHA1(2fdeb93f4bb2a60d391cac2822be41661b1e1795) )

	NEO_BIOS_AUDIO_128K( "m1romp", CRC(470dd5d4) SHA1(4291811b4aefe45261a1ae3631b6999fcd74fb3f) )

	ROM_REGION( 0x180000, "ymsnd", 0 )
	ROM_LOAD( "vroma0p", 0x000000, 0x180000, CRC(c2af2322) SHA1(d0959a1e7e7777ac22bb4529fab362bb0c01c66c) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0p", 0x0000000, 0x400000, CRC(0611bfd8) SHA1(4b57f182a4fa29eeadf0cbe05e6c1434a38872a6) )
ROM_END

ROM_START( burningfpadd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prompa", 0x000000, 0x100000, CRC(e4cbe72c) SHA1(0704ff3f6f6948d9917f73d076a55e2215f7559b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6799ea0d) SHA1(ec75ef9dfdcb0b123574fc6d81ebaaadfba32fb5) )

	NEO_BIOS_AUDIO_128K( "m1rompa", CRC(2b0c0415) SHA1(a5a0d5e3ea2ef77b6f5cd14f2907ab2f1aed76b7) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(1018b733) SHA1(26ef911a0afff0eb3b7bc528d9bb4aa77dfeb5a4) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0pa", 0x0000000, 0x400000, CRC(438dc555) SHA1(eae5df6a80724279c09976ee70dac97652863566) )
ROM_END

ROM_START( ct2k3sadd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(bc76c591) SHA1(8f17275f227f036aed082053b7e224db23f6b1d7) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(4e1f7eae) SHA1(3302ad290804272447ccd2e8edd3ce968f043db1) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(1ba996b1) SHA1(4711772b4f2061b96e310ee2b9489f6673a61c13) )
ROM_END

ROM_START( ct2k3spdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x500000, CRC(20e75892) SHA1(7fa8e02c29c6a4b11770e2f59dd318e972ac7edc) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_256K( "sroma", CRC(6c355ab4) SHA1(71ac2bcd3dbda8402baecc56dabc2297b148a900) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(1ba996b1) SHA1(4711772b4f2061b96e310ee2b9489f6673a61c13) )
ROM_END

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

/* Decrypted Darksoft */
GAME( 1993, 3countbdd,    3countb,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "3 Count Bout / Fire Suplex (NGM-043 ~ NGH-043) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, 2020bbdd,     2020bb,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK / Pallas", "2020 Super Baseball (set 1) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, 2020bbadd,    2020bb,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK / Pallas", "2020 Super Baseball (set 2) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, 2020bbhdd,    2020bb,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK / Pallas", "2020 Super Baseball (set 3) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, alpham2dd,    alpham2,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Alpha Mission II / ASO II - Last Guardian (NGM-007 ~ NGH-007) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, alpham2pdd,   alpham2,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Alpha Mission II / ASO II - Last Guardian (Prototype) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, androdundd,   androdun, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Andro Dunos (NGM-049 ~ NGH-049) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, aodkdd,       aodk,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "ADK / SNK", "Aggressors of Dark Kombat / Tsuukai GANGAN Koushinkyoku (ADM-008 ~ ADH-008) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, aofdd,        aof,      neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Art of Fighting / Ryuuko no Ken (NGM-044 ~ NGH-044) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, aof2dd,       aof2,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Art of Fighting 2 / Ryuuko no Ken 2 (NGM-056) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, aof2add,      aof2,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Art of Fighting 2 / Ryuuko no Ken 2 (NGH-056) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, aof3dd,       aof3,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Art of Fighting 3 - The Path of the Warrior / Art of Fighting - Ryuuko no Ken Gaiden (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, aof3kdd,      aof3,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Art of Fighting 3 - The Path of the Warrior (Korean release) (Darksoft)", MACHINE_MECHANICAL ) // no Japanese title / mode
GAME( 2000, b2bdd,        b2b,      neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Bang Bang Busters (2010 NCI release) (Darksoft)" , MACHINE_MECHANICAL )
GAME( 1991, bakatonodd,   bakatono, neogeo_mj,       mjneogeodd, neogeo_state, init_darksoft, ROT0, "Monolith Corp.", "Bakatonosama Mahjong Manyuuki (MOM-002 ~ MOH-002) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2000, bangbeadd,    bangbead, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Bang Bead (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, bjourneydd,   bjourney, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Alpha Denshi Co.", "Blue's Journey / Raguy (ALM-001)(ALH-001) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, bjourneyhdd,  bjourney, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Alpha Denshi Co.", "Blue's Journey / Raguy (ALH-001) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, blazstardd,   blazstar, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Yumekobo", "Blazing Star (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, breakersdd,   breakers, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Breakers (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, breakrevdd,   breakrev, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Breakers Revenge (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, bstarsdd,     bstars,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Baseball Stars Professional (NGM-002) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, bstarshdd,    bstars,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Baseball Stars Professional (NGH-002) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, bstars2dd,    bstars2,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Baseball Stars 2 (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, burningfdd,   burningf, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Burning Fight (NGM-018 ~ NGH-018) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, burningfhdd,  burningf, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Burning Fight (NGH-018)(US) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, burningfpdd,  burningf, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Burning Fight (Prototype) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, burningfpadd, burningf, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Burning Fight (Prototype, ver 23.3, 910326) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, ct2k3sadd,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_ct2k3sadd,  ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 Super Plus alternate (The King of Fighters 2001 bootleg) (Darksoft)", MACHINE_MECHANICAL ) /* Hack / Bootleg of kof2001 */
GAME( 2003, ct2k3spdd,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_ct2k3spdd,  ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 Super Plus (The King of Fighters 2001 bootleg) (Darksoft)", MACHINE_MECHANICAL ) /* Protected Hack / Bootleg of kof2001 */
GAME( 1999, garoudd,      garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garoudd,    ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530) (Darksoft) (Darksoft)", MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, garouhdd,     garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garouhdd,   ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530 ~ NGH-2530) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, garouhadd,    garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garoudd,    ROT0, "SNK", "Garou - Mark of the Wolves (NGH-2530) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99dd,      kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGM-2510) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99edd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Earlier) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99hdd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGH-2510) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX, crashes going into attract demo */
GAME( 1999, kof99kdd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Korean release) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 2000, kof2000dd,    kof2000,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2000dd,  ROT0, "SNK", "The King of Fighters 2000 (NGM-2570 ~ NGH-2570) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 2003, svcpcbdd,     svcpcb,   neogeo_noslot,   dualbios, neogeo_state, init_svcpcbdd,   ROT0, "SNK Playmore", "SNK vs. Capcom - SVC Chaos (JAMMA PCB, set 1) (Darksoft)", MACHINE_MECHANICAL ) // not a clone of neogeo because it's NOT a neogeo cart.
