#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

namespace oasis {
    using namespace eosio;
    using std::string;

    class marketplace : public contract {
        
        public:

            marketplace(account_name self): contract::contract(self){}
            

    }
}