// Proyecto Shadows Metal Slug Forever
// Copyright-Holders:Gaston90
// Thanks To The Collaborators Who Have Made A Great Contribution To The Project: Remikare and Robbert.


#include "includes/neogeo.h"


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

void neogeo_state::init_cthd2003dd()
{
	init_neogeo();
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_bootleg_prot->decrypt_cthd2003(spr_region, spr_region_size, audiocpu_region,audio_region_size, fix_region, fix_region_size);
	m_bootleg_prot->patch_cthd2003(m_maincpu,m_banked_cart, cpuregion, cpuregion_size);
}

void neogeo_state::init_fatfury2dd()
{
	init_neogeo();
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_fatfury2_prot->fatfury2_install_protection(m_maincpu,m_banked_cart);
}

void neogeo_state::init_garoudd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
    m_sma_prot->garou_install_protection(m_maincpu,m_banked_cart);
}

void neogeo_state::init_garouhdd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
    m_sma_prot->garouh_install_protection(m_maincpu,m_banked_cart);
}

void neogeo_state::init_jockeygpdd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
    m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region,audio_region_size);
    m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, JOCKEYGP_GFX_KEY);
	/* install some extra RAM */
	m_extra_ram = std::make_unique<uint16_t[]>(0x1000);
	m_maincpu->space(AS_PROGRAM).install_ram(0x200000, 0x201fff, m_extra_ram.get());
	save_pointer(NAME(m_extra_ram), 0x1000);
}

void neogeo_state::init_kf2k3pldd()
{
	init_neogeo();
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 5);
	m_bootleg_prot->kf2k3pl_px_decrypt(cpuregion, cpuregion_size);
	m_bootleg_prot->neogeo_bootleg_sx_decrypt(fix_region, fix_region_size,1);
	m_bootleg_prot->kf2k3pl_install_protection(m_maincpu, m_banked_cart, cpuregion, cpuregion_size);
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_kof98dd()
{
	init_neogeo();
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_kof98_prot->kof98_decrypt_68k(cpuregion, cpuregion_size);
	m_kof98_prot->install_kof98_protection(m_maincpu);
}

void neogeo_state::init_kof99dd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
    m_sma_prot->kof99_install_protection(m_maincpu, m_banked_cart);
}

void neogeo_state::init_kof2000dd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 2;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_sma_prot->kof2000_install_protection(m_maincpu, m_banked_cart);
}

void neogeo_state::init_kof2002dd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_kof2002_prot->kof2002_decrypt_68k(cpuregion, cpuregion_size);
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_samsh5spdd()
{
	init_neogeo();

    m_sprgen->m_fixed_layer_bank_type = 1;
    m_kof2002_prot->samsh5sp_decrypt_68k(cpuregion, cpuregion_size);
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_samsho5dd()
{
	init_neogeo();

    m_sprgen->m_fixed_layer_bank_type = 1;
    m_kof2002_prot->samsho5_decrypt_68k(cpuregion, cpuregion_size);
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_samsho5bdd()
{
	init_neogeo();

	m_bootleg_prot->samsho5b_px_decrypt(cpuregion, cpuregion_size);
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
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

/********************
  Decrypted Darksoft 
 *********************/

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

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(52e5d5a7) SHA1(d50f5bdc2b83232298e96059c380b41879506bdf) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(60366331) SHA1(8065f86a92a5b498fbe45d5b65eb8e199a756115) )
ROM_END

ROM_START( bjourneyhdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x100000, CRC(62cbe7b2) SHA1(f9a8fd98702c623ae793804ba50d09751e3fee4c) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(843c3624) SHA1(dbdf86c193b7c1d795f8c21f2c103c1d3e18abbe) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(8e1d4ab6) SHA1(deabc11ab81e7e68a3e041c03a127ae28d0d7264) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(52e5d5a7) SHA1(d50f5bdc2b83232298e96059c380b41879506bdf) )

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

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(8126a249) SHA1(1991a0f634d2882c5969686227c930de14dbef87) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(71f8eb10) SHA1(779958dd7696bff57c58722252452341f39a5fa7) )
ROM_END

ROM_START( bstarshdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x080000, CRC(3bc7790e) SHA1(50b2fffb1278151bb4849fbe1f8cb23916019815) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1a7fd0c6) SHA1(3fc701b7afddab369ddf9dedfbc5e1aaf80b8af3) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(4ecaa4ee) SHA1(50abfb8eed6cb4887393089f9ccc76f306ef69b5) )

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(8126a249) SHA1(1991a0f634d2882c5969686227c930de14dbef87) )

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

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(f6c7741e) SHA1(b53e47f10e12f8c67b2c1fa54b0feb3019ff9e21) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(7d63dc96) SHA1(b0a308ce23df248d7a5ff9e6bf71425a47ceec82) )
ROM_END

ROM_START( burningfhdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x080000, CRC(ddffcbf4) SHA1(c646c4bbdb4e9b32df76c90f582ccd69fcc9f8e7) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6799ea0d) SHA1(ec75ef9dfdcb0b123574fc6d81ebaaadfba32fb5) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0c939ee2) SHA1(57d580d3279e66b9fe66bbcc68529d3384a926ff) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(f6c7741e) SHA1(b53e47f10e12f8c67b2c1fa54b0feb3019ff9e21) )

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
	ROM_LOAD( "vroma0pa", 0x000000, 0x200000, CRC(1018b733) SHA1(26ef911a0afff0eb3b7bc528d9bb4aa77dfeb5a4) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0pa", 0x0000000, 0x400000, CRC(438dc555) SHA1(eae5df6a80724279c09976ee70dac97652863566) )
ROM_END

ROM_START( crswd2bldd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(b8559ece) SHA1(1aa976460f104cfff21ecae34a9192aac4ebc0a5) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(22e02ddd) SHA1(ebd834affc763cc5854abf1c6c42f43f3f3755fd) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(63e28343) SHA1(f46dbc2f1d6033b11047cca31a9a7d715dc69cb2) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(22d4b93b) SHA1(0515f2ee5d9a8ce424c80721e06f746ac6a543a8) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(733fe5e2) SHA1(46a1209e726b828c946962b9bd18b9c2a9fecf61) )
ROM_END

ROM_START( crsworddd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(e7f2553c) SHA1(8469ecb900477feed05ae3311fe9515019bbec2a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(74651f27) SHA1(bff7ff2429d2be82c1647abac2ee45b339b3b310) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(9504b2c6) SHA1(9ce8e681b9df6eacd0d23a36bad836bd5074233d) )

	ROM_REGION( 0x100000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x100000, CRC(61fedf65) SHA1(98f31d1e23bf7c1f7844e67f14707a704134042e) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(d7994f52) SHA1(da05865ede17d4c91cc5de75d7df126ccfb87e99) )
ROM_END

ROM_START( ct2k3sadd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promsa", 0x000000, 0x500000, CRC(bc76c591) SHA1(8f17275f227f036aed082053b7e224db23f6b1d7) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromsa", CRC(4e1f7eae) SHA1(3302ad290804272447ccd2e8edd3ce968f043db1) )

	NEO_BIOS_AUDIO_128K( "m1romsa", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0sa", 0x0000000, 0x4000000, CRC(1ba996b1) SHA1(4711772b4f2061b96e310ee2b9489f6673a61c13) )
ROM_END

ROM_START( ct2k3spdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x500000, CRC(20e75892) SHA1(7fa8e02c29c6a4b11770e2f59dd318e972ac7edc) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_256K( "sroma", CRC(6c355ab4) SHA1(71ac2bcd3dbda8402baecc56dabc2297b148a900) )

	NEO_BIOS_AUDIO_128K( "m1romsa", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0sa", 0x0000000, 0x4000000, CRC(1ba996b1) SHA1(4711772b4f2061b96e310ee2b9489f6673a61c13) )
ROM_END

ROM_START( cthd2003dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promc", 0x000000, 0x500000, CRC(d2313f91) SHA1(33c0300c093e8b87c8cd56823314bdf2485b5c8d) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromc", CRC(5ba29aab) SHA1(e7ea67268a10243693bff722e6fd2276ca540acf) )

	NEO_BIOS_AUDIO_128K( "m1romsa", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0sa", 0x0000000, 0x4000000, CRC(1ba996b1) SHA1(4711772b4f2061b96e310ee2b9489f6673a61c13) )
ROM_END

ROM_START( ctomadaydd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(2e067d0b) SHA1(85a750272f021105fb3d0644b39d8a80e1972e45) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(dc9eb372) SHA1(b8aa142243ba303799554479bfc88eb49260f3b1) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(80328a47) SHA1(34b6b1a81eab1cf38834b2eea55454ce1b6100e2) )

	ROM_REGION( 0x500000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x500000, CRC(2267cf15) SHA1(2e927a73752b5faff8a05a2ec7be248178bf0111) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(4f161357) SHA1(1d78cc846fb90ee7526b2a62f5c130a32bb54c7f) )
ROM_END

ROM_START( cyberlipdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(69a6b42d) SHA1(6e7cb089de83f1d22cc4a87db5b1a94bf76fb1e8) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(79a35264) SHA1(c2819a82adbe1f5e489496e0e03477863a5b7665) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(8be3a078) SHA1(054ec6a061fcc88df1ecbb0a01611a31f37a7709) )

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(e16a8638) SHA1(f70b8b7e039998ac6c71b2a2540649cbdea47154) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(067e11ff) SHA1(c246ff1b6575d654de190659416f1707e28071ef) )
ROM_END

ROM_START( diggermadd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(eda433d7) SHA1(abb14c66777ab0fe4ac76a402e253a49df7178d8) )

	NEO_SFIX_128K( "srom", CRC(9b3168f0) SHA1(9be8c625686a1482f7399e5a856cfe2fef25ec52) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(e777a234) SHA1(9f3974ac07859337bc0203f903c40ae3f60dc1fb) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x080000, CRC(ee15bda4) SHA1(fe2206728e6efd02d6302869a98b196eb19a17df) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x100000, CRC(29aa8013) SHA1(526aaaedb0cb234a0ea25e1b5fc8d5f153b16b1f) )
ROM_END

ROM_START( doubledrdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(90d6a562) SHA1(8debe5a5db1ab568fca98265ddab38b74c9dc4d0) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(bef995c5) SHA1(9c89adbdaa5c1f827632c701688563dac2e482a4) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(10b144de) SHA1(cf1ed0a447da68240c62bcfd76b1569803f6bf76) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(ba08bcf5) SHA1(08e32f0ce4d3829b6d888511b1137a779dba7b68) )

	ROM_REGION( 0xe00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xe00000, CRC(ea686c00) SHA1(491524aeec9e2ecd1ce3264878d7ec333857266f) )
ROM_END

ROM_START( dragonshdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(519db00c) SHA1(742b43694eb24f29aeced63998987ce1da8b5ecf) )

	NEO_SFIX_128K( "srom", CRC(706477a7) SHA1(8cbee7f6832e7edd2dc792ca330420a6a984b879) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(154803cc) SHA1(7e6591cd465cbb35d6d3446c5a83b46d30fafe95) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(9a4109e5) SHA1(ba59caac5f5a80fc52c507d8a47f322a380aa9a1) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(31600a99) SHA1(cd30b18f87b91ce2164479ed2d5ea19bab1000e1) )
ROM_END

ROM_START( eightmandd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(43344cb0) SHA1(29dfd699f35b0a74e20fedd6c9174c289f0ef6e0) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(a402202b) SHA1(75c44e1af459af155f5b892fd18706268dd5e602) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(9927034c) SHA1(205665361c5b2ab4f01ec480dd3c9b69db858d09) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(aaa8ff0c) SHA1(6d76b944d6cc738cc0d9d3287dabf5baf7527816) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(d5bf8bed) SHA1(382a7397f80c0cde7b3cb46a05842ac975cfb826) )
ROM_END

ROM_START( fatfurspdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x180000, CRC(f8361af0) SHA1(5d52d7ae636c7c1202b1ccd944747443b1cd0601) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(2df03197) SHA1(24083cfc97e720ac9e131c9fe37df57e27c49294) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(ccc5186e) SHA1(cf9091c523c182aebfb928c91640b2d72fd70123) )

	ROM_REGION( 0x500000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x500000, CRC(dfeebb9e) SHA1(2b52dbfc0826fe8142f3de264f8403f6a595f056) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xc00000, CRC(f633314c) SHA1(d2bbfa942d52de64d7cdd4bb209a984b0bd8fa09) )
ROM_END

ROM_START( fatfurspadd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x180000, CRC(605bab56) SHA1(88d69f5a8a2b05697805adab16745aff8acc9399) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(2df03197) SHA1(24083cfc97e720ac9e131c9fe37df57e27c49294) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(ccc5186e) SHA1(cf9091c523c182aebfb928c91640b2d72fd70123) )

	ROM_REGION( 0x500000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x500000, CRC(dfeebb9e) SHA1(2b52dbfc0826fe8142f3de264f8403f6a595f056) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xc00000, CRC(f633314c) SHA1(d2bbfa942d52de64d7cdd4bb209a984b0bd8fa09) )
ROM_END

ROM_START( fatfury1dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0xa0000, CRC(13f851ee) SHA1(9985c9fba7bc484e2cf6d1735550ee0702aa282c) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(3c3bdf8c) SHA1(2f3e5feed6c27850b2a0f6fae0b97041690e944c) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(5be10ffd) SHA1(90a5e6cbbc58a7883cd2a3a597180d631a466882) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(ad86f0cd) SHA1(ea7fe03a8e93cc4fba7b18ddbda74f1e562ba85b) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(69656d2a) SHA1(fefccfee8da24ab0153115d4bcb8d587d63c6696) )
ROM_END

ROM_START( fatfury2dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(ecfdbb69) SHA1(59e2f137c6eaf043df4ddae865a9159a10265c60) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(d7dbbf39) SHA1(29253e596f475ebd41a6e3bb53952e3a0ccd2eed) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(820b0ba7) SHA1(5708248d89446e49184eaadb52f7c61b2b6c13c5) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(d559fe79) SHA1(d7d426cd89003aa83e74c84a6e3e7170869f8e54) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(d26172c0) SHA1(bedc5871b264dd66d69dd9e8cf8162f834948492) )
ROM_END

ROM_START( fatfury3dd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x300000, CRC(fe1f6508) SHA1(e59acdfd1193d3983f18cce5d698dd5c70ad9546) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(0b33a800) SHA1(b7d2cc97da4f30ddebc7b801f5e1d17d2306b2db) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(fce72926) SHA1(a40c74f793900b8542f0b8383ce4bf46fca112d4) )

	ROM_REGION( 0xa00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xa00000, CRC(195f9afb) SHA1(167b2fdb8942ad204a442aa5d9fc6fe466bc659f) )

	ROM_REGION( 0x1400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1400000, CRC(94f2cf6a) SHA1(a2bee515426eeaec5344ebc71a8410d6cbbca56e) )
ROM_END

ROM_START( fbfrenzydd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(cdef6b19) SHA1(97482db0dffc6d625fb41fa38449c0a74d741a72) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8472ed44) SHA1(42e1a9671dddd090d2a634cff986f6c73ba08b70) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(f41b16b8) SHA1(f3e1cfc4cd2c5baece176f169906aa796367d303) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(14e641eb) SHA1(5041e00a0bc5af07d100ce4cc2686e81c92b0054) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(9d574aa4) SHA1(25505ebc44a0c0e60e4455c6f2926fe3d973859d) )
ROM_END

ROM_START( fightfevdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(2a104b50) SHA1(3eb663d3df7074e1cdf4c0e450a35c9cf55d8979) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(d62a72e9) SHA1(a23e4c4fd4ec11a7467ce41227c418b4dd1ef649) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0b7c4e65) SHA1(999a1e784de18db3f1332b30bc425836ea6970be) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(e46a0876) SHA1(acd71797ca742626b4292123cdb1820af2d1358c) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(8c8c3977) SHA1(80963b21bd1421575e0a12191c16dd61b5160903) )
ROM_END

ROM_START( fightfevadd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x0000000, 0x100000, CRC(da445cbe) SHA1(723032a892e1355ab9f825c67029c78552bffb6a) )

	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(d62a72e9) SHA1(a23e4c4fd4ec11a7467ce41227c418b4dd1ef649) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0b7c4e65) SHA1(999a1e784de18db3f1332b30bc425836ea6970be) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(e46a0876) SHA1(acd71797ca742626b4292123cdb1820af2d1358c) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(8c8c3977) SHA1(80963b21bd1421575e0a12191c16dd61b5160903) )
ROM_END

ROM_START( flipshotdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x0000000, 0x100000, CRC(95779094) SHA1(a985e033bc6f137fa65855d3eed245d66d5b244a) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6300185c) SHA1(cb2f1de085fde214f96a962b1c2fa285eb387d44) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(a9fe0144) SHA1(4cc076ecce9216a373f3dcd7ba28a03d6050e522) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(42ec743d) SHA1(f45b5167ebcbd59300f4e5b05448cd421654102a) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(7957f037) SHA1(88a5f5490a699b362d602a1fcd558ca9071550c1) )
ROM_END

