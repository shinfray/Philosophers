# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/11 17:10:39 by shinfray          #+#    #+#              #
#    Updated: 2023/07/03 08:55:35 by shinfray         ###   ########.fr        #
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

CPPFLAGS:= ${addprefix -I,${INC_DIRS}} -MMD -MP

LDFLAGS:= ${addprefix -L,${LIB_DIRS}}

RM:=	rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o $@

${BUILD_DIR}/%.o: %.c
	mkdir -p $(dir $@)
	${CC} ${CPPFLAGS} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${BUILD_DIR}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re

-include ${DEPS}
