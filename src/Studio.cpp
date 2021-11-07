#include "Studio.h"



    Studio::Studio(){}
    Studio::Studio(const std::string &configFilePath){}
    Studio::void start(){}
    Studio::int getNumOfTrainers() const{}
    Studio::Trainer* getTrainer(int tid){}
    Studio::const std::vector<BaseAction*>& getActionsLog() const{} // Return a reference to the history of actions
    std::vector<Workout>& Studio::getWorkoutOptions(){}



