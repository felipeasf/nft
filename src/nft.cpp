/**
*  @file nft.cpp
*
* ToDo: issue, burn or remove multiple tokens at once.
*       duplicated schemas will be allowed?
*/

#include "example/nft.hpp"

void example::nft::create(name issuer, symbol sym, uint64_t class_id) {
    require_auth(_self);

    eosio_assert(is_account(issuer), "issuer account does not exist");

    eosio_assert(sym.is_valid(), "invalid symbol");
    eosio_assert(sym.precision() == 0, "symbol precision must be 0");

    token_data_table td_table(_self, _self.value);
    auto token_data = td_table.find(sym.code().raw());
    eosio_assert(token_data == td_table.end(), "token with symbol already exists");

    td_table.emplace(_self, [&](auto& td) {
       td.data.symbol = sym;
       td.data.amount = 0;
       td.issuer = issuer;
       td.class_id = class_id;
    });
}

void example::nft::remove(symbol sym) {
    require_auth(_self);

    eosio_assert(sym.is_valid(), "invalid symbol");

    token_data_table td_table(_self, _self.value);
    auto token_data = td_table.find(sym.code().raw());
    eosio_assert(token_data != td_table.end(), "token with symbol doesn't exist");

    eosio_assert(token_data->data.amount == 0, "burn all tokens before removing");

    td_table.erase(token_data);
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

    auto token_data = td_table.find(sym.code().raw());
    eosio_assert(token_data != td_table.end(), "token with symbol does not exist");

    token_table token_table(_self, _self.value);

    auto token = token_table.find(tk_id);
    eosio_assert(token != token_table.end(), "token with id does not exist");

    require_auth(token->owner);

    // TODO: Check if token_data->issuer has a contract deployed
    eosio_assert(is_account(token_data->issuer), "contract account does not exist");

    // Inline action to Token Issuer's contract
    action(permission_level{_self, name("active")}, token_data->issuer, name("burn"),
        std::make_tuple(sym, tk_id)).send();

    td_table.modify(token_data, _self, [&](auto& td) {
        td.data.amount--;
    });

    token_table.erase(token);
}

void example::nft::transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo) {
    require_auth(from);

    eosio_assert(from != to, "cannot transfer to self");

    eosio_assert(is_account(to), "to account does not exist");

    eosio_assert(memo.size() <= 256, "memo has more than 256 bytes");

    token_data_table td_table(_self, _self.value);
    auto token_data = td_table.find(sym.code().raw());
    eosio_assert(token_data != td_table.end(), "token with symbol doesn't exist");

    token_table token_table(_self, _self.value);

    auto token = token_table.find(tk_id);
    eosio_assert(token != token_table.end(), "token with id does not exist");

    eosio_assert(token->owner == from, "sender does not own token with specified id");

    // TODO: Check if token_data->issuer has a contract deployed
    eosio_assert(is_account(token_data->issuer), "contract account does not exist");

    // Inline action to Token Issuer's contract
    action(permission_level{_self, name("active")}, token_data->issuer, name("transfer"),
        std::make_tuple(from, to, sym, tk_id, memo)).send();

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

void example::nft::createclsprm(uint64_t schema_id, uint128_t data_hash,
    std::vector<uint8_t> data) {
    require_auth(_self);

    cls_param_table class_table(_self, _self.value);
    auto cls_index_table = class_table.get_index<name("byhash")>();
    auto class_hash = cls_index_table.find(data_hash);
    eosio_assert(class_hash == cls_index_table.end(), "class hash already exists");

    class_table.emplace(_self, [&](auto& cls) {
       cls.id = class_table.available_primary_key();
       cls.schema_id = schema_id;
       cls.data_hash = data_hash;
       for (int i = 0; i < data.size(); ++i) {
            cls.data.push_back(data[i]);
        }
    });
}

void example::nft::removeclsprm(uint64_t id) {
    require_auth(_self);

    cls_param_table class_table(_self, _self.value);
    auto rmv_cls_prm = class_table.find( id );
    eosio_assert( rmv_cls_prm != class_table.end(), "class parameter with id does not exist" );

    class_table.erase( rmv_cls_prm );
}

void example::nft::updateclsprm(uint64_t id, uint128_t data_hash, std::vector<uint8_t> data) {
    require_auth(_self);

    cls_param_table class_table(_self, _self.value);
    auto class_id = class_table.find(id);
    eosio_assert(class_id != class_table.end(), "class parameter not found");

    class_table.modify(class_id, _self, [&](auto& cls) {
       cls.data_hash = data_hash;
       cls.data.clear();
       for (int i = 0; i < data.size(); ++i) {
            cls.data.push_back(data[i]);
        }
    });
}

void example::nft::createspwprm(uint64_t schema_id, uint128_t data_hash,
    std::vector<uint8_t> data) {
    require_auth(_self); 

    spw_param_table spawn_table(_self, _self.value);
    auto spw_index_table = spawn_table.get_index<name("byhash")>();
    auto spawn_hash = spw_index_table.find(data_hash);
    eosio_assert(spawn_hash == spw_index_table.end(), "spawn hash already exists");

    spawn_table.emplace(_self, [&](auto& spawn) {
       spawn.id = spawn_table.available_primary_key();
       spawn.schema_id = schema_id;
       spawn.data_hash = data_hash;
       for (int i = 0; i < data.size(); ++i) {
            spawn.data.push_back(data[i]);
        }
    });
}

void example::nft::removespwprm(uint64_t id) {
    require_auth(_self);

    spw_param_table spawn_table(_self, _self.value);
    auto rmv_spawn_prm = spawn_table.find( id );
    eosio_assert( rmv_spawn_prm != spawn_table.end(), "spawn parameter with id does not exist" );

    spawn_table.erase( rmv_spawn_prm );
}

void example::nft::createcstprm(uint64_t schema_id, uint128_t data_hash,
    std::vector<uint8_t> data) {
    require_auth(_self); 

    cst_param_table custom_table(_self, _self.value);
    auto cst_index_table = custom_table.get_index<name("byhash")>();
    auto custom_hash = cst_index_table.find(data_hash);
    eosio_assert(custom_hash == cst_index_table.end(), "custom hash already exists");

    custom_table.emplace(_self, [&](auto& cst) {
       cst.id = custom_table.available_primary_key();
       cst.schema_id = schema_id;
       cst.data_hash = data_hash;
       for (int i = 0; i < data.size(); ++i) {
            cst.data.push_back(data[i]);
        }
    });
}

void example::nft::removecstprm(uint64_t id) {
    require_auth(_self);

    cst_param_table custom_table(_self, _self.value);
    auto rmv_cst_prm = custom_table.find( id );
    eosio_assert( rmv_cst_prm != custom_table.end(), "custom parameter with id does not exist" );

    custom_table.erase( rmv_cst_prm );
}

void example::nft::createschema(std::string definition) {
    require_auth(_self); 

    schema_table schema_table(_self, _self.value);

    schema_table.emplace(_self, [&](auto& schema) {
       schema.id = schema_table.available_primary_key();
       schema.definition = definition;
    });
}

void example::nft::removeschema(uint64_t id) {
    require_auth(_self);

    schema_table schema_table(_self, _self.value);
    auto rmv_schema = schema_table.find( id );
    eosio_assert( rmv_schema != schema_table.end(), "schema with id does not exist" );

    schema_table.erase(rmv_schema);
}

EOSIO_DISPATCH(example::nft, (create)(remove)(issue)(burn)(transfer)(createclsprm)(removeclsprm)
    (updateclsprm)(createspwprm)(removespwprm)(createcstprm)(removecstprm)(createschema)
    (removeschema))
