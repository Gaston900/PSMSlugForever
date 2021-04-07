// Proyecto Shadows Mame Build Plus
// copyright-holders:Gaston90

#define BARE_BUILD_VERSION "2.3"

extern const char bare_build_version[];
extern const char build_version[];
const char bare_build_version[] = BARE_BUILD_VERSION;
#if defined(GIT_VERSION)
#define VERSION_TO_STRING(s) XVERSION_TO_STRING(s)
#define XVERSION_TO_STRING(ver) #ver
const char build_version[] = BARE_BUILD_VERSION " (" VERSION_TO_STRING(GIT_VERSION) ")";
#else
const char build_version[] = BARE_BUILD_VERSION " (" __DATE__")";
#endif
