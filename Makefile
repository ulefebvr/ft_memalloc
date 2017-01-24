# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ulefebvr <ulefebvr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/26 18:52:01 by ulefebvr          #+#    #+#              #
#    Updated: 2016/12/26 18:52:05 by ulefebvr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

TARGET_EXEC ?= libft_malloc_$(HOSTTYPE).so

BUILD_DIR ?= ./build
SRC_DIRS ?= ./srcs
INC_DIR ?= ./includes ./lib/libft/includes

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(INC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -Wall -Werror -Wextra

# Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as -L.
# Libraries (-lfoo) should be added to the LDLIBS variable instead.
LDFLAGS ?= -fPIC -L ./lib/libft/ -lft -L ./lib/ft_printf -lftprintf

all: $(TARGET_EXEC) $(OBJS)

# $(TARGET_EXEC): $(OBJS)
# 	ar rc $(TARGET_EXEC) $(OBJS)
# 	ranlib $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	make -C lib/libft
	make -C lib/ft_printf
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
# ln -s $(TARGET_EXEC) libft_malloc.so

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(CC) -shared $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean fclean re norme

clean:
	$(RM) -r $(BUILD_DIR)
	make clean -C lib/libft
	make clean -C lib/ft_printf

fclean: clean
	$(RM) $(TARGET_EXEC)
	make fclean -C lib/libft
	make fclean -C lib/ft_printf

re: fclean
	make

norme:
	norminette $(SRC_DIRS) $(INC_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
