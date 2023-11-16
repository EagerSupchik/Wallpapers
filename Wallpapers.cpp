#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>

using namespace std;

class Wallpaper 
{
public:
    string name;
    double size;
    double price;

    Wallpaper(string name, int size, double price) : name(name), size(size), price(price) {}

    string getWallname() { return name; }
    double getSize() { return size; }
    double getPrice() { return price; }
};


class Room
{
public:
    string name;
    double size;
    bool ceiling;
    double ceiling_size;

    Room(const string name, double size, bool ceiling, double ceiling_size) : name(name), size(size), ceiling(ceiling), ceiling_size(ceiling_size) {}
};


class Apartment
{
public:
    vector<Room> rooms;
    vector<Wallpaper> wallps;

    void addRoom(const Room& room) 
    {
        rooms.push_back(room);
    }

    void addWallp(const Wallpaper& wallp)
    {
        wallps.push_back(wallp);
    }

    void getPrice(string name)
    {
        double total_price = 0.0;
        int count = 0;
        int total_count = 0;

        for (auto i = wallps.begin(); i != wallps.end(); i++)
        {
            if (i->getWallname() == name)
            {
                for (const auto& room : rooms)
                {
                    count = 0;
                    double room_price = 0.0;
                    double room_area = room.size;
                    room_price = (room_area / i->getSize()) * i->getPrice();


                    if (room.ceiling)
                    {
                        double ceiling_size = room.ceiling_size;
                        double ceiling_price = 0.0;
                        ceiling_price = (ceiling_size / i->getSize()) * i->getPrice();
                        room_price += ceiling_price;
                        count += ceil(ceiling_size / i->getSize());
                        total_count += ceil(ceiling_size / i->getSize());
                    }

                    total_price += room_price;
                    total_count += ceil(room_area / i->getSize());
                    count += ceil(room_area / i->getSize());
                    
                    cout << "Стоимость поклейки обоев в " << room.name << " составляет: " << room_price << " рублей" << endl;
                    cout << "Кол-во рулонов обоев на эту комнату нужно: " << count << endl;
                }

                cout << "Общая стоимость обоев: " << total_price << " рублей" << endl;
                cout << "Кол-во рулонов обоев: " << total_count << endl;
            }
        }
    }
};


int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Apartment ap;

    int c;

    string room_name;
    string wallpaper_name;
    string c_wallp;


    while (true)
    {
        cout << R"(
-----Подбор обоев-----
1. Добавить комнату
2. Узнать стоимость
3. Добавить обои
0. Выход
)";

        cin >> c;
        system("cls");

        switch (c)
        {
        case 1:
            double room_size;
            bool ceiling;
            double ceiling_size;

            cout << "Введите название комнаты: ";
            cin.ignore();
            getline(cin, room_name);
            cout << "Введите размеры: ";
            cin >> room_size;
            cout << "Хотите ли вы поклеить потолок? (1 - да, 0 - нет)" << endl;
            cin >> ceiling;
            if (ceiling == true)
            {
                cout << "Введите площадь потолка: " << endl;
                cin >> ceiling_size;
            }
            ap.addRoom(Room(room_name, room_size, ceiling, ceiling_size));
            break;

        case 2:
            if (room_name.size() > 0 && wallpaper_name.size() > 0)
            {
                cout << "Напишите название обоев, которые вы хотите использовать:" << endl;
                cin.ignore();
                getline(cin, c_wallp);
                ap.getPrice(c_wallp);

            }
            else
            {
                cout << "Ошибка! Возможно вы забыли добавить обои или комнату" << endl;
            }
            break;


        case 3:
            double wallp_size, price;
            cout << "Введите название обоев: ";
            cin.ignore();
            getline(cin, wallpaper_name);
            cout << "Введите размеры: ";
            cin >> wallp_size;
            cout << "Введите цену: ";
            cin >> price;
            ap.addWallp(Wallpaper(wallpaper_name, wallp_size, price));
            break;

        default:
            exit(0);
            break;
        }
    }
}