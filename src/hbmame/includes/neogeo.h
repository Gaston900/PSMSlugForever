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

	// fixed software configurations
	void init_darksoft();
	void init_neogeo();	
	void init_ms5pcbhb();
	void init_ms5plusdd();
	void init_ms5plushb();
	void init_mslug3a();
	void init_mslug3hb();
	void init_mslug3dc();
	void init_mslug3dd();
	void init_mslug3de();
    void init_mslug3b6dd();
    void init_mslug3b6hb();
    void init_mslug4dc();
    void init_mslug4dd();
	void init_mslug4hb();
    void init_mslug4lw();
	void init_mslug4p();
	void init_mslug5b();
	void init_mslug5dc();
	void init_mslug5dd();
	void init_mslug5b1();
	void init_mslug5hb();
	void init_mslugx();
	void init_mslugxdd();

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

	u32 screen_update_neogeo(screen_device &screen, bitmap_rgb32 &bitmap, const rectangle &cliprect);

	void neogeo_main_map(address_map &map);
	void main_map_slot(address_map &map);
	void audio_map(address_map &map);
	void audio_io_map(address_map &map);
	void main_map_noslot(address_map &map);
	void main_map1(address_map &map);

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
