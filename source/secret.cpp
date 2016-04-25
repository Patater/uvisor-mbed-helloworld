#include "uvisor-lib/uvisor-lib.h"
#include "mbed.h"
#include "rtos.h"

struct box_context {
    uint32_t secret;
};

static const UvisorBoxAclItem acl[] = {
};

UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_MAIN(secret_main, osPriorityAboveNormal);
UVISOR_BOX_CONFIG(box_secret, acl, UVISOR_BOX_STACK_SIZE, box_context);

static void secret_main(const void *)
{
    uvisor_ctx->secret = 23;

    while (1)
    {
        Thread::wait(1000);

        ++uvisor_ctx->secret;
    }
}
