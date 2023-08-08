#include <iostream>
#include <fstream>

using namespace std;

class shopping
{
private:
    int pcode;
    int price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void shopping::menu()
{
m:
    int choice;
    string email;
    string password;

    cout << "\t\t\t\t___________________________________\n";
    cout << "\t\t\t\t                                   \n";
    cout << "\t\t\t\t      Supermarket main menu        \n";
    cout << "\t\t\t\t                                   \n";
    cout << "\t\t\t\t___________________________________\n";
    cout << "\t\t\t\t                                   \n";
    cout << "\t\t\t\t|      1) Administrator     |\n";
    cout << "\t\t\t\t|                           |\n";
    cout << "\t\t\t\t|      2) Buyer             |\n";
    cout << "\t\t\t\t|                           |\n";
    cout << "\t\t\t\t|      3) Exit              |\n";
    cout << "\t\t\t\t|                           |\n";
    cout << "\t\t\t\tPlease select: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\t\t Please login  \n";
        cout << "\t\t Enter email:  \n";
        cin >> email;
        cout << "\t\t Password:      \n";
        cin >> password;

        if (email == "ishika.29nov2000@gmail.com" && password == "ishika@29")
        {
            administrator();
        }
        else
        {
            cout << "Invalid email/password";
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0);

    default:
        cout << "Please select from the given options";
    }

    goto m;
}

void shopping::administrator()
{
m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator Menu";
    cout << "\n\t\t\t|_____1) Add the product_____|\n";
    cout << "\t\t\t|                            |\n";
    cout << "\t\t\t|_____2) Modify the product__|\n";
    cout << "\t\t\t|                            |\n";
    cout << "\t\t\t|_____3) Delete the Product__|\n";
    cout << "\t\t\t|                            |\n";
    cout << "\t\t\t|_____4) Back to Main Menu___|\n";
    cout << "\n\t\t\tPlease enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;

    case 2:
        edit();
        break;

    case 3:
        rem();
        break;

    case 4:
        menu();
        break;

    default:
        cout << "Invalid choice!";
    }

    goto m;
}

void shopping::buyer()
{
m:
    int choice;
    cout << "\t\t\t  Buyer  \n";
    cout << "\t\t\t_________\n";
    cout << "\n";
    cout << "\t\t\t 1) Buy Product \n";
    cout << "\n";
    cout << "\t\t\t 2) Go back\n";
    cout << "\t\t\t Enter your choice: ";

    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;

    case 2:
        menu();
        break;

    default:
        cout << "Invalid choice";
    }

    goto m;
}

void shopping::add()
{
m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\n\t Add New Product";
    cout << "\n\n\t Product Code of the Product: ";
    cin >> pcode;
    cout << "\n\n\t Name of the Product: ";
    cin >> pname;
    cout << "\n\n\t Discount on Product: ";
    cin >> dis;

    data.open("database.txt", ios::in);
    if (!data) // If the file doesn't exist, then create a file
    {
        data.open("database.txt", ios::in | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d; // If the file exists, then read the file

        while (!data.eof())
        {
            if (c == pcode)
            {
                token++; // If there is duplicacy, the token initialized with zero will be incremented and become 1
            }
            data >> c >> n >> p >> d; // For iteration purpose, we are reading from the file
        }
        data.close(); // Close the file

        if (token == 1)
            goto m; // If there is duplicacy, go back to the menu. The user has to enter another product code.
        else
        {
            // If the product is unique (not duplicate), then add the product to the database
            data.open("database.txt", ios::in | ios::out);
            data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
        }
    }
    cout << "\n\n\t\t Record inserted!";
}

//******Edit Function******//

void shopping::edit()
{
    fstream data, data1; // Objects of fstream class
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t Product Code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n File doesn't exist!";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out); // Edited data will save in database1 and will rename it with database.txt
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "\n\t\t New Product Code: ";
                cin >> c;
                cout << "\n\t\t Name of the Product: ";
                cin >> n;
                cout << "\n\t\t Price: ";
                cin >> p;
                cout << "\n\t\t Discount: ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Record edited";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << " "
                     << "\n";
            }
            data >> pcode >> pname >> price >> dis; // To iterate the while loop
        }
        data.close();
        data1.close();
        // We have to rename that database1 to database, so we will use the remove function
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) // If token value is not incremented
            cout << "\n\n\n Record not found, sorry!";
    }
}

void shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\n\n\t Delete Product";
    cout << "\n\n\t Product Code: ";
    cin >> pkey;
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File doesn't exist";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pcode == pkey)
            {
                cout << "\n\n\n\t Product deleted successfully";
                token++;
            }
            else
            {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0)
        {
            cout << "\n\n Record not found";
        }
    }
}

void shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in); // In reading mode
    cout << "\n\n|________________________________________________________________\n";
    cout << "Product No\tName\t\tPrice\n";
    cout << "\n|_________________________________________________________________\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shopping::receipt()
{
    // Here we have to use arrays, and then we will declare some variables because we have to store multiple product keys and multiple quantities of those products
    fstream data;

    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float discount = 0;
    float total = 0;

    cout << "\n\n\t\t\t\t RECEIPT";
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n Empty database";
    }
    else
    {
        data.close();
        list();
        cout << "\n________________________________________\n";
        cout << "\n|                                       \n";
        cout << "\n          Place the order               \n";
        cout << "\n|                                       \n";
        cout << "\n________________________________________\n";
        do
        {
        m:
            cout << "\n\nEnter Product Code: ";
            cin >> arrc[c];
            cout << "\nEnter the Product Quantity: ";
            cin >> arrq[c];
            for (int i = 0; i < c; i++)
            {
                if (arrc[c] == arrc[i])
                {
                    cout << "\n\n Duplicate product code. Please try again!";
                    goto m;
                }
            }
            c++;
            cout << "\n\nDo you want to buy another product? If yes, then click Y; else, click N: ";
            cin >> choice;
        } while (choice == 'Y' || choice == 'y');
        cout << "\n\n\t\t\t_______________________RECEIPT______________________________\n";
        cout << "\nProduct No\tProduct Name\tProduct Quantity\tPrice\tAmount\tAmount with discount\n";

        for (int i = 0; i < c; i++)
        {
            data.open("database.txt", ios::in);
            data >> pcode >> pname >> price >> dis;
            while (!data.eof())
            {
                if (pcode == arrc[i])
                {
                    amount = price * arrq[i];
                    discount = amount - (amount * dis / 100);
                    total = total + discount;
                    cout << "\n" << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t" << discount;
                }
                data >> pcode >> pname >> price >> dis;
            }
            data.close();
        }
    }
    cout << "\n\n_________________________________________";
    cout << "\n Total Amount: " << total;
}

int main()
{
    shopping s; // Create the object of the shopping class. First, call the s.menu function from the topmost function.
    s.menu();
    return 0;
}
