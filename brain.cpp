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

#include "brain.h"
#include <stdlib.h>

NN::NN()
{
	for(int y=0; y<N_NEURON_LAYER; y++)
		for(int x=0; x<N_NEURON; x++)
			neurons[y][x] = 0;
	for(int z=0; z<N_NEURON; z++)
		for(int y=0; y<N_NEURON; y++)
			for(int x=0; x<N_NEURON_LAYER; x++)
				weight[x][y][z] = 0;
	return;
}


int* NN::step(int input[N_NEURON])
{
	// ì¸óÕÇì¸óÕëwÇ÷îΩâf
	for(int n=0; n<N_NEURON; n++)
	{
		neurons[0][n] = input[n];
	}

	// äeëwÇââéZ
	for(int layer=1; layer<N_NEURON_LAYER; layer++)
	{
		for(int y=0; y<N_NEURON; y++)
		{
			int t = 0;
			for(int x=0; x<N_NEURON; x++)
			{
				t += (int)(weight[layer-1][y][x] * neurons[layer-1][x]);
				if(t - 0.5 >= 0)
					neurons[layer][y] = 1;
				else
					neurons[layer][y] = 0;
			}
		}
	}

	// èoóÕëwÇèoóÕ
	return neurons[N_NEURON_LAYER-1];
}

Brain::Brain()
{
	for(int y=0; y<NN::N_NEURON_LAYER; y++)
		for(int x=0; x<NN::N_NEURON; x++)
			nn.neurons[y][x] = 0;
	for(int z=0; z<NN::N_NEURON; z++)
		for(int y=0; y<NN::N_NEURON; y++)
			for(int x=0; x<NN::N_NEURON_LAYER; x++)
			{
				nn.weight[x][y][z] = 0.5;
				for ( int i = 0 ; i < 5 ; i ++ )
					nn.weight[x][y][z] += rand() % 2 == 1 ? 0.1 : -0.1;
				if ( nn.weight[x][y][z] < 0 )
					nn.weight[x][y][z] = 0;
				if ( nn.weight[x][y][z] > 1 )
					nn.weight[x][y][z] = 1;
			}
}

int Brain::input_and_output(int *input)
{
	int *output = nn.step(input);
	return output[0] * 2 + output[1];
}

void Brain::copy(Brain *b)
{
	for(int y=0; y<NN::N_NEURON_LAYER; y++)
		for(int x=0; x<NN::N_NEURON; x++)
			nn.neurons[y][x] = b->nn.neurons[y][x];
	for(int z=0; z<NN::N_NEURON; z++)
		for(int y=0; y<NN::N_NEURON; y++)
			for(int x=0; x<NN::N_NEURON_LAYER; x++)
				nn.weight[x][y][z] = b->nn.weight[x][y][z];

	// ìÀëRïœàŸ
	for ( int i = 0 ; i < 100 ; i ++ )
		nn.weight[rand()%NN::N_NEURON_LAYER][rand()%NN::N_NEURON][rand()%NN::N_NEURON] += 0.1 * ( rand()%2 == 0 ? -1 : 1 );
}

