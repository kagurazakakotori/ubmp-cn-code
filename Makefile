DIRS = baremetal/ gnuefi/

all:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE)); \
	done

clean:
	for i in $(DIRS); do \
		(cd $$i && $(MAKE) clean); \
	done
