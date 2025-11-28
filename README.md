# 💳 C++ ATM Console Application

A simple **ATM system built using C++** that allows users to log in,
withdraw money, deposit money, and check their account balance.\
All client data is stored in a text file to simulate real banking
operations.

------------------------------------------------------------------------

## 🚀 Features

-   ✅ Secure Login using:
    -   Account Number
    -   PIN Code
-   💸 Quick Withdraw (preset amounts)
-   ✍️ Normal Withdraw (custom amount)
-   💰 Deposit Money
-   📊 Check Account Balance
-   💾 File-based data storage (`Clients.txt`)
-   🔄 Automatic balance updating after each transaction

------------------------------------------------------------------------

## 🧠 How It Works

-   Client data is stored in a text file.
-   Each client record is loaded into memory.
-   Transactions update the balance and save changes back to the file.
-   The session continues until the user logs out.

------------------------------------------------------------------------

## 📁 File Structure

    /ATM-Project
    │
    ├── main.cpp
    ├── Clients.txt
    └── README.md

------------------------------------------------------------------------

## 📝 Clients.txt Format

Each client is stored as a single line using this format:

    AccountNumber|PINCode|Name|Phone|Balance

### ✅ Example:

    1001|1234|Ahmed Ali|0599123456|2500
    1002|4321|Sarah Omar|0599876543|1800

⚠️ **Important:**\
Do NOT leave empty spaces around the `|` symbol.

------------------------------------------------------------------------

## 🛠️ How to Compile & Run

### ✅ Using g++:

``` bash
g++ -o atm main.cpp
./atm
```

### ✅ On Windows (MinGW):

``` bash
g++ main.cpp -o atm.exe
atm.exe
```

------------------------------------------------------------------------

## 🖥️ ATM Main Menu

    [1] Quick Withdraw
    [2] Normal Withdraw
    [3] Deposit
    [4] Check Balance
    [5] Logout

------------------------------------------------------------------------

## 📌 Technologies Used

-   C++
-   Standard Library:
    -   `<iostream>`
    -   `<fstream>`
    -   `<vector>`
    -   `<string>`
    -   `<iomanip>`
    -   `<limits>`
    -   `<cctype>`

------------------------------------------------------------------------

## ⚠️ System Notes

This project uses:

``` cpp
system("cls");
```

✅ Works on **Windows only**\
❌ On Linux / macOS use:

``` cpp
system("clear");
```

------------------------------------------------------------------------

## 🔐 Security Notes

-   PIN Codes are stored as plain text (for learning purposes).
-   No encryption is applied.
-   Suitable for **educational use only**.

------------------------------------------------------------------------

## 📄 License

This project is open for **educational and personal use**.\
You are free to modify and improve it.

------------------------------------------------------------------------

## ✨ Author

Developed using ❤️ in C++ for learning: - File Handling - Console
Applications - Basic Banking Logic

------------------------------------------------------------------------

## 🔮 Future Improvements (Optional)

-   🔒 Encrypt PIN codes
-   🧾 Transaction history
-   🗂 Admin panel
-   🖥 GUI version using Qt
-   🌐 Database instead of text file
