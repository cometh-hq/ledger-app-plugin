#include "cometh_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    switch (context->selectorIndex) {
        case CRAFT:
            msg->numScreens = 2; // beneficiary + number of cards in the booster
            break;
        case REDEEM:
            msg->numScreens = 1; // beneficiary
            break;
        case GRIND:
            msg->numScreens = 1; // item id
            break;
        case GET_REWARD:
            msg->numScreens = 1; // game id
            break;
    }

    // If the beneficiary is NOT the sender, we will need an additional screen to display it.
    /*
    if (memcmp(msg->address, context->beneficiary, ADDRESS_LENGTH) != 0) {
        msg->numScreens += 1;
    }
    */
    
    /*
    msg->numScreens = 3;
    if (memcmp(context->beneficiary, NULL_ETH_ADDRESS, ADDRESS_LENGTH) != 0) {
        // An additional screen is required to display the `beneficiary` field.
        msg->numScreens += 1;
    }
    if (context->selectorIndex == CRAFT) {
        // An additional screen is required
        msg->numScreens += 1;
    }
    if (!ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        // Address is not network token (0xeee...) so we will need to look up the token in the
        // CAL.
        printf_hex_array("Setting address sent to: ",
                            ADDRESS_LENGTH,
                            context->contract_address_sent);
        msg->tokenLookup1 = context->contract_address_sent;
    } else {
        sent_network_token(context);
        msg->tokenLookup1 = NULL;
    }
    if (!ADDRESS_IS_NETWORK_TOKEN(context->contract_address_received)) {
        // Address is not network token (0xeee...) so we will need to look up the token in the
        // CAL.
        printf_hex_array("Setting address received to: ",
                            ADDRESS_LENGTH,
                            context->contract_address_received);
        msg->tokenLookup2 = context->contract_address_received;
    } else {
        received_network_token(context);
        msg->tokenLookup2 = NULL;
    }
    */

    msg->uiType = ETH_UI_TYPE_GENERIC;
    msg->result = ETH_PLUGIN_RESULT_OK;

    /*
    msg->uiType = ETH_UI_TYPE_GENERIC;

    // EDIT THIS: Set the total number of screen you will need.
    msg->numScreens = 2;
    // EDIT THIS: Handle this case like you wish to (i.e. maybe no additional screen needed?).
    // If the beneficiary is NOT the sender, we will need an additional screen to display it.
    if (memcmp(msg->address, context->beneficiary, ADDRESS_LENGTH) != 0) {
        msg->numScreens += 1;
    }

    // EDIT THIS: set `tokenLookup1` (and maybe `tokenLookup2`) to point to
    // token addresses you will info for (such as decimals, ticker...).
    msg->tokenLookup1 = context->token_received;

    msg->result = ETH_PLUGIN_RESULT_OK;
    */
}
