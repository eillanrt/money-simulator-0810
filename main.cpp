#include <iostream>
#include <algorithm>

using namespace std;

class MoneySimulator {
  protected: double moneyAmount;

  private:
    bool stringExistsInArray(const std::string & str,
      const std::string arr[], size_t size) {
      return std::find(arr, arr + size, str) != arr + size;
    }

  int random(int min, int max) { //range : [min, max]

    static bool first = true;

    if (first) {
      srand(time(NULL)); //seeding for the first time only!
      first = false;
    }
    return min + rand() % ((max + 1) - min);
  }

  public: MoneySimulator(double moneyAmount) {
    this -> moneyAmount = moneyAmount;
  }

  void homeScreen() {
   clearTerminal();
   cout << "----------------------------- HOME ------------------------------------\n";
   cout << "YOUR MONEY: " << getMoney() << "\n\n";
    string activities[] = {
      "Gamble",
      "Go to bank"
    };

    int numberOfActivities = sizeof(activities) / sizeof(activities[0]);
    int activityChoice;

    bool proceedToActivity = true;

    while (proceedToActivity) {

      for (int i = 0; i < numberOfActivities; i++) {
        cout << i << " -> " << activities[i] << endl;
      }

      cout << "\nWhat would you like to do?\n\n=> ";

      cin >> activityChoice;
      proceedToActivity = activityChoice > numberOfActivities || activityChoice < 0;
    }

    switch (activityChoice) {
    case 0:
      gamble();
      break;
    }
  }

  void gamble() {
   clearTerminal();
      cout << "----------------------------- CASINO ------------------------------------\n";

    double moneyToGamble;
    cout << "You have ₱" << moneyAmount << "\n";
    cout << "Money you want to bet: ";
    cin >> moneyToGamble;

    if (moneyToGamble > moneyAmount || moneyToGamble <= 0 ) {
      cout << "\nYou don't have that much money or money is not valid.\n\nContinue? 1=yes 0=no" << endl;
      bool conti;
      cin >> conti;

      if (!conti){
         system("clear");
         homeScreen();
      } else {
         system("clear");
         gamble();
         return;
      }
    }

    string colors[] = {
      "blue",
      "green",
      "red",
      "yellow"
    };

    int howManyColors = sizeof(colors) / sizeof(colors[0]);

    bool colorChosenIsValid = true;
    string chosenColor;

    do {
      if (!colorChosenIsValid) {
         cout << "INVALID COLOR PICK AGAIN!\n\n";
      }

      cout << "\nCOLORS:  ";

      for (const string color: colors) {
        cout << color << " ";
      }

      cout << "\n\n";
      cout << "Choose a color => ";

      cin >> chosenColor;
      colorChosenIsValid = stringExistsInArray(chosenColor, colors, howManyColors);
    } while (!colorChosenIsValid);

    string randomColor = colors[random(0, 2)];

    cout << "\n\nYOUR COLOR: " << chosenColor << "\nRANDOM COLOR: " << randomColor << "\n";

    if (randomColor == chosenColor) {
      addMoney(moneyToGamble);
      cout << "\nCONGRATULATIONS YOUR WON ₱" << moneyToGamble << "\n";
    } else {
      reduceMoney(moneyToGamble);
     cout << "\nBETTER LUCK NEXT TIME!!\n\nYOU LOSE ₱" << moneyToGamble << "\n";
    }

    cout << "You have now ₱" << getMoney() << "\n\n";

    bool goHome;
    cout << "Go back to home screen?\n1=yes 0=Gamble again\n=>";
    cin >> goHome;

    if (goHome) {
      homeScreen();
    } else {
      gamble();
    }
  }

  void start() {
    cout << "Game is starting..." << endl;
    homeScreen();
  }

  void addMoney(double amount) {
    moneyAmount += amount;
  }

  void reduceMoney(double amount) {
    moneyAmount -= amount;
  }

  double getMoney() {
    return moneyAmount;
  }
  
   void clearTerminal() {
      system("clear");
    }

};

int main() {
  MoneySimulator app(100);

  app.clearTerminal();
  app.start();

  return 0;
}