#pragma once
#include <UI/Elements/UiElements.h>
#include <UI/Elements/UiElement.h>
#include <Custom.h>
#include "../SceneObject.h"
#include <src/MonoScpecific/engine/uiClusters/EfectorEditor.h>
namespace monoEngine
{
	class ObjectEditor : public UI::UIelement
	{
		UI::Container container;
		std::vector<std::unique_ptr <EfectorEditor>> efectorList;
		SceneObject* activeObject;
	public:
		ObjectEditor(Unit width, Unit height);
		void setActiveObject(SceneObject* object);
		void Draw(UI::UIShader shader) override;
		void onResize(Vec2i screenSize)override;
		bool onRay(UI::Cursor& cursor)override;
	};
}

