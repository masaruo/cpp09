# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:12:23 by mogawa            #+#    #+#              #
#    Updated: 2024/05/19 14:58:52 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	RPN
# TARGET		:=	$(notdir $(shell pwd))
CXX			:=	c++
CXXFLAGS	:=	-Wall -Wextra -Werror -Wshadow -std=c++98 -MMD -MP
LDFLAGS		:=	
GTEST_INC	:=	-I../googletest/googletest/include -I../googletest/googlemock/include
GTEST_LIB	:=	-L../googletest/build/lib
INC			:=	-I../include
SRC			=	 \
				RPN.cpp \
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
CXXFLAGS	=	-Wall -Wextra -g3 -O0 -DDEBUG
endif

ifdef WITH_ASAN
CXXFLAGS	=	-Wall -Wextra -g3 -O0 -fsanitize=address,undefined
LDFLAGS		+=	-fsanitize=address,undefined
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

debug: fclean
	$(MAKE) all WITH_ASAN=1

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(TARGET)

re: fclean
	$(MAKE) all

dev: all
	./$(TARGET)

test:
	./$(TARGET) "8 9 * 9 - 9 - 9 - 4 - 1 +"
	./$(TARGET) "7 7 * 7 -"
	./$(TARGET) "1 2 * 2 / 2 * 2 4 - +"
	./$(TARGET) "(1 + 1)"

-include $(DEP)

.PHONY: clean fclean re dev
