-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   formats.lua
--
--   Rules for building formats
--
---------------------------------------------------------------------------
function formatsProject(_target, _subtarget)
project "formats"
	uuid (os.uuid("formats-" .. _target .."_" .. _subtarget))
	kind (LIBTYPE)
	targetsubdir(_target .."_" .. _subtarget)
	addprojectflags()

	options {
		"ArchiveSplit",
	}

	includedirs {
		MAME_DIR .. "src/osd",
		MAME_DIR .. "src/emu",
		MAME_DIR .. "src/lib",
		MAME_DIR .. "src/lib/util",
		MAME_DIR .. "3rdparty",
		ext_includedir("zlib"),
	}

	files {
		MAME_DIR .. "src/lib/formats/ioprocs.cpp",
		MAME_DIR .. "src/lib/formats/ioprocs.h",
		MAME_DIR .. "src/lib/formats/imageutl.cpp",
		MAME_DIR .. "src/lib/formats/imageutl.h",

		MAME_DIR .. "src/lib/formats/cassimg.cpp",
		MAME_DIR .. "src/lib/formats/cassimg.h",
		MAME_DIR .. "src/lib/formats/wavfile.cpp",
		MAME_DIR .. "src/lib/formats/wavfile.h",

		MAME_DIR .. "src/lib/formats/flopimg.cpp",
		MAME_DIR .. "src/lib/formats/flopimg.h",

		MAME_DIR .. "src/lib/formats/cqm_dsk.cpp",
		MAME_DIR .. "src/lib/formats/cqm_dsk.h",
		MAME_DIR .. "src/lib/formats/dsk_dsk.cpp",
		MAME_DIR .. "src/lib/formats/dsk_dsk.h",
		MAME_DIR .. "src/lib/formats/td0_dsk.cpp",
		MAME_DIR .. "src/lib/formats/td0_dsk.h",
		MAME_DIR .. "src/lib/formats/hxchfe_dsk.cpp",
		MAME_DIR .. "src/lib/formats/hxchfe_dsk.h",
		MAME_DIR .. "src/lib/formats/hxcmfm_dsk.cpp",
		MAME_DIR .. "src/lib/formats/hxcmfm_dsk.h",
		MAME_DIR .. "src/lib/formats/mfi_dsk.cpp",
		MAME_DIR .. "src/lib/formats/mfi_dsk.h",
		MAME_DIR .. "src/lib/formats/imd_dsk.cpp",
		MAME_DIR .. "src/lib/formats/imd_dsk.h",
		MAME_DIR .. "src/lib/formats/ipf_dsk.cpp",
		MAME_DIR .. "src/lib/formats/ipf_dsk.h",
		MAME_DIR .. "src/lib/formats/d88_dsk.cpp",
		MAME_DIR .. "src/lib/formats/d88_dsk.h",
		MAME_DIR .. "src/lib/formats/dfi_dsk.cpp",
		MAME_DIR .. "src/lib/formats/dfi_dsk.h",
		MAME_DIR .. "src/lib/formats/fdi_dsk.cpp",
	}

end
