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
        std::vector<pair<int,int>> *copy_workoutOptions = new vector<pair<int,int>>();
        for(int i=workout_options.size()-1;i>0;i--){
            if((workout_options)[i].getType()==ANAEROBIC) {
                copy_workoutOptions->push_back(pair<int,int>((workout_options)[i].getId(),(workout_options)[i].getPrice()));
            }
        }
        std::vector<int>* ordered= new std::vector<int>();
        std::sort(copy_workoutOptions->begin(),copy_workoutOptions->end(), [](const pair<int,int> left, const pair<int,int> right) {return left.second < right.second;} );
        for(int i=copy_workoutOptions->size()-1;i>0;i--){
                ordered->push_back((*copy_workoutOptions)[i].first);
            }
        return *ordered;
}
    std::string HeavyMuscleCustomer::toString() const{return getName()+",mcl";}


//FullBodyCustomer
    FullBodyCustomer::FullBodyCustomer(std::string name, int id): Customer(name,id){}
    std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options){
        std::vector<pair<int,int>>* cardioprice =  new vector<pair<int,int>>();
        std::vector<pair<int,int>>* mixedprice =  new vector<pair<int,int>>();
        std::vector<pair<int,int>>* anaerobicprice = new vector<pair<int,int>>();
        for(int i=workout_options.size()-1;i>0;i--){
            if(workout_options[i].getType() == CARDIO)
                cardioprice->push_back(pair<int,int>(workout_options[i].getId(),workout_options[i].getPrice()));
        }
        for(int i=workout_options.size()-1;i>0;i--){
            if(workout_options[i].getType() == MIXED)
                mixedprice->push_back(pair<int,int>(workout_options[i].getId(),workout_options[i].getPrice()));
        }
        for(int i=workout_options.size()-1;i>0;i--){
            if(workout_options[i].getType() == ANAEROBIC)
                anaerobicprice->push_back(pair<int,int>(workout_options[i].getId(),workout_options[i].getPrice()));
        }
        std::vector<int>* ordered= new std::vector<int>();
        std::sort(cardioprice->begin(),cardioprice->end(), [](const pair<int,int> left, const pair<int,int> right) {return left.second < right.second;});
        std::sort(mixedprice->begin(),mixedprice->end()), [](const pair<int,int> left, const pair<int,int> right) {return left.second < right.second;};
        std::sort(anaerobicprice->begin(),anaerobicprice->end(), [](const pair<int,int> left, const pair<int,int> right) {return left.second < right.second;});

        if(cardioprice->size()>0)
            ordered->push_back((*cardioprice)[0].first);

        if(mixedprice->size()>0)
            ordered->push_back((*mixedprice)[mixedprice->size()-1].first);

        if(anaerobicprice->size()>0)
            ordered->push_back((*anaerobicprice)[0].first);
        return *ordered;
    }
    std::string FullBodyCustomer::toString() const{return getName()+",fbd";}



