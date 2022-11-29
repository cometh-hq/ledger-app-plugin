#pragma once

#include <string.h>
#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include "debug_write.h"

// Number of selectors defined in this plugin. Should match the enum `selector_t`.
#define NUM_SELECTORS 12

// Name of the plugin.
#define PLUGIN_NAME "Cometh"

#define PARAMETER_LENGTH 32  // 32 bytes

// Plugin uses 0x00000 as a dummy address to reprecent ETH.
extern const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH];

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    CRAFT,
    REDEEM,
    GRIND,
    GET_REWARD,
    WELCOME_PACK_PURCHASE,
    RENTAL_CREATE_OFFER,
    RENTAL_CANCEL_OFFER,
    RENTAL_RENT,
    RENTAL_SUBLET,
    RENTAL_END_RENTAL,
    RENTAL_END_RENTAL_PREMATURELY,
    RENTAL_END_SUBLET,
} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    BENEFICIARY,
    CRAFT_RECIPE,
    ITEM_ID,
    GAME_ID,
    PURCHASE_TOKEN,
    PURCHASE_PRICE,
    PURCHASE_QUANTITY,
    RENTAL_OFFER_MAKER,
    RENTAL_OFFER_TAKER,
    RENTAL_OFFER_FEE_TOKEN,
    RENTAL_OFFER_FEE_AMOUNT,
    RENTAL_OFFER_NONCE,
    RENTAL_OFFER_STRUCT_NFT_LENGTH,
    RENTAL_NFT_ADDRESS,
    RENTAL_NFT_TOKEN_ID,
    RENTAL_TENANT,
    RENTAL_BASIS_POINTS,
    NONE,
} parameter;

extern const uint32_t COMETH_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
    // For display.
    uint8_t address[ADDRESS_LENGTH];
    uint8_t uint256_one[INT256_LENGTH];
    uint8_t uint256_two[INT256_LENGTH];
    uint8_t booster_card_count;
    uint16_t array_length;
    uint8_t rental_fee_token[ADDRESS_LENGTH];

    char ticker[MAX_TICKER_LEN];
    uint8_t token_found;

    // For parsing data.
    uint8_t skip;
    uint8_t decimals;
    uint8_t next_param;  // Set to be the next param we expect to parse.

    // For both parsing and display.
    selector_t selectorIndex;
} context_t;

// Piece of code that will check that the above structure is not bigger than 5 * 32. Do not remove
// this check.
_Static_assert(sizeof(context_t) <= 5 * 32, "Structure of parameters too big.");

void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_init_contract(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);

static inline void printf_hex_array(const char *title __attribute__((unused)),
                                    size_t len __attribute__((unused)),
                                    const uint8_t *data __attribute__((unused))) {
    PRINTF(title);
    for (size_t i = 0; i < len; ++i) {
        PRINTF("%02x", data[i]);
    };
    PRINTF("\n");
}
