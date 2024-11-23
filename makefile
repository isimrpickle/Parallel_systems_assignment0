CXX = gcc
CXXFLAGS = -Iheader_files      # Include path for header files
LDFLAGS = -lpthread            # Linker flags
OUTPUT_DIR = output
EXERCISE1_DIR = exercise1
EXERCISE2_DIR = exercise2
EXERCISE3_DIR = exercise3
# .PHONY targets
.PHONY: all clean exercise_1 exercise_2 print-debug

# Object files for exercise 1
OBJS1 = $(OUTPUT_DIR)/my_rand.o \
        $(OUTPUT_DIR)/ordinalPiCalculation.o \
        $(OUTPUT_DIR)/ParallelPiCalculation.o

# Object files for exercise 2
OBJS2 = $(OUTPUT_DIR)/shared_variable_a.o \
        $(OUTPUT_DIR)/shared_variable_p.o

# Default target builds both exercises
all: exercise_1 exercise_2 exercise_3

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

# Output directory creation
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

exercise_2: $(OUTPUT_DIR)/exercise_3

$(OUTPUT_DIR)/exercise_3: $(EXERCISE3_DIR)/exercise_3.c $ | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)



# Clean all generated files
clean:
	rm -f $(OUTPUT_DIR)/exercise_1 $(OBJS1)
	rm -f $(OUTPUT_DIR)/exercise_2 $(OBJS2)
	rm -f $(OUTPUT_DIR)/exercise_3 
	rmdir $(OUTPUT_DIR) 2>/dev/null || true
