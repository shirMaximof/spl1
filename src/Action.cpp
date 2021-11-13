#include "Action.h"
#include "Trainer.h"
#include "Studio.h"
#include <iostream>
#include "main.cpp"

//BaseAction
    BaseAction::BaseAction() { }
    ActionStatus BaseAction::getStatus() const { return status;}
    void BaseAction::complete(){status=COMPLETED; }
    void BaseAction::error(std::string errorMsg){
    BaseAction::errorMsg = "Error: "+errorMsg;
    status = ERROR;
     std::cout<<errorMsg<<std::endl;}
    std::string BaseAction::getErrorMsg() const {return errorMsg;}

//OpenTrainer
    OpenTrainer::OpenTrainer(int id, std::vector<Customer *> &customersList) : trainerId(id), customers(customersList) {}
    void OpenTrainer::act(Studio &studio) {
        Trainer *t = studio.getTrainer(trainerId);
        if(t== nullptr | t->isOpen())
            error("Workout session does not exist or is already open");
        for(int i=0;i<customers.size();i++)
            t->addCustomer(customers[i]);
        t->openTrainer();

}
    std::string OpenTrainer::toString() const {
    string costumers_s="";
    for(int i=0;i=customers.size();i++)
        costumers_s = costumers_s+" "+customers[i]->toString() ;
    return "open "+trainerId; //continue
} //continue



//Order

    Order::Order(int id):trainerId(id){}
    void Order::act(Studio &studio){
    Trainer* t=studio.getTrainer(trainerId);
    if(t==nullptr | !t->isOpen())
        error("\"Trainer does not exist or is not open\"");
    else
        for(Customer* c : t->getCustomers())
            t->order(c->getId(),c->order(studio.getWorkoutOptions()),studio.getWorkoutOptions());
}
    std::string Order::toString() const{} // continue


//MoveCustomer
    MoveCustomer::MoveCustomer(int src, int dst, int customerId):srcTrainer(src),dstTrainer(dst),id(customerId){
}
   void MoveCustomer::act(Studio &studio){
       Trainer *srcS = studio.getTrainer(srcTrainer);
       Trainer *srcD = studio.getTrainer(dstTrainer);
        if(srcD== nullptr | srcS == nullptr | !srcD->isOpen() | !srcS->isOpen() | srcS->getCustomer(id)== nullptr | srcD->isFull())
            error("Cannot move customer");
       if(srcS->isOpen() && srcD->isOpen()) {
           srcS->removeCustomer(id);
           srcD->addCustomer(studio.getTrainer(srcTrainer)->getCustomer(id));
            if(srcS->getCustomers().empty())
            {
                Close close(srcTrainer);
                close.act(studio);
            }
       }
       

}
    std::string MoveCustomer::toString() const{} //continue


//Close

    Close::Close(int id):trainerId(id){
}
   void  Close::act(Studio &studio){
    Trainer* t=studio.getTrainer(trainerId);
    int salary=t->getSalary();
    t->closeTrainer();
    std::cout<<"Trainer "<<trainerId<<" is closed. Salary "<<salary<<"NIS"<<std::endl;
}
    std::string  Close::toString() const{}


// CloseAll
    CloseAll::CloseAll(){}
    void CloseAll::act(Studio &studio){
        for (int id = 0; id < studio.getNumOfTrainers(); id++) {
            Trainer* t=studio.getTrainer(id);
            if(t->isOpen())
                Close(id).act(studio);
        }
}
    std::string  CloseAll::toString() const{}


//PrintWorkoutOptions

    PrintWorkoutOptions::PrintWorkoutOptions(){}
    void PrintWorkoutOptions::act(Studio &studio){
    for(Workout w : studio.getWorkoutOptions())
        std::cout<<w.getName()<<", "<<w.getType()<<", "<<w.getPrice()<<std::endl;
}
    std::string PrintWorkoutOptions::toString() const{}



//PrintTrainerStatus
    PrintTrainerStatus::PrintTrainerStatus(int id):trainerId(id){}
    void PrintTrainerStatus::act(Studio &studio){
    Trainer* t=studio.getTrainer(trainerId);
    std::string isOpen;
    if(t->isOpen())
        isOpen="open";
    else
        isOpen="closed";
    std::cout<<"Trainer "<<trainerId<<" status: "<<isOpen<<std::endl;
    if(t->isOpen()){
        std::cout<<"Customers:"<<std::endl;
        for(Customer* c : t->getCustomers())
            std::cout<<c->getId()<<" "<<c->getName()<<std::endl;
        std::cout<<"Orders:"<<std::endl;
        for(std::pair<int, Workout> p:t->getOrders())
            std::cout<<p.second.getName()<<" "<<p.second.getPrice()<<"NIS "<<p.first<<std::endl;
    }
}
    std::string PrintTrainerStatus::toString() const{}



//PrintActionsLog
    PrintActionsLog::PrintActionsLog(){}
    void PrintActionsLog::act(Studio &studio){
    std::vector<BaseAction*> bAction= studio.getActionsLog();
    for(int i=0;i<bAction.size();i++)
        bAction[i]->toString();
}
    std::string PrintActionsLog ::toString() const{}



//BackupStudio
    BackupStudio::BackupStudio(){}
    void BackupStudio::act(Studio &studio){
        backup = new Studio(studio);

}
    std::string BackupStudio::toString() const{
}


    //RestoreStudio
    RestoreStudio::RestoreStudio(){}
    void RestoreStudio::act(Studio &studio) {
        if (backup == nullptr)
            error("No backup available");
        else
            studio = *backup; //check
    }
    std::string RestoreStudio ::toString() const{}

