/**
*  @file nft.cpp
*/

#include "example/nft.hpp"

void example::nft::create(name issuer, symbol sym, uint64_t class_id) {
    require_auth(_self);

    eosio_assert(is_account(issuer), "issuer account does not exist");

    eosio_assert(sym.is_valid(), "invalid symbol");
    eosio_assert(sym.precision() == 0, "symbol precision must be 0");

    token_data_table td_table(_self, _self.value);
    auto token_stat = td_table.find(sym.code().raw());
    eosio_assert(token_stat == td_table.end(), "token with symbol already exists");

    td_table.emplace(_self, [&](auto& ts) {
       ts.data.symbol = sym;
       ts.data.amount = 0;
       ts.issuer = issuer;
       ts.class_id = class_id;
    });
}

void example::nft::remove(symbol sym) {
    require_auth(_self);

    eosio_assert(sym.is_valid(), "invalid symbol");

    token_data_table td_table(_self, _self.value);
    auto token_stat = td_table.find(sym.code().raw());
    eosio_assert(token_stat != td_table.end(), "token with symbol doesn't exist");

    eosio_assert(token_stat->data.amount == 0, "burn all tokens before removing");

    td_table.erase(token_stat);
}

void example::nft::issue(name to, symbol sym, uint64_t spawn_id, uint64_t cust_id) {
    eosio_assert(is_account(to), "to account does not exist");

    eosio_assert(sym.is_valid(), "invalid symbol name");

    token_data_table td_table(_self, _self.value);
    auto token_stat = td_table.find(sym.code().raw());
    eosio_assert(token_stat != td_table.end(), "token with symbol does not exist");

    require_auth(token_stat->issuer);

    eosio_assert(token_stat->data.amount < token_stat->data.max_amount, "invalid quantity");

    td_table.modify(token_stat, _self, [&](auto& ts) {
       ts.data.amount++;
    });

    mint(spawn_id, cust_id, to);
}

void example::nft::burn(symbol sym, uint64_t tk_id) {
    token_data_table td_table(_self, _self.value);

    auto token_stat = td_table.find(sym.code().raw());
    eosio_assert(token_stat != td_table.end(), "token with symbol does not exist");

    token_table token_table(_self, _self.value);

    auto token = token_table.find(tk_id);
    eosio_assert(token != token_table.end(), "token with id does not exist");

    require_auth(token->owner);

    td_table.modify(token_stat, _self, [&](auto& ts) {
        ts.data.amount--;
    });

    token_table.erase(token);
}

void example::nft::transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo) {
    eosio_assert(from != to, "cannot transfer to self");

    eosio_assert(is_account(to), "to account does not exist");

    eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");

    token_data_table td_table(_self, _self.value);
    auto token_data = td_table.find(sym.code().raw());
    eosio_assert(token_data != td_table.end(), "token with symbol doesn't exist");

    // Make sure that transfer can only be called from issuer contract through inline action
    require_auth(token_data->issuer);

    token_table token_table(_self, _self.value);

    auto token = token_table.find(tk_id);
    eosio_assert(token != token_table.end(), "token with id does not exist");

    eosio_assert(token->owner == from, "sender does not own token with specified id");

    token_table.modify(token, _self, [&](auto& token) {
        token.owner = to;
    });

    require_recipient(from);
    require_recipient(to);
}

void example::nft::mint(uint64_t spawn_id, uint64_t cust_id, name owner) {
    token_table token_table(_self, _self.value);
    token_table.emplace(_self, [&](auto& token) {
        token.id = token_table.available_primary_key();
        token.spawn_id = spawn_id;
        token.custom_id = cust_id;
        token.owner = owner;
    });
}

void example::nft::createclsprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data) {}

void example::nft::removeclsprm(uint64_t id) {}

void example::nft::updateclsprm(uint64_t id, uint128_t data_hash, std::vector<uint8_t> data) {}

void example::nft::createspwprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data) {}

void example::nft::removespwprm(uint64_t id) {}

void example::nft::createcstprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data) {}

void example::nft::removecstprm(uint64_t id) {}

void example::nft::createschema(std::string definition) {}

void example::nft::removeschema(uint64_t id) {}

EOSIO_DISPATCH(example::nft, (create)(remove)(issue)(burn)(transfer)(createclsprm)(removeclsprm)
    (updateclsprm)(createspwprm)(removespwprm)(createcstprm)(removecstprm)(createschema)
    (removeschema)) 
