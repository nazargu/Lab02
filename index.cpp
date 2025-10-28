#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <limits>
using namespace std;

struct UserInput
{
    double n;
    double step;
    double min;
    double max;
};

UserInput userComunication()
{
    UserInput input;
    bool nIsOk = false, minIsOk = false, maxIsOk = false, stepIsOk = false;

    while (!nIsOk)
    {
        cout << "Input n > 6, n: ";
        cin >> input.n;
        if (cin.fail()) {
            cout << "[ERROR] Please enter a number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (floor(input.n) != input.n) {
            cout << "[ERROR] Please enter an integer number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (input.n <= 6) {
            cout << "[ERROR] n should be bigger than 6" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else {
            nIsOk = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (!stepIsOk)
    {
        cout << "Input x step: ";
        cin >> input.step;
        if (cin.fail()) {
            cout << "[ERROR] Please enter a number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (input.step == 0) {
            cout << "[ERROR] Step can't be 0" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (input.step < 0)
        {
            cout << "[INFO] As step less than 0, second limit should be smaller than first" << endl;
            stepIsOk = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            stepIsOk = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (!minIsOk)
    {
        cout << "Input first x limit: ";
        cin >> input.min;
        if (cin.fail()) {
            cout << "[ERROR] Please enter a number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (floor(input.min) != input.min)
        {
            cout << "[ERROR] Please enter an integer number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else {
            minIsOk = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (!maxIsOk)
    {
        cout << "Input second x limit: ";
        cin >> input.max;
        if (cin.fail()) {
            cout << "[ERROR] Please enter a number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (floor(input.max) != input.max)
        {
            cout << "[ERROR] Please enter an integer number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (input.step > 0 and input.min >= input.max) {
            cout << "[ERROR] As step > 0, second limit must be bigger than first!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else if (input.step < 0 and input.min <= input.max) {
            cout << "[ERROR] As step < 0, second limit must be smaller than first!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else {
            maxIsOk = true;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return input;
}

bool checkPassword(const string &password)
{
    ifstream file("password.txt");

    string storedPassword;
    getline(file, storedPassword);
    file.close();

    if (password == storedPassword)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void getHistory()
{
    ifstream file("history.txt");

    string line;

    system("clear");
    cout << "#================History===============#" << endl;
    cout << "|       History of all calculation     |" << endl;
    cout << "#======================================#" << endl;

    while (getline(file, line))
    {
        cout << "=> ";
        cout << line << endl;
    }

    file.close();
}

void writeNewHistory(const string &newRecord)
{
    ofstream file("history.txt", ios::app);

    file << newRecord << "\n";
    file.close();
}

void calculatResult(int n, double step, int min, int max)
{
    string answers;
    int i = 1;
    system("clear");
    cout << "#================Results===============#" << endl;
    for (double x = min; (step > 0 ? x <= max : x >= max); x += step)
    {
        double y;
        if (x >= 1)
        {
            double sum = 0;
            for (int j = 2; j < (n - 4); j++)
            {
                double mlt = 1;
                for (int i = 0; i < n; i++)
                {
                    mlt *= (x - (i * j / (i + j) - 7));
                }
                sum += mlt;
            }
            y = sum;
        }
        else
        {
            double mlt = 1;
            for (int i = 2; i < (n - 3); i++)
            {
                mlt *= ((pow(x, 2) + 2 * x) / i);
            }
            y = mlt;
        }

        cout << fixed << setprecision(2);
        cout << "| Answer " << i << endl;
        cout << "| x=" << x << endl;
        cout << "| y=" << y << endl;
        cout << "|" << endl;

        i++;
        answers += "(" + to_string(x) + ", " + to_string(y) + ") ";
    }

    string historyLine = "n: " + to_string(n) + ", x_step: " + to_string(step) + ", min_x: " + to_string(min) + ", max_x: " + to_string(max) + ". Answers: " + answers;

    writeNewHistory(historyLine);
}

int main()
{
    int m;
    int a;
    string userPassword;

    cout << "#=================Lab 2================#" << endl;
    cout << "|             Hello in Lab 2           |" << endl;
    cout << "| Here you can calculate your equation |" << endl;
    cout << "|        Choose action from menu       |" << endl;

    while (true)
    {
        cout << "#=================Menu=================#" << endl;
        cout << "[1] View all results" << endl;
        cout << "[2] Use program" << endl;
        cout << "[3] Exit" << endl;
        cout << "#======================================#" << endl;
        cin >> m;

        if (cin.fail())
        {
            cout << "[ERROR] Please enter a number!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (m) 
        {
        case 1:
            system("clear");
            cout << "Enter admin password: ";
            cin >> userPassword;
           

            if (checkPassword(userPassword)) {
                bool inAdminMenu = true;
                cout << "Access granted!" << endl;

                while (inAdminMenu) {

                    cout << "#===========Admin menu=================#" << endl;
                    cout << "[1] View history" << endl;
                    cout << "[2] To main menu" << endl;
                    cout << "#======================================#" << endl;
                    cin >> a;

                    if (cin.fail())
                    {
                        cout << "[ERROR] Please enter a number!" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    switch (a)
                    {
                    case 1:
                        getHistory();
                        break;
                    case 2:
                        system("clear");
                        cout << "Main menu: " << endl;
                        inAdminMenu = false;
                        break;
                    default:
                        cout << "You entered incorrect menu number!" << endl;
                    }
                }
            }
            else
            {
                cout << "Access denied! Wrong password!" << endl;
            }
            break;
        case 2:
        {
            system("clear");
            UserInput ui = userComunication();
            calculatResult(ui.n, ui.step, ui.min, ui.max);
            break;
        }
        case 3:
            cout << "Goodbye!" << endl;
            return 0;
        default:
            cout << "You entered incorrect menu number!" << endl;
        }
    }
}

// changes for git test
//test test test