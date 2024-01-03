#include "fft.h"

inline void normalize_array(complex* arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i].re /= n;
        arr[i].im /= n;
    }
}

inline void fft(complex* arr, int n, int direction) {
    if (n <= 1) {
        return;
    }

    complex arr_even[n/2];
    complex arr_odd[n/2];

    for (int i = 0; i < n/2; ++i) {
        arr_even[i] = arr[2*i];
        arr_odd[i] = arr[2*i+1];
    }

    fft(arr_even, n/2, direction);
    fft(arr_odd, n/2, direction);

    for (int i = 0; i < n / 2; ++i) {
        double angle = -direction*(2.0*PI*i/n);
        double cos_a = cos(angle);
        double sin_a = sin(angle);

        double tmp_re = cos_a * arr_odd[i].re - sin_a * arr_odd[i].im;
        double tmp_im = cos_a * arr_odd[i].im + sin_a * arr_odd[i].re;

        arr[i].re = (arr_even[i].re + tmp_re);
        arr[i].im = (arr_even[i].im + tmp_im);
        arr[i+n/2].re = (arr_even[i].re - tmp_re);
        arr[i+n/2].im = (arr_even[i].im - tmp_im);
    }
} 

inline void normalized_fft(complex* arr, int n, int direction) {
    fft(arr, n, direction);
    normalize_array(arr, n);
}
