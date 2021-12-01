#include "MoveEfector.h"
#include <MonoScpecific/engine/uiClusters/inputElelements/SliderField.h>
namespace monoEngine
{
    std::vector<std::unique_ptr<InputElement>> MoveEfector::generateInputField()
    {
        std::unique_ptr<SliderField<float>> xSlider = 
            std::make_unique<SliderField<float>>(
                0,10,
                0.5f, 
                Vec2<Unit>(
                    Unit(),
                    Unit(UnitType::px, 15)
                    ),
                nullptr
                );
        std::unique_ptr<SliderField<float>> ySlider =
            std::make_unique<SliderField<float>>(
                0, 10,
                0.5f,
                Vec2<Unit>(
                    Unit(),
                    Unit(UnitType::px, 15)
                    ),
                xSlider.get()
                ); 
        std::unique_ptr<SliderField<float>> zSlider =
            std::make_unique<SliderField<float>>(
                0, 10,
                0.5f,
                Vec2<Unit>(
                    Unit(),
                    Unit(UnitType::px, 15)
                    ),
                ySlider.get()
                );

        
        std::vector<std::unique_ptr<InputElement>> inputField{};
        inputField.push_back(std::move(xSlider));
        inputField.push_back(std::move(ySlider));
        inputField.push_back(std::move(zSlider));
        
        
        return inputField;
    }
    MoveEfector::MoveEfector() :
        Efector("MoveEffector", std::move(generateInputField()))
    {

    }

    void MoveEfector::setPosition(float x, float y, float z)
    {
        position = { x,y,z };
    }

    void MoveEfector::setPosition(Vec3f position)
    {
        this->position = position;
    }

    void MoveEfector::setRotation(float x, float y, float z)
    {
        rotation = { x,y,z };
    }

    void MoveEfector::setRotation(Vec3f rotation)
    {
        this->rotation = rotation;
    }

    void MoveEfector::execute()
    {
        position.x = std::any_cast<float>(itemList[0]->getValue());
        position.y = std::any_cast<float>(itemList[1]->getValue());
        position.z = std::any_cast<float>(itemList[2]->getValue());
    }

    std::any MoveEfector::getProperty(std::string name)
    {
        size_t name_hash = std::hash<std::string>{}(name);
        if (name.length() == 0)
        {
            return nullptr;
        }
        if (name == "position") {
            return std::any(position);
        }
        if (name == "rotation") {
            return std::any(rotation);
        }


        return std::any(position);
    }

    std::any MoveEfector::getProperty(int name)
    {
        return std::any();
    }
    int MoveEfector::getPropertyCount()
    {
        return 3;
    }
}