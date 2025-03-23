#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Person;
class Skuf;
class MilkHunter;
class Altushka;
class Extended;

class Person
{
protected:
    string name;
    string surname;
    char sex;
    string date;
    string sign;

    int calculateAge(string birthDate)
    {
        int day, month, year;
        sscanf(birthDate.c_str(), "%d.%d.%d", &day, &month, &year);
        int age = 2024 - year - 1;
        if (month < 1 || (month == 1 && day <= 1))
            age++;
        return age;
    }

    string determineSign(string birthDate)
    {
        int day, month;
        sscanf(birthDate.c_str(), "%d.%d", &day, &month);

        if ((month == 3 && day >= 21) || (month == 4 && day <= 20))
            return "Овен";
        if ((month == 4 && day >= 21) || (month == 5 && day <= 21))
            return "Телец";
        if ((month == 5 && day >= 22) || (month == 6 && day <= 21))
            return "Близнецы";
        if ((month == 6 && day >= 22) || (month == 7 && day <= 22))
            return "Рак";
        if ((month == 7 && day >= 23) || (month == 8 && day <= 21))
            return "Лев";
        if ((month == 8 && day >= 22) || (month == 9 && day <= 23))
            return "Дева";
        if ((month == 9 && day >= 24) || (month == 10 && day <= 23))
            return "Весы";
        if ((month == 10 && day >= 24) || (month == 11 && day <= 22))
            return "Скорпион";
        if ((month == 11 && day >= 23) || (month == 12 && day <= 22))
            return "Стрелец";
        if ((month == 12 && day >= 23) || (month == 1 && day <= 20))
            return "Козерог";
        if ((month == 1 && day >= 21) || (month == 2 && day <= 19))
            return "Водолей";
        if ((month == 2 && day >= 20) || (month == 3 && day <= 20))
            return "Рыбы";
        return "Unknown";
    }

public:
    Person(string s, string n, char sx, string d) : surname(s), name(n), sex(sx), date(d)
    {
        sign = determineSign(d);
    }

    int compareDate(string date2)
    {
        int day1, month1, year1;
        int day2, month2, year2;
        sscanf(date.c_str(), "%d.%d.%d", &day1, &month1, &year1);
        sscanf(date2.c_str(), "%d.%d.%d", &day2, &month2, &year2);
        if (year1 != year2)
            return year1 - year2;
        if (month1 != month2)
            return month1 - month2;
        return day1 - day2;
    }
    virtual void find() = 0;
    virtual void goAway() = 0;
    string get_name() { return name; }
    string get_surname() { return surname; }
    string get_date() { return date; }
    string get_sign() { return sign; }
    char get_sex() { return sex; }
    int get_age() { return calculateAge(date); }
};

Person *peoples[10];

class Skuf : public Person
{
public:
    Skuf(string s, string n, char sx, string d) : Person(s, n, sx, d) {}
    void find() override;
    void goAway() override
    {
        for (int i = 0; i < 10; i++)
        {
            if (peoples[i] == this)
            {
                delete peoples[i];
                peoples[i] = nullptr;
                break;
            }
        }
    }
};

class MilkHunter : public Person
{
public:
    MilkHunter(string s, string n, char sx, string d) : Person(s, n, sx, d) {}
    void find() override;
    void goAway() override
    {
        for (int i = 0; i < 10; i++)
        {
            if (peoples[i] == this)
            {
                delete peoples[i];
                peoples[i] = nullptr;
                break;
            }
        }
    }
};

class Altushka : public Person
{
public:
    Altushka(string s, string n, char sx, string d) : Person(s, n, sx, d) {}
    void find() override;
    void goAway() override
    {
        for (int i = 0; i < 10; i++)
        {
            if (peoples[i] == this)
            {
                delete peoples[i];
                peoples[i] = nullptr;
                break;
            }
        }
    }
};

class Extended : public Person
{
private:
    int getOppositeSignIndex(string s)
    {
        if (s == "Овен")
            return 7;
        if (s == "Телец")
            return 8;
        if (s == "Близнецы")
            return 9;
        if (s == "Рак")
            return 10;
        if (s == "Лев")
            return 11;
        if (s == "Дева")
            return 12;
        if (s == "Весы")
            return 1;
        if (s == "Скорпион")
            return 2;
        if (s == "Стрелец")
            return 3;
        if (s == "Козерог")
            return 4;
        if (s == "Водолей")
            return 5;
        if (s == "Рыбы")
            return 6;
        return 0;
    }

public:
    Extended(string s, string n, char sx, string d) : Person(s, n, sx, d) {}
    void find() override;
    void goAway() override
    {
        for (int i = 0; i < 10; i++)
        {
            if (peoples[i] == this)
            {
                delete peoples[i];
                peoples[i] = nullptr;
                break;
            }
        }
    }
};

