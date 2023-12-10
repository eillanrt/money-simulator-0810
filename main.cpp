#include "nlohmann/json.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;

using namespace std;

struct Currency
{
  std::string code;
  std::string name;
  double rate;
};

class CurrencyConverter
{
private:
  void
  parseJsonFile (const std::string &filename, std::vector<Currency> &currencies)
  {
    std::ifstream file (filename);
    if (!file.is_open ())
      {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
      }

    json jsonData;
    file >> jsonData;

    const auto &currenciesArray = jsonData["currencies"];
    for (const auto &currencyJson : currenciesArray)
      {
        Currency currency;
        currency.code = currencyJson["code"];
        currency.name = currencyJson["name"];
        currency.rate = currencyJson["rate"];
        currencies.push_back (currency);
      }
  }
  double
  convertCurrency (double amount, const Currency &fromCurrency,
                   const Currency &toCurrency)
  {

    return amount * (toCurrency.rate / fromCurrency.rate);
  }

public:
  double
  convert (double amountToConvert, int fromCurrencyOrder, int toCurrencyOrder)
  {
    std::vector<Currency> currencies;
    parseJsonFile ("currencies.json", currencies);

    Currency fromCurrency, toCurrency;

    fromCurrency
        = currencies[fromCurrencyOrder]; // Assuming the first currency is PHP
    toCurrency
        = currencies[toCurrencyOrder]; // Assuming the second currency is USD

    double convertedAmount
        = convertCurrency (amountToConvert, fromCurrency, toCurrency);

    return convertedAmount;
  }
};

class MoneySimulator
{
private:
  double moneyAmount;

  CurrencyConverter currencyConverter;
  bool
  stringExistsInArray (const std::string &str, const std::string arr[],
                       size_t size)
  {
    return std::find (arr, arr + size, str) != arr + size;
  }

  int
  random (int min, int max)
  { // range : [min, max]

    static bool first = true;

    if (first)
      {
        srand (time (NULL)); // seeding for the first time only!
        first = false;
      }
    return min + rand () % ((max + 1) - min);
  }

public:
  MoneySimulator (double moneyAmount) { this->moneyAmount = moneyAmount; }

  void
  homeScreen ()
  {
    clearTerminal ();
    cout << "----------------------------- HOME "
            "------------------------------------\n";
    cout << "YOUR MONEY: " << getMoney () << "\n\n";
    string activities[] = { "Gamble", "Visit money converter" };

    int numberOfActivities = sizeof (activities) / sizeof (activities[0]);
    int activityChoice;

    bool proceedToActivity = true;

    while (proceedToActivity)
      {

        for (int i = 0; i < numberOfActivities; i++)
          {
            cout << i << " -> " << activities[i] << endl;
          }

        cout << "\nWhat would you like to do?\n\n=> ";

        cin >> activityChoice;
        proceedToActivity
            = activityChoice > numberOfActivities || activityChoice < 0;
      }

    switch (activityChoice)
      {
      case 0:
        gamble ();
        break;
      case 1:
        moneyConverter ();
        break;
      }
  }

  void
  gamble ()
  {
    clearTerminal ();
    cout << "----------------------------- CASINO "
            "------------------------------------\n";

    double moneyToGamble;
    cout << "You have ₱" << moneyAmount << "\n";
    cout << "Money you want to bet: ";
    cin >> moneyToGamble;

    if (moneyToGamble > moneyAmount || moneyToGamble <= 0)
      {
        cout << "\nYou don't have that much money or money is not "
                "valid.\n\nContinue? 1=yes 0=no"
             << endl;
        bool conti;
        cin >> conti;

        if (conti)
          {
            system ("clear");
            gamble ();
          }
        else
          {
            system ("clear");
            homeScreen ();
          }

        return;
      }

    string colors[] = { "blue", "green", "red", "yellow" };

    int howManyColors = 4;

    bool colorChosenIsValid = true;
    string chosenColor;

    do
      {
        if (!colorChosenIsValid)
          {
            cout << "INVALID COLOR PICK AGAIN!\n\n";
          }

        cout << "\nCOLORS:  ";

        for (const string color : colors)
          {
            cout << color << " ";
          }

        cout << "\n\n";
        cout << "Choose a color => ";

        cin >> chosenColor;
        colorChosenIsValid
            = stringExistsInArray(chosenColor, colors, 4);
      }
    while (!colorChosenIsValid);

    string randomColor = colors[random (0, howManyColors)];

    cout << "\n\nYOUR COLOR: " << chosenColor
         << "\nRANDOM COLOR: " << randomColor << "\n";

    if (randomColor == chosenColor)
      {
        addMoney (moneyToGamble);
        cout << "\nCONGRATULATIONS YOUR WON ₱" << moneyToGamble << "\n";
      }
    else
      {
        reduceMoney (moneyToGamble);
        cout << "\nBETTER LUCK NEXT TIME!!\n\nYOU LOSE ₱" << moneyToGamble
             << "\n";
      }

    cout << "You have now ₱" << getMoney () << "\n\n";

    bool goHome;
    cout << "Go back to home screen?\n1=yes 0=Gamble again\n=>";
    cin >> goHome;

    if (goHome)
      {
        homeScreen ();
      }
    else
      {
        gamble ();
      }
  }

  void
  moneyConverter ()
  {
    clearTerminal ();
    cout << "----------------------------- MONEY CONVERTER "
            "------------------------------------\n";

    string currenciesCodes[]
        = { "PHP", "USD", "EUR", "GBP", "JPY", "AUD", "CAD" };

    int fromCurrency, toCurrency;
    double amountToConvert;

    for (int i = 0; i < 7; i++)
      {
        cout << i << " => " << currenciesCodes[i] << "\n";
      }

    cout << "\nPICK YOUR CURRENCY => ";
    cin >> fromCurrency;

    string fromCurrencyCode = currenciesCodes[fromCurrency];

    cout << "CONVERT " << fromCurrencyCode << " TO => ";
    cin >> toCurrency;

    string toCurrencyCode = currenciesCodes[toCurrency];

    cout << "AMOUNT IN " << currenciesCodes[fromCurrency] << ": ";
    cin >> amountToConvert;

    double convertedAmount
        = currencyConverter.convert (amountToConvert, fromCurrency, toCurrency);
    cout << "\n"
         << amountToConvert << fromCurrencyCode << " is equivalent to "
         << convertedAmount << toCurrencyCode << "\n\n";

    bool goHome;
    cout << "Go back to home screen?\n1=yes 0=Convert other currency\n=>";
    cin >> goHome;
    
    if (goHome) {
       homeScreen();
    } else {
       moneyConverter();
    }
  }

  void
  start ()
  {
    cout << "----------------WELCOME TO MONEY SIMULATOR...-------------\nPress ANY KEY to continue\n";
    string key;
    cin >> key;
    cout << "\nThis is an unfinished project (for a practical exam) which I no longer have any plans for continuing...\nPress ANY KEY to continue\n";
    cin >> key;
    cout << "\nPress any key to start\n";
    cin >> key;
    homeScreen ();
  }

  void
  addMoney (double amount)
  {
    moneyAmount += amount;
  }

  void
  reduceMoney (double amount)
  {
    moneyAmount -= amount;
  }

  double
  getMoney ()
  {
    return moneyAmount;
  }

  void
  clearTerminal ()
  {
    system ("clear");
  }
};

int
main ()
{
  MoneySimulator app (100);

  app.clearTerminal ();
  app.start ();

  return 0;
}