ROM_START( froman2bdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x0000000, 0x080000, CRC(09675541) SHA1(6afb89d43e67f93e40f3877cbedfec9566e3ff0f) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(0e6a7c73) SHA1(31b1194524dcc80ec4d63bac088b6fb4909f496c) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(da4878cf) SHA1(ce13d18a4c5d01974df8542c67c4df00dbc6e7c1) )

	ROM_REGION( 0x100000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x100000, CRC(6f8ccddc) SHA1(696df2d0f416c2374b0eb7c858486054688c5bca) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(49bab7b8) SHA1(4b43f32508d4fbc2b232d3efc40f44720c67f08d) )
ROM_END

ROM_START( fswordsdd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proms", 0x0000000, 0x300000, CRC(77ace4a0) SHA1(45621baf8e1ae3d6a83e07fa73acec5fc65e7235) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(74ec7d9f) SHA1(d79c479838a7ca51735a44f91f1968ec5b3c6b91) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(8e6440eb) SHA1(e3f72150af4e326543b29df71cda27d73ec087c1) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(aab5a60a) SHA1(bc0a5687cd6b0f65693f0350ecfe1284c7c39f74) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1a00000, CRC(b3ad8f59) SHA1(c512d992b96d64254bb4aa7b41ddacdba8084341) )
ROM_END

ROM_START( galaxyfgdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x0000000, 0x200000, CRC(bef586ce) SHA1(429dbf66081c6489f3a53fdccf1281ed6e77ca7a) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(72f8923e) SHA1(da908bffc2b5d8baa2002dbb5bfb3aa17d2472b7) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(8e9e3b10) SHA1(7c44d1dbd4f8d337c99e90361d1dab837df85e31) )

	ROM_REGION( 0x500000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x500000, CRC(f64c4d83) SHA1(888cac2e639e683c7528221144ef54f2b73340d8) )

	ROM_REGION( 0xe00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xe00000, CRC(7dd4b6b3) SHA1(8add843c797adb40a9c0ffd82663bb4fb78f8cdf) )
ROM_END

ROM_START( ganryudd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x0000000, 0x200000, CRC(8f212084) SHA1(2ffcfd74f095425e45e118b89b7c0f220a5228f0) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(a8dadec9) SHA1(e909764d0377705cde0cc0accfdaf9b520c1df02) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(30cc4099) SHA1(46453b7aac41855a92724a785372f8daf931d8d4) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(e5946733) SHA1(d5904a50465af03d6ff33399a98f3259721ca0b2) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(4bde5c82) SHA1(1794f4062589f3d20183c8ddc38cf3d97108a9bc) )
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
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(27dcb714) SHA1(6631ae008e1990f98d2b4c0e7ec8a8433d839d04) )
ROM_END

ROM_START( garoubldd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promb", 0x000000, 0x500000, CRC(0e8362cd) SHA1(ee8e6483d0246f0504e6cd02305548caf7418b54) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromb", CRC(0ded51da) SHA1(1c359ff1f1545c7641ab88a2708e0a6808a0e952) )

	NEO_BIOS_AUDIO_512K( "m1romb", CRC(7c51d002) SHA1(01ffba6cbc8da07804f7b21d8c71c39d64a1a4e2) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0b", 0x000000, 0x1000000, CRC(3ae16bd4) SHA1(51feed35155ffafd25b75be3c4d58a381c8c27ea) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0b", 0x0000000, 0x4000000, CRC(d65c0ee8) SHA1(c217358f139e472195eb099a95022946b683e286) )
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
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(27dcb714) SHA1(6631ae008e1990f98d2b4c0e7ec8a8433d839d04) )
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
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(27dcb714) SHA1(6631ae008e1990f98d2b4c0e7ec8a8433d839d04) )
ROM_END

ROM_START( garoupdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promp", 0x000000, 0x500000, CRC(3ffbd386) SHA1(c07356cb265f5c91cac2be813f1feb6b81c5d6d6) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromp", CRC(779989de) SHA1(8bd550857b60f8a907f6d39a4225ceffdd330307) )

	NEO_BIOS_AUDIO_256K( "m1romp", CRC(bbe464f7) SHA1(f5f8f3e48f5d453f45107085d6f4023bcd24c053) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0p", 0x000000, 0x1000000, CRC(5cf3e13c) SHA1(9a5c718a6f4310a97d0a28dfa957fcaf6397e9f7) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0p", 0x0000000, 0x4000000, CRC(d65c0ee8) SHA1(c217358f139e472195eb099a95022946b683e286) )
ROM_END

ROM_START( ghostlopdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(6033172e) SHA1(f57fb706aa8dd9e5f9e992a5d35c1799578b59f8) )

	NEO_SFIX_128K( "srom", CRC(83c24e81) SHA1(585ef209d8bfc23bdccc1f37d8b764eeedfedc1c) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(fd833b33) SHA1(ab6c218c42cba821654cbdae154efecb69f844f6) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(c603fce6) SHA1(5a866471d35895b2ae13cbd5d1cb41bf2e72e1b8) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(42270645) SHA1(fa52ea8b5ad060e0f1a8cb600b395706d0cab0fd) )
ROM_END

ROM_START( goalx3dd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(0e4620e1) SHA1(f605ab4d63f26f682b34b44cd029f0d87a47a07a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(c0eaad86) SHA1(99412093c9707d51817893971e73fb8469cdc9d0) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(cd758325) SHA1(b51eac634fc646c07210dff993018ad9ebabd3f9) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(ef214212) SHA1(3e05ccaa2d06decb18b379b96f900c0e6b39ce70) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xa00000, CRC(8838cc4b) SHA1(8390b3ae157cec699276ce5e65166b2f200656f2) )
ROM_END

ROM_START( gowcaizrdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(14503b2a) SHA1(b27f8711f291575036ea9935c775d1cae00276b3) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(2f8748a2) SHA1(5cc723c4284120473d63d8b0c1a3b3be74bdc324) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(78c851cb) SHA1(a9923c002e4e2171a564af45cff0958c5d57b275) )

	ROM_REGION( 0x500000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x500000, CRC(8608b27d) SHA1(a06c07801cd6449a3730b6162b5edaf6cf999e6c) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(dc7a29e5) SHA1(47278fa00e5f901f293e9ee3fba2a7a8f15aded3) )
ROM_END

ROM_START( gpilotsdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0xa0000, CRC(0c727844) SHA1(0ba118b57f3a46d47fd87c0c997c6743789d1a51) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(a6d83d53) SHA1(9a8c092f89521cc0b27a385aa72e29cbaca926c5) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(48409377) SHA1(0e212d2c76856a90b2c2fdff675239525972ac43) )

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(7ed5d77c) SHA1(005e470870fe66668ad788f160acf86d4ccc7701) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(b4391c3e) SHA1(ef54ba4eae1b4f477f7b7408a3d5d86cea6013a6) )
ROM_END

ROM_START( gpilotshdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0xa0000, CRC(920ad15e) SHA1(3396bd064c27c589e580df2a1ba1dceea39ed560) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(a6d83d53) SHA1(9a8c092f89521cc0b27a385aa72e29cbaca926c5) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(48409377) SHA1(0e212d2c76856a90b2c2fdff675239525972ac43) )

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(7ed5d77c) SHA1(005e470870fe66668ad788f160acf86d4ccc7701) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(b4391c3e) SHA1(ef54ba4eae1b4f477f7b7408a3d5d86cea6013a6) )
ROM_END

ROM_START( gururindd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(4cea8a49) SHA1(cea4a35db8de898e30eb40dd339b3cbe77ac0856) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(b119e1eb) SHA1(f63a68a71aea220d3d4475847652e2a1f68b2b6f) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(9e3c6328) SHA1(17e8479c258f28a01d2283be9e692ff7685898cc) )

	ROM_REGION( 0x080000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x080000, CRC(cf23afd0) SHA1(10f87014ee10613f92b04f482f449721a6379db7) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(ddfca34c) SHA1(5667e39a8b68b6521765ee23716ab78920c77665) )
ROM_END

ROM_START( ironcladd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(65849961) SHA1(2846081bb1451a209412159991bfac95d394fe3a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(372fe217) SHA1(493433e682f519bf647e1481c8bdd3a980830ffb) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(3a08bb63) SHA1(d8fbbf42a006ccafc3cd99808d28c82dbaac4590) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(8f30a215) SHA1(0ee866a468c4c3608d55df2b5cb9243c8016d77c) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(a44cab28) SHA1(b1842053aeaf439b8701e34588ad6fe925750771) )
ROM_END

ROM_START( ironcladod )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promo", 0x000000, 0x200000, CRC(590ca356) SHA1(be87d0a0d9c202aec7fc4204321282d0489dd1dc) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(372fe217) SHA1(493433e682f519bf647e1481c8bdd3a980830ffb) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(3a08bb63) SHA1(d8fbbf42a006ccafc3cd99808d28c82dbaac4590) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(8f30a215) SHA1(0ee866a468c4c3608d55df2b5cb9243c8016d77c) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(a44cab28) SHA1(b1842053aeaf439b8701e34588ad6fe925750771) )
ROM_END

ROM_START( irrmazedd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(6d536c6e) SHA1(87d66683304a6617da8af7dfdfcbf4a3ab63056a) )

	NEO_SFIX_128K( "srom", CRC(5d1ca640) SHA1(40a9668a1742a44597a07ce72273d17119815637) )

	ROM_REGION16_BE( 0x20000, "mainbios", 0 )
	// special BIOS with trackball support, we only have one Irritating Maze bios and that's Asian
	ROM_SYSTEM_BIOS( 0, "asia-sp1", "Asia MV1B 263" )
	ROM_LOAD16_WORD_SWAP_BIOS( 0, "236-bios.sp1", 0x00000, 0x020000, CRC(853e6b96) SHA1(de369cb4a7df147b55168fa7aaf0b98c753b735e) )
	ROM_SYSTEM_BIOS( 1, "japan", "Japan (hack?)" ) // from a 'refurbished' Japanese cabinet, had label of the arcade distributor rather than original sticker however, and looks like a hack of above Asia ROM
	ROM_LOAD16_WORD_SWAP_BIOS( 1, "236-bios_japan_hack.sp1", 0x00000, 0x020000, CRC(02bf4426) SHA1(f4aa64bfe0b93e5df07b4fe2e0f638d91c7f2e71) )
	// Universe BIOS 2.2 and later allow joystick play as a cheat
	NEOGEO_UNIBIOS(2)
	ROM_REGION( 0x30000, "audiocpu", 0 )
	ROM_LOAD( "m1rom", 0x00000, 0x20000, CRC(880a1abd) SHA1(905afa157aba700e798243b842792e50729b19a0) )
	ROM_RELOAD( 0x10000, 0x20000 )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(faaadfba) SHA1(2dc75d39ce9e2a54bfba4ca960f7fc069d059995) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(ccbf61ef) SHA1(8cfb00d5252f98a33e5623857bdb0e26799c9171) )
ROM_END

ROM_START( janshindd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(fa818cbb) SHA1(afee2c897b766c84f13891fb52c574fb18df0951) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8285b25a) SHA1(d983640cda3e346e38469b4d3ec8048b116a7bb7) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(310467c7) SHA1(c529961195c9bdf5d1ce70a38ad129002d1f3b5f) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(f1947d2b) SHA1(955ff91ab24eb2a7ec51ff46c9f9f2ec060456b2) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(fa5fb991) SHA1(144dfe7992e25135f09ddb730c66c5559ed46da5) )
ROM_END

ROM_START( jockeygpdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(2fb7f388) SHA1(e3c9b03944b4c10cf5081caaf9c8be1f08c06493) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(bb0efa71) SHA1(203a572acdb48dc7b904a8f1e0766a13bfcaa3d3) )

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "m1rom", CRC(d163c690) SHA1(1dfd04d20c5985037f07cd01000d0b04f3a8f4f4) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(443eadba) SHA1(3def3c22f0e276bc4c2fc7ff70ce473c08b0d2df) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(7a603502) SHA1(83b38ce3df57a9ddbed7f1821297da1053a5c8e2) )
ROM_END

ROM_START( jockeygpadd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x100000, CRC(b8f35532) SHA1(b46c96677f1bfe324b678112e9c614a20c550d51) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(bb0efa71) SHA1(203a572acdb48dc7b904a8f1e0766a13bfcaa3d3) )

	NEO_BIOS_AUDIO_ENCRYPTED_512K( "m1rom", CRC(d163c690) SHA1(1dfd04d20c5985037f07cd01000d0b04f3a8f4f4) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(443eadba) SHA1(3def3c22f0e276bc4c2fc7ff70ce473c08b0d2df) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(7a603502) SHA1(83b38ce3df57a9ddbed7f1821297da1053a5c8e2) )
ROM_END

ROM_START( joyjoydd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(39c3478f) SHA1(06ebe54c9c4e14c5c31e770013d58b7162359ecc) )
	ROM_FILL(0x70b2,1,0x60) // force on story mode
	ROM_FILL(0x75bc,1,0x60) // force on demo mode

	NEO_SFIX_128K( "srom", CRC(6956d778) SHA1(e3757776d60dc07d8e07c9ca61b223b14732f860) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(5a4be5e8) SHA1(552f025ce0d51c25f42e1a81cf0d08376ca5475d) )

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(e189246a) SHA1(926e3d58258f25ec1085f120f524b2012b7fc9c5) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x100000, CRC(bdc8bcc9) SHA1(0bdc4b0a17281e1a1c8598de126ad26f357329c9) )
ROM_END

ROM_START( kabukikldd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(635d3e0d) SHA1(19c9e49af753ddfc1c8c8b1fd10011ef58495e10) )

	NEO_SFIX_128K( "srom", CRC(a3d68ee2) SHA1(386f6110a16967a72fbf788f9d968fddcdcd2889) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(91957ef6) SHA1(7b6907532a0e02ceb643623cbd689cf228776ed1) )

	ROM_REGION( 0x700000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x700000, CRC(5566aeed) SHA1(d892c4f944e69735473d2724775d8e839418c134) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(d0745bff) SHA1(135eb57536aef08db1083e54bfdd8a896d366cda) )
ROM_END

ROM_START( karnovrdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(8c86fd22) SHA1(8cf97c6fb9c5717167ccc54bf5856248ccaf32c6) )

	NEO_SFIX_128K( "srom", CRC(bae5d5e5) SHA1(aa69d9b235b781ec51f72a528fada9cb12e72cbc) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(030beae4) SHA1(ceb6ee6c09514504efacdbca7b280901e4c97084) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(0b7ea37a) SHA1(34e7d4f6db053674a7e8c8b2e3e398777d5b02e6) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xc00000, CRC(0add6634) SHA1(0a9259275eaf11cef1ced92d3cfaa92383f79383) )
ROM_END

