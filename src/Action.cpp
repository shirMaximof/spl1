#include "Action.h"
#include "Trainer.h"
#include "Studio.h"
#include <iostream>
extern Studio *backup;

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
    std::string costumers_s="";
    for(int i=0;i=customers.size();i++)
        costumers_s = costumers_s+" "+customers[i]->toString();
    std::string ans= "open " + std::to_string(trainerId) + " "+ costumers_s+" ";
        if(getStatus()==ERROR){
            ans+=getErrorMsg();
        }
        else{
            ans+= "Completed";
        }
        return ans;
} //continue



//Order

    Order::Order(int id):trainerId(id){}
    void Order::act(Studio &studio) {
        Trainer *t = studio.getTrainer(trainerId);
        if (t == nullptr | !t->isOpen())
            error("\"Trainer does not exist or is not open\"");
        else
            for (Customer *c: t->getCustomers()) {
                t->order(c->getId(), c->order(studio.getWorkoutOptions()), studio.getWorkoutOptions());
            }
    }

    std::string Order::toString() const{
    std::string ans= "order "+std::to_string(trainerId)+" ";
        if(getStatus()==ERROR){
            ans+=getErrorMsg();
        }
        else{
            ans+= "Completed";
        }
        return ans;
} // continue


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
    std::string MoveCustomer::toString() const{
    std::string ans= "move "+std::to_string(srcTrainer)+" "+std::to_string(dstTrainer)+" "+std::to_string(id)+" ";
    if(getStatus()==ERROR){
        ans+=getErrorMsg();
    }
    else{
        ans+= "Completed";
    }
        return ans;
}

//Close

    Close::Close(int id):trainerId(id){
}
   void  Close::act(Studio &studio){
    Trainer* t=studio.getTrainer(trainerId);
    int salary=t->getSalary();
    t->closeTrainer();
    std::cout<<"Trainer "<<trainerId<<" is closed. Salary "<<salary<<"NIS"<<std::endl;
}
    std::string  Close::toString() const{
        std::string ans= "close "+std::to_string(trainerId);
        if(getStatus()==ERROR){
            ans+=getErrorMsg();
        }
        else{
            ans+= "Completed";
        }
        return ans;
}


// CloseAll
    CloseAll::CloseAll(){}
    void CloseAll::act(Studio &studio){
        for (int id = 0; id < studio.getNumOfTrainers(); id++) {
            Trainer* t=studio.getTrainer(id);
            if(t->isOpen())
                Close(id).act(studio);
        }
}
    std::string  CloseAll::toString() const{
        std::string ans= "closeAll ";
        if(getStatus()==ERROR){
            ans+=getErrorMsg();
        }
        else{
            ans+= "Completed";
        }
        return ans;
}


//PrintWorkoutOptions

    PrintWorkoutOptions::PrintWorkoutOptions(){}
    void PrintWorkoutOptions::act(Studio &studio){
    for(Workout w : studio.getWorkoutOptions())
        std::cout<<w.getName()<<", "<<w.getType()<<", "<<w.getPrice()<<std::endl;
}
    std::string PrintWorkoutOptions::toString() const{
        std::string ans= "PrintWorkoutOptions ";
        if(getStatus()==ERROR){
            ans+=getErrorMsg();
        }
        else{
            ans+= "Completed";
        }
        return ans;
}



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
    std::string PrintTrainerStatus::toString() const{
        std::string ans= "PrintTrainerStatus "+std::to_string(trainerId)+" ";
        if(getStatus()==ERROR){
            ans+=getErrorMsg();
        }
        else{
            ans+= "Completed";
        }
        return ans;
}



//PrintActionsLog
    PrintActionsLog::PrintActionsLog(){}
    void PrintActionsLog::act(Studio &studio){
    std::vector<BaseAction*> bAction= studio.getActionsLog();
    for(int i=0;i<bAction.size();i++)
        bAction[i]->toString();
}
    std::string PrintActionsLog ::toString() const{
    std::string ans="log ";
        if(getStatus()==ERROR){
            ans+=getErrorMsg();
        }
        else{
            ans+= "Completed";
        }
        return ans;
}



//BackupStudio
    BackupStudio::BackupStudio(){}
    void BackupStudio::act(Studio &studio){
        backup = new Studio(studio);

}
    std::string BackupStudio::toString() const{
        std::string ans= "BackupStudio ";
        if(getStatus()==ERROR){
            ans+=getErrorMsg();
        }
        else{
            ans+= "Completed";
        }
        return ans;
}


    //RestoreStudio
    RestoreStudio::RestoreStudio(){}
    void RestoreStudio::act(Studio &studio) {
        if (backup == nullptr)
            error("No backup available");
        else
            studio = *backup; //check
    }
    std::string RestoreStudio ::toString() const{
        std::string ans= "RestoreStudio ";
        if(getStatus()==ERROR){
            ans+=getErrorMsg();
        }
        else{
            ans+= "Completed";
        }
        return ans;
}

