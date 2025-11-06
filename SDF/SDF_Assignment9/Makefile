COMPILER := gcc
FLAGS_COMPILER := -O2 -I ./include

ifeq ($(DEBUG),1)
	FLAGS_COMPILER+=-g -DDEBUG
endif

MATHOPS_FILES := $(foreach file, $(shell ls ./src/mathop/*.c), $(file))
STRINGOPS_FILES := $(foreach file, $(shell ls ./src/stringop/*.c), $(file))
DATAOPS_FILES := $(foreach file, $(shell ls ./src/dataop/*.c), $(file))
ALLOPS_FILES := ./src/main.c ./src/dataop/dataop.c ./src/mathop/mathop.c ./src/stringop/stringop.c

MATHOPS_DEP := $(foreach file, $(MATHOPS_FILES), $(file:.c=.o))
STRINGOPS_DEP := $(foreach file, $(STRINGOPS_FILES), $(file:.c=.o))
DATAOPS_DEP := $(foreach file, $(DATAOPS_FILES), $(file:.c=.o))
ALLOPS_DEP := $(foreach file, $(ALLOPS_FILES), $(file:.c=.o))

HEADER_D_FILES := $(foreach file, $(MATHOPS_DEP), $(file:.o=.d))
HEADER_D_FILES+=$(foreach file, $(STRINGOPS_DEP), $(file:.o=.d))
HEADER_D_FILES+=$(foreach file, $(DATAOPS_DEP), $(file:.o=.d))
HEADER_D_FILES+=$(foreach file, $(ALLOPS_DEP), $(file:.o=.d))

-include $(HEADER_D_FILES)
.PHONY: all clean run_math run_data run_string run_all_ops

all: math_ops string_ops data_ops all_ops

all_ops: $(ALLOPS_DEP)
	$(COMPILER) $(FLAGS_COMPILER) $^ -o all_ops

math_ops: $(MATHOPS_DEP)
	$(COMPILER) $(FLAGS_COMPILER) $^ -o math_ops

string_ops: $(STRINGOPS_DEP)
	$(COMPILER) $(FLAGS_COMPILER) $^ -o string_ops

data_ops: $(DATAOPS_DEP)
	$(COMPILER) $(FLAGS_COMPILER) $^ -o data_ops

run_all_ops:
	@[ -f ./all_ops ] && ./all_ops || echo "all_ops does not exist yet. run -> make all or -> make all_ops"

run_math:
	@[ -f ./math_ops ] && ./math_ops || echo "math_ops does not exist yet. run -> make all or -> make math_ops"

run_string:
	@[ -f ./string_ops ] && ./string_ops || echo "string_ops does not exist yet. run -> make all or -> make string_ops"

run_data:
	@[ -f ./data_ops ] && ./data_ops || echo "data_ops does not exist yet. run -> make all or -> make data_ops"


%.o: %.c
	$(COMPILER) $(FLAGS_COMPILER) -MMD -MF $(@:.o=.d) -MT $@ -c $< -o $@

clean:
	rm -f $(MATHOPS_DEP) $(DATAOPS_DEP) $(STRINGOPS_DEP) $(ALLOPS_DEP) $(HEADER_D_FILES)
	rm -f ./all_ops ./string_ops ./math_ops ./data_ops