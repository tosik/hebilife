#
# hebilife. Artificial Snake Life.
# Copyright (C) Toshiyuki Hirooka <toshi.hirooka@gmail.com> http://wasabi.in/
# 
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
#


PROJECT_NAME	= hebilife
SRCS		= main.cpp brain.cpp field.cpp snake.cpp
OBJS		= $(SRCS:.cpp=.o)

CC	= g++
CFLAGS	= -O2 -Wall
LDFLAGS	= 
MAKE	= make

all:	$(PROJECT_NAME)

$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<


.PHONY: clean
clean:
	rm -f $(OBJS)
	rm -f $(PROJECT_NAME)

