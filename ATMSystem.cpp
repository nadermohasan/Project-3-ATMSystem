#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
using namespace std;

void MainMenu();
void PressAnyKey();
const string filename = "Clients.txt";
enum enMainMenu {
    enQuickWithdraw = 1, enNormalWithdraw, enDeposit, enCheckBalance
};
struct sClients {
    string AccountNumber, PINCode, Name, Phone;
    double AccountBalance = 0.0; // Changed to double for better precision
    bool MarkForDelete = false;
};
sClients CurrentClient;
vector<string> Split(string text, string delim = "|") {
    vector<string> vString;
    size_t pos = 0;
    string word;
    while ((pos = text.find(delim)) != string::npos) {
        word = text.substr(0, pos);
        vString.push_back(word);
        text.erase(0, pos + delim.length());
    }
    if (!text.empty())
        vString.push_back(text);
    return vString;
}
sClients ConvertLineToRecord(const string& Line) {
    vector<string> vString = Split(Line);
    sClients Client;
    if (vString.size() == 5) {
        Client.AccountNumber = vString[0];
        Client.PINCode = vString[1];
        Client.Name = vString[2];
        Client.Phone = vString[3];
        Client.AccountBalance = stod(vString[4]);
    }
    return Client;
}
string ConvertRecordToLine(sClients &Client, string delim = "|") {
    string Line = "";
    Line += Client.AccountNumber + delim;
    Line += Client.PINCode + delim;
    Line += Client.Name + delim;
    Line += Client.Phone + delim;
    Line += to_string(Client.AccountBalance);
    Line += "\n";
    return Line;
}
vector<sClients> LoadClientsFromFile(string filename) {
    vector<sClients> vClients;
    sClients Client;
    fstream File;
    string Line = "";
    File.open(filename, ios::in);
    if (File.is_open()) {
        while (getline(File, Line)) {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }
    }
    return vClients;
}
void SaveAsFile(string filename, vector<sClients>& vClients){
    fstream File;
    File.open(filename, ios::out);
    if (File.is_open()) {
        for (sClients& C : vClients) {
            File << ConvertRecordToLine(C);
        }
    }
    File.close();
}
bool FindClientByAccountNumber(string filename, string AccountNumber, string PINCode, sClients& Client) {
    vector<sClients> vClients = LoadClientsFromFile(filename);
    for (sClients& C : vClients) {
        if (C.AccountNumber == AccountNumber && C.PINCode == PINCode) {
            Client = C;
            return true;
        }
    }
    return false;
}
void CurrentClientData() {
    cout << "Name: " << CurrentClient.Name << endl;
    cout << "Account Number: " << CurrentClient.AccountNumber << endl;
    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;
}
bool Withdraw(string AccountNumber, int Amount) {
    // Load all clients from the file
    vector<sClients> vClients = LoadClientsFromFile(filename);

    // Find the specific client to update
    for (sClients& C : vClients) {
        if (C.AccountNumber == CurrentClient.AccountNumber) {
            // Check if the client has enough balance
            if (C.AccountBalance >= Amount) {
                C.AccountBalance -= Amount;
                CurrentClient = C;
                cout << "Withdrawal successful. New balance is: " << C.AccountBalance << endl;
            }
            else {
                cout << "Withdrawal failed. Insufficient balance." << endl;
                return false;
            }
        }
    }
    SaveAsFile(filename, vClients);
    return true;
}
bool Deposit(string AccountNumber, int Amount) {
    vector<sClients> vClients = LoadClientsFromFile(filename);
    for (sClients& C : vClients) {
        if (C.AccountNumber == CurrentClient.AccountNumber) {
            if (Amount > 0) {
                C.AccountBalance += Amount;
                CurrentClient = C;
            }
            else {
                cout << "Invalid Amount Value!";
                return false;
            }
        }
    }
    SaveAsFile(filename, vClients);
    return true;
}
void QuickWithdraw() {
    int AmountIndex = 1;
    cout << "===================================================\n";
    cout << setw(40) << "Quick Withdraw Menu Screen\n";
    cout << "===================================================\n";
    int QuickAmounts[] = { 0, 100, 150, 200, 250, 300, 350, 400, 1000 };
    for (int i = 1; i < 9; i++) {
        cout << setw(15) << "[" << i << "] " << QuickAmounts[i];
        if (i % 2 == 0) {
            cout << endl;
        }
    }
    cout << "===================================================\n";
    CurrentClientData();
    cout << "Enter Amount: ";
    cin >> AmountIndex;
    Withdraw(CurrentClient.AccountNumber, QuickAmounts[AmountIndex]);
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
}
void NormalWithdraw() {
    int Amount;
    char Answer;
    bool WithdrawState = true;
    cout << "===================================================\n";
    cout << setw(40) << "Normal Withdraw Menu Screen\n";
    cout << "===================================================\n";
    CurrentClientData();
    do {
        cout << "Enter an Amount: ";
        cin >> Amount;
        cout << "Are you sure you want to perform this action ? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            WithdrawState = Withdraw(CurrentClient.AccountNumber, Amount);
        }
    } while (!WithdrawState);
}
void QuickDeposit() {
    int Amount;
    char Answer;
    bool DepositState = true;
    cout << "===================================================\n";
    cout << setw(40) << "Deposit Menu Screen\n";
    cout << "===================================================\n";
    CurrentClientData();
    do {
        cout << "\nEnter a Deposit Amount: ";
        cin >> Amount;
        cout << "Are you sure you want to perform this action ? y/n? ";
        cin >> Answer;
        if (toupper(Answer) == 'Y') {
            DepositState = Deposit(CurrentClient.AccountNumber, Amount);
        }
        if (DepositState)
            cout << "Amount Added Successfully!" << " New balance is: " << CurrentClient.AccountBalance;
        else
            cout << "Something went wrong!";
    } while (!DepositState);
}
void CheckBalance() {
    cout << "===================================================\n";
    cout << setw(40) << "Check Balance Screen\n";
    cout << "===================================================\n";
    cout << "Your Balance is " << CurrentClient.AccountBalance;
}
bool Login() {
    string AccountNumber, PINCode;
    cout << "===================================================\n";
    cout << setw(30) << "Login Screen\n";
    cout << "===================================================\n";
    do {
        cout << "Enter Account Number: ";
        cin >> AccountNumber;
        cout << "Enter PINCode: ";
        cin >> PINCode;
        if (FindClientByAccountNumber(filename, AccountNumber, PINCode, CurrentClient)) {
            return true;
        }
        else {
            cout << "Invalid Account Number or PINCode!" << endl;
        }
    } while (!FindClientByAccountNumber(filename, AccountNumber, PINCode, CurrentClient));
    return false;
}
void HandleMainMenueOptions(enMainMenu Choice) {
    switch (Choice) {
    case enMainMenu::enQuickWithdraw:
        system("cls");
        QuickWithdraw();
        break;
    case enMainMenu::enNormalWithdraw:
        system("cls");
        NormalWithdraw();
        break;
    case enMainMenu::enDeposit:
        system("cls");
        QuickDeposit();
        break;
    case enMainMenu::enCheckBalance:
        system("cls");
        CheckBalance();
        break;
    }
}
void PressAnyKey() {
    cout << "\nPress Enter to go back to the Menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
    MainMenu();
}
void MainMenu() {
        int Answer;
        cout << "===================================================\n";
        cout << setw(30) << "ATM Main Menu Screen\n";
        cout << "===================================================\n";
        cout << setw(15) << "[1] " << "Quick Withdraw.\n";
        cout << setw(15) << "[2] " << "Normal Withdraw.\n";
        cout << setw(15) << "[3] " << "Deposit.\n";
        cout << setw(15) << "[4] " << "Check Balance.\n";
        cout << setw(15) << "[5] " << "Logout.\n";
        cout << "===================================================\n";
        cout << "Choose what you want to do? [1 to 5]? ";
        cin >> Answer;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear input buffer
        if (Answer < 1 || Answer > 5) {
            cout << "\nInvalid choice. Please enter a number between 1 and 5.\n";
            MainMenu();
        }
        else {
            HandleMainMenueOptions(static_cast<enMainMenu>(Answer));
        }
}
void Start() {
    if (Login()) {
        system("cls");
        MainMenu();
    }
}
int main()
{
    Start();
}