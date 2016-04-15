#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "rtos.h"

struct box_context {
    Thread *thread;
    uint32_t secret;
};

static const UvisorBoxAclItem acl[] = {
};

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_CONFIG(box_attack, acl, UVISOR_BOX_STACK_SIZE, box_context);

int led1_val;
int led2_val;
int led3_val;

static void attack_main(const void *)
{
    while (1) {
        printf("secret: %d\r\n", uvisor_ctx->secret);

        led1_val = !led1_val;
        Thread::wait(100);
        led2_val = !led2_val;
        Thread::wait(100);
        led1_val = !led1_val;
        Thread::wait(100);
        led3_val = !led3_val;
        Thread::wait(100);
    }
}

UVISOR_EXTERN void __attack_init(void)
{
    uvisor_ctx->secret = 12;
    uvisor_ctx->thread = new Thread(attack_main, NULL, osPriorityHigh);
}

void attack_init(void)
{
    secure_gateway(box_attack, __attack_init);
}
