// license:BSD-3-Clause
// copyright-holders:Bryan McPhail,Ernesto Corvi,Andrew Prime,Zsolt Vasvari
// thanks-to:Fuzz
/*************************************************************************

    Neo-Geo hardware

*************************************************************************/

#include "emu.h"
#include "cpu/m68000/m68000.h"
#include "cpu/z80/z80.h"
#include "machine/nvram.h"
#include "machine/watchdog.h"
#include "sound/2610intf.h"
#include "machine/upd1990a.h"
#include "machine/ng_memcard.h"
#include "machine/gen_latch.h"
#include "video/neogeo_spr.h"
#include "imagedev/snapquik.h"
#include "bus/neogeo/prot.h"
#include "bus/neogeo/banked_cart.h"
#include "bus/neogeo_ctrl/ctrl.h"
#include "emupal.h"
#include "screen.h"
#include "speaker.h"

// On scanline 224, /VBLANK goes low 56 mclks (14 pixels) from the rising edge of /HSYNC.
// Two mclks after /VBLANK goes low, the hardware sets a pending IRQ1 flip-flop.
#define NEOGEO_VBLANK_IRQ_HTIM (attotime::from_ticks(56+2, NEOGEO_MASTER_CLOCK))
	// macros allow code below to be copy+pasted into slot devices more easily
#define cpuregion memregion("maincpu")->base()
#define cpuregion_size memregion("maincpu")->bytes()
#define spr_region memregion("sprites")->base()
#define spr_region_size memregion("sprites")->bytes()
#define fix_region memregion("fixed")->base()
#define fix_region_size memregion("fixed")->bytes()
#define ym_region memregion("ymsnd")->base()
#define ym_region_size memregion("ymsnd")->bytes()
#define audiocpu_region memregion("audiocpu")->base()
#define audio_region_size memregion("audiocpu")->bytes()
#define audiocrypt_region memregion("audiocrypt")->base()
#define audiocrypt_region_size memregion("audiocrypt")->bytes()


class neogeo_state : public driver_device
{
public:
	neogeo_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_use_cart_vectors(0)
		, m_use_cart_audio(0)
		, m_banked_cart(*this, "banked_cart")
		, m_maincpu(*this, "maincpu")
		, m_audiocpu(*this, "audiocpu")
		, m_ym(*this, "ymsnd")
		, m_region_maincpu(*this, "maincpu")
		, m_region_sprites(*this, "sprites")
		, m_region_fixed(*this, "fixed")
		, m_region_fixedbios(*this, "fixedbios")
		, m_bank_audio_main(*this, "audio_main")
		, m_upd4990a(*this, "upd4990a")
		, m_save_ram(*this, "saveram")
		, m_screen(*this, "screen")
		, m_palette(*this, "palette")
		, m_memcard(*this, "memcard")
		, m_dsw(*this, "DSW")
		, m_trackx(*this, "TRACK_X")
		, m_tracky(*this, "TRACK_Y")
		, m_edge(*this, "edge")
		, m_ctrl1(*this, "ctrl1")
		, m_ctrl2(*this, "ctrl2")
		, m_sprgen(*this, "spritegen")
		, m_soundlatch(*this, "soundlatch")
		, m_soundlatch2(*this, "soundlatch2")
		, m_mslugx_prot(*this, "mslugx_prot")
		, m_sma_prot(*this, "sma_prot")
		, m_cmc_prot(*this, "cmc_prot")
		, m_pcm2_prot(*this, "pcm2_prot")
		, m_pvc_prot(*this, "pvc_prot")
		, m_bootleg_prot(*this, "bootleg_prot")
		, m_kof2002_prot(*this, "kof2002_prot")
		, m_fatfury2_prot(*this, "fatfury2_prot")
		, m_kof98_prot(*this, "kof98_prot")
		, m_sbp_prot(*this, "sbp_prot")
		, m_kog_prot(*this, "kog_prot")
		, m_out_digit(*this, "digit%u", 0U)
	{ }

	// mainboard configurations
	void mvs(machine_config &config);
	void neogeo_arcade(machine_config &config);
	void neogeo_base(machine_config &config);
	void neogeo_noslot(machine_config &config);
    void aks_sakura(machine_config &config);
    void neosd(machine_config &config);

