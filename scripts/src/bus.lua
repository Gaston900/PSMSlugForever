-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   bus.lua
--
--   Rules for building bus cores
--
---------------------------------------------------------------------------

-- SYSTEM (NPG)
---------------------------------------------------
--
--@src/devices/bus/generic/slot.h,BUSES["GENERIC"] = true
---------------------------------------------------

if (BUSES["GENERIC"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/generic/slot.cpp",
		MAME_DIR .. "src/devices/bus/generic/slot.h",
		MAME_DIR .. "src/devices/bus/generic/carts.cpp",
		MAME_DIR .. "src/devices/bus/generic/carts.h",
		MAME_DIR .. "src/devices/bus/generic/ram.cpp",
		MAME_DIR .. "src/devices/bus/generic/ram.h",
		MAME_DIR .. "src/devices/bus/generic/rom.cpp",
		MAME_DIR .. "src/devices/bus/generic/rom.h",
	}
end

-- SYSTEM (MEGADRIVE)
---------------------------------------------------
--
--@src/devices/bus/megadrive/md_slot.h,BUSES["MEGADRIVE"] = true
---------------------------------------------------

if (BUSES["MEGADRIVE"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/megadrive/md_slot.cpp",
		MAME_DIR .. "src/devices/bus/megadrive/md_slot.h",
		MAME_DIR .. "src/devices/bus/megadrive/md_carts.cpp",
		MAME_DIR .. "src/devices/bus/megadrive/md_carts.h",
		MAME_DIR .. "src/devices/bus/megadrive/eeprom.cpp",
		MAME_DIR .. "src/devices/bus/megadrive/eeprom.h",
		MAME_DIR .. "src/devices/bus/megadrive/ggenie.cpp",
		MAME_DIR .. "src/devices/bus/megadrive/ggenie.h",
		MAME_DIR .. "src/devices/bus/megadrive/jcart.cpp",
		MAME_DIR .. "src/devices/bus/megadrive/jcart.h",
		MAME_DIR .. "src/devices/bus/megadrive/rom.cpp",
		MAME_DIR .. "src/devices/bus/megadrive/rom.h",
		MAME_DIR .. "src/devices/bus/megadrive/sk.cpp",
		MAME_DIR .. "src/devices/bus/megadrive/sk.h",
		MAME_DIR .. "src/devices/bus/megadrive/stm95.cpp",
		MAME_DIR .. "src/devices/bus/megadrive/stm95.h",
		MAME_DIR .. "src/devices/bus/megadrive/svp.cpp",
		MAME_DIR .. "src/devices/bus/megadrive/svp.h",
	}
end

-- SYSTEM (GBA)
---------------------------------------------------
--
--@src/devices/bus/gba/gba_slot.h,BUSES["GBA"] = true
---------------------------------------------------

if (BUSES["GBA"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/gba/gba_slot.cpp",
		MAME_DIR .. "src/devices/bus/gba/gba_slot.h",
		MAME_DIR .. "src/devices/bus/gba/rom.cpp",
		MAME_DIR .. "src/devices/bus/gba/rom.h",
	}
end

-- SYSTEM (GB)
---------------------------------------------------
--
--@src/devices/bus/gameboy/gb_slot.h,BUSES["GAMEBOY"] = true
---------------------------------------------------

if (BUSES["GAMEBOY"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/gameboy/gb_slot.cpp",
		MAME_DIR .. "src/devices/bus/gameboy/gb_slot.h",
		MAME_DIR .. "src/devices/bus/gameboy/rom.cpp",
		MAME_DIR .. "src/devices/bus/gameboy/rom.h",
		MAME_DIR .. "src/devices/bus/gameboy/mbc.cpp",
		MAME_DIR .. "src/devices/bus/gameboy/mbc.h",
	}
end
