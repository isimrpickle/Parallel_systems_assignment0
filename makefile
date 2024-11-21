CXX = gcc
CXXFLAGS = -Iheader_files # Include path for header files
LDFLAGS = -lpthread       # Linker flags
OUTPUT_DIR = output
MODULES_DIR = modules

.PHONY: all clean

# Object files
OBJS = $(OUTPUT_DIR)/my_rand.o \
	$(OUTPUT_DIR)/ordinalPiCalculation.o \
	$(OUTPUT_DIR)/ParallelPiCalculation.o

all: $(OUTPUT_DIR)/main

$(OUTPUT_DIR)/main: $(MODULES_DIR)/main.c $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OUTPUT_DIR)/my_rand.o: $(MODULES_DIR)/my_rand.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/ordinalPiCalculation.o: $(MODULES_DIR)/ordinalPiCalculation.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUTPUT_DIR)/ParallelPiCalculation.o: $(MODULES_DIR)/ParallelPiCalculation.c | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $< $(LDFLAGS)

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

clean:
	rm -f $(OUTPUT_DIR)/main $(OBJS)
	rmdir $(OUTPUT_DIR) 2>/dev/null || true
