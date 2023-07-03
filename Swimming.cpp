#include <iostream>
#include <thread>
#include <mutex>

class Swimmer
{
    std::string name;
    int speed;

public:
    bool finish;
    int distance = 100;

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

    }

    Swimmer(std::string inName, int inSpeed)
    {
        setName(inName);
        setSpeed(inSpeed);
        finish = false;
    }
};

int main()
{
    std::cout << "Hello World!\n";
}
