.PHONY: all
all: all-examples

FAIL_FAST ?= no
EXAMPLES = ex/example1 ex/example2 ex/example3 ex/example4 \
	ex/example5 ex/example6 ex/example7 ex/example8 ex/memory_checks \
	'ex ws/example1 ws' 'ex ws/example2 ws' 'ex ws/example3 ws' 'ex ws/example4 ws' \
	'ex ws/example5 ws' 'ex ws/example6 ws' 'ex ws/example7 ws' 'ex ws/example8 ws'
PARALLELISM ?= 1

.PHONY: all-examples
all-examples:
	@for ex in $(EXAMPLES); \
	do test_result=PASS; \
	   cp -a basic_testing.h "$$ex"/tests ;\
	   $(MAKE) -C "$$ex" clean > /dev/null || test_result=FAIL; \
	   $(MAKE) -C "$$ex" -j $(PARALLELISM) TEST_COLORS=no > "$$ex".out || test_result=FAIL ; \
	   if test -r "$$ex".expected; \
	   	then { IFS=''; while read l; \
	   	        do if fgrep -q "$$l" "$$ex".out; \
			   then : ; \
	   		   else echo "'$$ex.out' must contain '$$l'"; \
	   		        test_result=FAIL; \
	   		   fi; \
	   	        done; } < "$$ex".expected || test_result=FAIL; \
	   fi; \
	   if [ "$$test_result" = PASS ]; \
	   then echo "$$ex PASS" ; \
	        rm -f "$$ex".out; \
	   else echo  "$$ex FAIL" ; \
	        echo "check '$$ex.out' and '$$ex.expected' to see what went wrong"; \
		if [ "$(FAIL_FAST)" = "yes" ]; \
		then exit 1; \
		fi; \
	   fi; \
	done

.PHONY: clean veryclean
clean:
	rm -f *.out
	@for ex in $(EXAMPLES); do $(MAKE) -C "$$ex" clean; rm -f "$$ex.out"; done

veryclean: clean
	for ex in $(EXAMPLES); do rm -f "$$ex"/tests/basic_testing.h; done
