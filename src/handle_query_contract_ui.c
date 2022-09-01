#include "cometh_plugin.h"

// Set UI for "Beneficiary" screen.
static void set_beneficiary_ui(ethQueryContractUI_t *msg, context_t *context) {
    strlcpy(msg->title, "Beneficiary", msg->titleLength);

    // Prefix the address with `0x`.
    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    // We need a random chainID for legacy reasons with `getEthAddressStringFromBinary`.
    // Setting it to `0` will make it work with every chainID :)
    uint64_t chainid = 0;

    // Get the string representation of the address stored in `context->beneficiary`. Put it in
    // `msg->msg`.
    getEthAddressStringFromBinary(
        context->beneficiary,
        msg->msg + 2,  // +2 here because we've already prefixed with '0x'.
        msg->pluginSharedRW->sha3,
        chainid);
}

// Set UI for Booster cards count
static void set_craft_booster_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Booster", msg->titleLength);
    if (context->booster_card_count > 1) {
        snprintf(msg->msg, msg->msgLength, "%d cards", context->booster_card_count);
    } else {
        snprintf(msg->msg, msg->msgLength, "%d card", context->booster_card_count);
    }
}

// Set UI for Item ID
static void set_item_id_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Card ID", msg->titleLength);
    amountToString(context->item_id, sizeof(context->item_id), 0, "", msg->msg, msg->msgLength);
}

// Set UI for Game ID
static void set_game_id_ui(ethQueryContractUI_t *msg, const context_t *context) {
    strlcpy(msg->title, "Game ID", msg->titleLength);
    strlcpy(msg->msg, context->game_id, msg->msgLength);
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;

    // Clean the display fields.
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);
    msg->result = ETH_PLUGIN_RESULT_OK;

    PRINTF("Switching to selector: %d and screen: %d\n", context->selectorIndex, msg->screenIndex);

    switch (context->selectorIndex) {
        case CRAFT:
            switch (msg->screenIndex) {
                case 0:
                    set_beneficiary_ui(msg, context);
                    return;
                case 1:
                    set_craft_booster_ui(msg, context);
                    return;
            }
        case REDEEM:
            switch (msg->screenIndex) {
                case 0:
                    set_beneficiary_ui(msg, context);
                    return;
            }
        case GRIND:
            switch (msg->screenIndex) {
                case 0:
                    set_item_id_ui(msg, context);
                    return;
            }
        case GET_REWARD:
            switch (msg->screenIndex) {
                case 0:
                    set_game_id_ui(msg, context);
                    return;
            }
    }

    PRINTF("Received an invalid selectorIndex + screenIndex tuple\n");
    msg->result = ETH_PLUGIN_RESULT_ERROR;
    return;
}
