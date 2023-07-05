#include <iostream>
#include <thread>
#include <mutex>
#include <vector>


std::vector<std::string> result;
std::vector<std::thread> tracks;
std::mutex output_access;

class Swimmer
{
    std::string name;
    int speed;
        
public:
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

    

    Swimmer(std::string inName, int inSpeed)
    {
        setName(inName);
        setSpeed(inSpeed);
        distance = 0;
       
    }
};


void swim(Swimmer* swimmer)
{
    {
        while (swimmer->distance < 100)
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            swimmer->distance += swimmer->getSpeed();
            std::cout << swimmer->getName() << " swam " << swimmer->distance << " meters!" << std::endl;
        }
        output_access.lock();
        result.push_back(swimmer->getName());
        output_access.unlock();
    }
}

int main()
{
    std::vector<Swimmer*> swimmers;
    std::string tempName;
    int tempSpeed = 0;

    std::cout << "Introducing participants!\n";
    for (int i = 0; i < 6; i++)
    {
        std::cout << i+1 << ".\nEnter swimmer's name: ";
        std::cin >> tempName;
        std::cout << "Enter swimmer's speed: ";
        std::cin >> tempSpeed;
        Swimmer* swimmer = new Swimmer(tempName, tempSpeed);
        swimmers.push_back(swimmer);
    }
    std::cout << "Start!" << std::endl;   
    
    output_access.lock();
    std::thread swimmer0(swim, swimmers[0]);
    output_access.unlock();

    output_access.lock();
    std::thread swimmer1(swim, swimmers[1]);
    output_access.unlock();

    output_access.lock();
    std::thread swimmer2(swim, swimmers[2]);
    output_access.unlock();

    output_access.lock();
    std::thread swimmer3(swim, swimmers[3]);
    output_access.unlock();

    output_access.lock();
    std::thread swimmer4(swim, swimmers[4]);
    output_access.unlock();

    output_access.lock();
    std::thread swimmer5(swim, swimmers[5]);
    output_access.unlock();
    
    swimmer0.join();
    swimmer1.join();
    swimmer2.join();
    swimmer3.join();
    swimmer4.join();
    swimmer5.join();
    
    std::cout << "The competition is ower! Results: " << std::endl;
    output_access.lock();
    for (int i = 0; i < 6; i++)
    {
        
        std::cout << i + 1 << ". " << result[i] << std::endl;
        
    }
    output_access.unlock();

    for (int i = 5; i >= 0; i--)
    {
        delete swimmers[i];
    }
}



