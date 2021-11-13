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
      std::cout<<"Studio is now open"<<std::endl;
      std::string action_input;
      while(open)
      {
          std::cin >>  action_input;
          std::vector<std::string> action;
          std::string word = "";
          int j=0;
          while(j<action_input.size())
          {
              word = "";
              int i=0;
              while(action_input[i]!=' ')
              {
                  i++;
                  word = word +action_input[i];
              }
              j++;
              action.push_back(word);
          }

          std::string action="";
          int i=0;
          while(action_input[i]!=' ' && i<action_input.size()){
              action = action + action_input[i];
          }
          if(action == "open")
          {}
          if(action == "order"){
              //
             int id = std::stoi(action);
              Order order(id);
              order.act(*this);
              order.toString();

          }
          if(action == "move"){}
          if(action == "close"){}
          if(action == "workout_options"){}
          if(action == "status"){}
          if(action == "log"){}
          if(action == "backup"){}
          if(action == "restore"){}
          if(action == "closeall"){}
      }


}
    int Studio::getNumOfTrainers() const{return trainers.size();}
    Trainer* Studio::getTrainer(int tid){return trainers[tid];}
    const std::vector<BaseAction*>& Studio::getActionsLog() const{return actionsLog;} // Return a reference to the history of actions
    std::vector<Workout>& Studio::getWorkoutOptions(){return workout_options;}



