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

#include "snake.h"
#include "field.h"

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
using namespace std;

Field::Field()
{
	cnt = 0;
	steps = 0;
	srand((unsigned int)time(NULL));
	for ( int y = 0 ; y < size_y ; y ++ )
	{
		for ( int x = 0 ; x < size_x ; x ++ )
		{
			foods[x][y] = false;
			wall[x][y] = false;
		}
	}

//    if(false)
	// è·äQï®
	for ( int i = 0 ; i < 20 ; i ++ )
	{
		int r = rand()%3;

		if ( r == 0 )
		{
			int x = rand()%(size_x-8), y = rand()%(size_y-8);

			wall[x][y + 0] = true;
			wall[x][y + 1] = true;
			wall[x][y + 2] = true;
			wall[x][y + 3] = true;
			wall[x][y + 4] = true;
			wall[x][y + 5] = true;
			wall[x][y + 6] = true;
			wall[x][y + 7] = true;
			wall[x][y + 8] = true;

			wall[x + 1][y] = true;
			wall[x + 2][y] = true;
			wall[x + 3][y] = true;
			wall[x + 4][y] = true;
			wall[x + 5][y] = true;
			wall[x + 6][y] = true;
			wall[x + 7][y] = true;
			wall[x + 8][y] = true;

			wall[x + 8][y + 1] = true;
			wall[x + 8][y + 2] = true;
			wall[x + 8][y + 3] = true;
			wall[x + 8][y + 4] = true;
			wall[x + 8][y + 5] = true;
			wall[x + 8][y + 6] = true;
			wall[x + 8][y + 7] = true;
			wall[x + 8][y + 8] = true;

			wall[x + 1][y + 8] = true;
			wall[x + 7][y + 8] = true;
		}

		if ( r == 1 )
		{
			int x = rand()%(size_x-2), y = rand()%(size_y-2);

			wall[x + 0][y + 0] = true;
			wall[x + 0][y + 1] = true;
			wall[x + 1][y + 0] = true;
			wall[x + 1][y + 1] = true;
		}

		if ( r == 2 )
		{
			int x = rand()%(size_x-5), y = rand()%(size_y-3);

			wall[x + 0][y + 0] = true;
			wall[x + 1][y + 0] = true;
			wall[x + 2][y + 0] = true;
			wall[x + 3][y + 0] = true;
			wall[x + 4][y + 0] = true;

			wall[x + 0][y + 2] = true;
			wall[x + 1][y + 2] = true;
			wall[x + 2][y + 2] = true;
			wall[x + 3][y + 2] = true;
			wall[x + 4][y + 2] = true;

			wall[x + 4][y + 1] = true;
		}
	}
}

void Field::makeSnake(Snake *s)
{
	// ê∂ê¨Ç∑ÇÈSnakeÇÃID
	int id;

	// éÄÇÒÇæSnakeÇåüçı
	bool flag = false;
	for ( int i = 0 ; i < cnt ; i ++ )
	{
		if ( snake[i]->is_dead )
		{
			id = i;
			delete snake[i];

			flag = true;
			break;
		}
	}
	// åüçıÇ…ÉqÉbÉgÇµÇ»Ç©Ç¡ÇΩÇÁ
	if ( !flag )
		id = cnt++;

	snake[id] = new Snake(id, this, s);
}

void Field::makeSnake()
{
	// ê∂ê¨Ç∑ÇÈSnakeÇÃID
	int id;

	// éÄÇÒÇæSnakeÇåüçı
	bool flag = false;
	for ( int i = 0 ; i < cnt ; i ++ )
	{
		if ( snake[i]->is_dead )
		{
			id = i;
			delete snake[i];

			flag = true;
			break;
		}
	}
	// åüçıÇ…ÉqÉbÉgÇµÇ»Ç©Ç¡ÇΩÇÁ
	if ( !flag )
		id = cnt++;

	snake[id] = new Snake(id, this);
}

void Field::step()
{
	steps ++;
	for ( int i = 0 ; i < cnt; i ++ )
	{
		snake[i]->pre_move();
	}
	for ( int i = 0 ; i < cnt; i ++ )
	{
		snake[i]->step();
	}
}

void Field::view()
{
	cout << " --- snake --- ";

	{
		int population = 0;
		for ( int i = 0 ; i < cnt ; i ++ )
			if ( !snake[i]->is_dead )
				population ++;

		cout << " population = " << population;
	}

	cout << " steps = " << steps;
	cout << endl;

	for ( int y = 0 ; y < size_y ; y ++ )
	{
		for ( int x = 0 ; x < size_x ; x ++ )
		{
			bodies[x][y] = -1;
		}
	}
	for ( int j = 0 ; j < cnt ; j ++ )
	{
		if ( snake[j]->is_dead )
			continue;
		for ( int i = 0 ; i < snake[j]->length ; i ++ )
		{
			bodies[snake[j]->body_x[i]][snake[j]->body_y[i]] = j;
		}
	}
	for ( int y = 0 ; y < size_y ; y ++ )
	{
		for ( int x = 0 ; x < size_x ; x ++ )
		{
			if ( bodies[x][y] != -1 )
//                cout << setw(2) << bodies[x][y] ;
				cout << "o " ;
			else if ( wall[x][y] )
				cout << "@ " ;
			else if ( foods[x][y] )
				cout << ". " ;
			else
				cout << "  " ;
		}
		cout << endl;
	}
}

bool Field::isDead(int id)
{
	int x = snake[id]->pre_body_x[0];
	int y = snake[id]->pre_body_y[0];

	if ( x < 0 || x >= size_x || y < 0 || y >= size_y )
		return true;
	else if ( wall[x][y] )
		return true;
	else
	{
		for ( int j = 0 ; j < cnt ; j ++ )
		{
			if ( snake[j]->is_dead )
				continue;
			for ( int i = 0 ; i < snake[j]->length ; i ++ )
			{
				if ( snake[j]->pre_body_x[i] == x && snake[j]->pre_body_y[i] == y )
				{
					if ( j != id || i != 0 )
						return true;
				}
			}
		}
	}
	return false;
}

bool Field::canEat(int id)
{
	int x = snake[id]->pre_body_x[0];
	int y = snake[id]->pre_body_y[0];
	return foods[x][y];
}

int Field::random(int n)
{
	return rand() % n;
}

bool Field::getHazard(int x, int y)
{
	// wrap
	if ( x == -1 )
		x = size_x - 1;
	if ( y == -1 )
		y = size_y - 1;
	if ( x == size_x )
		x = 0;
	if ( y == size_y )
		y = 0;

	return bodies[x][y] != -1 || wall[x][y];
}

int Field::getBodies(int x, int y)
{
	// wrap
	if ( x == -1 )
		x = size_x - 1;
	if ( y == -1 )
		y = size_y - 1;
	if ( x == size_x )
		x = 0;
	if ( y == size_y )
		y = 0;

	return bodies[x][y];
}

int Field::getFoods(int x, int y)
{
	// wrap
	if ( x == -1 )
		x = size_x - 1;
	if ( y == -1 )
		y = size_y - 1;
	if ( x == size_x )
		x = 0;
	if ( y == size_y )
		y = 0;

	return foods[x][y];
}

Field::~Field()
{
	for ( int i = 0 ; i < cnt ; i ++ )
	{
		delete snake[i];
	}
}

