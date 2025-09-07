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

void neogeo_state::init_ganryudd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_cmc_prot->cmc42_neogeo_gfx_decrypt(spr_region, spr_region_size, GANRYU_GFX_KEY);
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

void neogeo_state::init_kf2k2mpdd()
{
	init_neogeo();
	m_bootleg_prot->kf2k2mp_decrypt(cpuregion, cpuregion_size);
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 0);
	m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region,audio_region_size);
	m_bootleg_prot->neogeo_bootleg_sx_decrypt(fix_region, fix_region_size,2);
	m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, KOF2002_GFX_KEY);
}

void neogeo_state::init_kf2k2mp2dd()
{
	init_neogeo();
	m_bootleg_prot->kf2k2mp2_px_decrypt(cpuregion, cpuregion_size);
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 0);
	m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region,audio_region_size);
	m_bootleg_prot->neogeo_bootleg_sx_decrypt(fix_region, fix_region_size,1);
	m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, KOF2002_GFX_KEY);
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

void neogeo_state::init_kf2k3upldd()
{
	init_neogeo();
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 5);
	m_bootleg_prot->kf2k3upl_px_decrypt(cpuregion, cpuregion_size);
	m_bootleg_prot->neogeo_bootleg_sx_decrypt(fix_region, fix_region_size,2);
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
	m_bootleg_prot->kf2k3bl_install_protection(m_maincpu, m_banked_cart, cpuregion, cpuregion_size);
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

void neogeo_state::init_kof2001dd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
    m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);
    m_cmc_prot->cmc50_neogeo_gfx_decrypt(spr_region, spr_region_size, KOF2001_GFX_KEY);
}

