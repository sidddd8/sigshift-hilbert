#ifndef SIG_UTILS_H
#define SIG_UTILS_H

#include <math.h>
#include <stdio.h>


#define PI 3.141592653589793238462643383279502884

typedef struct {
    float re;
    float im;
} complex;

void print_signal(complex* arr, int n);

void copy_signal(complex* target, complex* orig, int n);

// Normalizes elements of an array (division by its length)
// arr : array to be normalized
// n   : lenght of the array
void normalize_array(complex* arr, int n);

// Recursive Cooley-Tukey radix 2 FFT algorithm
// arr      : array to be converted
// n        : lenght of the array (must be a power of 2)
//direction : '1' for forward FFT, '-1' for inverse FFT  (NOTE: results are not normalized for inverse FFT)
void fft(complex* arr, int n, int direction);

// Performs 'fft()' and 'normalize_array()'
// arr : array to be converted and normalized
// n   : lenght of the array (must be a power of 2)
//direction : '1' for forward FFT, '-1' for inverse FFT 
void normalized_fft(complex* arr, int n, int direction);

void hilbert(complex* arr, int n);


#endif