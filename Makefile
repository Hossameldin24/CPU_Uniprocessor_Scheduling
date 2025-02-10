all: compile

compile: Scheduler.o InputParser.o Process.o
	g++ -std=c++11 -Wall -Wextra -o main Scheduler.o InputParser.o Process.o

Scheduler.o: Scheduler.cpp
	g++ -std=c++11 -Wall -Wextra -c Scheduler.cpp

InputParser.o: InputParser.cpp
	g++ -std=c++11 -Wall -Wextra -c InputParser.cpp

Process.o: Process.cpp
	g++ -std=c++11 -Wall -Wextra -c Process.cpp

output_dir:
	rm -rf outputs
	mkdir -p outputs

test: compile output_dir
	@for file in testcases/*input.txt; do \
		echo "Executing test $$file"; \
		basename=$$(basename "$$file" | sed 's/input/output/'); \
		cat "$$file" | ./main > outputs/$$basename; \
	done

	@if diff -q outputs testcases --exclude="*input.txt"; then \
		echo "All tests passed successfully!"; \
	else \
		echo "Some tests failed. Please check the differences."; \
	fi

clean:
	rm -f Scheduler.o InputParser.o Process.o main
	rm -rf outputs

.PHONY: all clean compile test output_dir
