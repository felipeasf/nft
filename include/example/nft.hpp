/**
*  @file nft.hpp
*/

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>

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
             * @brief Create a new type of NFT.
             * @param issuer - Account responsible for issueing new tokens.
             * @param sym - NFT symbol.
             * @param class_id - ID of Class Parameters registry.
             */
            ACTION create(name issuer, symbol sym, uint64_t class_id);

            /**
             * @brief Remove a type of NFT.
             * @param sym - Symbol of NFT to be removed.
             */
            ACTION remove(symbol sym);
            
            /**
             * @brief Issue a new token.
             * @param to - Account that will receive new token.
             * @param sym - NFT symbol.
             * @param spawn_id - ID of Spawn Parameters registry.
             * @param cust_id - ID of Custom Parameters registry.
             */
            ACTION issue(name to, symbol sym, uint64_t spawn_id, uint64_t cust_id); 

            /**
             * @brief Burn an existing token.
             * @param sym - NFT symbol.
             * @param tk_id - ID of token.
             */
            ACTION burn(symbol sym, uint64_t tk_id);

            /**
             * @brief Transfer token between accounts.
             * @param from - Account from where token will be transfered.
             * @param to - Account where token will be transfered to.
             * @param sym - Token symbol.
             * @param tk_id - ID of token.
             * @param memo - Transfer memo.
             */
            ACTION transfer(name from, name to, symbol sym, uint64_t tk_id, std::string memo);

            /** 
             * @brief Create class parameters.
             * @param schema_id - ID of schema registry used.
             * @param data_hash - Hash of serialized parameters data.
             * @param data - Serialized parameters data.
             */
            ACTION createclsprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief Remove class parameters.
             * @param id - ID of class parameters registry.
             */
            ACTION removeclsprm(uint64_t id);

            /** 
             * @brief Update class parameters.
             * @param id - ID of class parameters registry.
             * @param data_hash - Hash of new serialized parameters data.
             * @param data - New serialized parameters data.
             */
            ACTION updateclsprm(uint64_t id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief Create spawn parameters.
             * @param schema_id - ID of schema registry used.
             * @param data_hash - Hash of serialized parameters data.
             * @param data - Serialized parameters data.
             */
            ACTION createspwprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief Remove spawn parameters.
             * @param id - ID of spawn parameters registry.
             */
            ACTION removespwprm(uint64_t id);

            /** 
             * @brief Create custom parameters.
             * @param schema_id - ID of schema registry used.
             * @param data_hash - Hash of serialized parameters data.
             * @param data - Serialized parameters data.
             */
            ACTION createcstprm(uint64_t schema_id, uint128_t data_hash, std::vector<uint8_t> data);

            /** 
             * @brief Remove custom parameters.
             * @param id - ID of custom parameters registry.
             */
            ACTION removecstprm(uint64_t id);

            /** 
             * @brief Create schema.
             * @param definition - JSON of schema definition.
             */
            ACTION createschema(std::string definition);

            /** 
             * @brief Remove schema.
             * @param id - ID of schema registry.
             */
            ACTION removeschema(uint64_t id);

        private:
            /** 
             * @brief Mint a new token.
             * @param spawn_id - ID of spawn parameters registry.
             * @param cust_id - ID of custom parameters registry.
             * @param owner - Owner account of minted token.
             */
            void mint(uint64_t spawn_id, uint64_t cust_id, name owner);
   };

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

   typedef eosio::multi_index<name("clsparamtable"), class_parameter> cls_param_table;
   typedef eosio::multi_index<name("spwparamtable"), spawn_parameter> spw_param_table;
   typedef eosio::multi_index<name("cstparamtable"), cust_parameter> cst_param_table;
   typedef eosio::multi_index<name("schematable"), schema> schema_table;
   typedef eosio::multi_index<name("tdatatable"), token_data> token_data_table;
   typedef eosio::multi_index<name("tokentable"), token> token_table;

} //example namespace
