#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <ctime>

std::vector<Swimmer*> competition;
std::mutex access;

class Swimmer
{
    std::string name;
    int speed;

public:
    bool finish;
    //std::time_t timer;
    int distance;

    void setName(std::string inName)
    {
        name = inName;
    }

    void setSpeed(int inSpeed)
    {
        speed = inSpeed;
    }

    std::string getName()
    {
        return name;
    }

    int getSpeed()
    {
        return speed;
    }

    void swim()
    {
        while (distance > 0)
        {
            distance += speed;
        }
    }

    Swimmer(std::string inName, int inSpeed)
    {
        setName(inName);
        setSpeed(inSpeed);
        finish = false;
        distance = 0;
        //timer = std::time(nullptr);
    }
};

int main()
{
    std::string tempName;
    int tempSpeed = 0;

    std::cout << "Hello World!\n";
    for (int i = 0; i < 10; i++)
    {
        std::cout << i+1 << ".\nEnter swimmer's name: ";
        std::cin >> tempName;
        std::cout << "Enter swimmer's speed: ";
        std::cin >> tempSpeed;
        Swimmer* swimmer = new Swimmer(tempName, tempSpeed);
        competition.push_back(swimmer);
    }
}