	// fixed software configurations
	void init_neogeo();
	void init_ms5plusd();
	void init_ms5plush();
	void init_ms5plusdd();
	void init_ms5plushb();
	void init_ms5pcbhb();
	void init_ms5pcbdd();
	void init_mslugdd();
	void init_mslug2dd();
	void init_mslug3a();
	void init_mslug3e();
	void init_mslug3hb();
	void init_mslug3cqt();
	void init_mslug3dd();
	void init_mslug3ndd();
    void init_mslug3b6d();
    void init_mslug3b6dd();
    void init_mslug4dd();
	void init_mslug4ndd();
	void init_mslug4hb();
    void init_mslug4lw();
	void init_mslug4p();
	void init_mslug5b();
	void init_mslug5e();
	void init_mslug5dd();
	void init_mslug5ndd();
	void init_mslug5dde();
	void init_mslug5nd();
	void init_mslug5hb();
	void init_mslugx();
	void init_mslugxdd();
	void init_s1945p();

	DECLARE_CUSTOM_INPUT_MEMBER(get_memcard_status);
	DECLARE_CUSTOM_INPUT_MEMBER(get_audio_result);
	DECLARE_INPUT_CHANGED_MEMBER(select_bios);

private:

	void io_control_w(offs_t offset, u8 data);
	u16 memcard_r(offs_t offset);
	void memcard_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	void audio_command_w(u8 data);
	u8 audio_command_r();
	u8 audio_cpu_bank_select_r(offs_t offset);
	void audio_cpu_enable_nmi_w(offs_t offset, u8 data);
	void system_control_w(offs_t offset, u8 data);
	u16 neogeo_unmapped_r(address_space &space);
	u16 neogeo_paletteram_r(offs_t offset);
	void neogeo_paletteram_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	u16 neogeo_video_register_r(address_space &space, offs_t offset, u16 mem_mask = ~0);
	void neogeo_video_register_w(offs_t offset, u16 data, u16 mem_mask = ~0);
	u16 banked_vectors_r(offs_t offset);
	u16 in0_r();
	u16 in1_r();
	void save_ram_w(offs_t offset, u16 data, u16 mem_mask = ~0);

	TIMER_CALLBACK_MEMBER(display_position_interrupt_callback);
	TIMER_CALLBACK_MEMBER(display_position_vblank_callback);
	TIMER_CALLBACK_MEMBER(vblank_interrupt_callback);
    DECLARE_QUICKLOAD_LOAD_MEMBER(neo_q_cb);

