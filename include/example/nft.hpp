/**
*  @file nft.hpp
*/

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
//#include <boost/container_hash/hash.hpp>

using namespace eosio;

//TODO: Issuing, burning and tranfering multiple tokens can be a problem. What happens if one fail?

namespace example {

    CONTRACT nft : public contract {
        public:
            nft(name recvr, name code, datastream<const char*> ds) : contract(recvr, code, ds) {}

            ACTION create(name issuer, symbol sym, std::string gd_json);

            ACTION remove(symbol sym);

            ACTION issue(name to, symbol sym, std::string td_json, std::vector<std::string> json_data); 

            ACTION burn(name owner, symbol sym, std::vector<uint64_t> tk_ids);

            ACTION transfer(name from, name to, symbol sym, std::vector<uint64_t> tk_ids, std::string memo);

            //class parameters
            TABLE class_parameter {
                uint128_t hash;
                uint64_t id;
                uint64_t schema_id;
                std::vector<uint8_t> class_data;

                uint64_t primary_key() const {return id;}
            };
            //object parameters
            TABLE obj_parameter {
                uint128_t hash;
                uint64_t id;
                uint64_t schema_id;
                std::vector<uint8_t> obj_data;

                uint64_t primary_key() const {return id;}
            };

            //object parameters
            TABLE cust_parameter {
                uint128_t hash;
                uint64_t id;
                uint64_t schema_id;
                std::vector<uint8_t> cust_data;

                uint64_t primary_key() const {return id;}
            };

            //token kind parameters
            TABLE schema {
                uint64_t id;
                string definition;

                uint64_t primary_key() const {return id;}
            };

            //individual token parameters
            TABLE token {
                uint64_t class_id;
                uint64_t obj_id;
                uint64_t custom_id;
                name owner;

                uint64_t primary_key() const {return obj_record_id;}
            };

            typedef eosio::multi_index<"classtable"_n, class_parameter> class_table;
            typedef eosio::multi_index<"objtable"_n, obj_parameter> obj_table;
            typedef eosio::multi_index<"custtable"_n, cust_parameter> cust_table;
            typedef eosio::multi_index<"tstattable"_n, token_stat> tstat_table;
            typedef eosio::multi_index<"tokentable"_n, token> token_table;

        private:
            void mint(symbol sym, std::string json_data, name owner, uint64_t td_hash);
   };
} //example namespace
