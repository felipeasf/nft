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
             * @brief Create a NFT type
             * @param issuer - token issuer
             * @param sym - token symbol
             * @param class_id - class parameters id reference
             */
            ACTION create(name issuer, symbol sym, uint64_t class_id);

            /**
             * @brief At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             * @param sym - token symbol
             */
            ACTION remove(symbol sym);
            
            /**
             * @brief At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             * @param to - who is gonna receive the issued tokens
             * @param sym - token symbol
             * @param spawn_id - spawn parameters id reference
             * @param cust_id - custom parameters id reference
             */
            ACTION issue(name to, symbol sym, uint64_t spawn_id, uint64_t cust_id); 

            /**
             * @brief erase a token from state data.
             * @param sym - token symbol
             * @param tk_id - token id
             */
            ACTION burn(symbol sym, uint64_t tk_id);

            /**
             * @brief Transfer token to other users.
             * @param from - token sender
             * @param to - token receiver
             * @param sym - token symbol
             * @param tk_id - token id 
             * @param memo - text memo
             */
            ACTION transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo);

            /** 
             * @brief create class parameters
             * @param schema_id - schema id reference
             * @param data_hash - hash of class parameters data
             * @param data - class parameters serialized data
             */
            ACTION createclsprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief remove class parameters
             * @param id - class parameters id reference
             */
            ACTION removeclsprm(uint64_t id);

            /** 
             * @brief update class parameters - A modification on the class parameter will reflect
             * on all instances of the token class in the ecosystem,
             * including existing ones and ones to be minted.
             * @param id - class parameters id reference
             * @param data_hash - new hash of class parameters data
             * @param data - new class parameters serialized data
             */
            ACTION updateclsprm(uint64_t id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief create spawn parameters
             * schema_id - schema id reference
             * @param data_hash - hash of spawn parameters data
             * @param data - spawn parameters serialized data
             */
            ACTION createspwprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief remove spawn parameters
             * @param id - spawn parameters id reference
             */
            ACTION removespwprm(uint64_t id);

            /** 
             * @brief create custom parameters
             * @schema_id - schema id reference
             * @param data_hash - hash of custom parameters data
             * @param data - custom parameters serialized data
             */
            ACTION createcstprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief remove custom parameters
             * @param id - custom parameters id reference
             */
            ACTION removecstprm(uint64_t id);

            /** 
             * @brief create data schema
             * @param definition - json schema
             */
            ACTION createschema(std::string definition);

            /** 
             * @brief remove data schema
             * @param id - schema id reference
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
