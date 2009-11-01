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

class NN
{
	public:
//        static const int N_NEURON_LAYER = 2;
//        static const int N_NEURON = 2;
		static const int N_NEURON_LAYER = 3;
		static const int N_NEURON = 3;
//        static const int N_NEURON_LAYER = 6;
//        static const int N_NEURON = 6;
//        static const int N_NEURON_LAYER = 16;
//        static const int N_NEURON = 16;

		/** ニューロンの状態を記録 */
		int neurons[N_NEURON_LAYER][N_NEURON];

		/** ニューロン同士の結合荷重 */
		float weight[N_NEURON_LAYER][N_NEURON][N_NEURON];

		NN();

		int* step(int input[N_NEURON]);

};


class Brain
{
	public:
		Brain();

		NN nn;
		int input_and_output(int *input);
		void copy(Brain *b);
};

