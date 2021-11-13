#include "Customer.h"
#include <iostream>
#include <vector>
#include "algorithm"

using namespace std;


//class customer
    Customer::Customer(std::string c_name, int c_id):name(c_name),id(c_id){}
    std::string Customer::getName() const {return name;}
    int Customer::getId() const {return id;}


//sweatyCustomer

    SweatyCustomer::SweatyCustomer(std::string name, int id): Customer(name,id){}
    std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options){
       // std::vector<Workout>* copy_workoutOptions= new std::vector<Workout>(workout_options);
        std::vector<int>* ordered= new std::vector<int>();
        for(int i=0;i<workout_options.size();i++){
            if(workout_options[i].getType()==CARDIO){
                ordered->push_back(workout_options[i].getId());
            }
        }
        return *ordered;
}
    std::string SweatyCustomer::toString() const{return getName()+",swt";}



//CheapCustomer
    CheapCustomer::CheapCustomer(std::string name, int id): Customer(name,id){}
    std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options){
     //   std::vector<Workout>* copy_workoutOptions= new std::vector<Workout>(workout_options);
        std::vector<int>* ordered= new std::vector<int>();
        int cheap = workout_options[0].getPrice();
        int id = 0;
        for(int i=1;i<workout_options.size();i++){
            if(workout_options[i].getPrice()<cheap) {
                cheap = workout_options[i].getPrice();
                id = workout_options[i].getId();
            }
        }
        ordered->push_back(id);
        return *ordered;
}
    std::string CheapCustomer::toString() const{return getName()+",chp";} //complete



//HeavyMuscleCustomer
    HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id): Customer(name,id){}
    std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options){
        std::vector<Workout>* copy_workoutOptions= new std::vector<Workout>(workout_options);
        std::vector<int>* ordered= new std::vector<int>();
        std::sort(copy_workoutOptions->begin(),copy_workoutOptions->end());
        for(int i=copy_workoutOptions->size()-1;i>0;i--){
            if((*copy_workoutOptions)[i].getType()==ANAEROBIC) {
                ordered->push_back((*copy_workoutOptions)[i].getId());
            }
        }
        return *ordered;
}
    std::string HeavyMuscleCustomer::toString() const{return getName()+",mcl";}


//FullBodyCustomer
    FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name,id){}
    std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
        std::vector<Workout>* copy_workoutOptions= new std::vector<Workout>(workout_options);
        std::vector<int>* ordered= new std::vector<int>();
        std::sort(copy_workoutOptions->begin(),copy_workoutOptions->end());
        for(int i=0;i<copy_workoutOptions->size();i++){
            if((*copy_workoutOptions)[i].getType()==CARDIO) {
                ordered->push_back((*copy_workoutOptions)[i].getId());
            }
            break;
        }
        for(int i=copy_workoutOptions->size()-1;i>=0;i++){
            if((*copy_workoutOptions)[i].getType()==MIXED) {
                ordered->push_back((*copy_workoutOptions)[i].getId());
            }
            break;
        }
        for(int i=0;i<copy_workoutOptions->size();i++){
            if((*copy_workoutOptions)[i].getType()==ANAEROBIC) {
                ordered->push_back((*copy_workoutOptions)[i].getId());
            }
            break;
        }
        return *ordered;
    }
    std::string FullBodyCustomer::toString() const{return getName()+",fbd";}



