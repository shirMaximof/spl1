//
// Created by 97252 on 07/11/2021.
//

#include <vector>
#include "Customer.h"
#include "Workout.h"
#include "Trainer.h"

typedef std::pair<int, Workout> OrderPair;

//class Trainer{
    Trainer::Trainer(int t_capacity){
        capacity=t_capacity;
    }
    int Trainer::getCapacity() const{

    }
    void Trainer::addCustomer(Customer* customer){

    }
    void Trainer::removeCustomer(int id){

    }
    Customer* Trainer::getCustomer(int id){

    }
    std::vector<Customer*>& Trainer::getCustomers(){

    }
    std::vector<OrderPair>& Trainer::getOrders(){

    }
    void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options){

    }
    void Trainer::openTrainer(){

    }
    void Trainer::closeTrainer(){

    }
    int Trainer::getSalary(){
        return -1;
    }
    bool Trainer::isOpen(){
        return open;
    }
//};