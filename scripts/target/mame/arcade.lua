-- license:BSD-3-Clause
-- copyright-holders:Gaston90
---------------------------------------------------
--   PSMSLUGFOREVER target makefile
---------------------------------------------------

---------------------------------------------------
-- specify available CPU cores
---------------------------------------------------

CPUS["Z80"] = true 
CPUS["M680X0"] = true
CPUS["NEC"] = true -- m92
CPUS["ARM7"] = true -- pgm
CPUS["SH"] = true -- megadriv
CPUS["SSP1601"] = true -- megadriv
CPUS["G65816"] = true --snes
CPUS["LR35902"] = true --snes
CPUS["SPC700"] = true --snes
CPUS["SUPERFX"] = true --snes
CPUS["UPD7725"] = true --snes

--------------------------------------------------
-- specify available sound cores
--------------------------------------------------

SOUNDS["SPEAKER"] = true
SOUNDS["YM2610"] = true
SOUNDS["IREMGA20"] = true -- m92
SOUNDS["OKIM6295"] = true -- m92
SOUNDS["YM2151"] = true -- m92
SOUNDS["ICS2115"] = true -- pgm
SOUNDS["YM2203"] = true -- megadriv
SOUNDS["YM2608"] = true -- megadriv
SOUNDS["YM2610"] = true -- megadriv
SOUNDS["YM2612"] = true -- megadriv
SOUNDS["AY8910"] = true -- megadriv
SOUNDS["CDDA"] = true -- megadriv
SOUNDS["DAC"] = true -- megadriv
SOUNDS["RF5C68"] = true -- megadriv
SOUNDS["SN76496"] = true -- megadriv
SOUNDS["VOLT_REG"] = true -- megadriv
SOUNDS["GB_SOUND"] = true --snes
SOUNDS["S_DSP"] = true --snes

--------------------------------------------------
-- specify available machine cores
--------------------------------------------------

MACHINES["GEN_LATCH"] = true
MACHINES["UPD1990A"] = true
MACHINES["WATCHDOG"] = true
MACHINES["Z80DAISY"] = true
MACHINES["PIC8259"] = true -- m92
MACHINES["V3021"] = true -- pgm
MACHINES["I2CMEM"] = true -- megadriv
MACHINES["LC89510"] = true -- megadriv
MACHINES["S_SMP"] = true --snes
MACHINES["INTELFLASH"] = true --gba

--------------------------------------------------
-- specify available bus cores
--------------------------------------------------
BUSES["GENERIC"] = true -- megadriv
BUSES["MEGADRIVE"] = true -- megadriv
BUSES["GAMEBOY"] = true --snes
BUSES["MIDI"] = true --snes
BUSES["SNES"] = true --snes
BUSES["SNES_CTRL"] = true --snes
BUSES["GBA"] = true --gba

--------------------------------------------------
-- specify available video cores
--------------------------------------------------
VIDEOS["BUFSPRITE"] = true -- m92
VIDEOS["SEGA315_5124"] = true -- megadriv
VIDEOS["SEGA315_5313"] = true -- megadriv
VIDEOS["GB_LCD"] = true --snes
VIDEOS["GBA_LCD"] = true --gba
VIDEOS["SNES_PPU"] = true --snes

function linkProjects_mame_arcade(_target, _subtarget)
	links {
		"neogeo",
		"irem",
		"igs",
		"nintendo",
		"sega",
	}
end

function createMAMEProjects(_target, _subtarget, _name)
	project (_name)
	targetsubdir(_target .."_" .. _subtarget)
	kind (LIBTYPE)
	uuid (os.uuid("drv-" .. _target .."_" .. _subtarget .. "_" .._name))
	addprojectflags() -- no idea if this is needed, seems to work fine without it
	precompiledheaders()

	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/emu",
		MAME_DIR .. "src/devices",
		MAME_DIR .. "src/hbmame/includes",
		MAME_DIR .. "src/hbmame",
		MAME_DIR .. "src/mame",
		MAME_DIR .. "src/lib",
		MAME_DIR .. "src/lib/util",
		MAME_DIR .. "src/lib/netlist",
		MAME_DIR .. "3rdparty",
		MAME_DIR .. "3rdparty/zlib",
		GEN_DIR  .. "mame/layout",
		GEN_DIR  .. "hbmame/layout",
	}
	includedirs {
		ext_includedir("flac"),
		ext_includedir("glm"),
		ext_includedir("jpeg"),
		ext_includedir("rapidjson"),
	}
end

function createProjects_mame_arcade(_target, _subtarget)
--------------------------------------------------
-- the following files are general components and
-- shared across a number of drivers
--------------------------------------------------

createMAMEProjects(_target, _subtarget, "neogeo")
files {
	MAME_DIR .. "src/hbmame/drivers/neogeo_noslothb.cpp",
	MAME_DIR .. "src/hbmame/video/neogeo.cpp",
	MAME_DIR .. "src/hbmame/video/neogeo_spr.cpp",
	MAME_DIR .. "src/hbmame/machine/ng_memcard.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo/prot.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo/banked_cart.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/ctrl.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/joystick.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/mahjong.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/dial.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/irrmaze.cpp",
	MAME_DIR .. "src/hbmame/bus/neogeo_ctrl/kizuna4p.cpp",
}

createMAMEProjects(_target, _subtarget, "irem")
files {
	MAME_DIR .. "src/mame/drivers/m92.cpp",
	MAME_DIR .. "src/mame/machine/irem_cpu.cpp",
	MAME_DIR .. "src/mame/video/m92.cpp",
}

createMAMEProjects(_target, _subtarget, "igs")
files {
	MAME_DIR .. "src/mame/drivers/pgm.cpp",
	MAME_DIR .. "src/mame/machine/igs025.cpp",
	MAME_DIR .. "src/mame/machine/igs022.cpp",
	MAME_DIR .. "src/mame/machine/igs028.cpp",
	MAME_DIR .. "src/mame/machine/pgmcrypt.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs012.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs022.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs025_igs028.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type1.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type2.cpp",
	MAME_DIR .. "src/mame/machine/pgmprot_igs027a_type3.cpp",
    MAME_DIR .. "src/mame/machine/pgmprot_orlegend.cpp",
	MAME_DIR .. "src/mame/video/pgm.cpp",
}

createMAMEProjects(_target, _subtarget, "nintendo")
files {
    MAME_DIR .. "src/mame/drivers/gb.cpp",
	MAME_DIR .. "src/mame/machine/gb.cpp",
    MAME_DIR .. "src/mame/drivers/gba.cpp",
	MAME_DIR .. "src/mame/drivers/snes.cpp",
    MAME_DIR .. "src/mame/machine/snes.cpp",
	MAME_DIR .. "src/mame/machine/snescx4.cpp",
}

createMAMEProjects(_target, _subtarget, "sega")
files {
	MAME_DIR .. "src/mame/drivers/megadriv.cpp",
	MAME_DIR .. "src/mame/machine/megadriv.cpp",
	MAME_DIR .. "src/mame/machine/mega32x.cpp",
	MAME_DIR .. "src/mame/machine/megacd.cpp",
    MAME_DIR .. "src/mame/machine/megacdcd.cpp",
}

end
