CC = g++
CFLAGS =
COPTFLAGS = -O3 -g

default:
	@echo "=================================================="
	@echo "To build your sorting code, use:"
	@echo "  make insert_test  # For insert_test"
	@echo "  make search_test  # For search_test"
	@echo "  make edit_distance  # For edit_distance"
	@echo ""
	@echo "To clean this subdirectory (remove object files"
	@echo "and other junk), use:"
	@echo "  make clean"
	@echo "=================================================="

insert_test: HashTable.o insert_test.cc
	$(CC) $(COPTFLAGS) -o $@ $^

search_test: HashTable.o search_test.cc
	$(CC) $(COPTFLAGS) -o $@ $^

edit_distance: edit_distance.cc
	$(CC) $(COPTFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ -c $<

clean:
	rm -f core *.o *~ insert_test search_test edit_distance