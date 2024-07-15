#include <bits/stdc++.h>
using namespace std;

// global variables..
static int id = 0;
// enum declarations..
enum Gender
{
    Male,
    Female,
    Others
};

enum Berth_preference
{
    lower_berth,
    middle_berth,
    upper_berth,
    rac_berth,
    waiting
};

// passenger class..
class Passenger
{
public:
    string name;
    int age;
    Gender gender;
    Berth_preference berth;
    int passenger_id = id;

    void setdetails(string name, int age, Gender gen, Berth_preference berth)
    {
        this->name = name;
        this->age = age;
        this->gender = gen;
        this->berth = berth;
        id++;
    }

    string gender_reveal(int x)
    {
        if (x == 0)
        {
            return "Male";
        }
        else if (x == 1)
        {
            return "Female";
        }
        else
        {
            return "Others";
        }
    }

    string berth_reveal(int x)
    {
        if (x == 0)
        {
            return "Lower-berth";
        }
        else if (x == 1)
        {
            return "Middle-berth";
        }
        else if (x == 2)
        {
            return "Upper-berth";
        }
        else if (x == 3)
        {
            return "RAC-berth";
        }
        else
        {
            return "Waiting-List";
        }
    }

    void passenger_details()
    {
        cout << "____________________________________________________\n";
        cout << "Passenger name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Gender: " << gender_reveal(gender) << endl;
        cout << "Berth: " << berth_reveal(berth) << endl;
        cout << "Passenger id: " << passenger_id << endl;
        cout << "____________________________________________________\n";
    }
};

// Train class..
class Train
{
public:
    vector<Passenger> passenger_list;
    string train_name;
    int lower_count;
    int middle_count;
    int upper_count;
    int rac_count;
    int waiting_count;
    // parameterised constructor.. to create train
    Train(string name, int lb, int mb, int ub, int rac, int wl)
    {
        this->train_name = name;
        cout << "Train Name: " << name << endl;
        this->lower_count = lb;
        this->middle_count = mb;
        this->upper_count = ub;
        this->rac_count = rac;
        this->waiting_count = wl;
    }
    // function to print available tickets..
    void available_tickets()
    {
        cout << "------------------------------------\n";
        cout << "Available Tickets..." << endl;
        cout << "------------------------------------\n";
        cout << "Lower_berth: " << lower_count << endl;
        cout << "middle_berth: " << middle_count << endl;
        cout << "upper_berth: " << upper_count << endl;
        cout << "rac_berth: " << rac_count << endl;
        cout << "waiting_berth: " << waiting_count << endl;
        cout << "-----------------------------------\n";
    }

    // function to book tickets for passengers
    void book(Berth_preference berth, Passenger &current)
    {
        if (berth == lower_berth && lower_count > 0)
        {
            cout << "Lower-berth confirmed\n";
            current.berth = lower_berth;
            passenger_list.push_back(current);
            lower_count--;
            current.passenger_details();
        }
        else if (berth == middle_berth && middle_count > 0)
        {
            cout << "Middle-berth confirmed\n";
            current.berth = middle_berth;
            passenger_list.push_back(current);
            middle_count--;
            current.passenger_details();
        }
        else if (berth == upper_berth && upper_count > 0)
        {
            cout << "Upper-berth confirmed\n";
            current.berth = upper_berth;
            passenger_list.push_back(current);
            upper_count--;
            current.passenger_details();
        }
        else
        {
            if (lower_count > 0)
            {
                cout << "Lower-berth confirmed\n";
                current.berth = lower_berth;
                passenger_list.push_back(current);
                lower_count--;
                current.passenger_details();
            }
            else if (middle_count > 0)
            {
                cout << "Middle-berth confirmed\n";
                current.berth = middle_berth;
                passenger_list.push_back(current);
                middle_count--;
                current.passenger_details();
            }
            else if (upper_count > 0)
            {
                cout << "Upper-berth confirmed\n";
                current.berth = upper_berth;
                passenger_list.push_back(current);
                upper_count--;
                current.passenger_details();
            }
            else if (rac_count > 0)
            {
                cout << "RAC-berth confirmed\n";
                current.berth = rac_berth;
                passenger_list.push_back(current);
                cout << "Side lower berth is allocated..\n";
                rac_count--;
                current.passenger_details();
            }
            else if (waiting_count > 0)
            {
                cout << "In waiting list...\n";
                current.berth = waiting;
                passenger_list.push_back(current);
                cout << "Ticket not confirmed.. In waiting list..\n";
                waiting_count--;
                current.passenger_details();
            }
            else
            {
                cout << "Sorry.. Currently No Tickets Available.." << endl;
            }
        }
    }

