OUTPUT_DIR := Debug
OUTPUT_FILE := ${OUTPUT_DIR}/munchlex

C_SRC := src/main.c src/parser.c src/threading.c src/tree.c src/flagger.c

C_OBJS := $(C_SRC:%.c=${OUTPUT_DIR}/%.o)

CCOMPILER := gcc
CFLAGS := -c -O2 -Wall -Werror -ggdb -c -I"./src/include" -pthread -fsanitize=thread

# compile

$(C_OBJS): $(OUTPUT_DIR)/%.o : %.c
	@echo Compiling: $<
	@mkdir -p $(@D)
	@$(CCOMPILER) $(CFLAGS) -o "$@" "$<"

# link

all:	clean $(OUTPUT_FILE)

$(OUTPUT_FILE) : $(C_OBJS)
	@echo Linking: $@
	@$(CCOMPILER) -o "$(OUTPUT_FILE)" $(C_OBJS) -pthread -fsanitize=thread

.PHONY: clean
clean: 
	@echo Cleaning Debug
	@rm -rf $(OUTPUT_DIR)



