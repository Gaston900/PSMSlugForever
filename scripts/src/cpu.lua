-- license:BSD-3-Clause
-- copyright-holders:MAMEdev Team

---------------------------------------------------------------------------
--
--   cpu.lua
--
--   Rules for building CPU cores
--
---------------------------------------------------------------------------

--------------------------------------------------
-- Dynamic recompiler objects
--------------------------------------------------

DRC_CPUS = { "E1", "SH", "MIPS3", "POWERPC", "RSP", "ARM7", "ADSP21062", "MB86235", "DSP16", "UNSP" }
CPU_INCLUDE_DRC = false
for i, v in ipairs(DRC_CPUS) do
	if (CPUS[v]~=null) then
		CPU_INCLUDE_DRC = true
		break
	end
end


if (CPU_INCLUDE_DRC) then
	files {
		MAME_DIR .. "src/devices/cpu/drcbec.cpp",
		MAME_DIR .. "src/devices/cpu/drcbec.h",
		MAME_DIR .. "src/devices/cpu/drcbeut.cpp",
		MAME_DIR .. "src/devices/cpu/drcbeut.h",
		MAME_DIR .. "src/devices/cpu/drccache.cpp",
		MAME_DIR .. "src/devices/cpu/drccache.h",
		MAME_DIR .. "src/devices/cpu/drcfe.cpp",
		MAME_DIR .. "src/devices/cpu/drcfe.h",
		MAME_DIR .. "src/devices/cpu/drcuml.cpp",
		MAME_DIR .. "src/devices/cpu/drcuml.h",
		MAME_DIR .. "src/devices/cpu/uml.cpp",
		MAME_DIR .. "src/devices/cpu/uml.h",
		MAME_DIR .. "src/devices/cpu/x86log.cpp",
		MAME_DIR .. "src/devices/cpu/x86log.h",
		MAME_DIR .. "src/devices/cpu/drcumlsh.h",
	}
	if not _OPTIONS["FORCE_DRC_C_BACKEND"] then
		files {
			MAME_DIR .. "src/devices/cpu/drcbex64.cpp",
			MAME_DIR .. "src/devices/cpu/drcbex64.h",
			MAME_DIR .. "src/devices/cpu/drcbex86.cpp",
			MAME_DIR .. "src/devices/cpu/drcbex86.h",
		}
	end
end

--------------------------------------------------
-- Motorola 68000 series
--@src/devices/cpu/m68000/m68000.h,CPUS["M680X0"] = true
--------------------------------------------------

if (CPUS["M680X0"]~=null) then
	files {
		MAME_DIR .. "src/devices/cpu/m68000/m68kcpu.cpp",
		MAME_DIR .. "src/devices/cpu/m68000/m68kcpu.h",
		MAME_DIR .. "src/devices/cpu/m68000/m68kops.cpp",
		MAME_DIR .. "src/devices/cpu/m68000/m68kops.h",
		MAME_DIR .. "src/devices/cpu/m68000/m68000.h",
		MAME_DIR .. "src/devices/cpu/m68000/m68kfpu.hxx",
		MAME_DIR .. "src/devices/cpu/m68000/m68kmmu.h",
	}
end

if (CPUS["M680X0"]~=null or _OPTIONS["with-tools"]) then
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/m68000/m68kdasm.cpp")
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/m68000/m68kdasm.h")
end

--------------------------------------------------
-- Zilog Z80
--@src/devices/cpu/z80/z80.h,CPUS["Z80"] = true
--------------------------------------------------

