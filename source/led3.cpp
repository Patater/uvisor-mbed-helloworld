#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "rtos.h"
#include "main-hw.h"

struct box_context {
    Thread * thread;
    uint32_t heartbeat;
};

static const UvisorBoxAclItem acl[] = {
};

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(8192);
UVISOR_BOX_CONFIG(box_led3, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void led3_main(const void *)
{
    DigitalOut led3(LED3);
    led3 = LED_OFF;

    while (1) {
        void * memory;

        led3 = !led3;
        memory = malloc(500);
        ++uvisor_ctx->heartbeat;
        Thread::wait(500);
        free(memory);
    }
}

/*
 * The *_init functions will look different when uVisor has the box init
 * feature.
 */
UVISOR_EXTERN void __led3_init(void)
{
    uvisor_ctx->thread = new Thread(led3_main);
}

void led3_init(void)
{
    secure_gateway(box_led3, __led3_init);
}
