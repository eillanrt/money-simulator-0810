#include <iostream>
using namespace std;

class Item {
    private: 
      double price;

};

class MoneySimulator {
    protected:
      double moneyAmount;

   public:
     MoneySimulator(double moneyAmount) {
       this->moneyAmount = moneyAmount;
    }

    void homeScreen() {
       string activities[] = {"Gamble", "Go to bank"};
       int numberOfActivities = sizeof(activities)/sizeof(activities[0]);
       int activityChoice;

       bool proceedToActivity = true;

       while (proceedToActivity) {
          cout << "What would you like to do? \n PICK A NUMBER\n\n";
       
       for (int i = 0; i < numberOfActivities; i++) {
         cout << i << " -> " << activities[i] << endl;
       }

         cin >> activityChoice;
         proceedToActivity = activityChoice > numberOfActivities || activityChoice < 0;
       }

       switch (activityChoice) {
        case 0:
          gamble();
       }
    }

     void gamble() {
         // implement gamble
     }

     void start() {
         cout << "Game is starting..." << endl;
         homeScreen();
     }

     void addMoney(double amount){
        moneyAmount += amount;
     }

      void reduceMoney(double amount){
        moneyAmount -= amount;
     }

     double getMoney() { return moneyAmount; }
};

int main() {
   MoneySimulator app(100);
   app.start();

    return 0;
}