if (CPUS["Z80"]~=null) then
	files {
		MAME_DIR .. "src/devices/cpu/z80/z80.cpp",
		MAME_DIR .. "src/devices/cpu/z80/z80.h",
		MAME_DIR .. "src/devices/cpu/z80/tmpz84c011.cpp",
		MAME_DIR .. "src/devices/cpu/z80/tmpz84c011.h",
		MAME_DIR .. "src/devices/cpu/z80/tmpz84c015.cpp",
		MAME_DIR .. "src/devices/cpu/z80/tmpz84c015.h",
		MAME_DIR .. "src/devices/cpu/z80/kc82.cpp",
		MAME_DIR .. "src/devices/cpu/z80/kc82.h",
		MAME_DIR .. "src/devices/cpu/z80/kl5c80a12.cpp",
		MAME_DIR .. "src/devices/cpu/z80/kl5c80a12.h",
		MAME_DIR .. "src/devices/cpu/z80/kl5c80a16.cpp",
		MAME_DIR .. "src/devices/cpu/z80/kl5c80a16.h",
		MAME_DIR .. "src/devices/cpu/z80/kp69.cpp",
		MAME_DIR .. "src/devices/cpu/z80/kp69.h",
		MAME_DIR .. "src/devices/cpu/z80/ky80.cpp",
		MAME_DIR .. "src/devices/cpu/z80/ky80.h",
		MAME_DIR .. "src/devices/cpu/z80/lz8420m.cpp",
		MAME_DIR .. "src/devices/cpu/z80/lz8420m.h",
	}
end

if (CPUS["Z80"]~=null or _OPTIONS["with-tools"]) then
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/z80/z80dasm.cpp")
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/z80/z80dasm.h")
end

--------------------------------------------------
-- NEC V-series Intel-compatible
--@src/devices/cpu/nec/nec.h,CPUS["NEC"] = true
--@src/devices/cpu/nec/v25.h,CPUS["NEC"] = true
--@src/devices/cpu/nec/v5x.h,CPUS["NEC"] = true
--@src/devices/cpu/v30mz/v30mz.h,CPUS["V30MZ"] = true
--------------------------------------------------

if (CPUS["NEC"]~=null) then
	files {
		MAME_DIR .. "src/devices/cpu/nec/nec.cpp",
		MAME_DIR .. "src/devices/cpu/nec/nec.h",
		MAME_DIR .. "src/devices/cpu/nec/necea.h",
		MAME_DIR .. "src/devices/cpu/nec/necinstr.h",
		MAME_DIR .. "src/devices/cpu/nec/necinstr.hxx",
		MAME_DIR .. "src/devices/cpu/nec/nec80inst.hxx",
		MAME_DIR .. "src/devices/cpu/nec/necmacro.h",
		MAME_DIR .. "src/devices/cpu/nec/necmodrm.h",
		MAME_DIR .. "src/devices/cpu/nec/necpriv.ipp",
		MAME_DIR .. "src/devices/cpu/nec/v25instr.h",
		MAME_DIR .. "src/devices/cpu/nec/v25instr.hxx",
		MAME_DIR .. "src/devices/cpu/nec/v25priv.ipp",
		MAME_DIR .. "src/devices/cpu/nec/v25.cpp",
		MAME_DIR .. "src/devices/cpu/nec/v25.h",
		MAME_DIR .. "src/devices/cpu/nec/v25sfr.cpp",
		MAME_DIR .. "src/devices/cpu/nec/v5x.cpp",
		MAME_DIR .. "src/devices/cpu/nec/v5x.h",
	}
end

if (CPUS["NEC"]~=null or _OPTIONS["with-tools"]) then
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/nec/necdasm.cpp")
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/nec/necdasm.h")
end

--------------------------------------------------
-- Acorn ARM series
--
--@src/devices/cpu/arm/arm.h,CPUS["ARM"] = true
--@src/devices/cpu/arm7/arm7.h,CPUS["ARM7"] = true
--------------------------------------------------

if (CPUS["ARM"]~=null) then
	files {
		MAME_DIR .. "src/devices/cpu/arm/arm.cpp",
		MAME_DIR .. "src/devices/cpu/arm/arm.h",
	}
end

if (CPUS["ARM"]~=null or _OPTIONS["with-tools"]) then
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/arm/armdasm.cpp")
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/arm/armdasm.h")
end

