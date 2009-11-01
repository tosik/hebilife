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

#include "field.h"
#include "brain.h"

class Snake
{
	public:

		Snake(int id, Field *field);
		Snake(int id, Field *field, Snake *s);
		
		// stepする前に遺伝子により行動を決定し、仮に行動する
		void pre_move();

		void step();


		// 体の長さ
		int length;

		// 体
		int body_x[100];
		int body_y[100];

		int pre_body_x[100];
		int pre_body_y[100];

		bool is_dead;

	private:
		// pre_move で決定した行動を実際に行う
		void move();

		void die();

		void eat();

		void segmentation();

		// 全てのSnakeはFieldを参照する
		Field *field;

		// 動く方向
		int direction_x;
		int direction_y;

		// オブジェクトに割り当てられるユニークな番号
		int id;

		Brain brain;
};

