/**
*  @file nft.hpp
*/

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
// #include "flatbuffers/flatbuffers.h"
// #include "flatbuffers/idl.h"
// #include "flatbuffers/util.h"

using namespace eosio;

namespace example {

    CONTRACT nft : public contract {
        public:
            /**
             * @brief Construct a nft object.
             * @param recvr - The name of this contract.
             * @param cd - The code name of the action this contract is processing.
             * @param ds - The datastream used.
             */
            nft(name recvr, name code, datastream<const char*> ds) : contract(recvr, code, ds) {}

            /**
             * @brief At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             * @param issuer - 
             * @param sym - 
             * @param class_id - 
             */
            ACTION create(name issuer, symbol sym, uint64_t class_id);

            /**
             * @brief At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             * @param sym - 
             */
            ACTION remove(symbol sym);
            
            /**
             * @brief At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             * @param to - 
             * @param sym - 
             * @param spawn_id - 
             * @param cust_id - 
             */
            ACTION issue(name to, symbol sym, uint64_t spawn_id, uint64_t cust_id); 

            /**
             * @brief erase a token from state data.
             * @param sym - 
             * @param tk_id - 
             */
            ACTION burn(symbol sym, uint64_t tk_id);

            /**
             * @brief Transfer token to other users.
             * @param from - 
             * @param to - 
             * @param sym - 
             * @param tk_id - 
             * @param memo - 
             */
            ACTION transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo);

            /** 
             * @brief create class parameters
             * @param schema_id - 
             * @param data_hash - 
             * @param data - 
             */
            ACTION createclsprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief remove class parameters
             * @param id - 
             */
            ACTION removeclsprm(uint64_t id);

            /** 
             * @brief update class parameters - A modification on the class parameter will reflect
             * on all instances of the token class in the ecosystem,
             * including existing ones and ones to be minted.
             * @param id - 
             * @param data_hash - 
             * @param data - 
             */
            ACTION updateclsprm(uint64_t id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief create spawn parameters
             * @param schema_id - 
             * @param data_hash - 
             * @param data - 
             */
            ACTION createspwprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief remove spawn parameters
             * @param id - 
             */
            ACTION removespwprm(uint64_t id);

            /** 
             * @brief create custom parameters
             * @param schema_id - 
             * @param data_hash - 
             * @param data - 
             */
            ACTION createcstprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief remove custom parameters
             * @param id - 
             */
            ACTION removecstprm(uint64_t id);

            /** 
             * @brief create data schema
             * @param definition - 
             */
            ACTION createschema(std::string definition);

            /** 
             * @brief remove data schema
             * @param id - 
             */
            ACTION removeschema(uint64_t id);

        private:
            void mint(uint64_t spawn_id, uint64_t cust_id, name owner);
    };

    TABLE class_param {
        uint64_t id;
        uint64_t schema_id;
        uint128_t data_hash;
        std::vector<uint8_t> data;
 
        uint64_t primary_key() const {return id;}
        uint128_t get_dhash() const {return data_hash;}
    };
 
    TABLE spawn_param {
        uint64_t id;
        uint64_t schema_id;
        uint128_t data_hash;
        std::vector<uint8_t> data;
 
        uint64_t primary_key() const {return id;}
        uint128_t get_dhash() const {return data_hash;}
    };
 
    TABLE cust_param {
        uint64_t id;
        uint64_t schema_id;
        uint128_t data_hash;
        std::vector<uint8_t> data;
 
        uint64_t primary_key() const {return id;}
        uint128_t get_dhash() const {return data_hash;}
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
        uint64_t token_data_id;
        uint64_t spawn_id;
        uint64_t custom_id;
        name owner;
 
        uint64_t primary_key() const {return id;}
    };
 
    typedef eosio::multi_index<name("clsparamtbl"), class_param, 
        indexed_by<name("byhash"), const_mem_fun<class_param, uint128_t, &class_param::get_dhash>>>
        cls_param_table;
    typedef eosio::multi_index<name("spwparamtbl"), spawn_param, 
        indexed_by<name("byhash"), const_mem_fun<spawn_param, uint128_t, &spawn_param::get_dhash>>>
        spw_param_table;
    typedef eosio::multi_index<name("cstparamtbl"), cust_param,
        indexed_by<name("byhash"), const_mem_fun<cust_param, uint128_t, &cust_param::get_dhash>>>
        cst_param_table;
    typedef eosio::multi_index<name("schematable"), schema> schema_table;
    typedef eosio::multi_index<name("tdatatable"), token_data> token_data_table;
    typedef eosio::multi_index<name("tokentable"), token> token_table;

} //example namespace
