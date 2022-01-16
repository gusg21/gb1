# Thanks to Job Vranish (https://spin.atomicobject.com/2016/08/26/makefile-c-projects/)
TARGET_EXEC := gbmapper

BUILD_DIR := ./build
SRC_DIRS := ./src

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. Make will incorrectly expand these otherwise.
SRCS := $(shell find $(SRC_DIRS) -name '*.c')

# String substitution for every C/C++ file.
# As an example, hello.cpp turns into ./build/hello.cpp.o
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)

# Every folder in ./src will need to be passed to GCC so that it can find header files
# INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_DIRS := lib/include/raylib
# Add a prefix to INC_DIRS. So moduleA would become -ImoduleA. GCC understands this -I flag
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Linker directions
LD_DIRS := lib/static/
LD_LIBS := raylib
FRAMEWORKS := Cocoa IOKit OpenGL CoreVideo
LDFLAGS := $(addprefix -L,$(INC_DIRS)) $(addprefix -l,$(LD_LIBS)) $(addprefix -framework ,$(FRAMEWORKS))

all: $(BUILD_DIR)/$(TARGET_EXEC)
	$(BUILD_DIR)/$(TARGET_EXEC) ../bkg.png output.h

# The final build step.
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(INC_FLAGS) $(CFLAGS) -c $< -o $@

# Empty the build dir.
.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

# Update the res/ folder in the build/ directory
.PHONY: update-res
update-res:
	cp -r res/ build/res/