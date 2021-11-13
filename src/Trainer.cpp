//
// Created by 97252 on 07/11/2021.
//

#include <vector>
#include "Customer.h"
#include "Workout.h"
#include "Trainer.h"

#include <iostream>

typedef std::pair<int, Workout> OrderPair;

//class Trainer{
Trainer::Trainer(int t_capacity) {
    capacity = t_capacity;
    open = false;
}

int Trainer::getCapacity() const {
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {
    if (customersList.size() == capacity) {
        std::cout << "Cannot move customer" << std::endl;
    } else {
        customersList.push_back(customer);
    }
}

void Trainer::removeCustomer(int id) {
    int i = 0;
    for (Customer *c: customersList)
        if (c->getId() == id) {
            customersList.erase(customersList.begin() + i);
            int j = 0;
            for (OrderPair p: orderList) {
                if (p.first == id)
                    orderList.erase(orderList.begin() + j);
                j++;
            }
            break;
        }
    i++;
}

Customer *Trainer::getCustomer(int id) {
    for (Customer *c: customersList)
        if (c->getId() == id)
            return c;
}

std::vector<Customer *> &Trainer::getCustomers() {
    return customersList;
}

std::vector<OrderPair> &Trainer::getOrders() {
    return orderList;
}

void
Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout> &workout_options) {
            int id = 0;
            for(int i=0;i<customersList.size();i++)
            {
                if(customersList[i]->getId() == customer_id )
                {
                    id = i;
                    break;
                }
            }
            for (int id: workout_ids)
                for (Workout w: workout_options)
                    if (id == w.getId()) {
                        orderList.push_back(std::make_pair(customer_id, w));
                        std::cout << customersList[id]->getName() << " Is Doing " << w.getName();
                    }
}

void Trainer::openTrainer() {
    open = true;
}

void Trainer::closeTrainer() {
    open = false;
    customersList.clear();
    orderList.clear();
}

int Trainer::getSalary() {
    int salary = 0;
    for (OrderPair p: orderList) {
        salary += p.second.getPrice();
    }
    return salary;
}

bool Trainer::isOpen() {
    return open;
}
bool Trainer::isFull() {
    return capacity <= customersList.size();
}
//};