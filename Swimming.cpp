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

    void swim()
    {
        {
            while (distance < 100)
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                distance += getSpeed();
                std::cout << getName() << " swam " << distance << " meters!" << std::endl;
            }
            output_access.lock();
            result.push_back(getName());
            output_access.unlock();
        }
    }

    Swimmer(std::string inName, int inSpeed)
    {
        setName(inName);
        setSpeed(inSpeed);
        distance = 0;
       
    }
};




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
    
    for (int i = 0; i < 6; i++)
    {
        tracks.emplace_back(&Swimmer::swim, swimmers[i]);
    }
    
    for (int i = 0; i < 6; i++)
    {
        tracks[i].join();
    }
        
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



