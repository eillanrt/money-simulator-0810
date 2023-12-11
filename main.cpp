#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct Currency {
    std::string code;
    std::string name;
    double rate;
};

double convertCurrency(double amount, string fromCurrencyCode, string toCurrencyCode)
{
    vector<Currency> currencies = { 
      { "PHP", "Philippine Peso", 1.0 }, 
      { "USD", "US Dollar", 0.0199 }, 
      { "EUR", "Euro", 0.0235 }, 
      { "GBP", "British Pound", 0.0285 },
      { "JPY", "Japanese Yen", 2.2494 }, 
      { "AUD", "Australian Dollar", 0.7345 }, 
      { "CAD", "Canadian Dollar", 0.7894 } 
    };

    double fromCurrencyRate = 0, toCurrencyRate = 0;

    for (const auto& currency : currencies) {
        if (fromCurrencyRate > 0 && toCurrencyRate > 0)
            break;

        if (currency.code == fromCurrencyCode) {
            fromCurrencyRate = currency.rate;
        }

        if (currency.code == toCurrencyCode) {
            toCurrencyRate = currency.rate;
        }
    }

    return amount * (toCurrencyRate / fromCurrencyRate);
}

int main()
{
    bool convert_again = false;

    do {
        system("clear");

        cout << "----------------------------- MONEY CONVERTER ------------------------------------\n";

        string currenciesCodes[] = { "PHP", "USD", "EUR", "GBP", "JPY", "AUD", "CAD" };

        int fromCurrencyIndex, toCurrencyIndex;
        string fromCurrencyCode, toCurrencyCode;
        double amountToConvert;

        for (int i = 0; i < 7; i++) {
            cout << i << " => " << currenciesCodes[i] << "\n";
        }

        cout << "\nPICK YOUR CURRENCY => ";
        cin >> fromCurrencyIndex;

        fromCurrencyCode = currenciesCodes[fromCurrencyIndex];

        cout << "CONVERT " << fromCurrencyCode << " TO => ";
        cin >> toCurrencyIndex;

        toCurrencyCode = currenciesCodes[toCurrencyIndex];

        cout << "\nCONVERTING " << fromCurrencyCode << " to " << toCurrencyCode << "\n\n";

        cout << "AMOUNT IN " << currenciesCodes[fromCurrencyIndex] << ": ";
        cin >> amountToConvert;

        double convertedAmount = convertCurrency(amountToConvert, fromCurrencyCode, toCurrencyCode);
        cout << "\n" << amountToConvert << fromCurrencyCode << " is equivalent to " << convertedAmount << toCurrencyCode << "\n\n";

        cout << "convert another currency? 1=YES 0=EXIT\n=>";
        cin >> convert_again;
    } while (convert_again);

    exit(0);

    return 0;
}