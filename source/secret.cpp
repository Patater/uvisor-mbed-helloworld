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
UVISOR_BOX_CONFIG(box_secret, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void secret_main(const void *)
{
    while (1)
    {
        Thread::wait(1000);

    //    Not even this works without context switching
    //    ++uvisor_ctx->secret;
    }
}

UVISOR_EXTERN void __secret_init(void)
{
    uvisor_ctx->secret = 23;
    uvisor_ctx->thread = new Thread(secret_main, NULL, osPriorityAboveNormal);
}

void secret_init(void)
{
    secure_gateway(box_secret, __secret_init);
}
