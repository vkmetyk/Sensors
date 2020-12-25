#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /Volumes/Storage/shared/vkmetyk/ccs/simplelink_cc13x2_26x2_sdk_3_30_00_03/source;/Volumes/Storage/shared/vkmetyk/ccs/simplelink_cc13x2_26x2_sdk_3_30_00_03/kernel/tirtos/packages
override XDCROOT = /Volumes/Storage/shared/vkmetyk/ccs/xdctools_3_60_02_34_core
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /Volumes/Storage/shared/vkmetyk/ccs/simplelink_cc13x2_26x2_sdk_3_30_00_03/source;/Volumes/Storage/shared/vkmetyk/ccs/simplelink_cc13x2_26x2_sdk_3_30_00_03/kernel/tirtos/packages;/Volumes/Storage/shared/vkmetyk/ccs/xdctools_3_60_02_34_core/packages;..
HOSTOS = MacOS
endif
