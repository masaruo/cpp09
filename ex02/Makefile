# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:12:23 by mogawa            #+#    #+#              #
#    Updated: 2024/05/15 11:15:28 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	PmergeMe
CXX			:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -Wshadow -Wconversion -pedantic-errors -std=c++98 -MMD -MP
LDFLAGS		:=	
GTEST_INC	:=	-I../googletest/googletest/include -I../googletest/googlemock/include
GTEST_LIB	:=	-L../googletest/build/lib
INC			:=	-I../include
SRC			=	 \
				main.cpp
SRCDIR		:=	.
OBJDIR		:=	obj
OBJ			:=	$(SRC:%.cpp=$(OBJDIR)/%.o)
DEP			:=	$(SRC:%.cpp=$(OBJDIR)/%.d)

ifdef WITH_GTEST
CXXFLAGS	:=	-Wall -Wextra -std=c++17 $(GTEST_INC) -g3 -O0
LDFLAGS		:=	$(GTEST_LIB) -lpthread -lgtest -lgtest_main -lgmock 
SRC			=	Fixed.gtest.cpp Fixed.cpp
endif

ifdef WITH_LEAK
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-g3 -O0
endif

ifdef WITH_ASAN
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-g3 -O0 -fsanitize=address
LDFLAGS		=	-fsanitize=address
endif

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(TARGET):	$(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

# gtest: fclean
# 	$(MAKE) all WITH_GTEST=1
# 	./$(TARGET)

leak: fclean
	$(MAKE) all WITH_LEAK=1
	leaks -q --atExit -- ./$(TARGET)

debug: fclean
	$(MAKE) all WITH_ASAN=1

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(TARGET)

re: fclean
	$(MAKE) all

dev: debug
	./$(TARGET)

shuf:
	$(MAKE) all
	./$(TARGET) `gshuf -i 1-100000 -n 3000 | tr "\n" " "`

jot:
	$(MAKE) all
	./$(TARGET) `jot -r 3000 1 100000 | tr '\n' ' '`

-include $(DEP)

.PHONY: clean fclean re
