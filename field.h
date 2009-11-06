/*
 * hebilife. Artificial Snake Life.
 * Copyright (C) Toshiyuki Hirooka <toshi.hirooka@gmail.com> http://wasabi.in/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#pragma once

class Snake;

// SnakeÇä«óùÇ∑ÇÈ
class Field
{
	public:
		Field();
		~Field();

		void makeSnake();
		void makeSnake(Snake *s);
		void step();
		void view();

		bool isDead(int id);
		bool canEat(int id);

		int random(int n);

		static const int cnt_max = 1000;
		static const int length_max = 10;

		Snake *snake[cnt_max];
		int cnt;

		int steps;

		const static int size_x = 55;
		const static int size_y = 43;

		int bodies[size_x][size_y];
		bool foods[size_x][size_y];
		int wall[size_x][size_y];

		bool getHazard(int x, int y);
		int getBodies(int x, int y);
		int getFoods(int x, int y);
};

