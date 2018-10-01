#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

namespace oasis {
    using namespace eosio;
    using std::string;

    class marketplace : public contract {
        
        public:

            marketplace(account_name self): contract::contract(self){}


            //@abi table product i64

            struct product{
                uint64_t product_id;
                string name;
                uint64_t power;
                uint64_t health;
                string ability;
                uint64_t level_up;
                uint64_t quantity;
                uint64_t price;

                uint64_t primary_key() const { return product_id; }

                EOSLIB_SERIALIZE(product, (product_id)(name)(power)(health)(ability)(level_up)(quantity)(price))
            }

            typedef multi_index<N(product), product> productIndex;

            //@abi action
            void buy(const account_name buyer, uint64_t product_id);

            //@abi action
            void getbyid(uint64_t product_id);

            //@abi action
            void add(const account_name account, product newProduct );

            //@abi action
            void update(const account_name account, uint64_t product_id, uint64_t quantity);

            //@abi action
            void remove(const account_name account, uint64_t product_id);


    }

    EOSIO_ABI(marketplace, (buy)(getbyid)(add)(update)(remove))
}