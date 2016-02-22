/* PLEASE REPLACE "CORE_BOARD_REQUIRED" WITH AN APPROPRIATE BOARD SUPPORT FILE FROM module_board-support */
#include <CORE_BOARD_REQUIRED>

#include <xscope.h>

#define NUM_SAMPLES 64

unsigned int sine[NUM_SAMPLES] = {
        4000,4392,4780,5161,5531,5886,6222,6538,6828,7092,7326,7528,7696,7828,7923,7981,
        8000,7981,7923,7828,7696,7528,7326,7092,6828,6538,6222,5886,5531,5161,4780,4392,
        4000,3608,3220,2839,2469,2114,1778,1462,1172,908,674,472,304,172,77,19,
        0,19,77,172,304,472,674,908,1172,1462,1778,2114,2469,2839,3220,3608,
};

int main() {

    par{

        on tile[APP_TILE]:
        {
            while (1) {
                for (unsigned int i = 0; i < NUM_SAMPLES; ++i) {
                    xscope_int(VALUE, sine[i]);
                }
            }
        }
    }

    return 0;
}
