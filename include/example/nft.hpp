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

            ACTION create(name issuer, symbol sym, uint64_t class_id);

            ACTION remove(symbol sym);

            /*
             * At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             *
             */
            ACTION issue(name to, symbol sym, uint64_t spawn_id, uint64_t cust_id); 

            ACTION burn(symbol sym, uint64_t tk_id);

            ACTION transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo);

            //create class parameters
            ACTION createclsprm();

            //remove class parameters
            ACTION removeclsprm();

            /*updata class parameters
             *
             * A modification on the class parameter will reflect
             * on all instances of the token class in the ecosystem,
             * including existing ones and ones to be minted.
             *
             */
            ACTION updateclsprm();

            //create spawn parameters
            ACTION createspwprm();

            //remove spawn parameters
            ACTION removespwprm();

            //create custom parameters
            ACTION createcstprm();

            //remove custom parameters
            ACTION removecstprm();

            ACTION createschema();

            ACTION removeschema();

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

            TABLE token_data {
                asset data;
                name issuer;
                uint64_t class_id;

                uint64_t primary_key() const {return data.symbol.code().raw();}
            };

            TABLE token {
                uint64_t id;
                uint64_t spawn_id;
                uint64_t custom_id;
                name owner;

                uint64_t primary_key() const {return id;}
            };

            typedef eosio::multi_index<"clsparamtable"_n, class_parameter> cls_param_table;
            typedef eosio::multi_index<"spwparamtable"_n, spawn_parameter> spw_param_table;
            typedef eosio::multi_index<"cstparamtable"_n, cust_parameter> cst_param_table;
            typedef eosio::multi_index<"schematable"_n, schema> schema_table;
            typedef eosio::multi_index<"tdatatable"_n, token_data> token_data_table;
            typedef eosio::multi_index<"tokentable"_n, token> token_table;

        private:
            void mint(symbol sym, uint64_t spawn_id, uint64_t cust_id, name owner);
   };
} //example namespace