	u32 screen_update_neogeo(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	void neogeo_main_map(address_map &map);
	void main_map_slot(address_map &map);
	void audio_map(address_map &map);
	void audio_io_map(address_map &map);
	void main_map_noslot(address_map &map);
	void main_map1(address_map &map);
    void aks_sakura_map(address_map &map);

	void neogeo_postload();
	void update_interrupts();
	void create_interrupt_timers();
	void start_interrupt_timers();
	void neogeo_acknowledge_interrupt(u16  data);

	void neogeo_main_cpu_banking_init();
	void neogeo_audio_cpu_banking_init(int set_entry);
	void adjust_display_position_interrupt_timer();
	void neogeo_set_display_position_interrupt_control(u16  data);
	void neogeo_set_display_counter_msb(u16  data);
	void neogeo_set_display_counter_lsb(u16  data);
	void set_video_control( u16  data );

	void create_rgb_lookups();
	void set_pens();
	void neogeo_set_screen_shadow( int data );
	void neogeo_set_palette_bank( int data );

	void audio_cpu_check_nmi();
	void set_save_ram_unlock( u8 data );
	void set_outputs(  );
	void set_output_latch( u8 data );
	void set_output_data( u8 data );

	virtual void machine_start() override;
	virtual void machine_reset() override;

	memory_bank           *m_bank_audio_cart[4];

	// configuration
	enum {NEOGEO_MVS, NEOGEO_AES, NEOGEO_CD} m_type;

	// internal state
	bool       m_recurse;
	bool       m_audio_cpu_nmi_enabled;
	bool       m_audio_cpu_nmi_pending;

	// MVS-specific state
	u8      m_save_ram_unlocked;
	u8      m_output_data;
	u8      m_output_latch;
	u8      m_el_value;
	u8      m_led1_value;
	u8      m_led2_value;

	virtual void video_start() override;

	emu_timer  *m_display_position_interrupt_timer;
	emu_timer  *m_display_position_vblank_timer;
	emu_timer  *m_vblank_interrupt_timer;
	u32     m_display_counter;
	u8      m_vblank_interrupt_pending;
	u8      m_display_position_interrupt_pending;
	u8      m_irq3_pending;
	u8      m_display_position_interrupt_control;
	u8      m_vblank_level;
	u8      m_raster_level;

	u16  get_video_control(  );

	// color/palette related
	std::vector<u16 > m_paletteram;
	u8        m_palette_lookup[32][4];
	const pen_t *m_bg_pen;
	int          m_screen_shadow;
	int          m_palette_bank;

	u16 neogeo_slot_rom_low_r();
	u16 neogeo_slot_rom_low_vectors_r(offs_t offset);

	void install_banked_bios();

	int m_use_cart_vectors;
	int m_use_cart_audio;
	optional_device<neogeo_banked_cart_device> m_banked_cart;
	required_device<cpu_device> m_maincpu;
	required_device<cpu_device> m_audiocpu;
	required_device<ym2610_device> m_ym;
	required_memory_region m_region_maincpu;
	required_memory_region m_region_sprites;
	required_memory_region m_region_fixed;
	optional_memory_region m_region_fixedbios;
	optional_memory_bank   m_bank_audio_main; // optional because of neocd
	optional_device<upd4990a_device> m_upd4990a;
	optional_shared_ptr<u16 > m_save_ram;
	required_device<screen_device> m_screen;
	optional_device<palette_device> m_palette;
	optional_device<ng_memcard_device> m_memcard;
	optional_ioport m_dsw;
	optional_ioport m_trackx;
	optional_ioport m_tracky;
	optional_device<neogeo_ctrl_edge_port_device> m_edge;
	optional_device<neogeo_control_port_device> m_ctrl1;
	optional_device<neogeo_control_port_device> m_ctrl2;
	required_device<neosprite_device> m_sprgen;
	optional_device<generic_latch_8_device> m_soundlatch;
	optional_device<generic_latch_8_device> m_soundlatch2;
	optional_device<mslugx_prot_device> m_mslugx_prot;
	optional_device<sma_prot_device> m_sma_prot;
	optional_device<cmc_prot_device> m_cmc_prot;
	optional_device<pcm2_prot_device> m_pcm2_prot;
	optional_device<pvc_prot_device> m_pvc_prot;
	optional_device<ngbootleg_prot_device> m_bootleg_prot;
	optional_device<kof2002_prot_device> m_kof2002_prot;
	optional_device<fatfury2_prot_device> m_fatfury2_prot;
	optional_device<kof98_prot_device> m_kof98_prot;
	optional_device<sbp_prot_device> m_sbp_prot;
	optional_device<kog_prot_device> m_kog_prot;
	output_finder<5> m_out_digit;
};

/*----------- defined in drivers/neogeo.c -----------*/

INPUT_PORTS_EXTERN(neogeo);
INPUT_PORTS_EXTERN(dualbios);

/*************************************
 *
 *  Neo-Geo bios
 *
 *************************************

    These are the known Bios Roms, Set options.bios to the one you want.

    The Universe bios roms are supported because they're now used on enough PCBs
    to be considered 'in active arcade use' rather than just homebrew hacks.
    Some may be missing, there have been multiple CRCs reported for the same
    revision in some cases (the Universe bios has an option for entering / displaying
    a serial number; these should be noted as such if they're added).
    Universe bios prior to version 1.3 was incompatible with AES.

    The 'japan-hotel' BIOS is a dump of an MVS which could be found in some japanese
    hotels. it is a custom MVS mobo which uses MVS carts but it hasn't jamma
    connector and it's similar to a console with a coin mechanism, so it's a sort
    of little coin op console installed in hotels.

    The sp-45.sp1 bios is the latest 'ASIA' revision. Japan-j3.bin is the latest 'JAPAN'
    revision. Both of them are also used in the sp-4x.sp1 bios of the Jamma PCB boards.

    The current Neo-Geo MVS system set (SFIX/SM1/000-LO) used is from a NEO-MVH MV1FS board.
    Other boards (MV1xx / MV2x / MV4x /MV6x) other system sets?

    Zoom ROM (LO)    128K   TC531000CP      1x 128Kx8   Zoom look-up table ROM
    Fix ROM (SFIX)   128K   27C1000         1x 128Kx8   Text layer graphics ROM
    Sound ROM (SM1)  128K   27C1000/23C1000 1x 128Kx8   Z80 program ROM

*/

#define ROM_LOAD16_WORD_SWAP_BIOS(bios,name,offset,length,hash) \
		ROMX_LOAD(name, offset, length, hash, ROM_GROUPWORD | ROM_REVERSE | ROM_BIOS(bios))

#define NEOGEO_BIOS \
	ROM_REGION16_BE( 0x80000, "mainbios", 0 ) \
	ROM_SYSTEM_BIOS( 0, "arcade_mode", "Arcade Mode MVS" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 0, "arcade mode.rom",  0x00000, 0x020000, CRC(0de70ac8) SHA1(d41ab190a2c9f91c52649f7e0faf85a9cfa8ed24) ) \
	ROM_SYSTEM_BIOS( 1, "console_mode", "Consola Mode AES" ) \
	ROM_LOAD16_WORD_SWAP_BIOS( 1, "console mode.rom", 0x00000, 0x020000, CRC(a371d430) SHA1(9519a43eaed7a5753a9fdffaca8167b7214c4d93) ) \
	ROM_DEFAULT_BIOS("arcade_mode")

#define NEO_BIOS_AUDIO(size, name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_BIOS_AUDIO_32K(name, hash) \
	NEO_BIOS_AUDIO(0x8000, name, hash)

#define NEO_BIOS_AUDIO_64K(name, hash) \
	NEO_BIOS_AUDIO(0x10000, name, hash)

#define NEO_BIOS_AUDIO_128K(name, hash) \
    NEO_BIOS_AUDIO(0x20000, name, hash)

#define NEO_BIOS_AUDIO_256K(name, hash) \
	NEO_BIOS_AUDIO(0x40000, name, hash)

#define NEO_BIOS_AUDIO_512K(name, hash) \
	NEO_BIOS_AUDIO(0x80000, name, hash)

#define NEO_BIOS_AUDIO_ENCRYPTED(size, name, hash) \
	NEOGEO_BIOS \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash )

