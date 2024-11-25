CXX = gcc
CXXFLAGS = -Iheader_files -I$(EXERCISE4_DIR)
LDFLAGS = -lpthread
OUTPUT_DIR = output
EXERCISE1_DIR = exercise1
EXERCISE2_DIR = exercise2
EXERCISE3_DIR = exercise3
EXERCISE4_DIR = exercise4

.PHONY: all clean exercise_1 exercise_2 exercise_3 exercise_4

# Object files
OBJS1 = $(OUTPUT_DIR)/my_rand.o \
        $(OUTPUT_DIR)/ordinalPiCalculation.o \
        $(OUTPUT_DIR)/ParallelPiCalculation.o

OBJS2 = $(OUTPUT_DIR)/shared_variable_a.o \
        $(OUTPUT_DIR)/shared_variable_p.o

OBJS4 = $(OUTPUT_DIR)/r_w_lock_functions.o \
		$(OUTPUT_DIR)/my_rand.o

# Default target
all: exercise_1 exercise_2 exercise_3 exercise_4 $(OUTPUT_DIR)/pth_ll_rwl

# Build exercise 1
exercise_1: $(OUTPUT_DIR)/exercise_1

$(OUTPUT_DIR)/exercise_1: $(EXERCISE1_DIR)/exercise_1.c $(OBJS1) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OUTPUT_DIR)/my_rand.o: $(EXERCISE1_DIR)/my_rand.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/ordinalPiCalculation.o: $(EXERCISE1_DIR)/ordinalPiCalculation.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/ParallelPiCalculation.o: $(EXERCISE1_DIR)/ParallelPiCalculation.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Build exercise 2
exercise_2: $(OUTPUT_DIR)/exercise_2

$(OUTPUT_DIR)/exercise_2: $(EXERCISE2_DIR)/exercise_2.c $(OBJS2) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OUTPUT_DIR)/shared_variable_a.o: $(EXERCISE2_DIR)/shared_variable_a.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/shared_variable_p.o: $(EXERCISE2_DIR)/shared_variable_p.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Build exercise 3
exercise_3: $(OUTPUT_DIR)/exercise_3

$(OUTPUT_DIR)/exercise_3: $(EXERCISE3_DIR)/exercise_3.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Build exercise 4
exercise_4: $(OUTPUT_DIR)/exercise_4

$(OUTPUT_DIR)/exercise_4: $(EXERCISE4_DIR)/exercise_4.c $(OBJS4) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Build pth_ll_rwl
$(OUTPUT_DIR)/pth_ll_rwl: pth_ll_rwl.c $(OBJS4) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OUTPUT_DIR)/r_w_lock_functions.o: $(EXERCISE4_DIR)/r_w_lock_functions.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Output directory
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Clean
clean:
	rm -f $(OUTPUT_DIR)/exercise_1 $(OBJS1)
	rm -f $(OUTPUT_DIR)/exercise_2 $(OBJS2)
	rm -f $(OUTPUT_DIR)/exercise_3
	rm -f $(OUTPUT_DIR)/exercise_4 $(OBJS4)
	rm -f $(OUTPUT_DIR)/pth_ll_rwl
	rmdir $(OUTPUT_DIR) 2>/dev/null || true
