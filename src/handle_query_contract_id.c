#include "cometh_plugin.h"

// Sets the first screen to display.
void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const context_t *context = (const context_t *) msg->pluginContext;
    
    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    switch (context->selectorIndex) {
        case CRAFT:
            strlcpy(msg->version, "Craft", msg->versionLength);
            break;
        case REDEEM:
            strlcpy(msg->version, "Open Booster", msg->versionLength);
            break;
        case GRIND:
            strlcpy(msg->version, "Grind", msg->versionLength);
            break;
        case GET_REWARD:
            strlcpy(msg->version, "Get Reward", msg->versionLength);
            break;
        default:
            PRINTF("Selector Index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}