ROM_START( kf2k2mpdd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prommp", 0x000000, 0x800000, CRC(542f47e3) SHA1(6d1a9660c48dfe709b89cbb7a6632bad5098ca16) )

	NEO_SFIX_128K( "srommp", CRC(29c0693e) SHA1(a852d15a8558b4a1cadf1ed9ef357d765ff88d35) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1c661a4b) SHA1(4e5aa862a0a182a806d538996ddc68d9f2dffaf7) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
ROM_END

ROM_START( kf2k2mp2dd )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prommp2", 0x000000, 0x600000, CRC(c4f378a5) SHA1(3f8a6436cb51d743f0889d3da3b5bea2578d2a10) )

	NEO_SFIX_128K( "srommp2", CRC(df4ce33b) SHA1(1287c84c16e17df7d5887af57fc6657da452d0ae) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1c661a4b) SHA1(4e5aa862a0a182a806d538996ddc68d9f2dffaf7) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
ROM_END

ROM_START( kf2k2pladd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prompla", 0x000000, 0x500000, CRC(fd81168f) SHA1(3a7510ab72123d62de606b9d88c343d0a551c3ae) )

	NEO_SFIX_128K( "srompla", CRC(1a3ed064) SHA1(9749bb55c750e6b65d651998c2649c5fb68db68e) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1c661a4b) SHA1(4e5aa862a0a182a806d538996ddc68d9f2dffaf7) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
ROM_END

ROM_START( kf2k2plsdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prompls", 0x000000, 0x500000, CRC(7e1bce72) SHA1(18b990c4630df6e860028f548f678d6418ebd553) )

	NEO_SFIX_128K( "srompls", CRC(595e0006) SHA1(ff086bdaa6f40e9ad963e1100a27f44618d684ed) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1c661a4b) SHA1(4e5aa862a0a182a806d538996ddc68d9f2dffaf7) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
ROM_END

ROM_START( kf2k3bladd )
	ROM_REGION( 0x700000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prombld", 0x000000, 0x700000, CRC(c255a3ed) SHA1(8063fd2b7d2ecfb273252ae0489a4defa2b1d399) )

	NEO_SFIX_128K( "srombl", CRC(482c48a5) SHA1(27e2f5295a9a838e112be28dafc111893a388a16) )

	NEO_BIOS_AUDIO_128K( "m1rombl", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0bl", 0x000000, 0x1000000, CRC(1d96154b) SHA1(1d4e262b0d30cee79a4edc83bb9706023c736668) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(5f7aee9e) SHA1(7e0225ef1601c55092d0f19dbbcbe0e42ba956d9) )
ROM_END

ROM_START( kf2k3upldd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promupl", 0x000000, 0x800000, CRC(4793b724) SHA1(e49b8496c55bdcf12a8bf0e65f249c68339cc568) )

	NEO_SFIX_128K( "sromupl", CRC(eb232b3a) SHA1(a875222f0e9a37e0a7bf839a21d2feb5e0ac7572) )

	NEO_BIOS_AUDIO_512K( "m1rom", CRC(cc8b54c0) SHA1(c0dabaad7a8e9e57774af8fa1009296af5c60005) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(2964f36e) SHA1(bfc52f81354eb57e27acb3b80fe1547b9e070293) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(5f7aee9e) SHA1(7e0225ef1601c55092d0f19dbbcbe0e42ba956d9) )
ROM_END

ROM_START( kf2k3pldd )
	ROM_REGION( 0x700000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prompl", 0x000000, 0x700000, CRC(565dcd0a) SHA1(54ea6ff155ed0bec3415bb6405faace365867bf2) )

	NEO_SFIX_512K( "srompl", CRC(71b538cf) SHA1(d230aa4bd6eb24a08faebfc948a62c4b31d84b41) )

	NEO_BIOS_AUDIO_512K( "m1rom", CRC(cc8b54c0) SHA1(c0dabaad7a8e9e57774af8fa1009296af5c60005) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(2964f36e) SHA1(bfc52f81354eb57e27acb3b80fe1547b9e070293) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(5f7aee9e) SHA1(7e0225ef1601c55092d0f19dbbcbe0e42ba956d9) )
ROM_END

ROM_START( kizunadd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(4b14a16f) SHA1(62031cc67ecdc13cc2ee28d01cfc2ea6b70793ea) )

	NEO_SFIX_128K( "srom", CRC(efdc72d7) SHA1(be37cbf1852e2e4c907cc799b754b538544b6703) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1b096820) SHA1(72852e78c620038f8dafde5e54e02e418c31be9c) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x800000, CRC(c6263572) SHA1(cc9d2d77a3ef22426a2806fa55949377c2aa43b2) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1c00000, CRC(e3d61c41) SHA1(d5d60d045b5c8adec693153951ef68c83cde1755) )
ROM_END

ROM_START( kof2000dd )
	ROM_REGION( 0x900000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x900000, CRC(396aeed7) SHA1(0f0bad158b10855c32369d4ca6e5504ea4b611b6) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_512K( "srom.s1", CRC(38901d4d) SHA1(c7684f66ab4ed577094da6ae143477c9df28d1fe) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(d404db70) SHA1(8cd1f3e140a9a367de23544e76371b0491287909) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(fe16ee57) SHA1(405cca65759258193e982b252c359d998a3f4919) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(c9c836ca) SHA1(6794120f12d27bf7573a6ac4c314a67bd67beab0) )
ROM_END

ROM_START( kof2000ndd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promn", 0x000000, 0x500000, CRC(7d5dfdf9) SHA1(9ec4a2ee08f175eb8badbf2728f69a5d8643c2fd) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_512K( "srom.s1", CRC(38901d4d) SHA1(c7684f66ab4ed577094da6ae143477c9df28d1fe) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(d404db70) SHA1(8cd1f3e140a9a367de23544e76371b0491287909) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(fe16ee57) SHA1(405cca65759258193e982b252c359d998a3f4919) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(c9c836ca) SHA1(6794120f12d27bf7573a6ac4c314a67bd67beab0) )
ROM_END

ROM_START( kof2001dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(4707c379) SHA1(9aec323d432a9343f46fdf3d0fd52768f31ed25a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6d209796) SHA1(95fdb865e47d37916573ba12e8ba4a4aaece1cba) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(4bcc537b) SHA1(9fcf1342bcd53d5eec12c46ee41a51bf543256c2) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(d13bcc44) SHA1(dbbd421a35014e3fdb863a709a30ccf55ce489c8) )
ROM_END

ROM_START( kof2001hdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x500000, CRC(9e3dcf93) SHA1(acfd3cef0bd4af15f79e50d2b8b7326796cfc11e) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6d209796) SHA1(95fdb865e47d37916573ba12e8ba4a4aaece1cba) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(4bcc537b) SHA1(9fcf1342bcd53d5eec12c46ee41a51bf543256c2) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(d13bcc44) SHA1(dbbd421a35014e3fdb863a709a30ccf55ce489c8) )
ROM_END

ROM_START( kof2002dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(3c393c7b) SHA1(9ed4e986b3d38ef88c9b80357d3a079978d04e3f) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(e0eaaba3) SHA1(831b642da9fe7617498cdb1c86475b3b3d3043bc) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1c661a4b) SHA1(4e5aa862a0a182a806d538996ddc68d9f2dffaf7) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
ROM_END

ROM_START( kof2002bdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promb", 0x000000, 0x500000, CRC(63f5be1c) SHA1(ed14787b8043a00a66d2e05dae0eb15468d902f7) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(e0eaaba3) SHA1(831b642da9fe7617498cdb1c86475b3b3d3043bc) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1c661a4b) SHA1(4e5aa862a0a182a806d538996ddc68d9f2dffaf7) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
ROM_END

ROM_START( kof2003dd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x800000, CRC(57a1981d) SHA1(0bc21c09c127e9abb3b03924166c0065ddec2057) )
    ROM_DEFAULT_BIOS("console_mode")

    NEO_SFIX_128K( "srom", CRC(7c7829aa) SHA1(22f8d38d1d0891295d0593741d9477fbe6b4f48c) )

    NEO_BIOS_AUDIO_512K( "m1rom", CRC(cc8b54c0) SHA1(c0dabaad7a8e9e57774af8fa1009296af5c60005) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(2964f36e) SHA1(bfc52f81354eb57e27acb3b80fe1547b9e070293) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(5f7aee9e) SHA1(7e0225ef1601c55092d0f19dbbcbe0e42ba956d9) )
ROM_END

ROM_START( kof10thdd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promt", 0x000000, 0x800000, CRC(30c82f4c) SHA1(d02e6fa14af6fd4aff0349fcb3d275d9226ccbe7) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromt", CRC(3c757cb1) SHA1(fea798902c59c125c8d31f42d52aa22caa31fc7b) )

	NEO_BIOS_AUDIO_128K( "m1romt", CRC(f6fab859) SHA1(0184aa1394b9f9946d610278b53b846020dd88dc) )
	
	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0t", 0x0000000, 0x4000000, CRC(30265a0a) SHA1(9153e04a7e1d56e85378bdc381e69093637134a6) )
ROM_END

ROM_START( kf10thepdd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promtp", 0x000000, 0x800000, CRC(3e6ead94) SHA1(f8874a69ea0809a899f90d8f359fb31ae5dc4e5d) )
    ROM_DEFAULT_BIOS("console_mode")

    NEO_SFIX_128K( "sromtp", CRC(7f930e3c) SHA1(5832e5d6a3c7c6956a0fbc37881cd3c209e6d68f) )

    NEO_BIOS_AUDIO_128K( "m1romtp", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0t", 0x0000000, 0x4000000, CRC(30265a0a) SHA1(9153e04a7e1d56e85378bdc381e69093637134a6) )
ROM_END

ROM_START( kf2k5unidd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promu", 0x000000, 0x800000, CRC(acbe077a) SHA1(7d3b1ce4e06021f26dd1a7d97b03975f4ed17c24) )
    ROM_DEFAULT_BIOS("console_mode")

    NEO_SFIX_128K( "sromu", CRC(10de5d7c) SHA1(44f4f523a787cf3094923483b824d7795858aff6) )

    NEO_BIOS_AUDIO_128K( "m1romt", CRC(f6fab859) SHA1(0184aa1394b9f9946d610278b53b846020dd88dc) )
	
	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0t", 0x0000000, 0x4000000, CRC(30265a0a) SHA1(9153e04a7e1d56e85378bdc381e69093637134a6) )
ROM_END

ROM_START( kof2k4sedd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promse", 0x000000, 0x500000, CRC(cc5764d1) SHA1(73ed01fb0d671c8f25f8d1e86039afd6e0c26b5b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(a3c9b2d8) SHA1(1472d2cbd7bb73e84824ecf773924007e6117e77) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0se", 0x000000, 0x1000000, CRC(9e5f37b3) SHA1(ba53d702fe0af99561aaca953e8491b04840af9b) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0se", 0x0000000, 0x4000000, CRC(64ca7495) SHA1(e3bd5543b37c37b495fa0e19e3c281d836454cf8) )
ROM_END

ROM_START( kof94dd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(61aab4f0) SHA1(5b8b811ce0e76f3a899ff66d5c7b87f02046ccaf) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(825976c1) SHA1(cb6a70bdd95d449d25196ca269b621c362db6743) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(f6e77cf5) SHA1(292a3e3a4918ffe72bd1c41acb927b91844e035e) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(cc4d2f17) SHA1(85e58329f94e503dc3b1498759d2f48af0119a11) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(d4c9d701) SHA1(ed0893b744d4e69a2278c0b8cb951718eca867b0) )
ROM_END

ROM_START( kof95dd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(d2f37c67) SHA1(9f17a436c0618686e0417aa803cb11178a752f33) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(de716f8a) SHA1(f7386454a943ed5caf625f67ee1d0197b1c6fa13) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(6f2d7429) SHA1(6f8462e4f07af82a5ca3197895d5dcbb67bdaa61) )

	ROM_REGION( 0x900000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x900000, CRC(41442b1e) SHA1(7460f5815c374bdeac8b60045ae5d7f3e3e4d92d) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1a00000, CRC(2589a049) SHA1(46922d5dd9eca7ab569866806b0b909327a104ce) )
ROM_END

ROM_START( kof95hdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x200000, CRC(467a442f) SHA1(d58a5a0b0ac253caf1186ee6a688b16154bf145d) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(de716f8a) SHA1(f7386454a943ed5caf625f67ee1d0197b1c6fa13) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(6f2d7429) SHA1(6f8462e4f07af82a5ca3197895d5dcbb67bdaa61) )

	ROM_REGION( 0x900000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x900000, CRC(41442b1e) SHA1(7460f5815c374bdeac8b60045ae5d7f3e3e4d92d) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1a00000, CRC(2589a049) SHA1(46922d5dd9eca7ab569866806b0b909327a104ce) )
ROM_END

ROM_START( kof96dd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x300000, CRC(a9932756) SHA1(a2a0cdacd407e8a736f82a03653228ecd5808936) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1254cbdb) SHA1(fce5cf42588298711a3633e9c9c1d4dcb723ac76) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(dabc427c) SHA1(b76722ed142ee7addceb4757424870dbd003e8b3) )

	ROM_REGION( 0xa00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xa00000, CRC(4f14a72b) SHA1(fb1105aa271ea14016f777017cf6079ff61e176f) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(da30fd29) SHA1(6910a8d7a0e2be7bcbe3e0395bd6c662c7e2378c) )
ROM_END

ROM_START( kof96hdd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x300000, CRC(c2967103) SHA1(01a1129673a568b31c8ba890c22c5fd2ddb6d483) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1254cbdb) SHA1(fce5cf42588298711a3633e9c9c1d4dcb723ac76) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(dabc427c) SHA1(b76722ed142ee7addceb4757424870dbd003e8b3) )

	ROM_REGION( 0xa00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xa00000, CRC(4f14a72b) SHA1(fb1105aa271ea14016f777017cf6079ff61e176f) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(da30fd29) SHA1(6910a8d7a0e2be7bcbe3e0395bd6c662c7e2378c) )
ROM_END

ROM_START( kof97dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(f2e4c21a) SHA1(7c2717bde454dd1d238f72455fac4b0379a0b559) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8514ecf5) SHA1(18d8e7feb51ea88816f1c786932a53655b0de6a0) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(35656a78) SHA1(587c497cde12d069664320a2c09f187666c0dcfe) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2800000, CRC(17027a61) SHA1(9e87b110641d9917cad66edb7415579c5ecc2bc5) )
ROM_END

ROM_START( kof97hdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x500000, CRC(257ba66d) SHA1(47a70ca5410426c98fdee2e6ee60d25c42597b43) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8514ecf5) SHA1(18d8e7feb51ea88816f1c786932a53655b0de6a0) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(35656a78) SHA1(587c497cde12d069664320a2c09f187666c0dcfe) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2800000, CRC(17027a61) SHA1(9e87b110641d9917cad66edb7415579c5ecc2bc5) )
ROM_END

ROM_START( kof97kdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(f2e4c21a) SHA1(7c2717bde454dd1d238f72455fac4b0379a0b559) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8514ecf5) SHA1(18d8e7feb51ea88816f1c786932a53655b0de6a0) )

	NEO_BIOS_AUDIO_128K( "m1romk", CRC(bbea9070) SHA1(c26c2e29fe90966dd574838be63f0037ea799aca) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(35656a78) SHA1(587c497cde12d069664320a2c09f187666c0dcfe) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2800000, CRC(17027a61) SHA1(9e87b110641d9917cad66edb7415579c5ecc2bc5) )
ROM_END

ROM_START( kof97plsdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promp", 0x000000, 0x500000, CRC(8440a271) SHA1(c971116174928b25a55cd1a3f861f2270328ddf6) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromp", CRC(73254270) SHA1(8d06305f9d8890da1327356272b88bdd0dc089f5) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(35656a78) SHA1(587c497cde12d069664320a2c09f187666c0dcfe) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2800000, CRC(17027a61) SHA1(9e87b110641d9917cad66edb7415579c5ecc2bc5) )
ROM_END

ROM_START( kof97orodd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promo", 0x000000, 0x500000, CRC(e371a18a) SHA1(da563f344b2cb145b4f4000d7fcb17358a7df522) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromo", CRC(cf6afb00) SHA1(aca3d9f571af3195a96bf044f353b3f0bc4cfc3a) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(35656a78) SHA1(587c497cde12d069664320a2c09f187666c0dcfe) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD( "crom0o", 0x0000000, 0x2800000, CRC(17027a61) SHA1(9e87b110641d9917cad66edb7415579c5ecc2bc5) )
ROM_END

ROM_START( kof98dd )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x600000, CRC(3c8eafb3) SHA1(f0fe1df5495665702f9c70a13f01a59c4235c34b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(4ef7016b) SHA1(4182235e963bd70d398a79abeb54ab4d62887c48) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(abeef163) SHA1(fa3442a508dc5bc38a97ea82f87b4940013cd52e) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(ad03f449) SHA1(edf750538bde609195370a132eb59d9d1f5b4a16) )
ROM_END

ROM_START( kof98hdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x500000, CRC(13baefae) SHA1(f288fa39735420ad80841da370c28ff47cb749e3) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) )

	NEO_BIOS_AUDIO_256K( "m1romh", CRC(4e7a6b1b) SHA1(b54d08f88713ed0271aa06f9f7c9c572ef555b1a) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(abeef163) SHA1(fa3442a508dc5bc38a97ea82f87b4940013cd52e) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(ad03f449) SHA1(edf750538bde609195370a132eb59d9d1f5b4a16) )
ROM_END

ROM_START( kof98kdd )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x600000, CRC(3c8eafb3) SHA1(f0fe1df5495665702f9c70a13f01a59c4235c34b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) )

	NEO_BIOS_AUDIO_256K( "m1romk", CRC(ce12da0c) SHA1(e7c01dae2852d543d1a58d55735239f6a5aa05a5) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(abeef163) SHA1(fa3442a508dc5bc38a97ea82f87b4940013cd52e) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(ad03f449) SHA1(edf750538bde609195370a132eb59d9d1f5b4a16) )
ROM_END

ROM_START( kof98kadd )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x600000, CRC(3c8eafb3) SHA1(f0fe1df5495665702f9c70a13f01a59c4235c34b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7f7b4805) SHA1(80ee6e5d0ece9c34ebca54b043a7cb33f9ff6b92) )

	NEO_BIOS_AUDIO_256K( "m1romka", CRC(ce9fb07c) SHA1(631d995f1291dd803fb069f3b25e7b9ed30d8649) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(abeef163) SHA1(fa3442a508dc5bc38a97ea82f87b4940013cd52e) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(ad03f449) SHA1(edf750538bde609195370a132eb59d9d1f5b4a16) )
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
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(07656356) SHA1(6be666a475926eea9116b63d932016959e2bcd81) )
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
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(07656356) SHA1(6be666a475926eea9116b63d932016959e2bcd81) )
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
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(07656356) SHA1(6be666a475926eea9116b63d932016959e2bcd81) )
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
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(07656356) SHA1(6be666a475926eea9116b63d932016959e2bcd81) )
ROM_END

ROM_START( kof99pdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promp", 0x000000, 0x500000, CRC(df9a5322) SHA1(3541456d21e10c7294353d9395cddbdd59d57c04) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromp", CRC(fb1498ed) SHA1(d40060b31b6f217a4abdf3b336439fcd7bd7aaef) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(5e74539c) SHA1(6f49a9343cbd026b2c6720ff3fa2e5b1f85e80da) )

	ROM_REGION( 0xe00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xe00000, CRC(1fc7c930) SHA1(2d043636eeee0530f552fababa0d7d61336d647d) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0p", 0x0000000, 0x4000000, CRC(f2a7d624) SHA1(f835a1bd53dbb29bfbca4eaae6b4f885a33ffb50) )
ROM_END

ROM_START( kogdd )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promg", 0x000000, 0x600000, CRC(9c3974c2) SHA1(ac5c3333e5484734c7a02626b2f9e7a9cabcf06f) )
    ROM_DEFAULT_BIOS("console_mode")

//	NEO_SFIX_128K( "srom", CRC(0bef69da) SHA1(80918586e694dce35c4dba796eb18abf6a070ebb) )
    NEO_SFIX_128K( "srom", CRC(ec690592) SHA1(a5af2880778a1904dd6c6006be769ea36b15dae3) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(45348747) SHA1(ed77cbae2b208d1177a9f5f6e8cd57070e90b65b) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(35656a78) SHA1(587c497cde12d069664320a2c09f187666c0dcfe) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD( "crom0g", 0x0000000, 0x2800000, CRC(ce4e2e73) SHA1(3d0e99fd4ee7cad6dc1a25696245d7bf1c714128) )
ROM_END

ROM_START( kotmdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0xa0000, CRC(3f7dcb04) SHA1(a336212bda389f5e65d8befdb27be67b4c6f06ea) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1a2eeeb3) SHA1(8d2b96d395020197bc59294b6b0c8d62b1d8d4dd) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(9da9ca10) SHA1(88b915827d529f39c365d3e41197d5461e07a085) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(11ee40e1) SHA1(ab0e4032e4f6cec72b83f8bb341c89533ed61472) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(ec499a1a) SHA1(ee9ed99e327f290bdfe4fb52e88767680ad60b8d) )
ROM_END

ROM_START( kotmhdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0xa0000, CRC(fd7c6538) SHA1(ec5ee9345c1fcb813f6ff087b07c3ce80c573905) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1a2eeeb3) SHA1(8d2b96d395020197bc59294b6b0c8d62b1d8d4dd) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(9da9ca10) SHA1(88b915827d529f39c365d3e41197d5461e07a085) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(11ee40e1) SHA1(ab0e4032e4f6cec72b83f8bb341c89533ed61472) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(ec499a1a) SHA1(ee9ed99e327f290bdfe4fb52e88767680ad60b8d) )
ROM_END

ROM_START( kotm2dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(e17961c9) SHA1(24e2b2e5fed3e2183a324ad48520c5ffc24ecf18) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(63ee053a) SHA1(7d4b92bd022708975b1470e8f24d1f5a712e1b94) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0c5b2ad5) SHA1(15eb5ea10fecdbdbcfd06225ae6d88bb239592e7) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(ef60c93e) SHA1(906022b4b5cc6b2fcd360b6b9e00d0a5cc713a9c) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x600000, CRC(cc91e7c2) SHA1(34973f912c74a92f25d64d26fce4424f89359bb6) )
ROM_END

