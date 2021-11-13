#include "Studio.h"

#include "sstream"

Studio::Studio(){}
Studio::Studio(const std::string &configFilePath) {

    std::vector<std::string> elems;
    std::stringstream ss(configFilePath);
    std::string item;

    while (std::getline(ss, item, '\n')) {
        elems.push_back(item);
    }

    size_t pos = 0;
    std::string token;
    while ((pos = elems[4].find(',')) != std::string::npos) {
        token = elems[4].substr(0, pos);
        trainers.push_back(new Trainer(std::stoi(token)));
        elems[4].erase(0, pos + 1);
    }
    trainers.push_back(new Trainer(std::stoi(elems[4])));
    for (int i = 7; i < elems.size(); i++) {
        size_t pos = 0;
        std::string token;
        while ((pos = elems[i].find(", ")) != std::string::npos) {
            std::vector<std::string> wElems;
            for (int j = 0; j < 3; j++) {
                token = elems[i].substr(0, pos);
                wElems.push_back(token);
                elems[i].erase(0, pos + 2);
            }
            
            WorkoutType wt;
            if (wElems[1] == "Anaerobic")
                wt = ANAEROBIC;
            else if (wElems[1] == "Cardio")
                wt = CARDIO;
            else
                wt = MIXED;
            workout_options.push_back(Workout(i - 7, wElems[0], std::stoi(wElems[2]), wt));
        }
    }
}

void Studio::start(){
    int costumer_ID = 0;
    std::cout<<"Studio is now open"<<std::endl;
    std::string action_input;
    while(open)
    {
        std::cin >>  action_input;
        std::vector<std::string> actions_v;
        std::string word = "";
        int j=0;
        while(j<action_input.size())
        {
            word = "";
            while(action_input[j]!=' ' || action_input[j]!=',')
            {
                word = word +action_input[j];
                j++;
            }
            j++;
            actions_v.push_back(word);
        }
        std::string action=actions_v[0];
        if(action == "open")
        {
            std::vector<Customer *> customersList;
            for(int i=2;i<actions_v.size();i+=2)
            {
                if(actions_v[i+1] == "swt"){
                    SweatyCustomer *s = new SweatyCustomer(actions_v[i],costumer_ID);
                    customersList.push_back(s);
                }
                if(actions_v[i+1] == "chp"){
                    CheapCustomer *s = new CheapCustomer(actions_v[i],costumer_ID);
                    customersList.push_back(s);
                }
                if(actions_v[i+1] == "mcl"){
                    HeavyMuscleCustomer *s = new HeavyMuscleCustomer(actions_v[i],costumer_ID);
                    customersList.push_back(s);
                }
                if(actions_v[i+1] == "fbd"){
                    FullBodyCustomer *s = new  FullBodyCustomer(actions_v[i],costumer_ID);
                    customersList.push_back(s);
                }
                costumer_ID++;
            }
            OpenTrainer *openT = new OpenTrainer(std::stoi(actions_v[1]),customersList);
            openT->act(*this);
            actionsLog.push_back(openT);
        }
        if(action == "order"){
            int id = std::stoi(actions_v[1]);
            Order *order= new Order(id);
            order->act(*this); // print from here
            //print in trainer
            actionsLog.push_back(order);
        }
        if(action == "move"){
            int src = std::stoi(actions_v[1]);
            int dst = std::stoi(actions_v[2]);
            int id = std::stoi(actions_v[3]);
            MoveCustomer *move = new MoveCustomer(src,dst,id);
            move->act(*this);
            actionsLog.push_back(move);
        }
        if(action == "close"){
            int id = std::stoi(actions_v[1]);
            Close *c = new Close(id);
            c->act(*this);
            actionsLog.push_back(c);
        }
        if(action == "workout_options"){
            PrintWorkoutOptions *printW = new PrintWorkoutOptions();
            printW->act(*this);
            actionsLog.push_back(printW);
        }
        if(action == "status"){
            int id = std::stoi(actions_v[1]);
            PrintTrainerStatus *printS = new PrintTrainerStatus(id);
            printS->act(*this);
            actionsLog.push_back(printS);
        }
        if(action == "log"){
            PrintActionsLog *printL = new PrintActionsLog();
            printL ->act(*this);
            actionsLog.push_back(printL );
        }
        if(action == "backup"){
            BackupStudio *backup = new BackupStudio();
            backup->act(*this);
            actionsLog.push_back(backup);
        }
        if(action == "restore"){
            RestoreStudio *restore = new RestoreStudio();
            restore->act(*this);
            actionsLog.push_back(restore);
        }
        if(action == "closeall"){
            CloseAll *close = new CloseAll();
            close->act(*this);
            open = false;
            actionsLog.push_back(close);
        }
    }
}
int Studio::getNumOfTrainers() const{return trainers.size();}
Trainer* Studio::getTrainer(int tid){return trainers[tid];}
const std::vector<BaseAction*>& Studio::getActionsLog() const{return actionsLog;} // Return a reference to the history of actions
std::vector<Workout>& Studio::getWorkoutOptions(){return workout_options;}



