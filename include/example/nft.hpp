/**
*  @file nft.hpp
*/

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

using namespace eosio;

namespace example {

    CONTRACT nft : public contract {
        public:
            nft(name recvr, name code, datastream<const char*> ds) : contract(recvr, code, ds) {}

            ACTION create(name issuer, symbol sym);

            ACTION remove(symbol sym);

            ACTION issue(name to, symbol sym, uint64_t class_id, uint64_t spawn_id,
                uint64_t cust_id); 

            ACTION burn(symbol sym, uint64_t tk_id);

            ACTION transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo);

            TABLE class_parameter {
                uint64_t id;
                uint64_t schema_id;
                uint128_t data_hash;
                std::vector<uint8_t> data;

                uint64_t primary_key() const {return id;}
            };

            TABLE spawn_parameter {
                uint64_t id;
                uint64_t schema_id;
                uint128_t data_hash;
                std::vector<uint8_t> data;

                uint64_t primary_key() const {return id;}
            };

            TABLE cust_parameter {
                uint64_t id;
                uint64_t schema_id;
                uint128_t data_hash;
                std::vector<uint8_t> data;

                uint64_t primary_key() const {return id;}
            };

            TABLE schema {
                uint64_t id;
                std::string definition;

                uint64_t primary_key() const {return id;}
            };

            TABLE token {
                uint64_t id;
                uint64_t class_id;
                uint64_t spawn_id;
                uint64_t custom_id;
                name owner;

                uint64_t primary_key() const {return id;}
            };

            TABLE token_stat {
                asset data;
                name issuer;

                uint64_t primary_key() const {return data.symbol.code().raw();}
            };

            typedef eosio::multi_index<"clsparamtable"_n, class_parameter> cls_param_table;
            typedef eosio::multi_index<"spwparamtable"_n, spawn_parameter> spw_param_table;
            typedef eosio::multi_index<"cstparamtable"_n, cust_parameter> cst_param_table;
            typedef eosio::multi_index<"schematable"_n, schema> schema_table;
            typedef eosio::multi_index<"tokentable"_n, token> token_table;
            typedef eosio::multi_index<"tstattable"_n, token_stat> token_stat_table;

        private:
            void mint(symbol sym, uint64_t class_id, uint64_t spawn_id, uint64_t cust_id,
                name owner);
   };
} //example namespace
