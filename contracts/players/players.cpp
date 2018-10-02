#include "players.hpp"

namespace oasis {
    
    void players::add(const account_name account, string& username ) {
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);

        eosio_assert(iterator == players.end(), "Adress for account already exists");

        players.emplace(account, [&](auto& player){
            player.account_name = account;
            player.username = username;
            player.level = 1;
            player.health_points = 1000;
            player.energy_points = 1000;
        });


    }

    void players::update(const account_name account, uint64_t level, int64_t healthPoints, int64_t energyPoints){
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);

        eosio_assert(iterator != players.end(), "Adress for account does not exist");

        players.modify(iterator, account, [&](auto& player){
            player.level = level;

            if((player.health_points - healthPoints) < 0){
                player.health_points = 0;
            } else {
                player.health_points -=  healthPoints;
            }

            if((player.energy_points - energyPoints) < 0){
                player.energy_points = 0;
            } else {
                player.energy_points -=  energyPoints;
            }

        });

    }

    void players::getplayer(const account_name account){
        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Account not found");

        //auto currentPlayer = players.get(account);
        auto currentPlayer = *iterator;
        print("Username: ", currentPlayer.username.c_str());
        print(" | Level: ", currentPlayer.level);
        print(" | Health: ", currentPlayer.health_points);
        print(" | Energy: ", currentPlayer.energy_points);

        vector<string> abilities = currentPlayer.abilities;

        if(abilities.size() > 0){

            print(" | Abilities:");

            for_each(abilities.begin(), abilities.end(), [&](string& ability){
                print(" ", ability.c_str());
            });
        } else {
            print(" | No abilities.");
        }
         vector<item> inventory = currentPlayer.inventory;
         if(inventory.size() > 0){

            print(" | Inventory:");

            for_each(inventory.begin(), inventory.end(), [&](item& item){
                item.display();
            });
        } else {
            print(" | No Inventory.");
        }



    }

    //@abi action
    void players::addability(const account_name account, string& ability){
        
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Account not found");

        players.modify(iterator, account, [&](auto& player){
            player.abilities.push_back(ability);
        });
    }

    //@abi action
    void players::additem(const account_name account, item purchased_item){
        require_auth(account);
        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Account not found.");

        players.modify(iterator, account, [&](auto& player){
            player.energy_points += purchased_item.power;
            player.health_points += purchased_item.health;
            player.level += purchased_item.level_up;
            player.abilities.push_back(purchased_item.ability);
            player.inventory.push_back(item{
                purchased_item.item_id,
                purchased_item.name,
                purchased_item.power,
                purchased_item.health,
                purchased_item.ability,
                purchased_item.level_up
            });
        });

        purchased_item.display();
    }

}
