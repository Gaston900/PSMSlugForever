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
--@src/devices/video/mos6566.h,VIDEOS["MOS6566"] = true
--------------------------------------------------

--if (VIDEOS["MOS6566"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/video/mos6566.cpp",
--		MAME_DIR .. "src/devices/video/mos6566.h",
--	}
--end


files {
	MAME_DIR .. "src/devices/video/cgapal.cpp",
	MAME_DIR .. "src/devices/video/cgapal.h",
}
