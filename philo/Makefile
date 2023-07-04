# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 14:46:08 by shinfray          #+#    #+#              #
#    Updated: 2023/07/04 11:08:24 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:
.SILENT:

NAME:=	philo

SRCS_DIR:= src
BUILD_DIR:= build
INC_DIRS:= include

LDLIBS:=

CFLAGS:= -Wall -Wextra -Werror -Wpedantic

EXT:=	.c

SRCS_FILES:=	main

SRCS:=	${addprefix ${SRCS_DIR}/,${addsuffix ${EXT},${SRCS_FILES}}}

OBJS:=	${SRCS:%.c=${BUILD_DIR}/%.o}

DEPS:=	${OBJS:.o=.d}

CPPFLAGS:= ${addprefix -I,${INC_DIRS}} -MMD -MP -pthread

LDFLAGS:= ${addprefix -L,${LIB_DIRS}} -pthread

RM:=	rm -rf

COLOR_GREEN := \033[32m
COLOR_RESET := \033[0m

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o $@
	echo "${COLOR_GREEN}Compilation completed.${COLOR_RESET}"

${BUILD_DIR}/%.o: %.c
	mkdir -p $(dir $@)
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${BUILD_DIR}
	echo "${COLOR_GREEN}Objects cleaned.${COLOR_RESET}"

fclean: clean
	${RM} ${NAME}
	echo "${COLOR_GREEN}Executables cleaned.${COLOR_RESET}"

re: fclean all

.PHONY:	all clean fclean re

-include ${DEPS}
