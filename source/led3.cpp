#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "rtos.h"
#include "main-hw.h"

struct box_context {
    Thread *thread;
};

DigitalOut led3(LED3);

static const UvisorBoxAclItem acl[] = {
};

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(0);
UVISOR_BOX_CONFIG(box_led3, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void led3_main(const void *)
{
    led3 = LED_OFF;

    while (1) {
        led3 = !led3;
        Thread::wait(500);
    }
}

UVISOR_EXTERN void __led3_init(void)
{
    uvisor_ctx->thread = new Thread(led3_main, NULL, osPriorityAboveNormal);
}

void led3_init(void)
{
    secure_gateway(box_led3, __led3_init);
}
