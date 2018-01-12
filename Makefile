all: checker #push_swap

checker:
	$(MAKE) -C check

push_swap:
	$(MAKE) -C ps

clean:
	rm -f checker push_swap
	$(MAKE) -C check cleanlibs
	# $(MAKE) -C ps cleanlibs

fclean:
	rm -f checker push_swap
	$(MAKE) -C check fcleanlibs
	# $(MAKE) -C ps fcleanlibs
