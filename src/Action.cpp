#include "Action.h"

//BaseAction
    BaseAction::BaseAction() { }
    ActionStatus BaseAction::getStatus() const { }
    void BaseAction::complete(){}
    void BaseAction::error(std::string errorMsg){}
    std::string BaseAction::getErrorMsg() const {}

//OpenTrainer
    OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {}
    void OpenTrainer::act(Studio &studio) {}
    std::string OpenTrainer::toString() const {}



//Order

    Order::Order(int id){}
    Order::void act(Studio &studio){}
    std::string Order::toString() const{}


//MoveCustomer
    MoveCustomer::MoveCustomer(int src, int dst, int customerId){}
    MoveCustomer::void act(Studio &studio){}
    std::string MoveCustomer::toString() const{}


//Close

    Close::Close(int id){}
    Close::void act(Studio &studio){}
    std::string  Close::toString() const{}


// CloseAll
    CloseAll::CloseAll(){}
    CloseAll::void act(Studio &studio){}
    std::string  CloseAll::toString() const{}


//PrintWorkoutOptions

    PrintWorkoutOptions::PrintWorkoutOptions(){}
    PrintWorkoutOptions::void act(Studio &studio){}
    std::string PrintWorkoutOptions::toString() const{}



//PrintTrainerStatus
    PrintTrainerStatus::PrintTrainerStatus(int id){}
    PrintTrainerStatus::void act(Studio &studio){}
    std::string PrintTrainerStatus::toString() const{}



//PrintActionsLog
    PrintActionsLog ::PrintActionsLog(){}
    PrintActionsLog ::void act(Studio &studio){}
    std::string PrintActionsLog ::toString() const{}



//BackupStudio
    BackupStudio::BackupStudio(){}
    BackupStudio::void act(Studio &studio){}
    std::string BackupStudio::toString() const{}



    //RestoreStudio
    RestoreStudio ::RestoreStudio(){}
    RestoreStudio :: void act(Studio &studio){}
    std::string RestoreStudio ::toString() const{}

