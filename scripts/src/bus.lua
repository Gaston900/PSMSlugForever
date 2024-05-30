-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   bus.lua
--
--   Rules for building bus cores
--
---------------------------------------------------------------------------

---------------------------------------------------
--
--@src/devices/bus/neogeo/slot.h,BUSES["NEOGEO"] = true
---------------------------------------------------

if (BUSES["NEOGEO"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/neogeo/slot.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/slot.h",
		MAME_DIR .. "src/devices/bus/neogeo/carts.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/carts.h",
		MAME_DIR .. "src/devices/bus/neogeo/rom.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/rom.h",
		MAME_DIR .. "src/devices/bus/neogeo/fatfury2.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/fatfury2.h",
		MAME_DIR .. "src/devices/bus/neogeo/kof98.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/kof98.h",
		MAME_DIR .. "src/devices/bus/neogeo/mslugx.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/mslugx.h",
		MAME_DIR .. "src/devices/bus/neogeo/cmc.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/cmc.h",
		MAME_DIR .. "src/devices/bus/neogeo/sma.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/sma.h",
		MAME_DIR .. "src/devices/bus/neogeo/pcm2.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/pcm2.h",
		MAME_DIR .. "src/devices/bus/neogeo/kof2k2.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/kof2k2.h",
		MAME_DIR .. "src/devices/bus/neogeo/pvc.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/pvc.h",
		MAME_DIR .. "src/devices/bus/neogeo/boot_cthd.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/boot_cthd.h",
		MAME_DIR .. "src/devices/bus/neogeo/boot_misc.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/boot_misc.h",
		MAME_DIR .. "src/devices/bus/neogeo/boot_svc.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/boot_svc.h",
		MAME_DIR .. "src/devices/bus/neogeo/boot_kof2k2.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/boot_kof2k2.h",
		MAME_DIR .. "src/devices/bus/neogeo/boot_kof2k3.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/boot_kof2k3.h",
		MAME_DIR .. "src/devices/bus/neogeo/sbp.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/sbp.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_fatfury2.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_fatfury2.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_kof98.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_kof98.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_mslugx.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_mslugx.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_cmc.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_cmc.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_sma.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_sma.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_pcm2.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_pcm2.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_kof2k2.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_kof2k2.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_pvc.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_pvc.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_cthd.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_cthd.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_kof2k3bl.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_kof2k3bl.h",
		MAME_DIR .. "src/devices/bus/neogeo/boot_kof10th.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/boot_kof10th.h",
		MAME_DIR .. "src/devices/bus/neogeo/prot_misc.cpp",
		MAME_DIR .. "src/devices/bus/neogeo/prot_misc.h",
	}
end


---------------------------------------------------
--
--@src/devices/bus/neogeo_ctrl/ctrl.h,BUSES["NEOGEO_CTRL"] = true
---------------------------------------------------

if (BUSES["NEOGEO_CTRL"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/ctrl.cpp",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/ctrl.h",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/joystick.cpp",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/joystick.h",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/mahjong.cpp",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/mahjong.h",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/dial.cpp",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/dial.h",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/irrmaze.cpp",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/irrmaze.h",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/kizuna4p.cpp",
		MAME_DIR .. "src/devices/bus/neogeo_ctrl/kizuna4p.h",
	}
end