void Skuf::find()
{
    Altushka *youngest = nullptr;
    for (int i = 0; i < 10; i++)
    {
        if (peoples[i] != nullptr && peoples[i]->get_sex() == 'f' && peoples[i]->get_age() < 25)
        {
            Altushka *current = dynamic_cast<Altushka *>(peoples[i]);
            if (current && (youngest == nullptr || current->compareDate(youngest->get_date()) < 0))
            {
                youngest = current;
            }
        }
    }
    if (youngest == nullptr || youngest == dynamic_cast<Altushka *>(this))
    {
        cout << "oops" << endl;
    }
    else
    {
        cout << youngest->get_name() << " " << youngest->get_surname() << " " << youngest->get_date() << endl;
    }
}

void MilkHunter::find()
{
    Extended *oldest = nullptr;
    for (int i = 0; i < 10; i++)
    {
        if (peoples[i] != nullptr && peoples[i]->get_sex() == 'f' && peoples[i]->get_age() >= 25)
        {
            Extended *current = dynamic_cast<Extended *>(peoples[i]);
            if (current && (oldest == nullptr || current->compareDate(oldest->get_date()) > 0))
            {
                oldest = current;
            }
        }
    }
    if (oldest == nullptr || oldest == dynamic_cast<Extended *>(this))
    {
        cout << "oops" << endl;
    }
    else
    {
        cout << oldest->get_name() << " " << oldest->get_surname() << " " << oldest->get_date() << endl;
    }
}

void Altushka::find()
{
    Skuf *match = nullptr;
    Skuf *youngest = nullptr;
    for (int i = 0; i < 10; i++)
    {
        if (peoples[i] != nullptr && peoples[i]->get_sex() == 'm' && peoples[i]->get_age() >= 25)
        {
            Skuf *current = dynamic_cast<Skuf *>(peoples[i]);
            if (current)
            {
                if (current->get_sign() == this->get_sign())
                {
                    match = current;
                    break;
                }
                if (youngest == nullptr || current->get_age() < youngest->get_age())
                {
                    youngest = current;
                }
            }
        }
    }
    if (match != nullptr && match != dynamic_cast<Skuf *>(this))
    {
        cout << match->get_name() << " " << match->get_surname() << " " << match->get_date() << endl;
    }
    else if (youngest != nullptr && youngest != dynamic_cast<Skuf *>(this))
    {
        cout << youngest->get_name() << " " << youngest->get_surname() << " " << youngest->get_date() << endl;
    }
    else
    {
        cout << "oops" << endl;
    }
}

void Extended::find()
{
    MilkHunter *match = nullptr;
    MilkHunter *oldest = nullptr;
    string oppositeSign;
    int oppIndex = getOppositeSignIndex(this->get_sign());
    switch (oppIndex)
    {
    case 1:
        oppositeSign = "Овен";
        break;
    case 2:
        oppositeSign = "Телец";
        break;
    case 3:
        oppositeSign = "Близнецы";
        break;
    case 4:
        oppositeSign = "Рак";
        break;
    case 5:
        oppositeSign = "Лев";
        break;
    case 6:
        oppositeSign = "Дева";
        break;
    case 7:
        oppositeSign = "Весы";
        break;
    case 8:
        oppositeSign = "Скорпион";
        break;
    case 9:
        oppositeSign = "Стрелец";
        break;
    case 10:
        oppositeSign = "Козерог";
        break;
    case 11:
        oppositeSign = "Водолей";
        break;
    case 12:
        oppositeSign = "Рыбы";
        break;
    }
    for (int i = 0; i < 10; i++)
    {
        if (peoples[i] != nullptr && peoples[i]->get_sex() == 'm' && peoples[i]->get_age() < 25)
        {
            MilkHunter *current = dynamic_cast<MilkHunter *>(peoples[i]);
            if (current)
            {
                if (current->get_sign() == oppositeSign)
                {
                    match = current;
                    break;
                }
                if (oldest == nullptr || current->get_age() > oldest->get_age())
                {
                    oldest = current;
                }
            }
        }
    }
    if (match != nullptr && match != dynamic_cast<MilkHunter *>(this))
    {
        cout << match->get_name() << " " << match->get_surname() << " " << match->get_date() << endl;
    }
    else if (oldest != nullptr && oldest != dynamic_cast<MilkHunter *>(this))
    {
        cout << oldest->get_name() << " " << oldest->get_surname() << " " << oldest->get_date() << endl;
    }
    else
    {
        cout << "oops" << endl;
    }
}

Person *goIn()
{
    string surname, name, date;
    char sex;
    getline(cin, surname);
    getline(cin, name);
    cin >> sex;
    cin.ignore();
    getline(cin, date);

    int day, month, year;
    if (sscanf(date.c_str(), "%d.%d.%d", &day, &month, &year) != 3 ||
        day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2024)
    {
        return nullptr;
    }
    if (sex != 'm' && sex != 'f')
    {
        return nullptr;
    }

    int age = 2024 - year - 1;
    if (month < 1 || (month == 1 && day <= 1))
        age++;

    if (sex == 'm' && age >= 25)
        return new Skuf(surname, name, sex, date);
    if (sex == 'm' && age < 25)
        return new MilkHunter(surname, name, sex, date);
    if (sex == 'f' && age >= 25)
        return new Extended(surname, name, sex, date);
    if (sex == 'f' && age < 25)
        return new Altushka(surname, name, sex, date);
    return nullptr;
}

#include "main3_5.cpp"