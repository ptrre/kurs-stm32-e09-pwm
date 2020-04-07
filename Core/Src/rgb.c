/* The MIT License
 *
 * Copyright (c) 2020 Piotr Duba
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <stdlib.h>
#include "rgb.h"
#include "tim.h"

/* ustawienie wartosci 3 kanalow PWM timera 3 */
void set_color(uint16_t h, uint8_t s, uint8_t v)
{
	uint16_t r, g, b;
	hsv2rgb(h, s, v, &r, &g, &b);

	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, r);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, g);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b);
}

/* konwersja HSV na RGB - przeskalowane 0 - 1000 (dostosowane pod PWM) */
void hsv2rgb(uint16_t h, uint8_t s, uint8_t v, uint16_t * R, uint16_t * G, uint16_t * B)
{
	uint16_t c, m, hp, x;

    c = s * v / 10;
	hp = h * 100 / 60;
	x = c * (100- abs((hp % 200) - 100)) / 100;
	m = (v * 10) - c;

    switch((h / 60))
    {
    	case 0:
            *R = c + m;
            *G = x + m;
            *B = m;
            break;
        case 1:
            *R = x + m;
            *G = c + m;
            *B = m;
            break;
        case 2:
        	*R = m;
            *G = c + m;
            *B = x + m;
            break;
        case 3:
        	*R = m;
            *G = x + m;
            *B = c + m;
            break;
        case 4:
            *R = x + m;
            *G = m;
            *B = c + m;
            break;
        case 5:
            *R = c + m;
            *G = m;
            *B = x + m;
            break;
    }

}
