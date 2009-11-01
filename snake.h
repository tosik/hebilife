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
		
		// step����O�Ɉ�`�q�ɂ��s�������肵�A���ɍs������
		void pre_move();

		void step();


		// �̂̒���
		int length;

		// ��
		int body_x[100];
		int body_y[100];

		int pre_body_x[100];
		int pre_body_y[100];

		bool is_dead;

	private:
		// pre_move �Ō��肵���s�������ۂɍs��
		void move();

		void die();

		void eat();

		void segmentation();

		// �S�Ă�Snake��Field���Q�Ƃ���
		Field *field;

		// ��������
		int direction_x;
		int direction_y;

		// �I�u�W�F�N�g�Ɋ��蓖�Ă��郆�j�[�N�Ȕԍ�
		int id;

		Brain brain;
};

