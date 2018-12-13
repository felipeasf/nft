/**
*  @file game.cpp
*/

#include "example/game.hpp"

void example::game::transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo) {
    token_table token_table(name("example.nft"), name("example.nft").value);
    auto token = token_table.find(tk_id);
    eosio_assert(token != token_table.end(), "token with id does not exist");

    // TODO: Perform some logic with cust_table.
    print_f("Token's Custom ID: %", token->custom_id);

    action transfer = action(permission_level{_self, name("active")}, name("example.nft"),
        name("transfer"), std::make_tuple(from, to, sym, tk_id, memo));
    transfer.send();
}

EOSIO_DISPATCH(example::game, (transfer))
 
