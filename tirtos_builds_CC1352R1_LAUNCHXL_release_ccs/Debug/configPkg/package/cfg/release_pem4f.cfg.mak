# invoke SourceDir generated makefile for release.pem4f
release.pem4f: .libraries,release.pem4f
.libraries,release.pem4f: package/cfg/release_pem4f.xdl
	$(MAKE) -f /Users/vkmetyk/Work/Iot/sensors/tirtos_builds_CC1352R1_LAUNCHXL_release_ccs/src/makefile.libs

clean::
	$(MAKE) -f /Users/vkmetyk/Work/Iot/sensors/tirtos_builds_CC1352R1_LAUNCHXL_release_ccs/src/makefile.libs clean

