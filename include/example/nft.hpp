/**
*  @file nft.hpp
*/

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
//#include "flatbuffers/flatbuffers.h"

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
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION create(name issuer, symbol sym, uint64_t class_id);

            /**
             * @brief At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION remove(symbol sym);
            
            /**
             * @brief At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION issue(name to, symbol sym, uint64_t spawn_id, uint64_t cust_id); 

            /**
             * @brief At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION burn(symbol sym, uint64_t tk_id);

            /**
             * @brief At issue time, developer could update/change object parameter,
             * this  will affect only all future tokens, doesn’t affect 
             * previously minted tokens.
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo);

            /** 
             * @brief create class parameters
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION createclsprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief remove class parameters
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION removeclsprm(uint64_t id);

            /** 
             * @brief update class parameters - A modification on the class parameter will reflect
             * on all instances of the token class in the ecosystem,
             * including existing ones and ones to be minted.
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION updateclsprm(uint64_t id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief create spawn parameters
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION createspwprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief remove spawn parameters
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION removespwprm(uint64_t id);

            /** 
             * @brief create custom parameters
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION createcstprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief remove custom parameters
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION removecstprm(uint64_t id);

            /** 
             * @brief create data schema
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION createschema(std::string definition);

            /** 
             * @brief remove data schema
             * @param ??? - 
             * @param ??? - 
             * @param ??? - 
             */
            ACTION removeschema(uint64_t id);

            TABLE class_parameter {
                uint64_t id;
                uint64_t schema_id;
                uint128_t data_hash;
                std::vector<uint8_t> data;

                uint128_t get_data_hash() const {return data_hash;}
                uint64_t primary_key() const {return id;}
            };

            TABLE spawn_parameter {
                uint64_t id;
                uint64_t schema_id;
                uint128_t data_hash;
                std::vector<uint8_t> data;

                uint128_t get_data_hash() const {return data_hash;}
                uint64_t primary_key() const {return id;}
            };

            TABLE cust_parameter {
                uint64_t id;
                uint64_t schema_id;
                uint128_t data_hash;
                std::vector<uint8_t> data;

                uint128_t get_data_hash() const {return data_hash;}
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

            typedef eosio::multi_index<name("clsparamtbl"), class_parameter, 
                indexed_by<name("byhash"), const_mem_fun<class_parameter, uint128_t, &class_parameter::get_data_hash>>> cls_param_table;
            typedef eosio::multi_index<name("spwparamtbl"), spawn_parameter, 
                indexed_by<name("byhash"), const_mem_fun<spawn_parameter, uint128_t, &spawn_parameter::get_data_hash>>> spw_param_table;
            typedef eosio::multi_index<name("cstparamtbl"), cust_parameter,
                indexed_by<name("byhash"), const_mem_fun<cust_parameter, uint128_t, &cust_parameter::get_data_hash>>> cst_param_table;
            typedef eosio::multi_index<name("schematable"), schema> schema_table;
            typedef eosio::multi_index<name("tdatatable"), token_data> token_data_table;
            typedef eosio::multi_index<name("tokentable"), token> token_table;

        private:
            void mint(uint64_t spawn_id, uint64_t cust_id, name owner);
   };
} //example namespace
