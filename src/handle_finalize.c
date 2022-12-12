#include "cometh_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    switch (context->selectorIndex) {
        case CRAFT:
            msg->numScreens = 2;  // beneficiary + number of cards in the booster
            break;
        case REDEEM:
            msg->numScreens = 1;  // beneficiary
            break;
        case GRIND:
            msg->numScreens = 1;  // item id
            break;
        case GET_REWARD:
            msg->numScreens = 1;  // game id
            break;
        case WELCOME_PACK_PURCHASE:
            msg->numScreens = 2;  // purchase price + quantity
            msg->tokenLookup1 = context->address;
            break;
        case RENTAL_CREATE_OFFER:
            msg->numScreens = 3;  // bundle size + entry free + nonce
            if (memcmp(context->address, NULL_ETH_ADDRESS, ADDRESS_LENGTH) != 0) {
                // an additional screen is required to display the `beneficiary` field aka for whom
                // the private offer is
                msg->numScreens += 1;
            }
            msg->tokenLookup1 = context->rental_fee_token;
            break;
        case RENTAL_CANCEL_OFFER:
            msg->numScreens = 1;  // nonce
            break;
        case RENTAL_RENT:
            msg->numScreens = 3;  // bundle size + entry free + offer maker
            msg->tokenLookup1 = context->rental_fee_token;
            break;
        case RENTAL_SUBLET:
            msg->numScreens = 3;  // ship ID + tenant + basis points
            break;
        case RENTAL_END_RENTAL:
        case RENTAL_END_RENTAL_PREMATURELY:
        case RENTAL_END_SUBLET:
            msg->numScreens = 1;  // ship ID
            break;
    }

    msg->uiType = ETH_UI_TYPE_GENERIC;
    msg->result = ETH_PLUGIN_RESULT_OK;
}
