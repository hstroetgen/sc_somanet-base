/**
 * @file flash_somanet.xc
 * @brief Somanet Firmware Update implementation
 * @brief Flash device access
 * @author Synapticon GmbH <support@synapticon.com>
 */

#include <flash_somanet.h>
#include <xs1.h>

#if 1
static void core_reset(void)    // auto reset from software
{
    unsigned x;
    read_sswitch_reg(get_local_tile_id(), 6, x); // TODO verify operation
    write_sswitch_reg(get_local_tile_id(), 6, x);
}

void reset_cores(chanend sig_in, chanend ?sig_out)
{
    int read;
    timer t;
    unsigned ts;
    const unsigned delay = 100000;

    sig_in :> read;
    if (read == 1) {
        if (!isnull(sig_out)) {
            sig_out <: read;
        }
        t :> ts;
        t when timerafter(ts + delay) :> void;
        core_reset();
    }
}

void reset_cores1(void)
{
    timer t;
    unsigned ts;
    const unsigned delay = 100000;

    t :> ts;
    t when timerafter(ts + delay) :> void;
    core_reset();

}
#endif
