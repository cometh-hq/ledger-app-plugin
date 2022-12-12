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
        case WELCOME_PACK_PURCHASE:
            strlcpy(msg->version, "Welcome Pack Purchase", msg->versionLength);
            break;
        case RENTAL_CREATE_OFFER:
            strlcpy(msg->version, "Rental - Create offer", msg->versionLength);
            break;
        case RENTAL_CANCEL_OFFER:
            strlcpy(msg->version, "Rental - Cancel offer", msg->versionLength);
            break;
        case RENTAL_RENT:
            strlcpy(msg->version, "Rental - Rent", msg->versionLength);
            break;
        case RENTAL_SUBLET:
            strlcpy(msg->version, "Rental - Sublet", msg->versionLength);
            break;
        case RENTAL_END_RENTAL:
            strlcpy(msg->version, "Rental - End rental", msg->versionLength);
            break;
        case RENTAL_END_RENTAL_PREMATURELY:
            strlcpy(msg->version, "Rental - End rental prematurely", msg->versionLength);
            break;
        case RENTAL_END_SUBLET:
            strlcpy(msg->version, "Rental - End sublet", msg->versionLength);
            break;
        default:
            PRINTF("Selector Index: %d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}