#include "sig_utils.h"

inline void print_signal(complex* arr, int n) {
    for (int i = 0; i < n; ++i) {
        (void)fprintf(stderr, "[%d] : {%.3f, %.3fi}\n", i, arr[i].re, arr[i].im);
    }
}

inline void copy_signal(complex* target, complex* orig, int n) {
    for (int i = 0; i < n; ++i) {
        target[i].re = orig[i].re;
        target[i].im = orig[i].im;
    }
}

inline void normalize_signal(complex* arr, int n) {
    for (int i = 0; i < n; ++i) {
        arr[i].re /= n;
        arr[i].im /= n;
    }
}

inline float signal_EV(complex* arr, int n) {
    float sum = 0.0;
    for (int i = 0; i < n; ++i) {
        sum = sum + arr[i].re;
    }
    sum = sum/n;
    return sum;
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
    normalize_signal(arr, n);
}


inline void hilbert(complex* arr, int n) {
    complex arr_tmp[n];
    copy_signal(arr_tmp, arr, n);

    fft(arr, SIG_LENGTH, 1);

    arr[0].re = 0;
    arr[0].im = 0;
    arr[n/2].re = 0;
    arr[n/2].im = 0;

    float tmp = 0;

    // compute -j*sign(f)*FFT(arr)
    for (int i = 1; i < n/2; ++i) {
        tmp = arr[i].re;
        arr[i].re = arr[i].im;
        arr[i].im = -1*tmp;
    }
    for (int i = n/2+1; i < n; ++i) {
        tmp = arr[i].re;
        arr[i].re = -1*arr[i].im;
        arr[i].im = tmp;
    }
    // ---------------------------
    fft(arr, SIG_LENGTH, -1);

    // put the original signal and its Hilbert transform together
    // original signal is stored in the real part
    // Hilbert transform is stored in the imaginary part
    for (int i = 0; i < n; ++i) {
        arr[i].im = arr[i].re/n; // division by 'n' for normalization
        arr[i].re = arr_tmp[i].re;
    }
}