    void book_ticket(string name, int age, Gender gender, Berth_preference berth)
    {
        Passenger current;
        current.name = name;
        current.age = age;
        current.gender = gender;
        current.berth = berth;

        // age verification
        if (age <= 5)
        {
            cout << "Baduva rascal.. come with parents da" << endl;
            return;
        }

        if (berth == lower_berth && lower_count <= 0)
        {
            cout << "Sorry Lower-berth filled..\n";
            book(berth, current);
        }
        else if (berth == middle_berth && middle_count <= 0)
        {
            cout << "Sorry Middle-berth filled..\n";
            book(berth, current);
        }
        else if (berth == upper_berth && upper_count <= 0)
        {
            cout << "Sorry Upper-berth filled..\n";
            book(berth, current);
        }
        else
        {
            book(berth, current);
        }
    }

    // function to print booked tickets
    void booked_tickets()
    {
        if (passenger_list.size() > 0)
        {
            cout << "---------------------------------------------------------------------------------\n";
            for (int i = 0; i < passenger_list.size(); i++)
            {
                passenger_list[i].passenger_details();
                cout << "------------------------------------------------------------------------------\n";
            }
        }
        else
        {
            cout << "No tickets booked.." << endl;
        }
    }

    // function to cancel booked tickets
    void cancel_tickets(string name)
    {
        Berth_preference cancelled_berth;
        bool flag = false;
        for (int i = 0; i < passenger_list.size(); i++)
        {
            if (passenger_list[i].name == name)
            {
                cancelled_berth = passenger_list[i].berth;
                Berth_preference b = passenger_list[i].berth;
                if (b == lower_berth)
                {
                    lower_count++;
                }
                else if (b == middle_berth)
                {
                    middle_count++;
                }
                else if (b == upper_berth)
                {
                    upper_count++;
                }
                else
                {
                    rac_count++;
                }
                passenger_list.erase(passenger_list.begin() + i);
                cout << "Ticket cancelled!!" << endl;
                flag = true;
            }
        }

        if (flag == true)
        {
            // some ticket is cancelled..
            for (int i = 0; i < passenger_list.size(); i++)
            {
                if (passenger_list[i].berth == rac_berth)
                {
                    cancelled_berth = passenger_list[i].berth;
                    rac_count--;
                    if (cancelled_berth == lower_berth)
                    {
                        lower_count++;
                    }
                    else if (cancelled_berth == middle_berth)
                    {
                        middle_count++;
                    }
                    else if (cancelled_berth == upper_berth)
                    {
                        upper_count++;
                    }
                }
            }
            for (int i = 0; i < passenger_list.size(); i++)
            {
                if (passenger_list[i].berth == waiting)
                {
                    passenger_list[i].berth = rac_berth;
                    waiting_count--;
                }
            }
        }

        if (flag == false)
        {
            cout << "Ticket Not Booked..." << endl;
        }
    }
};

int main()
{
    cout << "------------------------|Welcome to Railway Ticket Booking|---------------------------\n";

    Train t1("Vaigai Express", 3, 3, 3, 3, 3);
    cout << "____________________________________________________________________________________\n";

    bool i = true;
    while (i)
    {
        cout << "1. BOOK TICKET\n";
        cout << "2. CANCEL TICKET\n";
        cout << "3. SHOW BOOKED TICKETS\n";
        cout << "4. SHOW AVAILABLE TICKETS\n";
        cout << "5. CLOSE \n";
        cout << "__________________________________________________________________________________\n";

        int n;
        cin >> n;
        cin.ignore();
        string name;
        int age;
        string g;
        string b;
        Passenger p;
        switch (n)
        {
        case 1:
            cout << "Enter your name: ";
            getline(cin, name);
            cout << "Enter your age: ";
            cin >> age;
            cin.ignore();
            cout << "Enter your gender: ";
            getline(cin, g);
            cout << "Enter your berth preference: ";
            getline(cin, b);
            Gender a;
            if (g == "Male")
            {
                a = Gender::Male;
            }
            else if (g == "Female")
            {
                a = Gender::Female;
            }
            else
            {
                a = Gender::Others;
            }
            Berth_preference berth;
            if (b == "Lower")
            {
                berth = Berth_preference::lower_berth;
            }
            else if (b == "Middle")
            {
                berth = Berth_preference::middle_berth;
            }
            else if (b == "Upper")
            {
                berth = Berth_preference::upper_berth;
            }

            p.setdetails(name, age, a, berth);
            t1.book_ticket(name, age, a, berth);
            break;
        case 2:
            cout << "Enter your name: \n";
            cin >> name;
            t1.cancel_tickets(name);
            break;
        case 3:
            t1.booked_tickets();
            break;
        case 4:
            t1.available_tickets();
            break;
        case 5:
            cout << "---------------------- Thank you for visiting ------------------------\n";
            return 0;
        default:
            cout << "Enter valid input..\n";
            break;
        }
    }

    return 0;
}
