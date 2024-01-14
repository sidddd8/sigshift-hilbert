#include <math.h>
#include "sig_utils.h"
#include "SIG_CONFIG.h"

void get_angle(float* ret, complex* signal, int n);

void unwrap_angle(float *in, float *out, int n);


float wrap_max(float x, float max);


float wrap_between(float x, float min, float max);

// finds immediate phase shift between the reference signal and a provided shifted signal.
// stores the result in 'phase_shift;
// phase_shift : array of lenght n where immediate phase shift is stored
// reference   : complex array with the reference signal
// shifted     : signal to find the shift of
// n           : lenght of the signals 
// RETURNS float : Expected value of the shift.
float determine_phase_shift(float* phase_shift, complex* reference, complex* shifted, int n);