#pragma once
#include <Custom.h>
#include <src/UI/Elements/UIelements.h>
#include "InputElement.h"
#include <MonoStd/monoMath.h>


namespace monoEngine
{
	template <mono::Aritmetic T>
	class SliderField : public InputElement
	{
		T value;
		T min;
		T size;
		UI::Slider slider;
	public:
		std::any getValue() override;
		void setValue(std::any val) override;
		void Draw(UI::UIShader shader) override {
			slider.Draw(shader);
		}
		void onResize(Vec2i ScreenSize) override {
			slider.Resize(ScreenSize);
		}
		bool onRay(UI::Cursor &cursor) override {
			slider.MouseRay(cursor);
			if (cursor.LMBState == UI::MouseState::RELEAS)
			{
				value = (T)(slider.mValue*size + min);
			}
			return false;
		}
		SliderField(T min, T max, T val, Vec2<Unit> position, UI::UIelement* parent) :
			InputElement(
				Unit(UnitType::pw, 1),
				Unit(UnitType::px, 15),
				position,
				parent),
			value(val),
			min(min),
			size(max - min),
			slider(
				Unit(UnitType::pw, 1),
				Unit(UnitType::ph, 1),
				Color4(0.2, 0.2, 0.7, 1.0),
				Vec2<Unit>(Unit(), Unit()),
				this)
		{
			slider.mValue = (value - min) / size;
		}
		std::unique_ptr<UI::UIelement> clone(UI::UIelement* parent) override{
			std::unique_ptr<SliderField<T>> instance = std::unique_ptr<SliderField<T>>(new SliderField(min, size + min, (T)(slider.mValue * size - min), mPosition, parent));
			return std::move(instance);
		}
		SliderField<T>* clone_imp(UI::UIelement* parent) override {
			return new SliderField(min, size + min, value, mPosition, parent);
		}
	};
	template<mono::Aritmetic T>
		inline std::any SliderField<T>::getValue()
		{
			return value;
		}
		template<mono::Aritmetic T>
		inline void SliderField<T>::setValue(std::any val)
		{
			value = std::any_cast<T>(val);
			slider.mValue = (value - min) / size;
		}
}

