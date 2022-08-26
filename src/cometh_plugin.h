#pragma once

#include <string.h>
#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include "debug_write.h"


// Number of selectors defined in this plugin. Should match the enum `selector_t`.
// EDIT THIS: Put in the number of selectors your plugin is going to support.
#define NUM_SELECTORS 3

// Name of the plugin.
#define PLUGIN_NAME "Cometh"

// Plugin uses 0x00000 as a dummy address to reprecent ETH.
extern const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH];

// Enumeration of the different selectors possible.
// Should follow the exact same order as the array declared in main.c
typedef enum {
    CRAFT,
    REDEEM,
    GRIND,
} selector_t;

// Enumeration used to parse the smart contract data.
typedef enum {
    CRAFT_RECIPE,
    //REDEEM_LOOTBOX,
    BENEFICIARY,
    NONE,
} parameter;

typedef enum {
    CRAFT_BOOSTER_SCREEN,
    //REDEEM_SCREEN,
    BENEFICIARY_SCREEN,
    AMOUNT_SCREEN,
    ERROR,
} screens_t;

extern const uint32_t COMETH_SELECTORS[NUM_SELECTORS];

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct context_t {
    // For display.
    //uint8_t lootbox_id[INT256_LENGTH];
    //uint8_t amount_received[INT256_LENGTH];
    uint8_t recipe_id[INT256_LENGTH];
    uint8_t beneficiary[ADDRESS_LENGTH];

    char ticker[MAX_TICKER_LEN];
    uint8_t token_found;

    // For parsing data.
    uint16_t offset;        // Offset at which the array or struct starts.
    uint16_t checkpoint;
    uint8_t skip;
    uint8_t decimals;
    uint8_t next_param;     // Set to be the next param we expect to parse.
    uint8_t tokens_found;
    bool go_to_offset;      // If set, will force the parsing to iterate through parameters until `offset` is reached.

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
