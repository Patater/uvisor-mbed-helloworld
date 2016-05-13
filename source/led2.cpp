#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "rtos.h"
#include "main-hw.h"

struct box_context {
    Thread *thread;
    uint32_t heartbeat;
};

static const UvisorBoxAclItem acl[] = {
};

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(8192);
UVISOR_BOX_CONFIG(box_led2, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void led2_main(const void *)
{
    DigitalOut led2(LED2);
    led2 = LED_OFF;

    while (1) {
        led2 = !led2;
        ++uvisor_ctx->heartbeat;
        Thread::wait(300);
    }
}

/*
 * The *_init functions will look different when uVisor has the box init
 * feature.
 */
UVISOR_EXTERN void __led2_init(void)
{
    uvisor_ctx->thread = new Thread(led2_main, NULL, osPriorityBelowNormal);
}

void led2_init(void)
{
    secure_gateway(box_led2, __led2_init);
}
