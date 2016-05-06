#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "rtos.h"
#include "main-hw.h"

struct box_context {
    Thread *thread;
};

DigitalOut led1(LED1);

static const UvisorBoxAclItem acl[] = {
};

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(0);
UVISOR_BOX_CONFIG(box_led1, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void led1_main(const void *)
{
    led1 = LED_OFF;

    while (1) {
        led1 = !led1;
        Thread::wait(200);
    }
}

UVISOR_EXTERN void __led1_init(void)
{
    uvisor_ctx->thread = new Thread(led1_main, NULL, osPriorityAboveNormal);
}

void led1_init(void)
{
    secure_gateway(box_led1, __led1_init);
}