ROM_START( kotm2add )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x100000, CRC(3296e2b3) SHA1(4452424a9c50ef07a6854cd8094894029ed56175) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(63ee053a) SHA1(7d4b92bd022708975b1470e8f24d1f5a712e1b94) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0c5b2ad5) SHA1(15eb5ea10fecdbdbcfd06225ae6d88bb239592e7) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(ef60c93e) SHA1(906022b4b5cc6b2fcd360b6b9e00d0a5cc713a9c) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x600000, CRC(cc91e7c2) SHA1(34973f912c74a92f25d64d26fce4424f89359bb6) )
ROM_END

ROM_START( kotm2pdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promp", 0x000000, 0x100000, CRC(1a066120) SHA1(9225ac7e732a23c0c2d3b05e126b0a8be9f88bb1) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(63ee053a) SHA1(7d4b92bd022708975b1470e8f24d1f5a712e1b94) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0c5b2ad5) SHA1(15eb5ea10fecdbdbcfd06225ae6d88bb239592e7) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(ef60c93e) SHA1(906022b4b5cc6b2fcd360b6b9e00d0a5cc713a9c) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD( "crom0p", 0x0000000, 0x600000, CRC(0cc7d1c5) SHA1(7bc8ee96ed1bab0f19c0329d5a665dd1e0659296) )
ROM_END

ROM_START( lans2004dd )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x600000, CRC(ec4eb4ae) SHA1(ca1cfa8a0a395fbe11d2749054684ee237f451d4) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8699c63a) SHA1(d1a0345bcb4e3f6044c93abd52ff6fe6280dc5ee) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(d0604ad1) SHA1(fae3cd52a177eadd5f5775ace957cc0f8301e65d) )

	ROM_REGION( 0xa00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xa00000, CRC(0c8b240d) SHA1(e9a74e30bdd5fefa62aaa40190554907717fb9b0) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x3000000, CRC(b06855da) SHA1(f1160713c3f975b2b62ea225e88dcc6b4030ba36) )
ROM_END

ROM_START( lastbladdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(5ded714e) SHA1(a8acfab571219b8d1fdff04fd58d74d34a8cc45d) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(95561412) SHA1(995de272f572fd08d909d3d0af4251b9957b3640) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(087628ea) SHA1(48dcf739bb16699af4ab8ed632b7dcb25e470e06) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(436e8345) SHA1(1008bead25169fe0011349aa570a2cf660d0661a) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2800000, CRC(517f347c) SHA1(491d6b7abc52e7ffa20aad22a55468b1fdd4977b) )
ROM_END

ROM_START( lastbladhdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x500000, CRC(c4e80eaa) SHA1(34f2e331c96ebc6707f526acfbf894aa6e4052e3) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(95561412) SHA1(995de272f572fd08d909d3d0af4251b9957b3640) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(087628ea) SHA1(48dcf739bb16699af4ab8ed632b7dcb25e470e06) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(436e8345) SHA1(1008bead25169fe0011349aa570a2cf660d0661a) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2800000, CRC(517f347c) SHA1(491d6b7abc52e7ffa20aad22a55468b1fdd4977b) )
ROM_END

ROM_START( lastsoldd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promd", 0x000000, 0x500000, CRC(d7b8ede4) SHA1(6c5cedab4460454206a55af4b3b3ea99bb308bdb) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(95561412) SHA1(995de272f572fd08d909d3d0af4251b9957b3640) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(087628ea) SHA1(48dcf739bb16699af4ab8ed632b7dcb25e470e06) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(436e8345) SHA1(1008bead25169fe0011349aa570a2cf660d0661a) )

	ROM_REGION( 0x2800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2800000, CRC(517f347c) SHA1(491d6b7abc52e7ffa20aad22a55468b1fdd4977b) )
ROM_END

ROM_START( lasthopedd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prompe", 0x000000, 0x100000, CRC(3776a88f) SHA1(ea8b669da06d7c6b5ff7fa97a195f56a9253a7a1) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_64K( "srompe", CRC(0c0ff9e6) SHA1(c87d1ea8731ac1e63ab960b8182dd1043bcc10bb) )

	NEO_BIOS_AUDIO_128K( "m1rompe", CRC(113c870f) SHA1(854425eb4be0d7fa088a6c3bf6078fdd011707f5) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0pe", 0x000000, 0x600000, CRC(15b988fe) SHA1(7322559c81e1a06986261787d2bd1b0dff9aab19) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0pe", 0x0000000, 0x1000000, CRC(c40d75e1) SHA1(c3cbfa9e4a23de4474e2255e77d0ba6315f96522) )
ROM_END

ROM_START( lastbld2dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(839893c2) SHA1(4008309137458a899696a975d6c4c38d9c14f47b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(c9cd2298) SHA1(a9a18b5347f9dbe29a2ccb63fd4c8fd19537bf8b) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(acf12d10) SHA1(6e6b98cc1fa44f24a5168877559b0055e6957b60) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(292764d2) SHA1(de6adf7d6d95ca4b7924aadde09d8720d2acea76) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x3000000, CRC(57b68e91) SHA1(f11f0adad894cf79d68b9debe4f18e5fd10970e6) )
ROM_END

ROM_START( lbowlingdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(a2de8445) SHA1(893d7ae72b4644123469de143fa35fac1cbcd61e) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(5fcdc0ed) SHA1(86415077e7adc3ba6153eeb4fb0c62cf36e903fa) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(d568c17d) SHA1(a2e318ed6ad1809c79f3f0853d75e0dd1a2f275c) )

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(1be11c1b) SHA1(a497ef21b894dc22f84ec1b4b44ba223cf57c077) )

	ROM_REGION( 0x100000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x100000, CRC(3830faca) SHA1(51cfbb91234627aa95334577c9e57decabdb65e0) )
ROM_END

ROM_START( legendosdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(9d563f19) SHA1(9bff7bf9fdcf81a0a6c4ce3e196097d4f05e67b6) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(bcd502f0) SHA1(a3400f52c037aa6a42e59e602cc24fa45fcbc951) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(6f2843f0) SHA1(975fb1598b87a2798fff05e951fca2e2e0329e79) )

	ROM_REGION( 0x100000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x100000, CRC(85065452) SHA1(7154b7c59b16c32753ac6b5790fb50b51ce30a20) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(5bccb448) SHA1(b246b6e6c257b9d7d2e3881cf7c6332a2e55f320) )
ROM_END

ROM_START( lresortdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(89c4ab97) SHA1(3a1817c427185ea1b44fe52f009c00b0a9007c85) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(5cef5cc6) SHA1(9ec305007bdb356e9f8f279beae5e2bcb3f2cf7b) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(cec19742) SHA1(ab6c6ba7737e68d2420a0617719c6d4c89039c45) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(30415bde) SHA1(47a9a38ab578496ee67e5f4a265b2cd410118b1f) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(89ddd148) SHA1(fa028064131cc3ad47dcdb9c997335e5cc647bb2) )
ROM_END

ROM_START( lresortpdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promp", 0x000000, 0x100000, CRC(a155c216) SHA1(59d61b3b1aba738cfbe62821ee0a778bce8693e2) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(5cef5cc6) SHA1(9ec305007bdb356e9f8f279beae5e2bcb3f2cf7b) )

	NEO_BIOS_AUDIO_128K( "m1romp", CRC(22122875) SHA1(540c21559163381467679f836cb068adaf526659) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(30415bde) SHA1(47a9a38ab578496ee67e5f4a265b2cd410118b1f) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0p", 0x0000000, 0x400000, CRC(b580f1a6) SHA1(71d20038fa273beacef0618f1d13766c0fc68bc4) )
ROM_END

ROM_START( magdrop2dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(7be82353) SHA1(08ab39f52b893591c13a7d7aa26b20ce86e9ddf5) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(2a4063a3) SHA1(0e09a7d88d85b1a2100888f4211960ea56ef978b) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(bddae628) SHA1(02c77e6aaaed43e39778bf83a3184e7c21db63d4) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(7e5e53e4) SHA1(72b063b2d4acaaf72a20d14ad5bfc90cb64d3fed) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(91a33ea0) SHA1(7741ee9a546586768439cef90405b22c801f7114) )
ROM_END

ROM_START( magdrop3dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(931e17fa) SHA1(4a95c4b79d0878485ce272e9f4c4f647bec0e070) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7399e68a) SHA1(b535ee56a0f0995f04674e676f6aa636ffad26aa) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(5beaf34e) SHA1(2905d26945932cddc2dd3a1dc5abba8aa3baee14) )

	ROM_REGION( 0x480000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x480000, CRC(830a92d0) SHA1(b5745575772cee4e96978dbf3d182072b1b4ea80) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(7be30aa2) SHA1(21f1f459d93cfb2acea6409179488140cc22155b) )
ROM_END

ROM_START( maglorddd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(bd0a492d) SHA1(d043d3710cf2b0d2b3798008e65e4c7c3ead1af3) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1c5369a2) SHA1(db0dba0a7dced6c9ca929c5abda491b05d84199c) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(26259f0f) SHA1(4f3e500093d61585048767dbd9fa09b3911a05d6) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(b4feaf72) SHA1(a09785576f449c6b30176eb8e931ce01afa37c8f) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(afb918ff) SHA1(9b0dbda90228bf2fb3fab16479cee0b1d9947949) )
ROM_END

ROM_START( maglordhdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x080000, CRC(599043c5) SHA1(43f234b0f89b72b4c6050c40d9daa5c4e96b94ce) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(1c5369a2) SHA1(db0dba0a7dced6c9ca929c5abda491b05d84199c) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(26259f0f) SHA1(4f3e500093d61585048767dbd9fa09b3911a05d6) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0h", 0x000000, 0x300000, CRC(5554e011) SHA1(73326df2971ef4e8ce7a5b50b74a179114cbfe91) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(afb918ff) SHA1(9b0dbda90228bf2fb3fab16479cee0b1d9947949) )
ROM_END

ROM_START( mahretsudd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(fc6f53db) SHA1(64a62ca4c8fb68954e06121399c9402278bd0467) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(2bd05a06) SHA1(876deadd4645373d82a503154eeddf18f440d743) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(c71fbb3b) SHA1(59c58665b53da61352359d191a0569de5dd1f4b3) )

	ROM_REGION( 0x380000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x380000, CRC(c40117d6) SHA1(603dc76a9805febf9bf3cb40710fb72235eaea30) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x200000, CRC(f4649ac0) SHA1(ae9670ae182ad3ddbd3c57814e092b7c8aa9c089) )
ROM_END

ROM_START( marukodqdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(c33ed21e) SHA1(bffff0d17e587e67672227e60c0ebd3f3a7193e6) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(f0b68780) SHA1(3f60950b14d121a5af3e6a8155ae9832ddc6ec46) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(0e22902e) SHA1(fb8466c342d4abd8bb4cad01c6ceab03f96cdad8) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(bf7c6eee) SHA1(d507499c615541e4331107774e318031d85f1dcf) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xa00000, CRC(0d1979c7) SHA1(7d05f57823af7e12421ed9eb08c592254962e647) )
ROM_END

ROM_START( matrimdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(673b9f1e) SHA1(fc614694460db03453c3c616dac7a2a42e70b460) )
    ROM_DEFAULT_BIOS("console_mode")

    NEO_SFIX_128K( "srom", CRC(aff2a3be) SHA1(57aba048573eacf8fbdd228f04a7f30da64cebe5) )

    NEO_BIOS_AUDIO_128K( "m1rom", CRC(d2f3742d) SHA1(dd42f8a301f07e079fbc2bfd23e788baa03ca72d) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(40d12c68) SHA1(e445a42ab722ae44cabe0d7403b3380caccaa868) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(b2ff3b39) SHA1(1b45c02fdd73f29b2ddee1e3021042c02552a9d0) )
ROM_END

ROM_START( miexchngdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(61be1810) SHA1(1ab0e11352ca05329c6e3f5657b60e4a227fcbfb) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(fe0c0c53) SHA1(54d56d4463db193e504658f4f6f4997a62ae3d95) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(de41301b) SHA1(59ce3836ac8f064d56a446c9374f05bcb40fcfd8) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(113fb898) SHA1(9168ba90c4aa969f69eb11ba3f4d76592d81e05a) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x600000, CRC(7e59882f) SHA1(16917f8fbf688b3e62f3fb9c88d46a0e07dc8041) )
ROM_END

ROM_START( minasandd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(c8381327) SHA1(c8f8be0ba276c6d12ef13d05af3cf83a2b924894) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(e5824baa) SHA1(8230ff7fe3cabeacecc762d90a084e893db84906) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(add5a226) SHA1(99995bef2584abbba16777bac52f55523f7aa97d) )

	ROM_REGION( 0x380000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x380000, CRC(9a3bf33b) SHA1(a73283e09606672f44e766f246ace54274b82d1d) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(89b63334) SHA1(b28894b747ede119926f9fba91b140b2ca657f5b) )
ROM_END

ROM_START( moshougidd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(7ba70e2d) SHA1(945f472cc3e7706f613c52df18de35c986d166e7) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(bfdc8309) SHA1(781337eab932a130b396a6c1080611d6f9c24c6e) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(a602c2c2) SHA1(19fd5d0379244c528b58343f6cbf78b4766fb23d) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(baa2b9a5) SHA1(914782b6c81d9a76ce02251575592b0648434ba3) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(c4ee1e25) SHA1(91642d1dea3c22e958b7c17dee6cc6f1f8710ac5) )
ROM_END

ROM_START( mutnatdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(6f1699c8) SHA1(87206f67a619dede7959230f9ff3701b8b78957a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(99419733) SHA1(b2524af8704941acc72282aa1d62fd4c93e3e822) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(b6683092) SHA1(623ec7ec2915fb077bf65b4a16c815e071c25259) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(fb573f10) SHA1(17c4f50e9a9f9d845f9c199a65f655e65d7b0f51) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(6363f2db) SHA1(3b8cf287b4eb31ce79cc60296f212a85b23f77d0) )
ROM_END

ROM_START( nam1975dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(cc9fc951) SHA1(92f4e6ddeeb825077d92dbb70b50afea985f15c0) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7988ba51) SHA1(bc2f661f381b06b34ac2fa215dd5689d3bf84832) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(ba874463) SHA1(a83514f4b20301f84a98699900e2593f1c1b8846) )

	ROM_REGION( 0x380000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x380000, CRC(6c3e3c4e) SHA1(99013865513620ddec81d19e3cff1c0d765a9843) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(f2cb94aa) SHA1(02541f550011c490338bac2ee05117e2b13d01b5) )
ROM_END

ROM_START( ncombatdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(b45fcfbf) SHA1(3872147dda2d1ba905d35f4571065d87b1958b4a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(d49afee8) SHA1(77615f12edf08ae8f1353f7a056a8f3a50d3ebdc) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(b5819863) SHA1(6f2309d51531052dbf7d712993c9e35649db0d84) )

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(00e898fe) SHA1(2ae6e8bdc663d9493e271762455f03a88aa7a4f9) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(79960f6f) SHA1(d4865565ba4b58b9649c1569bb304d34efbe476e) )
ROM_END

ROM_START( ncombathdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x080000, CRC(8e9f0add) SHA1(d0b908a86a58f2537eea73a431038f1cd74a5a2f) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(d49afee8) SHA1(77615f12edf08ae8f1353f7a056a8f3a50d3ebdc) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(b5819863) SHA1(6f2309d51531052dbf7d712993c9e35649db0d84) )

	ROM_REGION( 0x280000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x280000, CRC(00e898fe) SHA1(2ae6e8bdc663d9493e271762455f03a88aa7a4f9) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(79960f6f) SHA1(d4865565ba4b58b9649c1569bb304d34efbe476e) )
ROM_END

ROM_START( ncommanddd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(4e097c40) SHA1(43311a7ca14a14dcd4a99d8576a12e897b078643) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(db8f9c8e) SHA1(11cb82cf3c4d0fc2da5df0c26410a64808093610) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(6fcf07d3) SHA1(e9ecff4bfec1f5964bf06645f75d80d611b6231c) )

	ROM_REGION( 0x180000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x180000, CRC(21871447) SHA1(ed314846ad9944aa6b523ddd40c5e412db18c092) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(74dbd1df) SHA1(122f950ee1999982c9282131b8f91c88e1e14270) )
ROM_END

ROM_START( neobombedd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(a1a71d0d) SHA1(059284c84f61a825923d86d2f29c91baa2c439cd) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(4b3fa119) SHA1(41cb0909bfb017eb6f2c530cb92a423319ed7ab1) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(e81e780b) SHA1(c56c53984e0f92e180e850c60a75f550ee84917c) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(71030f5c) SHA1(6a6c9c87d480ba6d3614110de980a9f8cc141c5d) )

	ROM_REGION( 0x900000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x900000, CRC(b762e394) SHA1(e0d8142be520b1c425c5c6c868b8caf7840090e0) )
ROM_END

ROM_START( neocup98dd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(a1564aca) SHA1(2240612caf578da8c8d6bbd81173f188792e1251) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(9bddb697) SHA1(2f479bcd5a433201168792a578de3057252d649f) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(a701b276) SHA1(055550ebc650835bcf8ea4457b2c91bd73e21281) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(0a9054af) SHA1(e2555f2ca62cc72bec15996286216d8382227993) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(0e4a4c75) SHA1(bd2cdfbfed4274c7ca24b4b9592603bb45c80597) )
ROM_END

ROM_START( neodriftdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(e405551b) SHA1(6cbb32a05cc0444d9b746ab4472b88e26e880fe9) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(b76b61bc) SHA1(5fdb407d16ab9e33c4f26ee09ff70891ae1d2bd0) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(200045f1) SHA1(7a6cd1c8d4447ea260d7ff4520c676b8d685f2e4) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(1e2cb661) SHA1(0e6d3ed212d6d7f0bcedd70047d129e4659006c0) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(40f557c1) SHA1(da0e6f140b98ff4811a49fd5fb5daca4416c4cb4) )
ROM_END

ROM_START( neomrdodd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(334ea51e) SHA1(0a642f8565ec6e9587ed767bcf177f4677547162) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6aebafce) SHA1(5db03715fbed62f2ff3cef7f93606f30261c0362) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(b5b74a95) SHA1(7b01f3b87c247cc7472591f8cdcf0ae8065e31c6) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(4143c052) SHA1(561b19bc8811b80f2f42ffc0b5df27132696470a) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(b832b99d) SHA1(02b5a5267700a5133ee8d86e895eec14354ed3c8) )
ROM_END

ROM_START( ninjamasdd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x300000, CRC(76b419c1) SHA1(5b19d8bd9c02f09b036f8f7b6f3d372feba934d4) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8ff782f0) SHA1(90099c154357042ba658d4ef6abe4d9335bb7172) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(d00fb2af) SHA1(6bcaa52e1641cc24288e1f22f4dc98e8d8921b90) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(b66a9556) SHA1(18dfd8eaa5d81b41f7e7cd16a154f3d3a6c164e9) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(39a8be42) SHA1(c624fe120adb385aa3c05298b332f40a1f2f66e3) )
ROM_END

ROM_START( nitddd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(61361082) SHA1(441f3f41c1aa752c0e0a9a0b1d92711d9e636b85) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(dd3bf47c) SHA1(881271caee6508b8be51bf1b59c8f1e58e08e551) )

	NEO_BIOS_AUDIO_512K( "m1rom", CRC(6407c5e5) SHA1(d273e154cc905b63205a17a1a6d419cac3485a92) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(24b0480c) SHA1(d769e621be52a5cd2e2568891b5f95a48268e1e0) )
    ROM_FILL(0x50820,1,0x08)  // fix crackle when jumping

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(c5899c43) SHA1(b836fa19ecc026e17886d37ee9cead0fcfb8361f) )
ROM_END

