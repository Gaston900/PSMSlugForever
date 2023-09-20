###########################################################################
#
#   scale.mak
#
#   scale effects makefile
#
#   This is an unofficial version based on MAME.
#   Please do not send any reports from this build to the MAME team.
#
###########################################################################


SCALEOBJ = $(WINOBJ)/scale

OBJDIRS += $(SCALEOBJ)



#-------------------------------------------------
# compile-time definitions
#-------------------------------------------------

# enable USE_SCALE_EFFECTS flags
DEFS += -DUSE_SCALE_EFFECTS

# add hq2x/hq3x specific define
DEFS += -Drestrict=__restrict

# define the 64-bit without MMX
ifneq ($(PTR64),1)
DEFS += -DUSE_MMX_INTERP_SCALE
endif



#-------------------------------------------------
# scale effects framework code
#-------------------------------------------------

OSDOBJS += $(SCALEOBJ)/scale.o



#-------------------------------------------------
# scale effects objects
#-------------------------------------------------

OSDOBJS += \
	$(SCALEOBJ)/2xpm.o \
	$(SCALEOBJ)/2xsai.o \
	$(SCALEOBJ)/hq2x.o \
	$(SCALEOBJ)/hq3x.o \
	$(SCALEOBJ)/scale2x.o \
	$(SCALEOBJ)/scale3x.o \
	$(SCALEOBJ)/scanline.o \
	$(SCALEOBJ)/snes9x_render.o \
	$(SCALEOBJ)/vba_hq2x.o \
	$(SCALEOBJ)/xbrz.o \


