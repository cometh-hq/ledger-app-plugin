#include "cometh_plugin.h"

const uint8_t BOOSTER_CARD_1[INT256_LENGTH] = { 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2 };
const uint8_t BOOSTER_CARD_5[INT256_LENGTH] = { 0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1 };

static void handle_beneficiary(ethPluginProvideParameter_t *msg, context_t *context) {
    copy_address(context->beneficiary, msg->parameter, sizeof(context->beneficiary));
    printf_hex_array("BENEFICIARY: ", ADDRESS_LENGTH, context->beneficiary);
}

static void handle_craft(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }

    PRINTF("[handle_craft] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case BENEFICIARY: // to
            handle_beneficiary(msg, context);
            context->next_param = CRAFT_RECIPE;
            //context->go_to_offset = true;
            break;
        case CRAFT_RECIPE:  // recipeId
            // map recipeId to number of cards in the booster pack
            if (memcmp(msg->parameter, BOOSTER_CARD_5, INT256_LENGTH) == 0) {
                context->booster_card_count = 5;
            } else if (memcmp(msg->parameter, BOOSTER_CARD_1, INT256_LENGTH) == 0) {
                context->booster_card_count = 1;
            } else {
                PRINTF("Unknown recipe: %d\n", msg->parameter);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
            context->next_param = NONE;
            break;
        case NONE:
            break;
        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_redeem(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    
    PRINTF("[handle_redeem] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case BENEFICIARY: // to
            handle_beneficiary(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_grind(ethPluginProvideParameter_t *msg, context_t *context) {
    if (context->go_to_offset) {
        if (msg->parameterOffset != context->offset + SELECTOR_SIZE) {
            return;
        }
        context->go_to_offset = false;
    }
    
    PRINTF("[handle_grind] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case ITEM_ID:
            memcpy(context->item_id, msg->parameter, INT256_LENGTH);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        // Keep this
        default:
            PRINTF("Param not supported: %d\n", context->next_param);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    context_t *context = (context_t *) msg->pluginContext;
    // We use `%.*H`: it's a utility function to print bytes. You first give
    // the number of bytes you wish to print (in this case, `PARAMETER_LENGTH`) and then
    // the address (here `msg->parameter`).
    PRINTF("plugin provide parameter: offset %d\nBytes: %.*H\n",
           msg->parameterOffset,
           PARAMETER_LENGTH,
           msg->parameter);

    msg->result = ETH_PLUGIN_RESULT_OK;

    if (context->skip) {
        // Skip this step, and don't forget to decrease skipping counter.
        context->skip--;
    } else {
        if ((context->offset) && msg->parameterOffset != context->checkpoint + context->offset) {
            PRINTF("offset: %d, checkpoint: %d, parameterOffset: %d\n",
                   context->offset,
                   context->checkpoint,
                   msg->parameterOffset);
            return;
        }

        PRINTF("Dealing with selector %d\n", context->selectorIndex);

        context->offset = 0;  // Reset offset
        switch (context->selectorIndex) {
            case CRAFT:
                handle_craft(msg, context);
                break;
            case REDEEM:
                handle_redeem(msg, context);
                break;
            case GRIND:
                handle_grind(msg, context);
                break;
            default:
                PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                break;
        }
    }
}