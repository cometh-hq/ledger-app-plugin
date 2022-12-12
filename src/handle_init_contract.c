#include "cometh_plugin.h"

static int find_selector(uint32_t selector, const uint32_t *selectors, size_t n, selector_t *out) {
    for (selector_t i = 0; i < n; i++) {
        if (selector == selectors[i]) {
            *out = i;
            return 0;
        }
    }
    return -1;
}

// Called once to init.
void handle_init_contract(void *parameters) {
    // Cast the msg to the type of structure we expect (here, ethPluginInitContract_t).
    ethPluginInitContract_t *msg = (ethPluginInitContract_t *) parameters;

    // Make sure we are running a compatible version.
    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        // If not the case, return the `UNAVAILABLE` status.
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Double check that the `context_t` struct is not bigger than the maximum size (defined by
    // `msg->pluginContextLength`).
    if (msg->pluginContextLength < sizeof(context_t)) {
        PRINTF("Plugin parameters structure is bigger than allowed size\n");
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    context_t *context = (context_t *) msg->pluginContext;

    // Initialize the context (to 0).
    memset(context, 0, sizeof(*context));

    uint32_t selector = U4BE(msg->selector, 0);
    if (find_selector(selector, COMETH_SELECTORS, NUM_SELECTORS, &context->selectorIndex)) {
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        case CRAFT:
            context->next_param = BENEFICIARY;
            break;
        case REDEEM:
            context->next_param = BENEFICIARY;
            break;
        case GRIND:
            context->next_param = ITEM_ID;
            break;
        case GET_REWARD:
            context->skip = 1;
            context->next_param = GAME_ID;
            break;
        case WELCOME_PACK_PURCHASE:
            context->next_param = PURCHASE_TOKEN;
            break;
        case RENTAL_CREATE_OFFER:
            context->skip = 2;  // skip struct header + maker address (the user signing this tx)
            context->next_param = RENTAL_OFFER_TAKER;
            break;
        case RENTAL_CANCEL_OFFER:
            context->next_param = RENTAL_OFFER_NONCE;
            break;
        case RENTAL_RENT:
            context->skip = 3;
            context->next_param = RENTAL_OFFER_MAKER;
            break;
        case RENTAL_SUBLET:
        case RENTAL_END_RENTAL:
        case RENTAL_END_RENTAL_PREMATURELY:
        case RENTAL_END_SUBLET:
            context->next_param = RENTAL_NFT_ADDRESS;
            break;
        // Keep this
        default:
            PRINTF("Missing selectorIndex: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    // Return valid status.
    msg->result = ETH_PLUGIN_RESULT_OK;
}
