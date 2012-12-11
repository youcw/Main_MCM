SUBDIRS=eeprom register led beep ds18b20 adc
all:
	@for dir in $(SUBDIRS); do \
		(cd $$dir; $(MAKE) all); \
		done
clean:
	@for dir in $(SUBDIRS); do \
		(cd $$dir; $(MAKE) clean); \
		done

