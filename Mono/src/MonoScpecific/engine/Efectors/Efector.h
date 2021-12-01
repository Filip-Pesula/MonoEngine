#pragma once
#include <Custom.h>
#include <any>
#include <src/MonoScpecific/engine/uiClusters/inputElelements/InputElement.h>
#include <UI/Elements/UiElements.h>
namespace monoEngine
{
	class Efector
	{
		std::string name;
		Unit calculatHeight(std::vector<std::unique_ptr<InputElement>>& vecRef);
	public:
		std::vector<std::unique_ptr<InputElement>> itemList;
		std::unique_ptr<UI::Container> listContainer;
		Efector(std::string name);
		Efector(std::string name, std::vector<std::unique_ptr<InputElement>> itemList);
		std::string getName();
		virtual void execute() = 0;
		virtual std::any getProperty(std::string name) = 0;
		/**
		 * 
		 *
		 * @param name 
		 * @return
		 * @throw on element count overflow throws item count.
		*/
		virtual std::any getProperty(int name) throw(int) = 0;
		virtual int getPropertyCount() = 0;
	};
}