void neogeo_state::init_kof2002dd()
{
	init_neogeo();
	m_sprgen->m_fixed_layer_bank_type = 1;
    m_kof2002_prot->kof2002_decrypt_68k(cpuregion, cpuregion_size);
    m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region, audio_region_size);
    m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 0);
	m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_kof2002bdd()
{
	init_neogeo();
	m_kof2002_prot->kof2002_decrypt_68k(cpuregion, cpuregion_size);
	m_pcm2_prot->neo_pcm2_swap(ym_region, ym_region_size, 0);
	m_cmc_prot->neogeo_cmc50_m1_decrypt(audiocrypt_region, audiocrypt_region_size, audiocpu_region,audio_region_size);
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_kf10thepdd()
{
	init_neogeo();
	m_bootleg_prot->kf10thep_px_decrypt(cpuregion, cpuregion_size);
	m_bootleg_prot->neogeo_bootleg_sx_decrypt(fix_region, fix_region_size,1);
    m_bootleg_prot->neogeo_darksoft_cx_decrypt(spr_region, spr_region_size);
}

void neogeo_state::init_kf2k5unidd()
{
	init_neogeo();
	m_bootleg_prot->decrypt_kf2k5uni(cpuregion, cpuregion_size, audiocpu_region,audio_region_size, fix_region, fix_region_size);
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

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

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

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

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

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(1a8c274b) SHA1(5f6f9c533f4a296a18c741ce59a69cf6f5c836b9) )

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

	ROM_REGION( 0x200000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x200000, CRC(f93e8f47) SHA1(85693df548938acc42223271ae9b4a8a08d19aed) )

	ROM_REGION( 0x080000, "ymsnd.deltat", 0 )
	ROM_LOAD( "vroma1", 0x000000, 0x080000, CRC(586f4cb2) SHA1(588460031d84c308e3353ecf714db9986425c21c) )

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
	ROM_LOAD( "crom0", 0x0000000, 0x1000000, CRC(05d4ca88) SHA1(be0eb71c2adbdcaa02eb4a03eaefb7c40b85854a) )
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

	ROM_REGION( 0x180000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x180000, CRC(3b641067) SHA1(5ed753c125e730ef25aca326f85ed11f01222251) )

    ROM_REGION( 0x080000, "ymsnd.deltat", 0 )
    ROM_LOAD( "vroma1", 0x000000, 0x080000, CRC(7abf113d) SHA1(5b2a0e70f2eaf4638b44702dacd4cb17838fb1d5) )

	ROM_REGION( 0x400000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x400000, CRC(b4391c3e) SHA1(ef54ba4eae1b4f477f7b7408a3d5d86cea6013a6) )
ROM_END

ROM_START( gpilotshdd )
	ROM_REGION( 0x100000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0xa0000, CRC(920ad15e) SHA1(3396bd064c27c589e580df2a1ba1dceea39ed560) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(a6d83d53) SHA1(9a8c092f89521cc0b27a385aa72e29cbaca926c5) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(48409377) SHA1(0e212d2c76856a90b2c2fdff675239525972ac43) )

	ROM_REGION( 0x180000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x180000, CRC(3b641067) SHA1(5ed753c125e730ef25aca326f85ed11f01222251) )

    ROM_REGION( 0x080000, "ymsnd.deltat", 0 )
    ROM_LOAD( "vroma1", 0x000000, 0x080000, CRC(7abf113d) SHA1(5b2a0e70f2eaf4638b44702dacd4cb17838fb1d5) )

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

	ROM_REGION( 0x080000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x080000, CRC(66c1e5c4) SHA1(7e85420021d4c39c36ed75a1cec567c5610ffce0) )

	ROM_REGION( 0x080000, "ymsnd.deltat", 0 )
	ROM_LOAD( "vroma1", 0x000000, 0x080000, CRC(8ed20a86) SHA1(d15cba5eac19ea56fdd4877541f1bb3eb755ebba) )

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
	ROM_LOAD16_WORD_SWAP( "prommp", 0x000000, 0x800000, CRC(eb3608e5) SHA1(a70e4a37906c1c78dd00f33a87d3f121248c6575) )

	NEO_SFIX_128K( "srommp", CRC(348d6f2c) SHA1(586da8a936ebbb71af324339a4b60ec91dfa0990) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "m1rom", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(479cf678) SHA1(e3471ab0255f3ea8a2c920df82655c96f00a6f85) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(b4e531d2) SHA1(5a2537e485003d1e1665c284f0bae208681fa9d3) )
ROM_END

ROM_START( kf2k2mp2dd )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prommp2", 0x000000, 0x600000, CRC(a19e8188) SHA1(5c3efcd50a972c0022d9ac49c14f1d3b0de519e7) )

	NEO_SFIX_128K( "srommp2", CRC(446e74c5) SHA1(efc2afb26578bad9eb21659c70eb0f827d6d1ef6) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "m1rom", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(479cf678) SHA1(e3471ab0255f3ea8a2c920df82655c96f00a6f85) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(b4e531d2) SHA1(5a2537e485003d1e1665c284f0bae208681fa9d3) )
ROM_END

ROM_START( kf2k2pladd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prompla", 0x000000, 0x500000, CRC(fd81168f) SHA1(3a7510ab72123d62de606b9d88c343d0a551c3ae) )

	NEO_SFIX_128K( "srompla", CRC(1a3ed064) SHA1(9749bb55c750e6b65d651998c2649c5fb68db68e) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "m1rom", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(479cf678) SHA1(e3471ab0255f3ea8a2c920df82655c96f00a6f85) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
ROM_END

ROM_START( kf2k2plsdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prompls", 0x000000, 0x500000, CRC(7e1bce72) SHA1(18b990c4630df6e860028f548f678d6418ebd553) )

	NEO_SFIX_128K( "srompls", CRC(595e0006) SHA1(ff086bdaa6f40e9ad963e1100a27f44618d684ed) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "m1rom", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(479cf678) SHA1(e3471ab0255f3ea8a2c920df82655c96f00a6f85) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
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
	ROM_LOAD16_WORD_SWAP( "promupl", 0x000000, 0x800000, CRC(87294c01) SHA1(21420415a6b2ba1b43ecc1934270dc085d6bd7d9) )

	NEO_SFIX_128K( "sromupl", CRC(e5708c0c) SHA1(5649446d3b0b1bd138b5a8b40b96a6d0f892f4d8) )

	NEO_BIOS_AUDIO_128K( "m1rombl", CRC(3a4969ff) SHA1(2fc107a023a82053a8df63025829bcf12cee9610) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0bl", 0x000000, 0x1000000, CRC(1d96154b) SHA1(1d4e262b0d30cee79a4edc83bb9706023c736668) )

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

	NEO_BIOS_AUDIO_ENCRYPTED_256K( "m1rom", CRC(4b749113) SHA1(2af2361146edd0ce3966614d90165a5c1afb8de4) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(fe16ee57) SHA1(405cca65759258193e982b252c359d998a3f4919) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(82004ca6) SHA1(e37c5f6fa248ba9d11c46f117b5722f3895e455f) )
ROM_END

ROM_START( kof2000ndd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promn", 0x000000, 0x500000, CRC(7d5dfdf9) SHA1(9ec4a2ee08f175eb8badbf2728f69a5d8643c2fd) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_512K( "srom.s1", CRC(38901d4d) SHA1(c7684f66ab4ed577094da6ae143477c9df28d1fe) )

	NEO_BIOS_AUDIO_ENCRYPTED_256K( "m1rom", CRC(4b749113) SHA1(2af2361146edd0ce3966614d90165a5c1afb8de4) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(fe16ee57) SHA1(405cca65759258193e982b252c359d998a3f4919) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(82004ca6) SHA1(e37c5f6fa248ba9d11c46f117b5722f3895e455f) )
ROM_END

ROM_START( kof2001dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(4707c379) SHA1(9aec323d432a9343f46fdf3d0fd52768f31ed25a) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6d209796) SHA1(95fdb865e47d37916573ba12e8ba4a4aaece1cba) )

	NEO_BIOS_AUDIO_ENCRYPTED_256K( "m1rom", CRC(a7f8119f) SHA1(71805b39b8b09c32425cf39f9de59b2f755976c2) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(731a5526) SHA1(816f7779cc34311d92f31b551911e5234a7afa45) )
ROM_END

ROM_START( kof2001hdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promh", 0x000000, 0x500000, CRC(9e3dcf93) SHA1(acfd3cef0bd4af15f79e50d2b8b7326796cfc11e) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(6d209796) SHA1(95fdb865e47d37916573ba12e8ba4a4aaece1cba) )

	NEO_BIOS_AUDIO_ENCRYPTED_256K( "m1rom", CRC(a7f8119f) SHA1(71805b39b8b09c32425cf39f9de59b2f755976c2) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(f5314040) SHA1(8443085f2d8e28d8191dc12e343bfe70f378d97a) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0", 0x0000000, 0x4000000, CRC(731a5526) SHA1(816f7779cc34311d92f31b551911e5234a7afa45) )
ROM_END

ROM_START( kof2002dd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x000000, 0x500000, CRC(3c393c7b) SHA1(9ed4e986b3d38ef88c9b80357d3a079978d04e3f) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(e0eaaba3) SHA1(831b642da9fe7617498cdb1c86475b3b3d3043bc) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "m1rom", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(479cf678) SHA1(e3471ab0255f3ea8a2c920df82655c96f00a6f85) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
ROM_END

ROM_START( kof2002bdd )
	ROM_REGION( 0x500000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promb", 0x000000, 0x500000, CRC(63f5be1c) SHA1(ed14787b8043a00a66d2e05dae0eb15468d902f7) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(e0eaaba3) SHA1(831b642da9fe7617498cdb1c86475b3b3d3043bc) )

	NEO_BIOS_AUDIO_ENCRYPTED_128K( "m1rom", CRC(85aaa632) SHA1(744fba4ca3bc3a5873838af886efb97a8a316104) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x1000000, CRC(479cf678) SHA1(e3471ab0255f3ea8a2c920df82655c96f00a6f85) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
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
	ROM_LOAD( "vroma0d", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0t", 0x0000000, 0x4000000, CRC(30265a0a) SHA1(9153e04a7e1d56e85378bdc381e69093637134a6) )
ROM_END

ROM_START( kf10thepdd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promtp", 0x000000, 0x800000, CRC(33e793cf) SHA1(2ad437a99ee8f08eabd2b06867cd368b88e2eb9d) )
    ROM_DEFAULT_BIOS("console_mode")

    NEO_SFIX_128K( "sromtp", CRC(92410064) SHA1(1fb800b46341858207d3b6961a760289fbec7faa) )

    NEO_BIOS_AUDIO_128K( "m1romtp", CRC(5a47d9ad) SHA1(0197737934653acc6c97221660d789e9914f3578) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0d", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0t", 0x0000000, 0x4000000, CRC(30265a0a) SHA1(9153e04a7e1d56e85378bdc381e69093637134a6) )
ROM_END

ROM_START( kf2k5unidd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "promu", 0x000000, 0x800000, CRC(dd135fb6) SHA1(4e85814a44ee9fee9760048dd6d6fd2b66521bb1) )
    ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "sromu", CRC(91f8c544) SHA1(9d16cafb9ca4bc54f31f7fd82b1be06ec8b11c79) )

//    NEO_BIOS_AUDIO_128K( "m1romt", CRC(f6fab859) SHA1(0184aa1394b9f9946d610278b53b846020dd88dc) )
    NEO_BIOS_AUDIO_128K( "m1romu", CRC(9050bfe7) SHA1(765bf3d954f775231b7ef2504bb844cd0b29e3f7) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0d", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

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

ROM_START( ganryudnd )
	ROM_REGION( 0x200000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prom", 0x0000000, 0x200000, CRC(8f212084) SHA1(2ffcfd74f095425e45e118b89b7c0f220a5228f0) )
	ROM_DEFAULT_BIOS("console_mode")

	NEO_SFIX_128K( "srom", CRC(a8dadec9) SHA1(e909764d0377705cde0cc0accfdaf9b520c1df02) )

	NEO_BIOS_AUDIO_128K( "m1rom", CRC(30cc4099) SHA1(46453b7aac41855a92724a785372f8daf931d8d4) )

	ROM_REGION( 0x400000, "ymsnd", 0 )
	ROM_LOAD( "vroma0", 0x000000, 0x400000, CRC(e5946733) SHA1(d5904a50465af03d6ff33399a98f3259721ca0b2) )

	ROM_REGION( 0x1000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x1000000, CRC(4bde5c82) SHA1(1794f4062589f3d20183c8ddc38cf3d97108a9bc) )
ROM_END

ROM_START( kf2k2mpdnd )
	ROM_REGION( 0x800000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prommpd", 0x000000, 0x800000, CRC(542f47e3) SHA1(6d1a9660c48dfe709b89cbb7a6632bad5098ca16) )

	NEO_SFIX_128K( "srommpd", CRC(29c0693e) SHA1(a852d15a8558b4a1cadf1ed9ef357d765ff88d35) )

	NEO_BIOS_AUDIO_128K( "m1romd", CRC(1c661a4b) SHA1(4e5aa862a0a182a806d538996ddc68d9f2dffaf7) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0d", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
ROM_END

ROM_START( kf2k2mp2dnd )
	ROM_REGION( 0x600000, "maincpu", 0 )
	ROM_LOAD16_WORD_SWAP( "prommp2d", 0x000000, 0x600000, CRC(c4f378a5) SHA1(3f8a6436cb51d743f0889d3da3b5bea2578d2a10) )

	NEO_SFIX_128K( "srommp2d", CRC(df4ce33b) SHA1(1287c84c16e17df7d5887af57fc6657da452d0ae) )

	NEO_BIOS_AUDIO_128K( "m1romd", CRC(1c661a4b) SHA1(4e5aa862a0a182a806d538996ddc68d9f2dffaf7) )

	ROM_REGION( 0x1000000, "ymsnd", 0 )
	ROM_LOAD( "vroma0d", 0x000000, 0x1000000, CRC(29d3cbc9) SHA1(ac0fc9e86f9f3510f300e464c3e2589888aceee5) )

	ROM_REGION( 0x4000000, "sprites", 0 )
	ROM_LOAD( "crom0d", 0x0000000, 0x4000000, CRC(a1f7fa68) SHA1(a1616bd7da916e37e8d14965692fccbb6ca0d248) )
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
GAME( 1991, bakatonodd,   bakatono, neogeo_mj,       mjneogeo, neogeo_state, init_darksoft, ROT0, "Monolith Corp.", "Bakatonosama Mahjong Manyuuki (MOM-002 ~ MOH-002) (Darksoft)", MACHINE_MECHANICAL )
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
GAME( 1999, ganryudd,     ganryu,   neogeo_noslot,   neogeo, neogeo_state,   init_ganryudd,   ROT0, "Visco", "Ganryu / Musashi Ganryuki (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 1999, garoudd,      garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garoudd,    ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530) (Darksoft) (Darksoft)", MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, garoubldd,    garou,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "Garou - Mark of the Wolves (bootleg) (Darksoft)", MACHINE_MECHANICAL ) /* Bootleg of garoup */
GAME( 1999, garouhdd,     garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garouhdd,   ROT0, "SNK", "Garou - Mark of the Wolves (NGM-2530 ~ NGH-2530) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, garouhadd,    garou,    neogeo_noslot,   neogeo, neogeo_state,   init_garoudd,    ROT0, "SNK", "Garou - Mark of the Wolves (NGH-2530) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
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
GAME( 2002, kf2k2mpdd,    kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k2mpdd,  ROT0, "bootleg", "The King of Fighters 2002 Magic Plus (bootleg, set 1) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kf2k2mp2dd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k2mp2dd, ROT0, "bootleg", "The King of Fighters 2002 Magic Plus II (bootleg) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kf2k2plsdd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002dd,  ROT0, "bootleg", "The King of Fighters 2002 Plus (bootleg, set 1) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kf2k2pladd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002dd,  ROT0, "bootleg", "The King of Fighters 2002 Plus (bootleg, set 2) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2003, kf2k3bladd,   kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k3pldd,  ROT0, "bootleg", "The King of Fighters 2003 (bootleg, set 2) (Darksoft)", MACHINE_MECHANICAL ) // zooming is wrong because its a bootleg of the pcb version on a cart
GAME( 2003, kf2k3upldd,   kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k3upldd, ROT0, "bootleg", "The King of Fighters 2004 Ultra Plus (The King of Fighters 2003 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // zooming is wrong because its a bootleg of the pcb version on a cart
GAME( 2003, kf2k3pldd,    kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters 2004 Plus / Hero (The King of Fighters 2003 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // zooming is wrong because its a bootleg of the pcb version on a cart
GAME( 1996, kizunadd,     kizuna,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "Kizuna Encounter - Super Tag Battle / Fu'un Super Tag Battle (Darksoft)", MACHINE_MECHANICAL )
GAME( 2000, kof2000dd,    kof2000,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2000dd,  ROT0, "SNK", "The King of Fighters 2000 (NGM-2570 ~ NGH-2570) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 2000, kof2000ndd,   kof2000,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2000dd,  ROT0, "SNK", "The King of Fighters 2000 (Not encrypted) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2001, kof2001dd,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2001dd,  ROT0, "Eolith / SNK", "The King of Fighters 2001 (NGM-2621) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2001, kof2001hdd,   kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2001dd,  ROT0, "Eolith / SNK", "The King of Fighters 2001 (NGH-2621) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kof2002dd,    kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002dd,  ROT0, "Eolith / Playmore", "The King of Fighters 2002 (NGM-2650)(NGH-2650) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted GFX */
GAME( 2002, kof2002bdd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kof2002bdd, ROT0, "bootleg", "The King of Fighters 2002 (bootleg) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2003, kof2003dd,    kof2003,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK Playmore", "The King of Fighters 2003 (NGM-2710) (Darksoft)", MACHINE_MECHANICAL )
GAME( 2002, kof10thdd,    kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters 10th Anniversary (The King of Fighters 2002 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // fake SNK copyright
GAME( 2005, kf10thepdd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kf10thepdd, ROT0, "bootleg", "The King of Fighters 10th Anniversary Extra Plus (The King of Fighters 2002 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // fake SNK copyright
GAME( 2004, kf2k5unidd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_kf2k5unidd, ROT0, "bootleg", "The King of Fighters 10th Anniversary 2005 Unique (The King of Fighters 2002 bootleg) (Darksoft)", MACHINE_MECHANICAL ) // fake SNK copyright
GAME( 2004, kof2k4sedd,   kof2k4se, neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "bootleg", "The King of Fighters Special Edition 2004 (The King of Fighters 2002 bootleg, Set 1) (Darksoft)", MACHINE_MECHANICAL ) /* Hack / Bootleg of kof2002 */
GAME( 1994, kof94dd,      kof94,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '94 (NGM-055 ~ NGH-055) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, kof95dd,      kof95,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '95 (NGM-084) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1995, kof95hdd,     kof95,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '95 (NGH-084) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, kof96dd,      kof96,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '96 (NGM-214) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1996, kof96hdd,     kof96,    neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,   ROT0, "SNK", "The King of Fighters '96 (NGH-214) (Darksoft)", MACHINE_MECHANICAL )
GAME( 1999, kof99dd,      kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGM-2510) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99edd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Earlier) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 1999, kof99hdd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (NGH-2510) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX, crashes going into attract demo */
GAME( 1999, kof99kdd,     kof99,    neogeo_noslot,   neogeo, neogeo_state,   init_kof99dd,    ROT0, "SNK", "The King of Fighters '99 - Millennium Battle (Korean release) (Darksoft)" , MACHINE_MECHANICAL ) /* Encrypted Code & GFX */
GAME( 2003, svcpcbdd,     svcpcb,   neogeo_noslot,   dualbios, neogeo_state, init_svcpcbdd,   ROT0, "SNK Playmore", "SNK vs. Capcom - SVC Chaos (JAMMA PCB, set 1) (Darksoft)", MACHINE_MECHANICAL ) // not a clone of neogeo because it's NOT a neogeo cart.

/* Decrypted Darksoft */
GAME( 2003, ct2k3spdnd,    kof2001,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,  ROT0, "bootleg", "Crouching Tiger Hidden Dragon 2003 Super Plus (The King of Fighters 2001 bootleg) (Fully Decrypted / Darksoft)", MACHINE_MECHANICAL )
GAME( 1999, ganryudnd,     ganryu,   neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,  ROT0, "Visco", "Ganryu / Musashi Ganryuki (Fully Decrypted / Darksoft)" , MACHINE_MECHANICAL )
GAME( 2002, kf2k2mpdnd,    kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,  ROT0, "bootleg", "The King of Fighters 2002 Magic Plus (bootleg, set 1) (Fully Decrypted / Darksoft)" , MACHINE_MECHANICAL )
GAME( 2002, kf2k2mp2dnd,   kof2002,  neogeo_noslot,   neogeo, neogeo_state,   init_darksoft,  ROT0, "bootleg", "The King of Fighters 2002 Magic Plus II (bootleg) (Fully Decrypted / Darksoft)" , MACHINE_MECHANICAL )
