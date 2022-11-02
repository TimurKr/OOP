#include <iostream>
#include <string>

class BaseBuilding
{
protected:
    unsigned int number, num_floors;

public:
    // Constructors
    BaseBuilding(unsigned int house_number = 0, unsigned int number_of_floors = 0)
    {
        if (house_number == 0)
        {
            number = std::rand() % 100 + 1;
        }
        else
        {
            number = house_number;
        }
        if (number_of_floors == 0)
        {
            num_floors = std::rand() % 5 + 1;
        }
        else
        {
            num_floors = number_of_floors;
        }
    }

    // Interface
    virtual void print_info()
    {
        std::cout << "Číslo domu: " << number << std::endl;
        std::cout << "Počet poschodí: " << num_floors << std::endl;
    }
};

class ComercialBuilding : public BaseBuilding
{
protected:
    unsigned int num_employees, daily_revenue;

public:
    // Constructor
    ComercialBuilding(
        unsigned int house_number = 0,
        unsigned int number_of_floors = 0,
        unsigned int number_of_employees = 0,
        unsigned int revenue_per_day = 0) : BaseBuilding(house_number, number_of_floors)
    {
        if (number_of_employees == 0)
        {
            num_employees = std::rand() % 1000 + 1;
        }
        else
        {
            num_employees = number_of_employees;
        }
        if (revenue_per_day == 0)
        {
            daily_revenue = std::rand() % 1000 + 1;
        }
        else
        {
            daily_revenue = revenue_per_day;
        }
    }

    // Interface
    virtual void print_info()
    {
        BaseBuilding::print_info();
        std::cout << "Počet zamestnancov: " << num_employees << std::endl;
        std::cout << "Denný obrat: " << daily_revenue << " €" << std::endl;
    }
};


class House : public BaseBuilding
{
private:
    unsigned int house_area, garden_area;

public:
    // Constructors
    House(
        unsigned int house_number = 0,
        unsigned int number_of_floors = 0,
        unsigned int area_of_house = 0,
        unsigned int area_of_garden = 0) : BaseBuilding(house_number, number_of_floors)
    {
        if (area_of_house == 0)
        {
            house_area = std::rand() % 100 + 1;
        }
        else
        {
            house_area = area_of_house;
        }
        if (area_of_garden == 0)
        {
            garden_area = std::rand() % 100 + 1;
        }
        else
        {
            garden_area = area_of_garden;
        }
    }

    // Interface
    void print_info()
    {
        std::cout << "\n\nRodinný dom:\n" << std::endl;
        BaseBuilding::print_info();
        std::cout << "Rozloha budovy: " << house_area << " m2" << std::endl;
        std::cout << "Rozloha záhrady: " << garden_area << " m2" << std::endl;
    }
};

class FlatHouse : public BaseBuilding
{
private:
    unsigned int num_flats;

public:
    // Constructors
    FlatHouse(
        unsigned int house_number = 0,
        unsigned int number_of_floors = 0,
        unsigned int number_of_flats = 0) : BaseBuilding(house_number, number_of_floors)
    {
        if (number_of_flats == 0)
        {
            num_flats = std::rand() % 100 + 1;
        }
        else
        {
            num_flats = number_of_flats;
        }
    }

    // Interface
    void print_info()
    {
        std::cout << "\n\nBytový dom:\n" << std::endl;
        BaseBuilding::print_info();
        std::cout << "Počet bytov: " << num_flats << std::endl;
    }
};

class Office : public ComercialBuilding
{
private:
    unsigned int num_sections;

public:
    // Constructor
    Office(
        unsigned int house_number = 0,
        unsigned int number_of_floors = 0,
        unsigned int number_of_employees = 0,
        unsigned int revenue_per_day = 0,
        unsigned int number_of_sections = 0) : ComercialBuilding(house_number, number_of_floors, number_of_employees, revenue_per_day)
    {
        if (number_of_sections == 0)
        {
            num_sections = std::rand() % 100 + 1;
        }
        else
        {
            num_sections = number_of_sections;
        }
    }

    // Interface
    void print_info()
    {
        std::cout << "\n\nKancelárska budova:\n" << std::endl;
        ComercialBuilding::print_info();
        std::cout << "Počet sekcií: " << num_sections << std::endl;
    }
};

class Factory : public ComercialBuilding
{
private:
    unsigned int area;

public:
    // Construct
    Factory(
        unsigned int house_number = 0,
        unsigned int number_of_floors = 0,
        unsigned int number_of_employees = 0,
        unsigned int revenue_per_day = 0,
        unsigned int area_of_factory = 0) : ComercialBuilding(house_number, number_of_floors, number_of_employees, revenue_per_day)
    {
        if (area_of_factory == 0)
        {
            area = std::rand() % 100000 + 1;
        }
        else
        {
            area = area_of_factory;
        }
    }

    // Interface
    void print_info()
    {
        std::cout << "\n\nFabrika:\n" << std::endl;
        ComercialBuilding::print_info();
        std::cout << "Rozloha výrobnej plochy: " << area << " m2" << std::endl;
    }
};


class Street {
    private:
        std::string city, name;
        unsigned int num_buildings;
        BaseBuilding** buildings;

    public:
        // Constructor
        Street(std::string city_name, std::string street_name, unsigned int number_of_buildings = 0) : 
            city(city_name), name(street_name), num_buildings(number_of_buildings) 
        {
            if (number_of_buildings == 0) { 
                buildings =nullptr; 
                return;
            }

            buildings = new BaseBuilding*[number_of_buildings];
            unsigned int building_type;
            for (unsigned int i = 0; i < number_of_buildings; i++) {
                building_type = std::rand() % 4;
                if (building_type == 0) { 
                    buildings[i] = new House(i+1);
                } else if (building_type == 1) {
                    buildings[i] = new FlatHouse(i+1);
                } else if (building_type == 2) {
                    buildings[i] = new Office(i+1);
                } else if (building_type == 3) {
                    buildings[i] = new Factory(i+1);
                }
            }
        }
        // Destructor
        ~Street(){
            for (unsigned int i = 0; i < num_buildings; i++) {
                delete buildings[i];
            }
            delete[] buildings;
        }


        // Interface
        void print_info() { 
            std::cout << "\n\nUlica " << name << " v meste " << city << std::endl;
            std::cout << "Počet budov: " << num_buildings << std::endl;
            for (unsigned int i = 0; i < num_buildings; i++) {
                buildings[i]->print_info();
            }
        }
};

int main()
{
    Street street("Bratislava", "Hlboká", 20);
    street.print_info();
    return 0;
}