#include "players.hpp"

namespace Oasis {
    
    //@abi action
    void Players::add(const account_name account, string& username ) {
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

    //@abi action
    void Players::update(const account_name account, uint64_t level, int64_t healthPoints, int64_t energyPoints){
        require_auth(account);

        playerIndex players(_self, _self);

        auto iterator = players.find(account);

        eosio_assert(iterator != players.end(), "Adress for account does not exist");

        players.modify(iterator, account, [&](auto& player){
            player.level = 1;

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

    //@abi action
    void Players::getplayer(const account_name account){
        playerIndex players(_self, _self);

        auto iterator = players.find(account);
        eosio_assert(iterator != players.end(), "Account not found");

        auto currentPlayer = players.get(account);
        print("Username: ", currentPlayer.username.c_str(), " Level: ", currentPlayer.level, " Health: ", currentPlayer.health_points, " Energy: ", currentPlayer.energy_points);
    }

}
