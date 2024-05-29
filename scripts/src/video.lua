-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   video.lua
--
--   Rules for building video cores
--
---------------------------------------------------------------------------

files {
	MAME_DIR .. "src/devices/video/poly.h",
	MAME_DIR .. "src/devices/video/sprite.cpp",
	MAME_DIR .. "src/devices/video/sprite.h",
	MAME_DIR .. "src/devices/video/vector.cpp",
	MAME_DIR .. "src/devices/video/vector.h",
}

--------------------------------------------------
--
--@src/devices/video/bufsprite.h,VIDEOS["BUFSPRITE"] = true
--------------------------------------------------

if (VIDEOS["BUFSPRITE"]~=null) then
	files {
		MAME_DIR .. "src/devices/video/bufsprite.cpp",
		MAME_DIR .. "src/devices/video/bufsprite.h",
	}
end


--------------------------------------------------
--
--@src/devices/video/315_5124.h,VIDEOS["SEGA315_5124"] = true
--------------------------------------------------

if (VIDEOS["SEGA315_5124"]~=null) then
	files {
		MAME_DIR .. "src/devices/video/315_5124.cpp",
		MAME_DIR .. "src/devices/video/315_5124.h",
	}
end


--------------------------------------------------
--
--@src/devices/video/315_5313.h,VIDEOS["SEGA315_5313"] = true
--------------------------------------------------

if (VIDEOS["SEGA315_5313"]~=null) then
	files {
		MAME_DIR .. "src/devices/video/315_5313.cpp",
		MAME_DIR .. "src/devices/video/315_5313.h",
	}
end


--------------------------------------------------
--
--@src/devices/video/gb_lcd.h,VIDEOS["GB_LCD"] = true
--------------------------------------------------

if (VIDEOS["GB_LCD"]~=null) then
	files {
		MAME_DIR .. "src/devices/video/gb_lcd.cpp",
		MAME_DIR .. "src/devices/video/gb_lcd.h",
	}
end


--------------------------------------------------
--
--@src/devices/video/snes_ppu.h,VIDEOS["SNES_PPU"] = true
--------------------------------------------------
if (VIDEOS["SNES_PPU"]~=null) then
	files {
		MAME_DIR .. "src/devices/video/snes_ppu.cpp",
		MAME_DIR .. "src/devices/video/snes_ppu.h",
	}
end


--------------------------------------------------
--
--@src/devices/video/gba_lcd.h,VIDEOS["GBA_LCD"] = true
--------------------------------------------------

if (VIDEOS["GBA_LCD"]~=null) then
	files {
		MAME_DIR .. "src/devices/video/gba_lcd.cpp",
		MAME_DIR .. "src/devices/video/gba_lcd.h",
	}
end
