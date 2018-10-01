#include "marketplace.hpp"

namespace oasis{

   void marketplace::getbyid(uint64_t product_id){

       productIndex products(_self, _self);

       auto iterator = products.find(product_id);

       eosio_assert(iterator != products.end(), "Product does not exist");

       product product = *iterator;

       print("Id: ", product.product_id);
       print(" | Name: ", product.name.c_str());
       print(" | Power: ", product.power);
       print(" | Health: ", product.health);
       print(" | Ability: ", product.ability.c_str());
       print(" | Level up: ", product.level_up);
       print(" | Quantity: ", product.quantity);
       print(" | Price: ", product.price);

   }

   void marketplace::buy(const account_name buyer, uint64_t product_id){
       
       productIndex products(_self,_self);

       auto iterator = products.find(product_id);
       eosio_assert(iterator != products.end(), "Product does not exist");

       product product = *iterator;
       eosio_assert(product.quantity > 0, "Product out of stock");

       asset productPrice = asset(product.price, string_to_symbol(4, "OAS"));

       action(vector<permission_level>(), N(eosiotoken), N(transfer), make_tuple(buyer), _self, productPrice, string(""))).send();

       action(vector<permission_level>(), N(marketplace), N(additem), make_tuple(buyer, 
            product.product_id,
            product.name,
            product.power,
            product.health,
            product.ability,
            product.level_up
        )).send();

        update(buyer, product.prodcut_id, -1);
       
   }    

    void marketplace::add(const account_name account, product newProduct){
       
        require_auth(account);

        productIndex products(_self,_self);

        auto iterator = products.find(product.product_id);

        eosio_assert(iterator == products.end(), "Product already exists");

        products.emplace(account, [&](auto& product){
            product.product_id = newProduct.product_id;
            product.name = newProduct.name;
            product.power = newProduct.power;
            product.health = newProduct.health;
            product.ability = newProduct.ability;
            product.level_up = newProduct.level_up;
            product.quantity = newProduct.quantity;
            product.price = newProduct.price;
        });
    
    }

    void marketplace::update(const account_name account, uint64_t product_id, uint64_t quantity){
        require_auth(account);

        productIndex products(_self, _self);

        auto iterator = products.find(product_id);

        eosio_assert(iterator != products.end(), "Product not found");

        products.modify(iterator, account, [&](product& product){
            product.quantity += quantity;
        });
    }

    void marketplace::remove(const account_name, uint64_t product_id){
        require_auth(account);

        productIndex products(_self, _self);

        auto iterator = products.find(product_id);

        eosio_assert(iterator != products.end(), "Product not found");

        products.erase(product_id);
    }
}