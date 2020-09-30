.PHONY: all
all: all-examples

EXAMPLES = example1 example2 example3 example4
HEADERS = example1/tests/basic_testing.h \
	example2/tests/basic_testing.h \
	example3/tests/basic_testing.h \
	example4/tests/basic_testing.h 

example%/tests/basic_testing.h: basic_testing.h
	cp basic_testing.h $@

.PHONY: all-examples
all-examples: $(HEADERS)
	@for ex in $(EXAMPLES); \
	do test_result=PASS; \
	   $(MAKE) -C $$ex clean > /dev/null || test_result=FAIL; \
	   $(MAKE) -C $$ex > $$ex.out || test_result=FAIL ; \
	   if test -r $$ex.expected; \
	   	then { while read l; \
	   	       do if fgrep -q "$l" "$$ex.out"; \
			  then : ; \
	   		  else echo "$$ex.out must contain '$$l'"; \
	   		       test_result=FAIL; \
	   		  fi; \
	   	       done; } < $$ex.expected || test_result=FAIL; \
	   fi; \
	   if [ "$$test_result" = PASS ]; \
	   then echo "$$ex PASS" ; \
	        rm -f $$ex.out; \
	   else echo  "$$ex FAIL" ; \
	        echo "check $$ex.out and $$ex.expected to see what went wrong"; \
	   fi; \
	done

.PHONY: clean veryclean
clean:
	rm -f *.out
	@for ex in $(EXAMPLES); do $(MAKE) -C $$ex clean; done

veryclean: clean
	rm -f $(HEADERS)

