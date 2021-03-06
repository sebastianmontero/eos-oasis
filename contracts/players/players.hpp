#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>


namespace oasis {
    using namespace eosio;
    using std::string;


    class players : public contract {
        using contract::contract;

        public:

            players(account_name self): contract(self){}

          //@abi table item i64
            struct item {
                uint64_t item_id;
                string name;
                uint64_t power;
                uint64_t health;
                string ability;
                uint64_t level_up;

                uint64_t primary_key() const { return item_id; }

                void  display(){
                    print("[Item Id: ", item_id);
                    print(" | Name: ", name.c_str());
                    print(" | Power: ", power);
                    print(" | Health: ", health);
                    print(" | Ability: ", ability.c_str());
                    print(" | Level up: ", level_up, "]");
                }

                EOSLIB_SERIALIZE(item, (item_id)(name)(power)(health)(ability)(level_up))
            };

            typedef multi_index<N(item), item> itemIndex;

            //@abi table player2 i64
            struct player {
                uint64_t account_name;
                string username;
                uint64_t level;
                uint64_t health_points = 1000;
                uint64_t energy_points = 1000;
                vector<string> abilities;
                vector<item> inventory;

                uint64_t primary_key() const {return account_name;}

                EOSLIB_SERIALIZE(player, (account_name)(username)(level)(health_points)(energy_points)(abilities)(inventory))
            };

            typedef multi_index<N(player2), player> playerIndex;

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

    EOSIO_ABI(players, (add)(update)(getplayer)(addability)(additem))
}

