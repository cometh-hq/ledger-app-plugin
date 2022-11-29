#include "cometh_plugin.h"

const uint8_t BOOSTER_CARD_1[INT256_LENGTH] = {
    0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0,  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2};
const uint8_t BOOSTER_CARD_5[INT256_LENGTH] = {
    0x00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0,  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1};

static void handle_address(ethPluginProvideParameter_t *msg, context_t *context) {
    copy_address(context->address, msg->parameter, sizeof(context->address));
    printf_hex_array("BENEFICIARY: ", ADDRESS_LENGTH, context->address);
}

static void handle_craft(ethPluginProvideParameter_t *msg, context_t *context) {
    PRINTF("[handle_craft] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case BENEFICIARY:  // to
            handle_address(msg, context);
            context->next_param = CRAFT_RECIPE;
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
    PRINTF("[handle_redeem] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case BENEFICIARY:  // to
            handle_address(msg, context);
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
    PRINTF("[handle_grind] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case ITEM_ID:
            copy_parameter(context->uint256_one, msg->parameter, INT256_LENGTH);
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

static void handle_get_reward(ethPluginProvideParameter_t *msg, context_t *context) {
    PRINTF("[handle_get_reward] next_param=%d\n", context->next_param);
    switch (context->next_param) {
        case GAME_ID:
            copy_parameter(context->uint256_one, msg->parameter, INT256_LENGTH);
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

static void handle_welcome_pack(ethPluginProvideParameter_t *msg, context_t *context) {
    PRINTF("[handle_welcome_pack] next_param=%d\n", context->next_param);
    switch (context->next_param) {
        case PURCHASE_TOKEN:
            copy_address(context->address, msg->parameter, ADDRESS_LENGTH);
            context->next_param = PURCHASE_PRICE;
            break;
        case PURCHASE_PRICE:
            copy_parameter(context->uint256_one, msg->parameter, INT256_LENGTH);
            context->next_param = PURCHASE_QUANTITY;
            break;
        case PURCHASE_QUANTITY:
            copy_parameter(context->uint256_two, msg->parameter, INT256_LENGTH);
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

static void handle_rental_create_offer(ethPluginProvideParameter_t *msg, context_t *context) {
    PRINTF("[handle_rental_create_offer] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case RENTAL_OFFER_TAKER:
            copy_address(context->address, msg->parameter, ADDRESS_LENGTH);
            context->skip++;
            context->next_param = RENTAL_OFFER_FEE_TOKEN;
            break;
        case RENTAL_OFFER_FEE_TOKEN:
            copy_address(context->rental_fee_token, msg->parameter, ADDRESS_LENGTH);
            context->next_param = RENTAL_OFFER_FEE_AMOUNT;
            break;
        case RENTAL_OFFER_FEE_AMOUNT:
            copy_parameter(context->uint256_two, msg->parameter, INT256_LENGTH);
            context->next_param = RENTAL_OFFER_NONCE;
            break;
        case RENTAL_OFFER_NONCE:
            copy_parameter(context->uint256_one, msg->parameter, INT256_LENGTH);
            context->skip++;
            context->next_param = RENTAL_OFFER_STRUCT_NFT_LENGTH;
            break;
        case RENTAL_OFFER_STRUCT_NFT_LENGTH:
            if (!U2BE_from_parameter(msg->parameter, &context->array_length)) {
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

static void handle_rental_cancel_offer(ethPluginProvideParameter_t *msg, context_t *context) {
    PRINTF("[handle_rental_cancel_offer] next_param=%d\n", context->next_param);
    switch (context->next_param) {
        case RENTAL_OFFER_NONCE:
            copy_parameter(context->uint256_one, msg->parameter, INT256_LENGTH);
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

static void handle_rental_rent(ethPluginProvideParameter_t *msg, context_t *context) {
    PRINTF("[handle_rental_rent] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case RENTAL_OFFER_MAKER:
            copy_address(context->address, msg->parameter, ADDRESS_LENGTH);
            context->skip += 2;  // skip taker and array offset
            context->next_param = RENTAL_OFFER_FEE_TOKEN;
            break;
        case RENTAL_OFFER_FEE_TOKEN:
            copy_address(context->rental_fee_token, msg->parameter, ADDRESS_LENGTH);
            context->next_param = RENTAL_OFFER_FEE_AMOUNT;
            break;
        case RENTAL_OFFER_FEE_AMOUNT:
            copy_parameter(context->uint256_two, msg->parameter, INT256_LENGTH);
            context->skip += 2;  // skip nonce and deadline
            context->next_param = RENTAL_OFFER_STRUCT_NFT_LENGTH;
            break;
        case RENTAL_OFFER_STRUCT_NFT_LENGTH:
            if (!U2BE_from_parameter(msg->parameter, &context->array_length)) {
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

static void handle_rental_sublet(ethPluginProvideParameter_t *msg, context_t *context) {
    PRINTF("[handle_rental_sublet] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case RENTAL_NFT_ADDRESS:
            context->next_param = RENTAL_NFT_TOKEN_ID;
            break;
        case RENTAL_NFT_TOKEN_ID:
            copy_parameter(context->uint256_one, msg->parameter, INT256_LENGTH);
            context->next_param = RENTAL_TENANT;
            break;
        case RENTAL_TENANT:
            copy_address(context->address, msg->parameter, ADDRESS_LENGTH);
            context->next_param = RENTAL_BASIS_POINTS;
            break;
        case RENTAL_BASIS_POINTS:
            copy_parameter(context->uint256_two, msg->parameter, INT256_LENGTH);
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

static void handle_rental_end_rental_or_end_sublet(ethPluginProvideParameter_t *msg,
                                                   context_t *context) {
    PRINTF("[handle_rental_end_rental_or_end_sublet] next_param=%d\n", context->next_param);

    switch (context->next_param) {
        case RENTAL_NFT_ADDRESS:
            copy_address(context->address, msg->parameter, ADDRESS_LENGTH);
            context->next_param = RENTAL_NFT_TOKEN_ID;
            break;
        case RENTAL_NFT_TOKEN_ID:
            copy_parameter(context->uint256_one, msg->parameter, INT256_LENGTH);
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
        PRINTF("Dealing with selector %d\n", context->selectorIndex);

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
            case GET_REWARD:
                handle_get_reward(msg, context);
                break;
            case WELCOME_PACK_PURCHASE:
                handle_welcome_pack(msg, context);
                break;
            case RENTAL_CREATE_OFFER:
                handle_rental_create_offer(msg, context);
                break;
            case RENTAL_CANCEL_OFFER:
                handle_rental_cancel_offer(msg, context);
                break;
            case RENTAL_RENT:
                handle_rental_rent(msg, context);
                break;
            case RENTAL_SUBLET:
                handle_rental_sublet(msg, context);
                break;
            case RENTAL_END_RENTAL:
            case RENTAL_END_RENTAL_PREMATURELY:
            case RENTAL_END_SUBLET:
                handle_rental_end_rental_or_end_sublet(msg, context);
                break;
            default:
                PRINTF("Selector Index not supported: %d\n", context->selectorIndex);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                break;
        }
    }
}