# Makefile - 2014-04-09 20:09
#
# Copyright (c) 2014 Paul Houghton <paul4hough@gmail.com>
#

CFLAGS		= -Wall
CPPFLAGS	= -I.

PROGRAM = basecv

C_SOURCES	=				\
	main.c					\
	options.c

OBJECTS		= $(C_SOURCES:.c=.o)

default: ${PROGRAM}

clean:
	rm -f ${PROGRAM} $(OBJECTS)

${PROGRAM}: ${OBJECTS}
	${CC} ${OBJECTS} -o $@

check: ${PROGRAM}
	echo 12 | ./${PROGRAM} -i 10 -o 16
	./${PROGRAM} -h || exit 0

install:
	install ${PROGRAM} /usr/local/bin

.wiki_tmp:
	mkdir -p $@

update_wiki: .wiki_tmp
	pushd .wiki_tmp;					\
	[ -d dtree.wiki ]					\
	  || git clone git@github.com:pahoughton/dtree.wiki;	\
	cd dtree.wiki && git pull;				\
	cp ../../README.md Home.md;				\
	if git diff --exit-code ; then				\
	  echo no changes;					\
	else							\
	  git add Home.md;					\
	  git commit -m 'updated from README.md';		\
	  git push;						\
	fi