#define NEO_BIOS_AUDIO_ENCRYPTED_64K(name, hash) \
	NEO_BIOS_AUDIO_ENCRYPTED(0x10000, name, hash)

#define NEO_BIOS_AUDIO_ENCRYPTED_128K(name, hash) \
	NEO_BIOS_AUDIO_ENCRYPTED(0x20000, name, hash)

#define NEO_BIOS_AUDIO_ENCRYPTED_256K(name, hash) \
	NEO_BIOS_AUDIO_ENCRYPTED(0x40000, name, hash)

#define NEO_BIOS_AUDIO_ENCRYPTED_512K(name, hash) \
	NEO_BIOS_AUDIO_ENCRYPTED(0x80000, name, hash)

#define ROM_Y_ZOOM \
	ROM_REGION( 0x20000, "zoomy", 0 ) \
	ROM_LOAD( "000-lo.lo", 0x00000, 0x20000, CRC(5a86cff2) SHA1(5992277debadeb64d1c1c64b0a92d9293eaf7e4a) )

#define NEO_SFIX_MT(size) \
	ROM_Y_ZOOM \
	ROM_REGION( 0x20000, "fixedbios", 0 ) \
	ROM_LOAD( "sfix.sfix",  0, 0x20000, CRC(c2ea0cfd) SHA1(fd4a618cdcdbf849374f0a50dd8efe9dbab706c3) ) \
	ROM_REGION( size, "fixed", ROMREGION_ERASE00 )

#define NEO_SFIX_MT_64K \
	NEO_SFIX_MT( 0x10000 )

#define NEO_SFIX_MT_128K \
	NEO_SFIX_MT( 0x20000 )

#define NEO_SFIX_MT_256K \
	NEO_SFIX_MT( 0x40000 )

#define NEO_SFIX_MT_512K \
	NEO_SFIX_MT( 0x80000 )

