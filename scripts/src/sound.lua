-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   sound.lua
--
--   Rules for building sound cores
--
----------------------------------------------------------------------------

files {
	MAME_DIR .. "src/devices/sound/flt_vol.cpp",
	MAME_DIR .. "src/devices/sound/flt_vol.h",
	MAME_DIR .. "src/devices/sound/flt_rc.cpp",
	MAME_DIR .. "src/devices/sound/flt_rc.h",
	MAME_DIR .. "src/devices/sound/samples.cpp",
	MAME_DIR .. "src/devices/sound/samples.h",
}

---------------------------------------------------
-- DACs
--@src/devices/sound/dac.h,SOUNDS["DAC"] = true
--@src/devices/sound/dmadac.h,SOUNDS["DMADAC"] = true
--@src/devices/sound/spkrdev.h,SOUNDS["SPEAKER"] = true
--@src/devices/sound/beep.h,SOUNDS["BEEP"] = true
---------------------------------------------------

--if (SOUNDS["DAC"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/dac.cpp",
--		MAME_DIR .. "src/devices/sound/dac.h",
--	}
--end

--if (SOUNDS["DMADAC"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/dmadac.cpp",
--		MAME_DIR .. "src/devices/sound/dmadac.h",
--	}
--end

if (SOUNDS["SPEAKER"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/spkrdev.cpp",
		MAME_DIR .. "src/devices/sound/spkrdev.h",
	}
end

--if (SOUNDS["BEEP"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/beep.cpp",
--		MAME_DIR .. "src/devices/sound/beep.h",
--	}
--end

---------------------------------------------------
-- Yamaha FM synthesizers
--@src/devices/sound/ym2151.h,SOUNDS["YM2151"] = true
--@src/devices/sound/2203intf.h,SOUNDS["YM2203"] = true
--@src/devices/sound/ym2413.h,SOUNDS["YM2413"] = true
--@src/devices/sound/2608intf.h,SOUNDS["YM2608"] = true
--@src/devices/sound/2610intf.h,SOUNDS["YM2610"] = true
--@src/devices/sound/2612intf.h,SOUNDS["YM2612"] = true
--@src/devices/sound/3812intf.h,SOUNDS["YM3812"] = true
--@src/devices/sound/3526intf.h,SOUNDS["YM3526"] = true
--@src/devices/sound/8950intf.h,SOUNDS["Y8950"] = true
--@src/devices/sound/ymf262.h,SOUNDS["YMF262"] = true
--@src/devices/sound/ymf271.h,SOUNDS["YMF271"] = true
--@src/devices/sound/ymf278b.h,SOUNDS["YMF278B"] = true
--@src/devices/sound/262intf.h,SOUNDS["YMF262"] = true
---------------------------------------------------

-- SYSTEM (M92)
if (SOUNDS["YM2151"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/ym2151.cpp",
		MAME_DIR .. "src/devices/sound/ym2151.h",
	}
end

--if (SOUNDS["YM2413"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/ym2413.cpp",
--		MAME_DIR .. "src/devices/sound/ym2413.h",
--	}
--end

if (SOUNDS["YM2203"]~=null or SOUNDS["YM2608"]~=null or SOUNDS["YM2610"]~=null or SOUNDS["YM2610B"]~=null or SOUNDS["YM2612"]~=null or SOUNDS["YM3438"]~=null) then
--if (SOUNDS["YM2203"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/2203intf.cpp",
		MAME_DIR .. "src/devices/sound/2203intf.h",
		MAME_DIR .. "src/devices/sound/ay8910.cpp",
		MAME_DIR .. "src/devices/sound/ay8910.h",
		MAME_DIR .. "src/devices/sound/fm.cpp",
		MAME_DIR .. "src/devices/sound/fm.h",
	}
--end


--if (SOUNDS["YM2608"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/2608intf.cpp",
		MAME_DIR .. "src/devices/sound/2608intf.h",
		MAME_DIR .. "src/devices/sound/ay8910.cpp",
		MAME_DIR .. "src/devices/sound/ay8910.h",
		MAME_DIR .. "src/devices/sound/fm.cpp",
		MAME_DIR .. "src/devices/sound/fm.h",
		MAME_DIR .. "src/devices/sound/ymdeltat.cpp",
		MAME_DIR .. "src/devices/sound/ymdeltat.h",
	}
--end

--if (SOUNDS["YM2610"]~=null or SOUNDS["YM2610B"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/2610intf.cpp",
		MAME_DIR .. "src/devices/sound/2610intf.h",
		MAME_DIR .. "src/devices/sound/ay8910.cpp",
		MAME_DIR .. "src/devices/sound/ay8910.h",
		MAME_DIR .. "src/devices/sound/fm.cpp",
		MAME_DIR .. "src/devices/sound/fm.h",
		MAME_DIR .. "src/devices/sound/ymdeltat.cpp",
		MAME_DIR .. "src/devices/sound/ymdeltat.h",
	}
--end

--if (SOUNDS["YM2612"]~=null or SOUNDS["YM3438"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/2612intf.cpp",
		MAME_DIR .. "src/devices/sound/2612intf.h",
		MAME_DIR .. "src/devices/sound/ay8910.cpp",
		MAME_DIR .. "src/devices/sound/ay8910.h",
		MAME_DIR .. "src/devices/sound/fm2612.cpp",
	}
--end
end

--if (SOUNDS["YM3812"]~=null or SOUNDS["YM3526"]~=null or SOUNDS["Y8950"]~=null) then
--if (SOUNDS["YM3812"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/3812intf.cpp",
--		MAME_DIR .. "src/devices/sound/3812intf.h",
--		MAME_DIR .. "src/devices/sound/fmopl.cpp",
--		MAME_DIR .. "src/devices/sound/fmopl.h",
--		MAME_DIR .. "src/devices/sound/ymdeltat.cpp",
--		MAME_DIR .. "src/devices/sound/ymdeltat.h",
--	}
--end

--if (SOUNDS["YM3526"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/3526intf.cpp",
--		MAME_DIR .. "src/devices/sound/3526intf.h",
--		MAME_DIR .. "src/devices/sound/fmopl.cpp",
--		MAME_DIR .. "src/devices/sound/fmopl.h",
--		MAME_DIR .. "src/devices/sound/ymdeltat.cpp",
--		MAME_DIR .. "src/devices/sound/ymdeltat.h",
--	}
--end

--if (SOUNDS["Y8950"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/8950intf.cpp",
--		MAME_DIR .. "src/devices/sound/8950intf.h",
--		MAME_DIR .. "src/devices/sound/fmopl.cpp",
--		MAME_DIR .. "src/devices/sound/fmopl.h",
--		MAME_DIR .. "src/devices/sound/ymdeltat.cpp",
--		MAME_DIR .. "src/devices/sound/ymdeltat.h",
--	}
--end
--end

--if (SOUNDS["YMF262"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/ymf262.cpp",
--		MAME_DIR .. "src/devices/sound/ymf262.h",
--		MAME_DIR .. "src/devices/sound/262intf.cpp",
--		MAME_DIR .. "src/devices/sound/262intf.h",
--	}
--end

--if (SOUNDS["YMF271"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/ymf271.cpp",
--		MAME_DIR .. "src/devices/sound/ymf271.h",
--	}
--end

--if (SOUNDS["YMF278B"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/ymf278b.cpp",
--		MAME_DIR .. "src/devices/sound/ymf278b.h",
--	}
--end

-- SYSTEM (M92)
---------------------------------------------------
-- Irem custom sound chips
--@src/devices/sound/iremga20.h,SOUNDS["IREMGA20"] = true
---------------------------------------------------

if (SOUNDS["IREMGA20"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/iremga20.cpp",
		MAME_DIR .. "src/devices/sound/iremga20.h",
	}
end


---------------------------------------------------
-- OKI ADPCM sample players
--@src/devices/sound/okim6258.h,SOUNDS["OKIM6258"] = true
--@src/devices/sound/msm5205.h,SOUNDS["MSM5205"] = true
--@src/devices/sound/msm5232.h,SOUNDS["MSM5232"] = true
--@src/devices/sound/okim6376.h,SOUNDS["OKIM6376"] = true
--@src/devices/sound/okim6295.h,SOUNDS["OKIM6295"] = true
--@src/devices/sound/okim9810.h,SOUNDS["OKIM9810"] = true
--@src/devices/sound/okiadpcm.h,SOUNDS["OKIADPCM"] = true
---------------------------------------------------

if (SOUNDS["OKIM6258"]~=null or SOUNDS["OKIM6295"]~=null or SOUNDS["OKIM9810"]~=null or SOUNDS["I5000_SND"]~=null or SOUNDS["OKIADPCM"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/okiadpcm.cpp",
		MAME_DIR .. "src/devices/sound/okiadpcm.h",
	}
end

--if (SOUNDS["MSM5205"]~=null or SOUNDS["MSM6585"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/msm5205.cpp",
--		MAME_DIR .. "src/devices/sound/msm5205.h",
--	}
--end

--if (SOUNDS["MSM5232"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/msm5232.cpp",
--		MAME_DIR .. "src/devices/sound/msm5232.h",
--	}
--end

--if (SOUNDS["OKIM6376"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/okim6376.cpp",
--		MAME_DIR .. "src/devices/sound/okim6376.h",
--	}
--end

if (SOUNDS["OKIM6295"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/okim6295.cpp",
		MAME_DIR .. "src/devices/sound/okim6295.h",
	}
end

--if (SOUNDS["OKIM6258"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/okim6258.cpp",
--		MAME_DIR .. "src/devices/sound/okim6258.h",
--	}
--end

--if (SOUNDS["OKIM9810"]~=null) then
--	files {
--		MAME_DIR .. "src/devices/sound/okim9810.cpp",
--		MAME_DIR .. "src/devices/sound/okim9810.h",
--	}
--end

-- SYSTEM (PGM)
---------------------------------------------------
-- ICS2115 sound chip
--@src/devices/sound/ics2115.h,SOUNDS["ICS2115"] = true
---------------------------------------------------

if (SOUNDS["ICS2115"]~=null) then
	files {
		MAME_DIR .. "src/devices/sound/ics2115.cpp",
		MAME_DIR .. "src/devices/sound/ics2115.h",
	}
end


