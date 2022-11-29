#include "cometh_plugin.h"

// List of selectors supported by this plugin.
static const uint32_t CRAFT_SELECTOR = 0xb60099b7;
static const uint32_t REDEEM_SELECTOR = 0x1e9a6950;
static const uint32_t GRIND_SELECTOR = 0x54506e92;
static const uint32_t GET_REWARD_SELECTOR = 0x6363e882;
static const uint32_t WELCOME_PACK_PURCHASE_SELECTOR = 0x28dec395;
static const uint32_t RENTAL_CREATE_OFFER_SELECTOR = 0x1ae50184;
static const uint32_t RENTAL_CANCEL_OFFER_SELECTOR = 0x6e09f420;
static const uint32_t RENTAL_RENT_SELECTOR = 0x8d259eb1;
static const uint32_t RENTAL_SUBLET_SELECTOR = 0x03388b4e;
static const uint32_t RENTAL_END_RENTAL_SELECTOR = 0x1157decb;
static const uint32_t RENTAL_END_RENTAL_PREMATURELY_SELECTOR = 0xe1649e8d;
static const uint32_t RENTAL_END_SUBLET_SELECTOR = 0x1beddfdd;

const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// Array of all the different Cometh selectors. Make sure this follows the same order as the
// enum defined in `cometh_plugin.h`
const uint32_t COMETH_SELECTORS[NUM_SELECTORS] = {
    CRAFT_SELECTOR,
    REDEEM_SELECTOR,
    GRIND_SELECTOR,
    GET_REWARD_SELECTOR,
    WELCOME_PACK_PURCHASE_SELECTOR,
    RENTAL_CREATE_OFFER_SELECTOR,
    RENTAL_CANCEL_OFFER_SELECTOR,
    RENTAL_RENT_SELECTOR,
    RENTAL_SUBLET_SELECTOR,
    RENTAL_END_RENTAL_SELECTOR,
    RENTAL_END_RENTAL_PREMATURELY_SELECTOR,
    RENTAL_END_SUBLET_SELECTOR,
};