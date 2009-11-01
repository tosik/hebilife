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

#include <iostream>

using namespace std;


#include "field.h"
#include "snake.h"


Snake::Snake(int id, Field *field)
{
	this->id = id;
	this->field = field;

	is_dead = false;

	// 動く方向の初期化
	int r = field->random(4);
	switch ( r )
	{
		case 0:
			direction_x = 0;
			direction_y = 1;
			break;
		case 1:
			direction_x = 1;
			direction_y = 0;
			break;
		case 2:
			direction_x = 0;
			direction_y = -1;
			break;
		case 3:
			direction_x = -1;
			direction_y = 0;
			break;
		default:
			break;
	}

	// 座標の初期化
	length = field->random(field->length_max-1) + 1;
	body_x[0] = field->random(field->size_x-length);
	body_y[0] = field->random(field->size_y-length);
	for ( int i = 1 ; i < length ; i ++ )
	{
		body_x[i] = body_x[i-1] - direction_x;
		body_y[i] = body_y[i-1] - direction_y;
	}
	for ( int i = length ; i < 100 ; i ++ )
	{
		body_x[i] = -1;
		body_y[i] = -1;
	}
}

Snake::Snake(int id, Field *field, Snake *s)
{
	this->id = id;
	this->field = field;

	is_dead = false;

	length = s->length / 2;
	for ( int i = 0 ; i < length ; i ++ )
	{
		body_x[i] = s->pre_body_x[i + length];
		body_y[i] = s->pre_body_y[i + length];
		pre_body_x[i] = body_x[i];
		pre_body_y[i] = body_y[i];
	}
	for ( int i = length ; i < 100 ; i ++ )
	{
		body_x[i] = -1;
		body_y[i] = -1;
	}

	// 動く方向の初期化
	direction_x = s->pre_body_x[length - 1] - s->pre_body_x[length];
	direction_y = s->pre_body_y[length - 1] - s->pre_body_y[length];

	brain.copy(&s->brain);
}

// stepする前に遺伝子により行動を決定し、仮に行動する
void Snake::pre_move()
{
	if ( is_dead )
		return;

	// bodyをpre_bodyにコピー
	for ( int i = 0 ; i < length ; i ++ )
	{
		pre_body_x[i] = body_x[i];
		pre_body_y[i] = body_y[i];
	}

	// 動く方向を決定
	int x = body_x[0];
	int y = body_y[0];
	int input[NN::N_NEURON];

	// いじって遊ぶ場所
//    input[0] = field->getHazard(x+direction_y,y-direction_x+direction_y) ? 1 : 0;
//    input[1] = field->getHazard(x+direction_y,y+direction_x+direction_y) ? 1 : 0;
	input[0] = field->getHazard(x+direction_y,y-direction_x) ? 1 : 0;
	input[1] = field->getHazard(x+direction_x*3,y+direction_y*3) ? 1 : 0;
	input[2] = field->getHazard(x+direction_y,y+direction_x) ? 1 : 0;
//    input[3] = field->getHazard(x+direction_x,y+direction_y*2) ? 1 : 0;
//    input[4] = field->getHazard(x+direction_x,y+direction_y*3) ? 1 : 0;
	int output = brain.input_and_output(input);

	if ( output == 1 )
	{
		int temp = direction_x;
		direction_x = direction_y;
		direction_y = - temp;
	}
	else if ( output == 2 )
	{
		int temp = direction_x;
		direction_x = - direction_y;
		direction_y = temp;
	}

//    if ( field->random(10) == 0 )
//    {
//        int r = field->random(4);
//        switch ( r )
//        {
//            case 0:
//                if ( direction_x == 0 && direction_y == -1 )
//                    break;
//                direction_x = 0;
//                direction_y = 1;
//                break;
//            case 1:
//                if ( direction_x == -1 && direction_y == 0 )
//                    break;
//                direction_x = 1;
//                direction_y = 0;
//                break;
//            case 2:
//                if ( direction_x == 0 && direction_y == 1 )
//                    break;
//                direction_x = 0;
//                direction_y = -1;
//                break;
//            case 3:
//                if ( direction_x == 1 && direction_y == 0 )
//                    break;
//                direction_x = -1;
//                direction_y = 0;
//                break;
//            default:
//                break;
//        }
//    }

	// その方向に動く
	for ( int i = length ; i > 0 ; i -- )
	{
		pre_body_x[i] = pre_body_x[i-1];
		pre_body_y[i] = pre_body_y[i-1];
	}
	pre_body_x[0] += direction_x;
	pre_body_y[0] += direction_y;

	// wrap
	if ( pre_body_x[0] == -1 )
		pre_body_x[0] = field->size_x - 1;
	if ( pre_body_y[0] == -1 )
		pre_body_y[0] = field->size_y - 1;
	if ( pre_body_x[0] == field->size_x )
		pre_body_x[0] = 0;
	if ( pre_body_y[0] == field->size_y )
		pre_body_y[0] = 0;

//    if ( output == 3 && length >= field->length_max )
//        segmentation();
}

void Snake::step()
{
	if ( is_dead )
		return;

	if ( field->isDead(id) )
	{
		die();
		return;
	}
	else if ( field->canEat(id) )
	{
		eat();
		if ( length >= field->length_max )
			segmentation();
	}
	move();
}

// pre_move で決定した行動を実際に行う
void Snake::move()
{
	if ( is_dead )
		return;

	for ( int i = 0 ; i < length ; i ++ )
	{
		body_x[i] = pre_body_x[i];
		body_y[i] = pre_body_y[i];
	}
}

void Snake::die()
{
	is_dead = true;

	for ( int i = 0 ; i < length; i ++ )
	{
		field->foods[body_x[i]][body_y[i]] = true;
	}
}

void Snake::eat()
{
	length++;
	if ( length == 100 )
		length --;
	field->foods[pre_body_x[0]][pre_body_y[0]] = false;
}

void Snake::segmentation()
{
	field->makeSnake(this);
	length /= 2;
}