ROM_START( nitdbldd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promb", 0x000000, 0x080000, CRC(1a05bd1b) SHA1(7bbddef842d50b0778711063af695b168a76ff61) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(dd3bf47c) SHA1(881271caee6508b8be51bf1b59c8f1e58e08e551) )

	NEO_BIOS_AUDIO_512K( "m1rom", CRC(6407c5e5) SHA1(d273e154cc905b63205a17a1a6d419cac3485a92) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(24b0480c) SHA1(d769e621be52a5cd2e2568891b5f95a48268e1e0) )
    ROM_FILL(0x50820,1,0x08)  // fix crackle when jumping

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0b", 0x0000000, 0x800000, CRC(bf0aa3cd) SHA1(6abd75fd02bf8cd26fc251f136516e5901d56b7e) )
ROM_END

ROM_START( overtopdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(f63e7281) SHA1(8e690ef0d5f5751b7e2e2f31b296597b07587d31) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(481d3ddc) SHA1(7b0df3fc5b19f282abfd0eb5a4c6ed836a536ece) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(fcab6191) SHA1(488b8310b0957f0012fe50f73641b606f6ac4a57) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(013d4ef9) SHA1(438a697c44525bdf78b54432c4f7217ab5667047) )

	ROM_REGION( 0x1400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1400000, CRC(a0099114) SHA1(133f09dd74a66817f42a5f0b3a0186bf586690c2) )
ROM_END

ROM_START( panicbomdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(adc356ad) SHA1(801e0a54b65d7a3500e6cef2d6bba40c6356dc1f) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(b876de7e) SHA1(910347d7657470da914fb0a6b0ea02891e13c081) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(3cdf5d88) SHA1(6d8365a946fbd0b7c7b896536322638d80f6a764) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(58cf9f43) SHA1(ec09dc75a84da9479554dc83ab7002414e8809a3) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x200000, CRC(b1f181be) SHA1(6ade15b48d6dc2254657fe4e1ea0a8c9c1d524a0) )
ROM_END

ROM_START( pbobbl2ndd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(9d6c0754) SHA1(95c70c2d51fc4de01e768e03cc800a850aaad5dc) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(0a3fee41) SHA1(0ab2120e462086be942efcf6ffb37f58ea966ca3) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(883097a9) SHA1(677bf9684c0c7977a9a3f0c1288e430040a53b49) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x800000, CRC(f64a1c80) SHA1(329089bbbb005e79f0ed1d1100588b6537bfc1a1) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xa00000, CRC(0b944136) SHA1(c3b4885a21bd27939b2face0052ab5ac4709cdea) )
ROM_END

ROM_START( pbobblendd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(6102ca14) SHA1(328429d11de5b327a0654ae0548da4d0025a2ae6) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(9caae538) SHA1(cf2d90a7c1a42107c0bb8b9a61397634286dbe0a) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(f424368a) SHA1(5e5bbcaeb82bed2ee17df08f005ca20ad1030723) )

	ROM_REGION( 0x380000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x380000, CRC(f864513f) SHA1(7dbf5306c97ab26b8520284a836fee47111a9b67) )

	ROM_REGION( 0x500000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x500000, CRC(169366c6) SHA1(5a8534d6abb99b1f0ff65533ea03496f28c45f04) )
ROM_END

ROM_START( pbobblenbdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promb", 0x000000, 0x080000, CRC(ac1e9ef3) SHA1(a2b125ee70869667431ab125bc29e768500802ad) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(9caae538) SHA1(cf2d90a7c1a42107c0bb8b9a61397634286dbe0a) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(f424368a) SHA1(5e5bbcaeb82bed2ee17df08f005ca20ad1030723) )

	ROM_REGION( 0x380000, "ymsnd", 0 )
	ROM_LOAD( "vroma0b", 0x000000, 0x380000, CRC(84a65b55) SHA1(b90540dcc1574106c027054b75193031c044cebd) )

	ROM_REGION( 0x500000, "sprites", 0 )
	ROM_LOAD( "crom0b", 0x0000000, 0x500000, CRC(cf288d14) SHA1(6f4ca1c5246644312876459ce02240446e03197a) )
ROM_END

ROM_START( pgoaldd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(07d63483) SHA1(d3178ed163da50b83dd77b337c3697867a5f54e5) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(002f3c88) SHA1(a8a5bbc5397c8ae9858e38997ebdc713b7b4f50a) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(958efdc8) SHA1(aacc6056b1ff48cde8f241a11a27473cfb4b4aa3) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(d0ae33d9) SHA1(cb21a91184d9d84ff25ca86c00dcadfc210272a8) )

	ROM_REGION( 0xc00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xc00000, CRC(24aac638) SHA1(5b8a99b39668f199f31752d2578c5f15560b1160) )
ROM_END

ROM_START( pnyaadd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(bf34e71c) SHA1(cfa7a2c7c41601a758414faf34e59583d7537363) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(88ffbb15) SHA1(e5b97c17167c44f6425006e939149c9fb4e6b1b2) )

	NEO_BIOS_AUDIO_512K( "m1rom", CRC(d58eaa8e) SHA1(4c4faf1da671a41b4d854790eb623a40cb35f256) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(1ac7db71) SHA1(98ef758181da1632f9ba4aed70e8bd1f338976d7) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(6395e6a3) SHA1(6fa7609e78518109ffecec5b50f52caca94d295e) )
ROM_END

ROM_START( pnyaaadd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x100000, CRC(112fe2c0) SHA1(01420e051f0bdbd4f68ce306a3738161b96f8ba8) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(88ffbb15) SHA1(e5b97c17167c44f6425006e939149c9fb4e6b1b2) )

	NEO_BIOS_AUDIO_512K( "m1rom", CRC(d58eaa8e) SHA1(4c4faf1da671a41b4d854790eb623a40cb35f256) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(1ac7db71) SHA1(98ef758181da1632f9ba4aed70e8bd1f338976d7) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(6395e6a3) SHA1(6fa7609e78518109ffecec5b50f52caca94d295e) )
ROM_END

ROM_START( popbouncdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(be96e44f) SHA1(43679da8664fbb491103a1108040ddf94d59fc2b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(b61cf595) SHA1(b14f8b78af7c634d41cf34d36b11b116e61f7342) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(d4c946dd) SHA1(6ca09040b5db8d89511d627954c783154d58ab01) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(edcb1beb) SHA1(62f086b9968b366b59276ee4ae3c32c4d76fc6ce) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(1055cbf2) SHA1(a796bdcec6574c44f82e5932c850bee4bd66e3ab) )
ROM_END

ROM_START( preisle2dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(e7d7692a) SHA1(6c053e2c1d0918f6f17d1090b6456f13ff01d8a5) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(666cabdc) SHA1(f37206ea84b3053f38b2263c1c228463899e425e) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(8efd4014) SHA1(5b73809b6e4e49264d281ef3e5004ac8a9de296d) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(2eebf135) SHA1(aed689fb1f7045d1752cfd0c301df5c3747b3791) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x3000000, CRC(3304b56d) SHA1(fdb6e5bf32a80d35fe6e0063f67ad632d2ef7c2c) )
ROM_END

ROM_START( pspikes2dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(105a408f) SHA1(2ee51defa1c24c66c63a6498ee542ac26de3cfbb) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(18082299) SHA1(efe93fabe6a76a5dc8cf12f255e571480afb40a0) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(b1c7911e) SHA1(27b298e7d50981331e17aa642e2e363ffac4333a) )

	ROM_REGION( 0x300000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x300000, CRC(4888fd2d) SHA1(cf65d7216cc3759603fba59c8c265a6f9e4a99ea) )

	ROM_REGION( 0x600000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x600000, CRC(fcf834b0) SHA1(d8eb87ed2b15bbc307090c19a2da46e12b6384b0) )
ROM_END

ROM_START( pulstardd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x300000, CRC(c5c0be46) SHA1(440c68be98f700183735f2b9833d44a2d9174f46) )

	NEO_SFIX_128K( "srom", CRC(c79fc2c8) SHA1(914c224fb3c461a68d7425cae724cf22bd5f985d) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(ff3df7c7) SHA1(59d2ef64f734f6026073b365300221909057a512) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x800000, CRC(d2321023) SHA1(db60c6b4a26a32e9668fa0d4bc67f6075e832110) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1c00000, CRC(f160dbbb) SHA1(fab7e302bd18a97f30624f6e2a007552e1f6ff17) )
ROM_END

ROM_START( puzzldprdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(afed5de2) SHA1(a5d82c6dbe687505e8c8d7339908da45cd379a0b) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(3b13a22f) SHA1(4506fc340d9658a50fa415676564f10bbfba2703) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

	ROM_REGION( 0x080000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x080000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x200000, CRC(8ba4d59d) SHA1(41838279523687d8e33d854f3db3519b7c358a2c) )
ROM_END

ROM_START( puzzledpdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promp", 0x000000, 0x080000, CRC(2b61415b) SHA1(0e3e4faf2fd6e63407425e1ac788003e75aeeb4f) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromp", CRC(cd19264f) SHA1(531be2305cd56d332fb7a53ab924214ade34a9e8) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(9c0291ea) SHA1(3fa67c62acba79be6b3a98cc1601e45569fa11ae) )

	ROM_REGION( 0x080000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x080000, CRC(debeb8fb) SHA1(49a3d3578c087f1a0050168571ef8d1b08c5dc05) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x200000, CRC(8ba4d59d) SHA1(41838279523687d8e33d854f3db3519b7c358a2c) )
ROM_END

ROM_START( quizdai2dd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(ed719dcf) SHA1(12baf2601e86c0e4358517b9fa1c55f2f5835f1d) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(164fd6e6) SHA1(dad35bedc33d502a5ae745a45a972af8d901b160) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(bb19995d) SHA1(ed458fad5a23c6bd0d099927d98c31e1e6562d1b) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(587ba62a) SHA1(7c755ddeaaa28b5f3375906a37731df67f34a425) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(e4bd00f1) SHA1(228872a806b84678fefe1681a7b3224d774183f7) )
ROM_END

ROM_START( quizdaisdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(c488fda3) SHA1(4cdf2f1837fffd720efef42f81f933bdf2ef1402) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(ac31818a) SHA1(93c8d67a93606a2e02f12ca4cab849dc3f3de286) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(2a2105e0) SHA1(26fc13556fda2dbeb7b5b035abd994e302dc7662) )

	ROM_REGION( 0x100000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x100000, CRC(a53e5bd3) SHA1(cf115c6478ce155d889e6a5acb962339e08e024b) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x200000, CRC(cb5936af) SHA1(fdfc074dc77482c40332921ff887bf794c7c01d8) )
ROM_END

ROM_START( quizdaiskdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x100000, CRC(a6f35eae) SHA1(edd3fd5ba8eae2231e2b0a6605fa00e5c6de094a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromk", CRC(53de938a) SHA1(5024fee3b245f8a069d7ecfa6f033b70ed1a5fce) )

	NEO_BIOS_AUDIO_128K( "m1romk", CRC(d67f53f9) SHA1(73a1bd175ae29dd957a907a046884f8715bd0a34) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0k", 0x000000, 0x200000, CRC(986f4af9) SHA1(9e15d2142ec5e5d076582dc1cecfd724b0924f54) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD( "crom0k", 0x0000000, 0x200000, CRC(868cf4f4) SHA1(b936df57dd21e0569f7fede3bab604c5e5a2e349) )
ROM_END

ROM_START( quizkofdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x100000, CRC(4440315e) SHA1(f4adba8e341d64a1f6280dfd98ebf6918c00608d) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(d7b86102) SHA1(09e1ca6451f3035ce476e3b045541646f860aad5) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(f5f44172) SHA1(eaaba1781622901b91bce9257be4e05f84df053b) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(1cb0cc24) SHA1(74f3367e77b3c64575c7ecea98b1e6ef377e3c78) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x800000, CRC(66272664) SHA1(66ac9a98a279fd74b83d904f95d962daafab47c4) )
ROM_END

ROM_START( quizkofkdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x100000, CRC(2589488e) SHA1(609f3095c1cf8b11335b56f23c5d955eebd66dd2) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromk", CRC(af72c30f) SHA1(f6a2c583f38295b7da2cbcf4b2c7ed3d3e01db4f) )

	NEO_BIOS_AUDIO_128K( "m1romk", CRC(4f157e9a) SHA1(8397bfdd5738914670ada7cd8c611c20ed1f74da) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0k", 0x000000, 0x600000, CRC(55b781a3) SHA1(443d3f88cd15e52fd322c78a6e5056529ed0468b) )

	ROM_REGION( 0x800000, "sprites", 0 )
	ROM_LOAD( "crom0k", 0x0000000, 0x800000, CRC(f7dcaec9) SHA1(a2b0b55e1f06a4479154f32cc286d9550f705c51) )
ROM_END

ROM_START( ragnagrdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(cf5684ef) SHA1(1669073ae6ebe545b862e7361c020e89948524eb) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7d402f9a) SHA1(59ec29d03e62e7a8bef689a124a9164f43b2ace1) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(17028bcf) SHA1(7a4e8f33ce9b41beac2152b8f6003f247699e2e1) )

	ROM_REGION( 0x800000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x800000, CRC(b82a1235) SHA1(d35f9a5e2b345d3d4d0c4c92efca8dc660c0bac7) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(7a3c6d64) SHA1(18145cd64b67dc36a64222d4e40e0655de11b982) )
ROM_END

ROM_START( rbff1dd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x300000, CRC(639dec1f) SHA1(2e63e8652cead5358d739e59b0a8d4d641faa8c1) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(b6bf5e08) SHA1(b527355c35ea097f3448676f2ffa65b8e56ae30c) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(653492a7) SHA1(39e511fb9ed5d2135dc8428a31d0baafb2ab36e0) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(2c1aafd8) SHA1(2a2be69232dbeb49d33d938321c7a271c6d5b6cc) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1c00000, CRC(10af3ab0) SHA1(f7b01d53f6e92fc9985d0058c3f5d95691d16db2) )
ROM_END

ROM_START( rbff1add )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x300000, CRC(54454d9d) SHA1(ea44cfa70b327a4b10ab8ae8b397039a1cd9a258) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(b6bf5e08) SHA1(b527355c35ea097f3448676f2ffa65b8e56ae30c) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(653492a7) SHA1(39e511fb9ed5d2135dc8428a31d0baafb2ab36e0) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(2c1aafd8) SHA1(2a2be69232dbeb49d33d938321c7a271c6d5b6cc) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1c00000, CRC(10af3ab0) SHA1(f7b01d53f6e92fc9985d0058c3f5d95691d16db2) )
ROM_END

ROM_START( rbff1kdd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x300000, CRC(63a18188) SHA1(f692ec04e817e453490f1b4870a288a84aad0e59) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(b6bf5e08) SHA1(b527355c35ea097f3448676f2ffa65b8e56ae30c) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(653492a7) SHA1(39e511fb9ed5d2135dc8428a31d0baafb2ab36e0) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(2c1aafd8) SHA1(2a2be69232dbeb49d33d938321c7a271c6d5b6cc) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1c00000, CRC(10af3ab0) SHA1(f7b01d53f6e92fc9985d0058c3f5d95691d16db2) )
ROM_END

ROM_START( rbff1kadd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x300000, CRC(63a18188) SHA1(f692ec04e817e453490f1b4870a288a84aad0e59) )
    ROM_LOAD16_WORD_SWAP( "promka", 0x000000, 0x080000, CRC(422093ed) SHA1(1b4cceec9b622d35f1bfdf01e314771b98483348) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(b6bf5e08) SHA1(b527355c35ea097f3448676f2ffa65b8e56ae30c) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(653492a7) SHA1(39e511fb9ed5d2135dc8428a31d0baafb2ab36e0) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(2c1aafd8) SHA1(2a2be69232dbeb49d33d938321c7a271c6d5b6cc) )

	ROM_REGION( 0x1c00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1c00000, CRC(10af3ab0) SHA1(f7b01d53f6e92fc9985d0058c3f5d95691d16db2) )
ROM_END

ROM_START( rbff2dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(e9381358) SHA1(c8dcb65afe887dd71c70a2f07972837968731272) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(da3b40de) SHA1(e6bf74e057ac6fe1f249a7547f13ba7fbc694561) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(ed482791) SHA1(1f54a45967cb7842c33aa24be322c9f33ff75ac3) )

	ROM_REGION( 0xe00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xe00000, CRC(b61bb6c5) SHA1(aee5865ae77a0b9be0bb8ce0f19cc8ffebe7120f) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x3000000, CRC(e3fcc8d8) SHA1(d787645127dddb56fd918f28772f20e45fec5138) )
ROM_END

ROM_START( rbff2hdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x500000, CRC(d1e7d08d) SHA1(f4a83e110ff19cce37334b5ecfbe95e4407b21ff) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(da3b40de) SHA1(e6bf74e057ac6fe1f249a7547f13ba7fbc694561) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(ed482791) SHA1(1f54a45967cb7842c33aa24be322c9f33ff75ac3) )

	ROM_REGION( 0xe00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xe00000, CRC(b61bb6c5) SHA1(aee5865ae77a0b9be0bb8ce0f19cc8ffebe7120f) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x3000000, CRC(e3fcc8d8) SHA1(d787645127dddb56fd918f28772f20e45fec5138) )
ROM_END

ROM_START( rbff2kdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x500000, CRC(20e1ca7f) SHA1(66bd41753f1549cdb1a8306d069d3d76bdce4761) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(da3b40de) SHA1(e6bf74e057ac6fe1f249a7547f13ba7fbc694561) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(ed482791) SHA1(1f54a45967cb7842c33aa24be322c9f33ff75ac3) )

	ROM_REGION( 0xe00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xe00000, CRC(b61bb6c5) SHA1(aee5865ae77a0b9be0bb8ce0f19cc8ffebe7120f) )

	ROM_REGION( 0x3000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x3000000, CRC(e3fcc8d8) SHA1(d787645127dddb56fd918f28772f20e45fec5138) )
ROM_END

ROM_START( rbffspecdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(2688ae88) SHA1(317297d96e9bea5dcbabc507dc891753201724c2) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7ecd6e8c) SHA1(465455afc4d83cbb118142be4671b2539ffafd79) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(3fee46bf) SHA1(e750f85233953853618fcdff980a4721af1710a3) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(a91dec92) SHA1(3822784150b84167a6efb9e3757f8d6cf02d8eb7) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(1b76b309) SHA1(0fdedc0fecd43ef088e5eb3f0ea11696445e6968) )
ROM_END

ROM_START( rbffspeckdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x500000, CRC(f2dff82a) SHA1(6c33054ed66da6e8cdb4ba5b6cdb524dd586649c) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(7ecd6e8c) SHA1(465455afc4d83cbb118142be4671b2539ffafd79) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(3fee46bf) SHA1(e750f85233953853618fcdff980a4721af1710a3) )

	ROM_REGION( 0xc00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xc00000, CRC(a91dec92) SHA1(3822784150b84167a6efb9e3757f8d6cf02d8eb7) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(1b76b309) SHA1(0fdedc0fecd43ef088e5eb3f0ea11696445e6968) )
ROM_END

ROM_START( ridherodd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(d4aaf597) SHA1(34d35b71adb5bd06f4f1b50ffd9c58ab9c440a84) )

	ROM_REGION( 0x2000, "mcu", 0 )
	ROM_LOAD( "rhcom.bin", 0x0000, 0x2000, CRC(e5cd6306) SHA1(f6bbb8ae562804d67e137290c765c3589fa334c0) ) // dumped from a prototype with external ROM, not 100% confirmed as being the same on a final, or other games (lbowling, trally)

	NEO_SFIX_128K( "srom", CRC(eb5189f0) SHA1(0239c342ea62e73140a2306052f226226461a478) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(92e7b4fe) SHA1(d240056cd632f92bdfaa5e0492c09aa9bd7b0471) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(542a1821) SHA1(5f4db6e415ae5e0599b28d49305d16ab5145b003) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x200000, CRC(424faa86) SHA1(50a828f29ab13683d178901fa9790e272550d87e) )
ROM_END

ROM_START( ridherohdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x080000, CRC(52445646) SHA1(647bb31f2f68453c1366cb6e2e867e37d1df7a54) )

	ROM_REGION( 0x2000, "mcu", 0 )
	ROM_LOAD( "rhcom.bin", 0x0000, 0x2000, CRC(e5cd6306) SHA1(f6bbb8ae562804d67e137290c765c3589fa334c0) ) // dumped from a prototype with external ROM, not 100% confirmed as being the same on a final, or other games (lbowling, trally)

	NEO_SFIX_128K( "srom", CRC(eb5189f0) SHA1(0239c342ea62e73140a2306052f226226461a478) )

	NEO_BIOS_AUDIO_256K( "m1rom", CRC(92e7b4fe) SHA1(d240056cd632f92bdfaa5e0492c09aa9bd7b0471) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(542a1821) SHA1(5f4db6e415ae5e0599b28d49305d16ab5145b003) )

	ROM_REGION( 0x200000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x200000, CRC(424faa86) SHA1(50a828f29ab13683d178901fa9790e272550d87e) )
ROM_END

ROM_START( roboarmydd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x080000, CRC(cd11cbd4) SHA1(23163e3da2f07e830a7f4a02aea1cb01a54ccbf3) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(ac0daa1b) SHA1(93bae4697dc403fce19422752a514326ccf66a91) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(35ec952d) SHA1(8aed30e26d7e2c70dbce5de752df416091066f7b) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(41648ed1) SHA1(b7ca7a4e851a9b49cd4a98a1ad48563e32700a52) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(068c3137) SHA1(5cec638be8ffd20bb1aa7b9d6bf037840b988b6e) )
ROM_END

ROM_START( roboarmyadd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x080000, CRC(27c773cb) SHA1(597ca73f142b1129cc7780540bb9cfacd47bc6ce) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(ac0daa1b) SHA1(93bae4697dc403fce19422752a514326ccf66a91) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(35ec952d) SHA1(8aed30e26d7e2c70dbce5de752df416091066f7b) )

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(41648ed1) SHA1(b7ca7a4e851a9b49cd4a98a1ad48563e32700a52) )

	ROM_REGION( 0x300000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x300000, CRC(068c3137) SHA1(5cec638be8ffd20bb1aa7b9d6bf037840b988b6e) )
ROM_END

ROM_START( rotddd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x800000, CRC(b8cc969d) SHA1(4f2205b4bdd32dd1522106ef4df10ac0eb1b852d) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(c155d4ff) SHA1(cc20d4e30004ca82da2ba075c084d294c94651d0) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(c5d36af9) SHA1(320739d0cfa6cc84455ae1f7b1f9cdab3c018933) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(2964f8d1) SHA1(1ddf77a928448560de417e7e277a090b9ee91023) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(1bde17b5) SHA1(a88a269c707586e40479a8fca19410f644d6adb0) )
ROM_END

ROM_START( rotdhdd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x300000, CRC(b26813c1) SHA1(c818597dd630bb2695efbcc61e235bc6ad273cea) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(c155d4ff) SHA1(cc20d4e30004ca82da2ba075c084d294c94651d0) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(c5d36af9) SHA1(320739d0cfa6cc84455ae1f7b1f9cdab3c018933) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(2964f8d1) SHA1(1ddf77a928448560de417e7e277a090b9ee91023) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(1bde17b5) SHA1(a88a269c707586e40479a8fca19410f644d6adb0) )
ROM_END

ROM_START( s1945pdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(1fedc918) SHA1(4fee71f6ab33281d1a47b0b1abe1d92cef39b109) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(121a4f94) SHA1(5f00f3c5eb6f95c16add2050157803a375bb333d) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(994b4487) SHA1(a4e645a3ababa48a8325980ff022e04a8b51b017) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(7ea05e1c) SHA1(b70587b30135b25bae2e6681014e6c64ec202ec1) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(64834a23) SHA1(f3fc9788c7e41120e8431d60d3d498691515f0a6) )
ROM_END

ROM_START( samsh5spdd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x800000, CRC(f5a77983) SHA1(fbc5fe5801c16ae443c6bf545a44aed068f39ad4) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(c297f973) SHA1(b31af6b51e7536b538cd7eb3542c631c6327e826) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(654e9236) SHA1(e13a1b4b73d43008565ee419c9714a220927d0bc) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(80369c31) SHA1(dba53b5669f14ebf4a40738c8664c72b72d460e0) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(c734c427) SHA1(522c776a7c06c6f3b246aad1e9103d9ebbfead14) )
ROM_END

ROM_START( samsh5sphdd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x800000, CRC(9ec77bc7) SHA1(d7507119f7a6dcac37d7514aa16d53b3159d8d47) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(c297f973) SHA1(b31af6b51e7536b538cd7eb3542c631c6327e826) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(654e9236) SHA1(e13a1b4b73d43008565ee419c9714a220927d0bc) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(80369c31) SHA1(dba53b5669f14ebf4a40738c8664c72b72d460e0) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(c734c427) SHA1(522c776a7c06c6f3b246aad1e9103d9ebbfead14) )
ROM_END

ROM_START( samsh5sphodd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promho", 0x000000, 0x800000, CRC(e5826906) SHA1(6b2319ccd5c5883d9529a21a40b36addbbab99db) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(c297f973) SHA1(b31af6b51e7536b538cd7eb3542c631c6327e826) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(654e9236) SHA1(e13a1b4b73d43008565ee419c9714a220927d0bc) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(80369c31) SHA1(dba53b5669f14ebf4a40738c8664c72b72d460e0) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(c734c427) SHA1(522c776a7c06c6f3b246aad1e9103d9ebbfead14) )
ROM_END

ROM_START( samshodd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(f3222b24) SHA1(a23c2ae466b720d50b6ac54a699774dc0fe79329) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(9142a4d3) SHA1(54088e99fcfd75fd0f94852890a56350066a05a3) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(95170640) SHA1(125c502db0693e8d11cef619b090081c14a9a300) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(73379dae) SHA1(33ad195156741e2173a7085f1f15519be0a6aca6) )

	ROM_REGION( 0xa00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0xa00000, CRC(e99e75c2) SHA1(4600126ac95999271633bdfc293fbc1090491214) )
ROM_END

ROM_START( samshohdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x180000, CRC(b69877fd) SHA1(095fd08129655f3e7a4879ba37c31c97eed7f3ea) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(9142a4d3) SHA1(54088e99fcfd75fd0f94852890a56350066a05a3) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(95170640) SHA1(125c502db0693e8d11cef619b090081c14a9a300) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(73379dae) SHA1(33ad195156741e2173a7085f1f15519be0a6aca6) )

	ROM_REGION( 0x900000, "sprites", 0 )
	ROM_LOAD( "crom0h", 0x0000000, 0x900000, CRC(b1276a26) SHA1(e7d1a1a748b6f85650db828c22e58356b942cd0a) )
ROM_END

ROM_START( samsho2dd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x200000, CRC(13049404) SHA1(075d904a3113754cc8b931e6b409a7b82a199249) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(64a5cd66) SHA1(12cdfb27bf9ccd5a8df6ddd4628ef7cf2c6d4964) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(56675098) SHA1(90429fc40d056d480d0e2bbefbc691d9fa260fc4) )

	ROM_REGION( 0x700000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x700000, CRC(7cfa47d1) SHA1(c8d0f278498117fbe2bb26983dfa6a83616e0a01) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(2c696498) SHA1(ee345e55afd9c3334e01c5d9193d44fb305de03f) )
ROM_END

ROM_START( samsho2kdd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x200000, CRC(4ec1997a) SHA1(bb01cd920f1d92eb67a3a625b0156a8df517c0e9) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromk", CRC(ff08f80b) SHA1(240c6a1c52edebb49cc99ea08484c6a2d61ebf84) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(56675098) SHA1(90429fc40d056d480d0e2bbefbc691d9fa260fc4) )

	ROM_REGION( 0x700000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x700000, CRC(7cfa47d1) SHA1(c8d0f278498117fbe2bb26983dfa6a83616e0a01) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(2c696498) SHA1(ee345e55afd9c3334e01c5d9193d44fb305de03f) )
ROM_END

ROM_START( samsho2kadd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promka", 0x000000, 0x200000, CRC(c7ef3c2b) SHA1(c7057b02b598404394ee4d36de379d9aea638f6a) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromk", CRC(ff08f80b) SHA1(240c6a1c52edebb49cc99ea08484c6a2d61ebf84) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(56675098) SHA1(90429fc40d056d480d0e2bbefbc691d9fa260fc4) )

	ROM_REGION( 0x700000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x700000, CRC(7cfa47d1) SHA1(c8d0f278498117fbe2bb26983dfa6a83616e0a01) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(2c696498) SHA1(ee345e55afd9c3334e01c5d9193d44fb305de03f) )
ROM_END

ROM_START( samsho3dd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x300000, CRC(3caa76b9) SHA1(62fa30b66e1e69f66fc271d78bd6f8ae59af39d6) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(74ec7d9f) SHA1(d79c479838a7ca51735a44f91f1968ec5b3c6b91) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(8e6440eb) SHA1(e3f72150af4e326543b29df71cda27d73ec087c1) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(aab5a60a) SHA1(bc0a5687cd6b0f65693f0350ecfe1284c7c39f74) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1a00000, CRC(b3ad8f59) SHA1(c512d992b96d64254bb4aa7b41ddacdba8084341) )
ROM_END

ROM_START( samsho3hdd )
	ROM_REGION( 0x300000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x300000, CRC(cd2f768a) SHA1(4c375205bdac0f4cead3f8b97ac9c976ec7c383f) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(74ec7d9f) SHA1(d79c479838a7ca51735a44f91f1968ec5b3c6b91) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(8e6440eb) SHA1(e3f72150af4e326543b29df71cda27d73ec087c1) )

	ROM_REGION( 0x600000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x600000, CRC(aab5a60a) SHA1(bc0a5687cd6b0f65693f0350ecfe1284c7c39f74) )

	ROM_REGION( 0x1a00000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x1a00000, CRC(b3ad8f59) SHA1(c512d992b96d64254bb4aa7b41ddacdba8084341) )
ROM_END

ROM_START( samsho4dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(4b3989f3) SHA1(a4159baf4e9203e72a4256e553e3ddfd18c0167c) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(8d3d3bf9) SHA1(9975ed9b458bdd14e23451d2534153f68a5e4e6c) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(7615bc1b) SHA1(b936f7b341f6fe0921b4c41049734684583e3596) )

	ROM_REGION( 0xa00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xa00000, CRC(35632afa) SHA1(36f29de056583dd9acca35f39281a4c1ef0adb32) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(f5cfe108) SHA1(0ed88a109785f0d48cc61b32d0b62a4795407fd8) )
ROM_END

ROM_START( samsho4kdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promk", 0x000000, 0x500000, CRC(b7bcbb8a) SHA1(e5a0b0eccbed2503b3b31f39d2c23508e5360c50) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromk", CRC(d313687d) SHA1(9ba468a9d582ef76c863f57ad9a0f811f3f08bd9) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(7615bc1b) SHA1(b936f7b341f6fe0921b4c41049734684583e3596) )

	ROM_REGION( 0xa00000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0xa00000, CRC(35632afa) SHA1(36f29de056583dd9acca35f39281a4c1ef0adb32) )

	ROM_REGION( 0x2000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x2000000, CRC(f5cfe108) SHA1(0ed88a109785f0d48cc61b32d0b62a4795407fd8) )
ROM_END

ROM_START( samsho5dd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x800000, CRC(5c7272fe) SHA1(e99c098d58df88cdb46fe57cd09b31aa5ba226f3) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(2ad6048b) SHA1(173c8561f0633e0d6e4a9750e632f2e46766e674) )

	NEO_BIOS_AUDIO_512K( "m1rom", CRC(5218a10a) SHA1(da4968e55d4a56249d85d6742a6acffcff4ad65d) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(e32a49d0) SHA1(b659f9e014d2a208839d17e8527d88e7cf094c39) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(1140df84) SHA1(f6c83db5c5a26b6923ecc00fef5526afaf97a4d1) )
ROM_END

ROM_START( samsho5add )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "proma", 0x000000, 0x800000, CRC(5e138d79) SHA1(be9ceabb43e2dcaf483e9a05b25aac7563664079) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(2ad6048b) SHA1(173c8561f0633e0d6e4a9750e632f2e46766e674) )

	NEO_BIOS_AUDIO_512K( "m1rom", CRC(5218a10a) SHA1(da4968e55d4a56249d85d6742a6acffcff4ad65d) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(e32a49d0) SHA1(b659f9e014d2a208839d17e8527d88e7cf094c39) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(1140df84) SHA1(f6c83db5c5a26b6923ecc00fef5526afaf97a4d1) )
ROM_END

ROM_START( samsho5hdd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x800000, CRC(e4e6c082) SHA1(883aa145edb9149ce595ccfd45ef3f163b06c967) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(2ad6048b) SHA1(173c8561f0633e0d6e4a9750e632f2e46766e674) )

	NEO_BIOS_AUDIO_512K( "m1rom", CRC(5218a10a) SHA1(da4968e55d4a56249d85d6742a6acffcff4ad65d) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(e32a49d0) SHA1(b659f9e014d2a208839d17e8527d88e7cf094c39) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(1140df84) SHA1(f6c83db5c5a26b6923ecc00fef5526afaf97a4d1) )
ROM_END

ROM_START( samsho5bdd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promb", 0x000000, 0x800000, CRC(dac5e3ee) SHA1(84270ad9c989bcc4511bc1ebb1bd09fd43b68a14) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromb", CRC(33227d62) SHA1(5f4b7ab642175657af212304783a1df98415ed44) )

	NEO_BIOS_AUDIO_128K( "m1romb", CRC(18114fb1) SHA1(016dc2f328340f3637a9bff373a20973df29f6b8) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0b", 0x000000, 0x1000000, CRC(fbfb6ea1) SHA1(201e39885d00abf3efaeca8fd0a53a7cf9c6dc06) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0b", 0x0000000, 0x4000000, CRC(c91ad92e) SHA1(a4430a004a91983e88e9f5b859e3d7ac99529ec1) )
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

/********************
  Decrypted Darksoft 
 *********************/

ROM_START( ct2k3spdnd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promd", 0x000000, 0x500000, CRC(fa115c60) SHA1(bc12b5d1aeb5c3abf6bea96abaf598987a856ba6) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromd", CRC(b86c8ba0) SHA1(cfb8f317c061899343f2c80ea16da131fd50a6e7) )

	NEO_BIOS_AUDIO_128K( "m1romd", CRC(7dfce5c0) SHA1(56084223e23ad5ca60f7d819bdcd2c61c0a7d523) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(0eaa2cc2) SHA1(f184111b9d8234c1c784540000638ceeb127072a) )
ROM_END

/*    YEAR  NAME        PARENT    MACHINE          INPUT   INIT            MONITOR */
/* SNK Decrypted Darksoft */
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
GAME( 1991, bakatonodd,   bakatono, neogeo_mj,       mjneogeo, neogeo_state, init_darksoft,   ROT0, "Monolith Corp.", "Bakatonosama Mahjong Manyuuki (MOM-002 ~ MOH-002) (Darksoft)", MACHINE_MECHANICAL )
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
GAME( 1996, crswd2bldd,   crswd2bl, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "CD_conv", "Crossed Swords 2 (CD to MVS Conversion) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, crsworddd,    crsword,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Alpha Denshi Co.", "Crossed Swords (ALM-002)(ALH-002) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, ct2k3sadd,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_ct2k3sadd,  ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 Super Plus alternate (The King of Fighters 2001 bootleg) (Darksoft)", MACHINE_MECHANICAL ) /* Hack / Bootleg of kof2001 */
GAME( 2003, ct2k3spdd,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_ct2k3spdd,  ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 Super Plus (The King of Fighters 2001 bootleg) (Darksoft)", MACHINE_MECHANICAL ) /* Protected Hack / Bootleg of kof2001 */
GAME( 2003, cthd2003dd,   kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_cthd2003dd, ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 (The King of Fighters 2001 bootleg, set 1) (Darksoft)", MACHINE_MECHANICAL ) /* Protected Hack / Bootleg of kof2001 */
GAME( 1999, ctomadaydd,   ctomaday, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Captain Tomaday (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, cyberlipdd,   cyberlip, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Cyber-Lip (NGM-010) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2000, diggermadd,   diggerma, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Kyle Hodgetts", "Digger Man (Prototype) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, doubledrdd,   doubledr, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Technos Japan", "Double Dragon (Neo-Geo) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, dragonshdd,   dragonsh, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Face", "Dragon's Heaven (development board) (Darksoft)", MACHINE_IS_INCOMPLETE | MACHINE_NO_SOUND | MACHINE_MECHANICAL ) // same ID code as Voltage Fighter Gowkaizer, developed by ex-Technos staff
GAME( 1991, eightmandd,   eightman, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK / Pallas", "Eight Man (NGM-025)(NGH-025) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1993, fatfurspdd,   fatfursp, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Fatal Fury Special / Garou Densetsu Special (set 1)(NGM-058 ~ NGH-058) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1993, fatfurspadd,  fatfursp, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Fatal Fury Special / Garou Densetsu Special (set 2)(NGM-058 ~ NGH-058) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, fatfury1dd,   fatfury1, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Fatal Fury - King of Fighters / Garou Densetsu - shukumei no tatakai (NGM-033 ~ NGH-033) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, fatfury2dd,   fatfury2, neogeo_noslot,   neogeo, neogeo_state,   init_fatfury2dd, ROT0, "SNK", "Fatal Fury 2 / Garou Densetsu 2 - arata-naru tatakai (NGM-047 ~ NGH-047) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, fatfury3dd,   fatfury3, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Fatal Fury 3 - Road to the Final Victory / Garou Densetsu 3 - haruka-naru tatakai (NGM-069 ~ NGH-069) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, fbfrenzydd,   fbfrenzy, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Football Frenzy (NGM-034 ~ NGH-034) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, fightfevdd,   fightfev, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Viccom", "Fight Fever (set 1) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, fightfevadd,  fightfev, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Viccom", "Fight Fever (set 2) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, flipshotdd,   flipshot, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Battle Flip Shot (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, froman2bdd,   froman2b, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "Idol Mahjong Final Romance 2 (Neo-Geo, bootleg of CD version) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, fswordsdd,    samsho3,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Fighters Swords (Korean release of Samurai Shodown III) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, galaxyfgdd,   galaxyfg, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Sunsoft", "Galaxy Fight - Universal Warriors (Darksoft)", MACHINE_MECHANICAL )
GAME( 1999, ganryudd,     ganryu,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Ganryu / Musashi Ganryuki (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 1999, garoudd,      garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garoudd,    ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1999, garoubldd,    garou,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "Garou - Mark of the Wolves (bootleg) (Darksoft)", MACHINE_MECHANICAL ) /* Bootleg of garoup */
GAME( 1999, garouhdd,     garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garouhdd,   ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530 ~ NGH-2530) (Darksoft)" , MACHINE_MECHANICAL )
GAME( 1999, garouhadd,    garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garoudd,    ROT0, "SNK", "Garou - Mark of the Wolves (NGH-2530) (Darksoft)" , MACHINE_MECHANICAL )
GAME( 1999, garoupdd,     garou,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Garou - Mark of the Wolves (Prototype) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, ghostlopdd,   ghostlop, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Data East Corporation", "Ghostlop (Prototype) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, goalx3dd,     goalx3,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Goal! Goal! Goal! (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, gowcaizrdd,   gowcaizr, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Technos Japan", "Voltage Fighter - Gowcaizer / Choujin Gakuen Gowcaizer (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, gpilotsdd,    gpilots,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Ghost Pilots (NGM-020 ~ NGH-020) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, gpilotshdd,   gpilots,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Ghost Pilots (NGH-020)(US) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, gururindd,    gururin,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Face", "Gururin (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, ironcladd,    ironclad, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Saurus", "Choutetsu Brikin'ger - Iron clad (Prototype) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, ironcladod,   ironclad, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "Choutetsu Brikin'ger - Iron clad (Prototype, bootleg) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, irrmazedd,    irrmaze,  neogeo_imaze,    irrmaze,  neogeo_state, init_darksoft,   ROT0, "SNK / Saurus", "The Irritating Maze / Ultra Denryu Iraira Bou (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, janshindd,    janshin,  neogeo_mj,       mjneogeo, neogeo_state, init_darksoft,   ROT0, "Aicom", "Jyanshin Densetsu - Quest of Jongmaster (Darksoft)", MACHINE_MECHANICAL )
GAME( 2001, jockeygpdd,   jockeygp, neogeo_noslot,   jockeygp, neogeo_state, init_jockeygpdd, ROT0, "Sun Amusement / BrezzaSoft", "Jockey Grand Prix (set 1) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2001, jockeygpadd,  jockeygp, neogeo_noslot,   jockeygp, neogeo_state, init_jockeygpdd, ROT0, "Sun Amusement / BrezzaSoft", "Jockey Grand Prix (set 2) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, joyjoydd,     joyjoy,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Puzzled / Joy Joy Kid (NGM-021)(NGH-021) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, kabukikldd,   kabukikl, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Hudson", "Far East of Eden - Kabuki Klash / Tengai Makyou - Shin Den (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, karnovrdd,    karnovr,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Data East Corporation", "Karnov's Revenge / Fighter's History Dynamite (Darksoft)", MACHINE_MECHANICAL )
GAME( 2002, kf2k2mpdd,    kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters 2002 Magic Plus (bootleg, set 1) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kf2k2mp2dd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters 2002 Magic Plus II (bootleg) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kf2k2plsdd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002dd,  ROT0, "bootleg", "The King of Fighters 2002 Plus (bootleg, set 1) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kf2k2pladd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002dd,  ROT0, "bootleg", "The King of Fighters 2002 Plus (bootleg, set 2) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2003, kf2k3bladd,   kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k3pldd,  ROT0, "bootleg", "The King of Fighters 2003 (bootleg, set 2) (Darksoft)", MACHINE_MECHANICAL ) // zooming is wrong because its a bootleg of the pcb version on a cart
GAME( 2003, kf2k3upldd,   kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters 2004 Ultra Plus (The King of Fighters 2003 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // zooming is wrong because its a bootleg of the pcb version on a cart
GAME( 2003, kf2k3pldd,    kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters 2004 Plus / Hero (The King of Fighters 2003 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // zooming is wrong because its a bootleg of the pcb version on a cart
GAME( 1996, kizunadd,     kizuna,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Kizuna Encounter - Super Tag Battle / Fu'un Super Tag Battle (Darksoft)", MACHINE_MECHANICAL )
GAME( 2000, kof2000dd,    kof2000,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2000dd,  ROT0, "SNK", "The King of Fighters 2000 (NGM-2570 ~ NGH-2570) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 2000, kof2000ndd,   kof2000,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2000dd,  ROT0, "SNK", "The King of Fighters 2000 (Not encrypted) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2001, kof2001dd,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Eolith / SNK", "The King of Fighters 2001 (NGM-2621) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2001, kof2001hdd,   kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Eolith / SNK", "The King of Fighters 2001 (NGH-2621) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kof2002dd,    kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002dd,  ROT0, "Eolith / Playmore", "The King of Fighters 2002 (NGM-2650)(NGH-2650) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kof2002bdd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002dd,  ROT0, "bootleg", "The King of Fighters 2002 (bootleg) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, kof2003dd,    kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK Playmore", "The King of Fighters 2003 (NGM-2710) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2002, kof10thdd,    kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters 10th Anniversary (The King of Fighters 2002 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // fake SNK copyright
GAME( 2005, kf10thepdd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters 10th Anniversary Extra Plus (The King of Fighters 2002 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // fake SNK copyright
GAME( 2004, kf2k5unidd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters 10th Anniversary 2005 Unique (The King of Fighters 2002 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // fake SNK copyright
GAME( 2004, kof2k4sedd,   kof2k4se, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters Special Edition 2004 (The King of Fighters 2002 bootleg, Set 1) (Darksoft)", MACHINE_MECHANICAL ) /* Hack / Bootleg of kof2002 */
GAME( 1994, kof94dd,      kof94,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '94 (NGM-055 ~ NGH-055) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, kof95dd,      kof95,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '95 (NGM-084) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, kof95hdd,     kof95,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '95 (NGH-084) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, kof96dd,      kof96,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '96 (NGM-214) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, kof96hdd,     kof96,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '96 (NGH-214) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, kof97dd,      kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '97 (NGM-2320) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, kof97hdd,     kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '97 (NGH-2320) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, kof97kdd,     kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '97 (Korean release) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, kof97plsdd,   kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters '97 Plus (bootleg) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, kof97orodd,   kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters '97 Oroshi Plus 2003 (bootleg) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, kof98dd,      kof98,    neogeo_noslot,   neogeo, neogeo_state,   init_kof98dd,    ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (NGM-2420) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, kof98hdd,     kof98,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (NGH-2420) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, kof98kdd,     kof98,    neogeo_noslot,   neogeo, neogeo_state,   init_kof98dd,    ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (Korean board) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, kof98kadd,    kof98,    neogeo_noslot,   neogeo, neogeo_state,   init_kof98dd,    ROT0, "SNK", "The King of Fighters '98 - The Slugfest / King of Fighters '98 - dream match never ends (Korean board 2) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1999, kof99dd,      kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGM-2510) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99edd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Earlier) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99hdd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGH-2510) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX, crashes going into attract demo */
GAME( 1999, kof99kdd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Korean release) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99pdd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Prototype) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, kogdd,        kof97,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "King of Gladiator (The King of Fighters '97 bootleg) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, kotmdd,       kotm,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "King of the Monsters (set 1) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, kotmhdd,      kotm,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "King of the Monsters (set 2) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, kotm2dd,      kotm2,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "King of the Monsters 2 - The Next Thing (NGM-039 ~ NGH-039) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, kotm2add,     kotm2,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "King of the Monsters 2 - The Next Thing (Older) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, kotm2pdd,     kotm2,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "King of the Monsters 2 - The Next Thing (Prototype) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, lans2004dd,   shocktr2, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "Lansquenet 2004 (Shock Troopers - 2nd Squad bootleg) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, lastbladdd,   lastblad, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The Last Blade / Bakumatsu Roman - Gekka no Kenshi (NGM-2340) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, lastbladhdd,  lastblad, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The Last Blade / Bakumatsu Roman - Gekka no Kenshi (NGH-2340) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, lastsoldd,    lastblad, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The Last Soldier (Korean release of The Last Blade) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2005, lasthopedd,   lasthope, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "NG:DEV.TEAM", "Last Hope (bootleg AES to MVS conversion, no coin support) (Darksoft)", MACHINE_MECHANICAL ) // wasn't actually released on MVS but bootleg carts have been sold, this doesn't accept coins, runs like a console game
GAME( 1998, lastbld2dd,   lastbld2, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The Last Blade 2 / Bakumatsu Roman - Dai Ni Maku Gekka no Kenshi (NGM-2430)(NGH-2430) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, lbowlingdd,   lbowling, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "League Bowling (NGM-019 ~ NGH-019) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, legendosdd,   legendos, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Legend of Success Joe / Ashita no Joe Densetsu (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, lresortdd,    lresort,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Last Resort (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, lresortpdd,   lresort,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Last Resort (Prototype) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, magdrop2dd,   magdrop2, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Data East Corporation", "Magical Drop II (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, magdrop3dd,   magdrop3, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Data East Corporation", "Magical Drop III (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, maglorddd,    maglord,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Alpha Denshi Co.", "Magician Lord (NGM-005) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, maglordhdd,   maglord,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Alpha Denshi Co.", "Magician Lord (NGH-005) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, mahretsudd,   mahretsu, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Mahjong Kyo Retsuden (NGM-004 ~ NGH-004) (Darksoft)", MACHINE_MECHANICAL ) // does not support mahjong panel in MVS mode
GAME( 1995, marukodqdd,   marukodq, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Takara", "Chibi Marukochan Deluxe Quiz (Darksoft)", MACHINE_MECHANICAL )
GAME( 2002, matrimdd,     matrim,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Noise Factory / Atlus", "Matrimelee / Shin Gouketsuji Ichizoku Toukon (NGM-2660 ~ NGH-2660) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, miexchngdd,   miexchng, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Face", "Money Puzzle Exchanger / Money Idol Exchanger (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, minasandd,    minasan,  neogeo_mj,       mjneogeo, neogeo_state, init_darksoft,   ROT0, "Monolith Corp.", "Minasanno Okagesamadesu! Daisugorokutaikai (MOM-001 ~ MOH-001) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, moshougidd,   moshougi, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "ADK / SNK",        "Syougi No Tatsujin - Master of Syougi (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, mutnatdd,     mutnat,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Mutation Nation (NGM-014 ~ NGH-014) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, nam1975dd,    nam1975,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "NAM-1975 (NGM-001 ~ NGH-001) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, ncombatdd,    ncombat,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Alpha Denshi Co.", "Ninja Combat (NGM-009) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, ncombathdd,   ncombat,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Alpha Denshi Co.", "Ninja Combat (NGH-009) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, ncommanddd,   ncommand, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Alpha Denshi Co.", "Ninja Commando (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, neobombedd,   neobombe, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Hudson", "Neo Bomberman (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, neocup98dd,   neocup98, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Neo-Geo Cup '98 - The Road to the Victory (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, neodriftdd,   neodrift, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Neo Drift Out - New Technology (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, neomrdodd,    neomrdo,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Visco", "Neo Mr. Do! (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, ninjamasdd,   ninjamas, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "ADK / SNK", "Ninja Master's - haoh-ninpo-cho (Darksoft)", MACHINE_MECHANICAL )
GAME( 2000, nitddd,       nitd,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Eleven / Gavaking", "Nightmare in the Dark (Darksoft)" , MACHINE_MECHANICAL )
GAME( 2001, nitdbldd,     nitd,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "Nightmare in the Dark (bootleg) (Darksoft)" , MACHINE_MECHANICAL )
GAME( 1996, overtopdd,    overtop,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "ADK", "Over Top (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, panicbomdd,   panicbom, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Eighting / Hudson", "Panic Bomber (Darksoft)", MACHINE_MECHANICAL )
GAME( 1999, pbobbl2ndd,   pbobbl2n, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Taito (SNK license)", "Puzzle Bobble 2 / Bust-A-Move Again (Neo-Geo) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, pbobblendd,   pbobblen, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Taito", "Puzzle Bobble / Bust-A-Move (Neo-Geo) (NGM-083) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, pbobblenbdd,  pbobblen, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "Puzzle Bobble / Bust-A-Move (Neo-Geo) (bootleg) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, pgoaldd,      pgoal,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Saurus", "Pleasure Goal / Futsal - 5 on 5 Mini Soccer (NGM-219) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, pnyaadd,      pnyaa,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Aiky / Taito", "Pochi and Nyaa (Ver 2.00) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, pnyaaadd,     pnyaa,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Aiky / Taito", "Pochi and Nyaa (Ver 2.02) (Darksoft)", MACHINE_MECHANICAL ) // this version does not show the web address on the title screen
GAME( 1997, popbouncdd,   popbounc, neogeo_dial,     neogeo, neogeo_state,   init_darksoft,   ROT0, "Video System Co.", "Pop 'n Bounce / Gapporin (Darksoft)", MACHINE_MECHANICAL )
GAME( 1999, preisle2dd,   preisle2, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Yumekobo", "Prehistoric Isle 2 (Darksoft)" , MACHINE_MECHANICAL )
GAME( 1994, pspikes2dd,   pspikes2, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Video System Co.", "Power Spikes II (NGM-068) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, pulstardd,    pulstar,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Aicom", "Pulstar (Darksoft)", MACHINE_MECHANICAL )
GAME( 1997, puzzldprdd,   puzzledp, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Taito (Visco license)", "Puzzle De Pon! R! (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, puzzledpdd,   puzzledp, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Taito (Visco license)", "Puzzle De Pon! (Darksoft)", MACHINE_MECHANICAL )
GAME( 1992, quizdai2dd,   quizdai2, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Quiz Meitantei Neo & Geo - Quiz Daisousa Sen part 2 (NGM-042 ~ NGH-042) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, quizdaisdd,   quizdais, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Quiz Daisousa Sen - The Last Count Down (NGM-023 ~ NGH-023) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, quizdaiskdd,  quizdais, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Quiz Daisousa Sen - The Last Count Down (Korean release) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, quizkofdd,    quizkof,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Saurus", "Quiz King of Fighters (SAM-080 ~ SAH-080) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, quizkofkdd,   quizkof,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Saurus", "Quiz King of Fighters (Korean release) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, ragnagrdd,    ragnagrd, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Saurus", "Ragnagard / Shin-Oh-Ken (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, rbff1dd,      rbff1,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Real Bout Fatal Fury / Real Bout Garou Densetsu (NGM-095 ~ NGH-095) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, rbff1add,     rbff1,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Real Bout Fatal Fury / Real Bout Garou Densetsu (bug fix revision) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, rbff1kdd,     rbff1,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Real Bout Fatal Fury / Real Bout Garou Densetsu (Korean release) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, rbff1kadd,    rbff1,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Real Bout Fatal Fury / Real Bout Garou Densetsu (Korean release, bug fix revision) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, rbff2dd,      rbff2,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Real Bout Fatal Fury 2 - The Newcomers / Real Bout Garou Densetsu 2 - the newcomers (NGM-2400) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, rbff2hdd,     rbff2,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Real Bout Fatal Fury 2 - The Newcomers / Real Bout Garou Densetsu 2 - the newcomers (NGH-2400) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1998, rbff2kdd,     rbff2,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Real Bout Fatal Fury 2 - The Newcomers (Korean release) (Darksoft)", MACHINE_MECHANICAL ) // no Japanese title / mode
GAME( 1996, rbffspecdd,   rbffspec, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Real Bout Fatal Fury Special / Real Bout Garou Densetsu Special (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, rbffspeckdd,  rbffspec, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Real Bout Fatal Fury Special / Real Bout Garou Densetsu Special (Korean release) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, ridherodd,    ridhero,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Riding Hero (NGM-006)(NGH-006) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1990, ridherohdd,   ridhero,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Riding Hero (set 2) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, roboarmydd,   roboarmy, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Robo Army (Darksoft)", MACHINE_MECHANICAL )
GAME( 1991, roboarmyadd,  roboarmy, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Robo Army (NGM-032 ~ NGH-032) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2002, rotddd,       rotd,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Evoga / Playmore", "Rage of the Dragons (NGM-2640?) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2002, rotdhdd,      rotd,     neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Evoga / Playmore", "Rage of the Dragons (NGH-2640?) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1999, s1945pdd,     s1945p,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "Psikyo", "Strikers 1945 Plus (Darksoft)" , MACHINE_MECHANICAL )
GAME( 2004, samsh5spdd,   samsh5sp, neogeo_noslot,   neogeo, neogeo_state,   init_samsh5spdd, ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V Special / Samurai Spirits Zero Special (NGM-2720) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2004, samsh5sphdd,  samsh5sp, neogeo_noslot,   neogeo, neogeo_state,   init_samsh5spdd, ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V Special / Samurai Spirits Zero Special (NGH-2720) (2nd release, less censored) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2004, samsh5sphodd, samsh5sp, neogeo_noslot,   neogeo, neogeo_state,   init_samsh5spdd, ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V Special / Samurai Spirits Zero Special (NGH-2720) (1st release, censored) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1993, samshodd,     samsho,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Samurai Shodown / Samurai Spirits (NGM-045) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1993, samshohdd,    samsho,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Samurai Shodown / Samurai Spirits (NGH-045) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, samsho2dd,    samsho2,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Samurai Shodown II / Shin Samurai Spirits - Haohmaru jigokuhen (NGM-063)(NGH-063) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1994, samsho2kdd,   samsho2,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Saulabi Spirits / Jin Saulabi Tu Hon (Korean release of Samurai Shodown II, set 1) (Darksoft)", MACHINE_MECHANICAL ) // official or hack?
GAME( 1994, samsho2kadd,  samsho2,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Saulabi Spirits / Jin Saulabi Tu Hon (Korean release of Samurai Shodown II, set 2) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, samsho3dd,    samsho3,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Samurai Shodown III / Samurai Spirits - Zankurou Musouken (NGM-087) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, samsho3hdd,   samsho3,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Samurai Shodown III / Samurai Spirits - Zankurou Musouken (NGH-087) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, samsho4dd,    samsho4,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Samurai Shodown IV - Amakusa's Revenge / Samurai Spirits - Amakusa Kourin (NGM-222 ~ NGH-222) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, samsho4kdd,   samsho4,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Pae Wang Jeon Seol / Legend of a Warrior (Korean censored Samurai Shodown IV) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, samsho5dd,    samsho5,  neogeo_noslot,   neogeo, neogeo_state,   init_samsho5dd,  ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V / Samurai Spirits Zero (NGM-2700, set 1) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, samsho5add,   samsho5,  neogeo_noslot,   neogeo, neogeo_state,   init_samsho5dd,  ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V / Samurai Spirits Zero (NGM-2700, set 2) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, samsho5hdd,   samsho5,  neogeo_noslot,   neogeo, neogeo_state,   init_samsho5dd,  ROT0, "Yuki Enterprise / SNK Playmore", "Samurai Shodown V / Samurai Spirits Zero (NGH-2700) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, samsho5bdd,   samsho5,  neogeo_noslot,   neogeo, neogeo_state,   init_samsho5bdd, ROT0, "bootleg", "Samurai Shodown V / Samurai Spirits Zero (bootleg) (Darksoft)", MACHINE_MECHANICAL ) // different program scrambling
GAME( 2003, svcpcbdd,     svcpcb,   neogeo_noslot,   dualbios, neogeo_state, init_svcpcbdd,   ROT0, "SNK Playmore", "SNK vs. Capcom - SVC Chaos (JAMMA PCB, set 1) (Darksoft)", MACHINE_MECHANICAL ) // not a clone of neogeo because it's NOT a neogeo cart.

/* Decrypted Darksoft */
GAME( 2003, ct2k3spdnd,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,  ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 Super Plus (The King of Fighters 2001 bootleg) (Fully Decrypted / Darksoft)", MACHINE_MECHANICAL )
