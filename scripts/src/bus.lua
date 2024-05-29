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


---------------------------------------------------
--
--@src/devices/bus/midi/midi.h,BUSES["MIDI"] = true
---------------------------------------------------

if (BUSES["MIDI"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/midi/midi.cpp",
		MAME_DIR .. "src/devices/bus/midi/midi.h",
		MAME_DIR .. "src/devices/bus/midi/midiinport.cpp",
		MAME_DIR .. "src/devices/bus/midi/midiinport.h",
		MAME_DIR .. "src/devices/bus/midi/midioutport.cpp",
		MAME_DIR .. "src/devices/bus/midi/midioutport.h",
	}
end


---------------------------------------------------
--
--@src/devices/bus/snes/snes_slot.h,BUSES["SNES"] = true
---------------------------------------------------

if (BUSES["SNES"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/snes/snes_slot.cpp",
		MAME_DIR .. "src/devices/bus/snes/snes_slot.h",
		MAME_DIR .. "src/devices/bus/snes/snes_carts.cpp",
		MAME_DIR .. "src/devices/bus/snes/snes_carts.h",
		MAME_DIR .. "src/devices/bus/snes/bsx.cpp",
		MAME_DIR .. "src/devices/bus/snes/bsx.h",
		MAME_DIR .. "src/devices/bus/snes/event.cpp",
		MAME_DIR .. "src/devices/bus/snes/event.h",
		MAME_DIR .. "src/devices/bus/snes/rom.cpp",
		MAME_DIR .. "src/devices/bus/snes/rom.h",
		MAME_DIR .. "src/devices/bus/snes/rom21.cpp",
		MAME_DIR .. "src/devices/bus/snes/rom21.h",
		MAME_DIR .. "src/devices/bus/snes/sa1.cpp",
		MAME_DIR .. "src/devices/bus/snes/sa1.h",
		MAME_DIR .. "src/devices/bus/snes/sdd1.cpp",
		MAME_DIR .. "src/devices/bus/snes/sdd1.h",
		MAME_DIR .. "src/devices/bus/snes/sfx.cpp",
		MAME_DIR .. "src/devices/bus/snes/sfx.h",
		MAME_DIR .. "src/devices/bus/snes/sgb.cpp",
		MAME_DIR .. "src/devices/bus/snes/sgb.h",
		MAME_DIR .. "src/devices/bus/snes/spc7110.cpp",
		MAME_DIR .. "src/devices/bus/snes/spc7110.h",
		MAME_DIR .. "src/devices/bus/snes/sufami.cpp",
		MAME_DIR .. "src/devices/bus/snes/sufami.h",
		MAME_DIR .. "src/devices/bus/snes/upd.cpp",
		MAME_DIR .. "src/devices/bus/snes/upd.h",
	}
end


---------------------------------------------------
--
--@src/devices/bus/snes_ctrl/ctrl.h,BUSES["SNES_CTRL"] = true
---------------------------------------------------

if (BUSES["SNES_CTRL"]~=null) then
	files {
		MAME_DIR .. "src/devices/bus/snes_ctrl/ctrl.cpp",
		MAME_DIR .. "src/devices/bus/snes_ctrl/ctrl.h",
		MAME_DIR .. "src/devices/bus/snes_ctrl/bcbattle.cpp",
		MAME_DIR .. "src/devices/bus/snes_ctrl/bcbattle.h",
		MAME_DIR .. "src/devices/bus/snes_ctrl/joypad.cpp",
		MAME_DIR .. "src/devices/bus/snes_ctrl/joypad.h",
		MAME_DIR .. "src/devices/bus/snes_ctrl/miracle.cpp",
		MAME_DIR .. "src/devices/bus/snes_ctrl/miracle.h",
		MAME_DIR .. "src/devices/bus/snes_ctrl/mouse.cpp",
		MAME_DIR .. "src/devices/bus/snes_ctrl/mouse.h",
		MAME_DIR .. "src/devices/bus/snes_ctrl/multitap.cpp",
		MAME_DIR .. "src/devices/bus/snes_ctrl/multitap.h",
		MAME_DIR .. "src/devices/bus/snes_ctrl/pachinko.cpp",
		MAME_DIR .. "src/devices/bus/snes_ctrl/pachinko.h",
		MAME_DIR .. "src/devices/bus/snes_ctrl/sscope.cpp",
		MAME_DIR .. "src/devices/bus/snes_ctrl/sscope.h",
		MAME_DIR .. "src/devices/bus/snes_ctrl/twintap.cpp",
		MAME_DIR .. "src/devices/bus/snes_ctrl/twintap.h",
	}
end


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
