# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:12:23 by mogawa            #+#    #+#              #
#    Updated: 2024/05/27 11:40:30 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	PmergeMe
CXX			:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -MMD -MP
LDFLAGS		:=	
GTEST_INC	:=	-I../googletest/googletest/include -I../googletest/googlemock/include
GTEST_LIB	:=	-L../googletest/build/lib
INC			:=	-I../include -I./include
SRC			=	 \
				XString.cpp \
				main.cpp
SRCDIR		:=	src
OBJDIR		:=	obj
OBJ			:=	$(SRC:%.cpp=$(OBJDIR)/%.o)
DEP			:=	$(SRC:%.cpp=$(OBJDIR)/%.d)

ifdef WITH_LEAK
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-g3 -O0
endif

ifdef WITH_ASAN
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-g3 -O0 -fsanitize=address,undefined -Wshadow -Wconversion -Wno-sign-conversion -pedantic-errors
LDFLAGS		:=	-fsanitize=address,undefined
endif

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(TARGET):	$(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

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

dev: 
	./$(TARGET) 9 2 21 15 20 3 7 1 6 11 17 4 19 16 10 13 18 5 12 22 8 14

shuf:
	$(MAKE) all
	./$(TARGET) `gshuf -i 1-100000 -n 3000 | tr "\n" " "`

jot:
	$(MAKE) all
	./$(TARGET) `jot -r 3000 1 100000 | tr '\n' ' '`

-include $(DEP)

.PHONY: clean fclean re
