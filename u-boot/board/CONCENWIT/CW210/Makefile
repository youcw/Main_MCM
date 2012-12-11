include $(TOPDIR)/config.mk

LIB	= lib$(BOARD).a

OBJS	:= cw210.o flash.o concenwit_FAT.module
SOBJS	:= lowlevel_init.o

$(LIB):	$(OBJS) $(SOBJS)
	$(AR) crv $@ $(SOBJS) $(OBJS)

clean:
	rm -f $(SOBJS) $(OBJS)

distclean:	clean
	rm -f $(LIB) core *.bak .depend

#########################################################################

# defines $(obj).depend target
include $(SRCTREE)/rules.mk

sinclude $(obj).depend

#########################################################################
