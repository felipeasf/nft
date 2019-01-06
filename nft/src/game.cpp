/**
*  @file game.cpp
*/

#include "example/game.hpp"

void example::game::transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo) {
    // TODO: Find a better way to get nft contract name
    token_table token_table(name("example.nft"), name("example.nft").value);
    auto token = token_table.find(tk_id);
    eosio_assert(token != token_table.end(), "token with id does not exist");

    // TODO: Perform some logic with cust_table.
    // TODO: Data need to be deserialized
    print_f("Token's Custom ID: %", token->custom_id);
}

void example::game::burn(symbol sym, uint64_t tk_id) {
    // TODO: Find a better way to get nft contract name
    token_table token_table(name("example.nft"), name("example.nft").value);
    auto token = token_table.find(tk_id);
    eosio_assert(token != token_table.end(), "token with id does not exist");

    // TODO: Perform some logic with cust_table.
    // TODO: Data need to be deserialized
    print_f("Token's Custom ID: %", token->custom_id);
}

EOSIO_DISPATCH(example::game, (transfer)(burn))
 