#define NEO_SFIX(bytes, name, hash) \
	NEO_SFIX_MT( bytes ) \
	ROM_LOAD( name, 0x00000, bytes, hash )

#define NEO_SFIX_64K(name, hash) \
	NEO_SFIX( 0x10000, name, hash )

#define NEO_SFIX_128K(name, hash) \
	NEO_SFIX( 0x20000, name, hash )

#define NEO_SFIX_256K(name, hash) \
	NEO_SFIX( 0x40000, name, hash )

#define NEO_SFIX_512K(name, hash) \
	NEO_SFIX( 0x80000, name, hash )

#define NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(size, name, hash) \
	ROM_REGION16_BE( 0x80000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-3.sp1",  0x00000, 0x80000, CRC(b4590283) SHA1(47047ed5b6062babc0a0bebcc30e4b3f021e115a) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash )

#define NEO_JAPAN_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_64K(name, hash) \
	NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(0x10000, name, hash)

#define NEO_JAPAN_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_128K(name, hash) \
	NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(0x20000, name, hash)

#define NEO_JAPAN_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_256K(name, hash) \
	NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(0x40000, name, hash)

#define NEO_JAPAN_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_512K(name, hash) \
	NEO_JAPAN_MVS_BIOS_AUDIO_ENCRYPTED(0x80000, name, hash)

#define NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-s2.sp1",  0x00000, 0x20000, CRC(9b1a7cbe) SHA1(1695d3c488961a0f3667bd9b94ff678fd7c56d76) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash )

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_64K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(0x10000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_128K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(0x20000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_256K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(0x40000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_ENCRYPTED_512K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO_ENCRYPTED(0x80000, name, hash)

#define NEO_EUROPE_MVS_BIOS_AUDIO(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-s2.sp1",  0x00000, 0x20000, CRC(9b1a7cbe) SHA1(1695d3c488961a0f3667bd9b94ff678fd7c56d76) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_64K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO(0x10000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_128K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO(0x20000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_256K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO(0x40000, name, hash)

#define NEO_EUROPE_MVS_BIOS_BOOT_AUDIO_512K(name, hash) \
	NEO_EUROPE_MVS_BIOS_AUDIO(0x80000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-1.sp1",  0x00000, 0x20000, CRC(98f34e99) SHA1(ff63c492d11d0f26533d6e73d331e15152e62cc7) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO_64K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(0x10000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO_128K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(0x20000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO_256K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(0x40000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO_512K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_BOOT_AUDIO(0x80000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-1.sp2",  0x00000, 0x20000, CRC(0161e81d) SHA1(2cd9e13f85070651a6ca6a3727fc6312efffd3cf) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO_64K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(0x10000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO_128K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(0x20000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO_256K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(0x40000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO_512K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_TIME_BOOT_AUDIO(0x80000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-1.sp1",  0x00000, 0x20000, CRC(98f34e99) SHA1(ff63c492d11d0f26533d6e73d331e15152e62cc7) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( 0x90000, "audiocpu", ROMREGION_ERASEFF ) \
	ROM_REGION( 0x80000, "audiocrypt", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash )

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED_64K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(0x10000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED_128K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(0x20000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED_256K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(0x40000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED_512K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_ENCRYPTED(0x80000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(size, name, hash) \
	ROM_REGION16_BE( 0x20000, "mainbios", 0 ) \
	ROM_LOAD16_WORD_SWAP("sp-1.sp1",  0x00000, 0x20000, CRC(98f34e99) SHA1(ff63c492d11d0f26533d6e73d331e15152e62cc7) ) \
	ROM_REGION( 0x20000, "audiobios", 0 ) \
	ROM_LOAD( "sm1.sm1", 0x00000, 0x20000, CRC(94416d67) SHA1(42f9d7ddd6c0931fd64226a60dc73602b2819dcf) ) \
	ROM_REGION( size+0x10000, "audiocpu", 0 ) \
	ROM_LOAD( name, 0x00000, size, hash ) \
	ROM_RELOAD(     0x10000, size )

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_64K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(0x10000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_128K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(0x20000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_256K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(0x40000, name, hash)

#define NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO_512K(name, hash) \
	NEO_MSLUG_FOREVER_BIOS_FIX_COIN_AUDIO(0x80000, name, hash)


