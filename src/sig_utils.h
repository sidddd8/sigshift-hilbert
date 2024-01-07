#ifndef SIG_UTILS_H
#define SIG_UTILS_H

#include <math.h>
#include <stdio.h>

#define PI 3.141592653589793238462643383279502884

typedef struct {
    float re;
    float im;
} complex;

// Prints out the reall and imaginary parts of all samples of a signal
void print_signal(complex* arr, int n);

// Copies the real and imaginary parts of all samples of a signal
// target : new copy
// orig   : original signal
// n      : lenght of the signals
void copy_signal(complex* target, complex* orig, int n);

// Normalizes elements of a signal (division by its length)
// arr : signal to be normalized
// n   : lenght of the signal
void normalize_signal(complex* arr, int n);

// Recursive Cooley-Tukey radix 2 FFT algorithm
// arr      : array to be converted into its FFT image
// n        : lenght of the array (must be a power of 2)
//direction : '1' for forward FFT, '-1' for inverse FFT  (NOTE: results are not normalized for inverse FFT)
void fft(complex* arr, int n, int direction);

// Performs 'fft()' and 'normalize_array()'
// arr      : array to be converted and normalized
// n        : lenght of the array (must be a power of 2)
//direction : '1' for forward FFT, '-1' for inverse FFT 
void normalized_fft(complex* arr, int n, int direction);

// Hilbert transformation of a signal. The original signal is unchanged, Hilbert transform is stored in the imaginary part
// arr : input array for the Hilbert transformation
// n   : lenght of the array (must be a power of 2)
void hilbert(complex* arr, int n);


#endif