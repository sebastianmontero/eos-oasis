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
            }

            //@abi action
            void add(const account_name account, )

    }
}