if (CPUS["ARM7"]~=null) then
	files {
		MAME_DIR .. "src/devices/cpu/arm7/arm7.cpp",
		MAME_DIR .. "src/devices/cpu/arm7/arm7.h",
		MAME_DIR .. "src/devices/cpu/arm7/arm7thmb.cpp",
		MAME_DIR .. "src/devices/cpu/arm7/arm7ops.cpp",
		MAME_DIR .. "src/devices/cpu/arm7/lpc210x.cpp",
		MAME_DIR .. "src/devices/cpu/arm7/lpc210x.h",
		MAME_DIR .. "src/devices/cpu/arm7/arm7core.h",
		MAME_DIR .. "src/devices/cpu/arm7/arm7core.hxx",
		MAME_DIR .. "src/devices/cpu/arm7/arm7drc.hxx",
		MAME_DIR .. "src/devices/cpu/arm7/arm7help.h",
		MAME_DIR .. "src/devices/cpu/arm7/arm7tdrc.hxx",
	}
end

if (CPUS["ARM7"]~=null or _OPTIONS["with-tools"]) then
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/arm7/arm7dasm.cpp")
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/arm7/arm7dasm.h")
end


--------------------------------------------------
-- Intel 80x86 series (also a dynamic recompiler target)
--@src/devices/cpu/i86/i86.h,CPUS["I86"] = true
--@src/devices/cpu/i86/i286.h,CPUS["I86"] = true
--@src/devices/cpu/i386/i386.h,CPUS["I386"] = true
--------------------------------------------------

if (CPUS["I86"]~=null) then
	files {
		MAME_DIR .. "src/devices/cpu/i86/i86.cpp",
		MAME_DIR .. "src/devices/cpu/i86/i86.h",
		MAME_DIR .. "src/devices/cpu/i86/i186.cpp",
		MAME_DIR .. "src/devices/cpu/i86/i186.h",
		MAME_DIR .. "src/devices/cpu/i86/i286.cpp",
		MAME_DIR .. "src/devices/cpu/i86/i286.h",
		MAME_DIR .. "src/devices/cpu/i86/i86inline.h",
	}
end

if (CPUS["I86"]~=null or CPUS["I386"]~=null or CPU_INCLUDE_DRC or _OPTIONS["with-tools"]) then
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/i386/i386dasm.cpp")
	table.insert(disasm_files , MAME_DIR .. "src/devices/cpu/i386/i386dasm.h")
end

if (CPUS["I386"]~=null) then
	files {
		MAME_DIR .. "src/devices/cpu/i386/i386.cpp",
		MAME_DIR .. "src/devices/cpu/i386/i386.h",
		MAME_DIR .. "src/devices/cpu/i386/athlon.cpp",
		MAME_DIR .. "src/devices/cpu/i386/athlon.h",
		MAME_DIR .. "src/devices/cpu/i386/cache.h",
		MAME_DIR .. "src/devices/cpu/i386/cycles.h",
		MAME_DIR .. "src/devices/cpu/i386/i386op16.hxx",
		MAME_DIR .. "src/devices/cpu/i386/i386op32.hxx",
		MAME_DIR .. "src/devices/cpu/i386/i386ops.h",
		MAME_DIR .. "src/devices/cpu/i386/i386ops.hxx",
		MAME_DIR .. "src/devices/cpu/i386/i386priv.h",
		MAME_DIR .. "src/devices/cpu/i386/i386segs.hxx",
		MAME_DIR .. "src/devices/cpu/i386/i486ops.hxx",
		MAME_DIR .. "src/devices/cpu/i386/pentops.hxx",
		MAME_DIR .. "src/devices/cpu/i386/x87ops.hxx",
		MAME_DIR .. "src/devices/cpu/i386/x87priv.h",
		MAME_DIR .. "src/devices/cpu/i386/cpuidmsrs.hxx",
	}
end
