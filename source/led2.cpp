#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "rtos.h"
#include "main-hw.h"

struct box_context {
    Thread *thread;
};

DigitalOut led2(LED2);

static const UvisorBoxAclItem acl[] = {
};

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(0);
UVISOR_BOX_CONFIG(box_led2, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void led2_main(const void *)
{
    led2 = LED_OFF;

    while (1) {
        led2 = !led2;
        Thread::wait(300);
    }
}

UVISOR_EXTERN void __led2_init(void)
{
    uvisor_ctx->thread = new Thread(led2_main, NULL, osPriorityAboveNormal);
}

void led2_init(void)
{
    secure_gateway(box_led2, __led2_init);
}
