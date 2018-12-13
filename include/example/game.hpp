/**
*  @file game.hpp
*/

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;

namespace example {

    CONTRACT game : public contract {
        public:
            /**
             * @brief Construct a game object.
             * @param recvr - The name of this contract.
             * @param cd - The code name of the action this contract is processing.
             * @param ds - The datastream used.
             */
            game(name recvr, name code, datastream<const char*> ds) : contract(recvr, code, ds) {}

            /**
             * @brief Transfer token between accounts.
             * @param from - Account from where token will be transfered.
             * @param to - Account where token will be transfered to.
             * @param sym - Token symbol.
             * @param tk_id - Token id.
             * @param memo - Transfer memo.
             */
            ACTION transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo);

            TABLE token {
                uint64_t id;
                uint64_t spawn_id;
                uint64_t custom_id;
                name owner;

                uint64_t primary_key() const {return id;}
            };

            typedef eosio::multi_index<name("tokentable"), token> token_table;
   };
} //example namespace
