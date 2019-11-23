CFLAGS ?= -Wall -W -Werror
ifeq (${DEBUG},)
CFLAGS += -O3 -flto
LDFLAGS += -flto
else
CFLAGS += -O0 -g
endif
OBJS = n80.o xgetopt.o ihex.o
all :: n80
clean :: ; $(RM) n80 ${OBJS}
n80 : ${OBJS}
tests :: xgetopt-test
xgetopt-test : xgetopt.o xgetopt-test.c
