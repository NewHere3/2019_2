#include <iostream>
#include <vector>
#include <fstream>


using namespace std;

struct dalyvis
{
    string name = "";
    int number = -1;
    int start = -1;
    int finish = -1;
    int time = -1;
};

void read(vector<dalyvis>& dalyviai);
void write(vector<dalyvis>& dalyviai, string kas, ofstream& rez);
void my_sort(vector<dalyvis>& dalyviai);

int main()
{
    vector<dalyvis> dalyviai;
    read(dalyviai);
    my_sort(dalyviai);
    ofstream rez("Rezultatai.txt");
    write(dalyviai, "Merginos", rez);
    write(dalyviai, "Vaikinai", rez);
    return 0;
}

void read(vector<dalyvis>& dalyviai)
{
    ifstream duom("Duomenys.txt");
    int n;
    duom >> n;
    for (int i = 0; i < n; i++)
    {
        dalyvis temp;
        int h, m, s;
        duom.ignore();
        for (int j = 0; j < 20; j++)
        {
            temp.name+=duom.get();
        }
        duom >> temp.number >> h >> m >> s;
        temp.start = h * 60 * 60 + m * 60 + s;
        dalyviai.push_back(temp);
    }
    int m;
    duom >> m;
    for (int i = 0; i < m; i++)
    {
        int temp;
        duom >> temp;
        for (int j = 0; j < n; j++)
        {
            if (temp == dalyviai[j].number)
            {
                int h, m, s, n1, n2, n3=0, n4=0;
                duom >> h >> m >> s;
                dalyviai[j].finish = h * 60 * 60 + m * 60 + s;
                dalyviai[j].time = dalyviai[j].finish - dalyviai[j].start;
                if (temp>=200)
                {
                    duom >> n1 >> n2 >> n3 >> n4;
                    dalyviai[j].time += (20 - (n1 + n2 + n3 + n4)) * 60;
                }
                else
                {
                    duom >> n1 >> n2;
                    dalyviai[j].time += (10 - (n1 + n2)) * 60;
                }
            }
        }
    }
}

void write(vector<dalyvis>& dalyviai, string kas, ofstream& rez)
{
    rez << kas << '\n';
    for (int i = 0; i < dalyviai.size(); i++)
    {
        if (kas == "Merginos")
        {
            if (dalyviai[i].number < 200)
            {
                rez << dalyviai[i].number << ' ' << dalyviai[i].name << ' ' << dalyviai[i].time / 3600 << ' ' << (dalyviai[i].time % 3600) / 60 << ' ' << (dalyviai[i].time % 60) % 60 << '\n';
            }
        }
        else
        {
            if (dalyviai[i].number >= 200)
            {
                rez << dalyviai[i].number << ' ' << dalyviai[i].name << ' ' << dalyviai[i].time / 3600 << ' ' << (dalyviai[i].time % 3600) / 60 << ' ' << (dalyviai[i].time % 60) % 60 << '\n';
            }
        }
    }
}

void my_sort(vector<dalyvis>& dalyviai)
{
    for (int i = 0; i < dalyviai.size(); i++)
    {
        if (dalyviai[i].time==-1)
        {
            dalyviai.erase(dalyviai.begin() + i);
            i = 0;
        }
        else
        {
            for (int j = 0; j < dalyviai.size(); j++)
            {
                if (dalyviai[i].time<=dalyviai[j].time)
                {
                    swap(dalyviai[i], dalyviai[j]);
                }
            }
        }
    }
}