#
# $Id$
#
# MAKEFILE GNU MAKE for Linux Version 1.0
# Copyright (C) 2002 by Free Software Foundation, Inc.
# Author: Antonio Téllez Flores <atellezf@yahoo.com.mx>
#
#                         COPYING
#
# This  program  is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License  as
# published by the Free Software Foundation; either version 2, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty  of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE.  See  the
# GNU General Public License for more details.
#
# You  should  have  received  a  copy  of the GNU General Public
# License along with this program; if  not,  write  to  the  Free
# Software Foundation, Inc., 675  Mass  Ave, Cambridge, MA 02139,
# USA.
#
# ###################### Revision History #######################
#
# $Log$
# ###############################################################

#================================================================
# GNU C COMPILER FOR LINUX
#================================================================
#CFLAGS := -g -ggdb -I.
# Make declarations

CC := gcc
LINKER := gcc
CFLAGS := -g -ggdb -O
LDFLAGS := 
CFILES := $(wildcard *.c)
OBJS := $(patsubst %.c, %.o, $(CFILES))
PROGRAM := labolsa
RM := rm -f
INSTALAR := cp $(PROGRAM) /usr/bin/

#----------------------------------------------------------------

# Make rules

.PHONY: all clean distclean

compile: $(PROGRAM)

all:	clean compile
	@echo -en "\n"
clean:
	$(RM) *~ core $(OBJS) "#*"

distclean: clean
	$(RM) $(PROGRAM)

install:
	$(INSTALAR)
#----------------------------------------------------------------

# Make depend

$(OBJS): %.o: %.c
	$(CC) -c $< 
	@echo -en "\n"

$(PROGRAM): $(OBJS)
	$(LINKER) $(LDFLAGS) $(OBJS) -lm -o $(PROGRAM)

#---------------------------------------------------------------

# End Make
