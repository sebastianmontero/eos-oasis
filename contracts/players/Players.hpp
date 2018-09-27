#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>


namespace Oasis {
    using namespace eosio;
    using std::string;


    class Players : public contract {
        using contract::contract;

        public:

          //@abi table item i64
            struct item {
                uint64_t item_id;
                string name;
                uint64_t power;
                uint64_t health;
                string ability;
                uint64_t level_up;

                uint64_t primary_key() const { return item_id; }

                EOSLIB_SERIALIZE(item, (item_id)(name)(power)(health)(ability)(level_up))
            };

            typedef multi_index<N(item), item> itemIndex;

            //@abi table player i64
            struct player {
                uint64_t account_name;
                string username;
                uint64_t level;
                uint64_t health_points = 1000;
                uint64_t energy_points = 1000;
                vector<string> abilities;
                vector<item> inventory;

                uint64_t primary_key() const {return account_name;}

                EOSLIB_SERIALIZE(player, (account_name)(username)(level)(health_points)(energy_points)(abilities))
            };

            typedef multi_index<N(player), player> playerIndex;

            Players(account_name self): contract(self){}

            //@abi action
            void add(const account_name account, string& username );

            //@abi action
            void update(const account_name account, uint64_t level, int64_t healthPoints, int64_t energyPoints);

            //@abi action
            void getplayer(const account_name account);

            //@abi action
            void addability(const account_name account, string& ability);

            //@abi action
            void additem(const account_name account, item purchased_item);      
    };

    EOSIO_ABI(Players, (add)(update)(getplayer)(addability)(additem))
}

