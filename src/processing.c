#include "processing.h"

void get_angle(float* ret, complex* signal, int n) {
    for (int i = 0; i < n; ++i) {
        ret[i] = atan2(signal[i].im, signal[i].re);
    }
}

void unwrap_angle(float *in, float *out, int n) {
    out[0] = in[0];
    for (int i = 1; i < n; i++) {
        float d = in[i] - in[i-1];
        d = d > PI ? d - 2 * PI : (d < -PI ? d + 2 * PI : d);
        out[i] = out[i-1] + d;
    }
}

void determine_phase_shift(float* phase_shift, complex* reference, complex* shifted, int n) {

    hilbert(reference, n);
    hilbert(shifted, n);

    float angle_ref[n];
    float angle_shift[n];

    float unwrapped_ref[n];
    float unwrapped_shift[n];

    get_angle(angle_ref, reference, n);
    get_angle(angle_shift, shifted, n);

    unwrap_angle(angle_ref, unwrapped_ref, n);
    unwrap_angle(angle_shift, unwrapped_shift, n);

    for (int i = 0; i < n; ++i) { 
        phase_shift[i] = unwrapped_ref[i] - unwrapped_shift[i];
    }
}