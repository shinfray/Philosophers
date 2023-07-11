# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shinfray <shinfray@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/03 14:46:08 by shinfray          #+#    #+#              #
#    Updated: 2023/07/11 17:07:57 by shinfray         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


################################################################################
#                                 CONFIG                                       #
################################################################################

.DELETE_ON_ERROR:
.SILENT:

NAME:=	philo

SRCS_DIR:= src
BUILD_DIR:= build
INC_DIRS:= include

LDLIBS:=
LIB_DIRS:=

CFLAGS= -std=c17 -Wall -Wextra -Werror -Wpedantic -pedantic-errors -O3

CFLAGS+=	-Wcast-qual \
			-Wconversion \
			-Wdouble-promotion \
			-Wfloat-equal \
			-Wformat=2 \
			-Winit-self \
			-fno-common \
			-Wshadow \
			-Wundef \
			-Wunused-macros \
			-Wwrite-strings \
			-Wmissing-prototypes \
			-Wmissing-declarations \
			-Wstrict-prototypes
#			-Wpadded \

#			gcc flags only
#			-Wformat-overflow \
			-Wformat-truncation \
			-Wlogical-op \
			-Wformat-signedness \
			-Wduplicated-cond \
			-Wduplicated-branches \
			-Walloc-zero

ADDITIONAL_CPPFLAGS:= -pthread
ADDITIONAL_LDFLAGS:= -pthread

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

EXT:=	.c

MAIN:=	main

SRCS_FILES:=	parsing/parse \
				initialization/initialize \
				cleaning/clean \
				threads/threads

################################################################################
#                                 SRC's FORMATING                              #
################################################################################

SRCS:=	${addprefix ${SRCS_DIR}/,${addsuffix ${EXT},${MAIN} ${SRCS_FILES}}}

OBJS:=	${SRCS:%.c=${BUILD_DIR}/%.o}

DEPS:=	${OBJS:.o=.d}

CPPFLAGS= ${addprefix -I,${INC_DIRS}} -MMD -MP
CPPFLAGS+= ${ADDITIONAL_CPPFLAGS}

LDFLAGS= ${addprefix -L,${LIB_DIRS}}
LDFLAGS+= ${ADDITIONAL_LDFLAGS}

RM:=	rm -rf

COLOR_GREEN := \033[32m
COLOR_RESET := \033[0m

################################################################################
#                                 Makefile rules                               #
################################################################################

all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${LDFLAGS} ${OBJS} ${LDLIBS} -o $@ -fsanitize=address
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
