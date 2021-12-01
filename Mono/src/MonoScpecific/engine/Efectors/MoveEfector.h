#pragma once
#include "Efector.h"
namespace monoEngine
{
	class MoveEfector : public Efector
	{
		Vec3f position;
		Vec3f rotation;
		std::vector<std::unique_ptr<InputElement>> generateInputField();
	public:
		MoveEfector();
		void setPosition(float x, float y, float z);
		void setPosition(Vec3f position);
		void setRotation(float x, float y, float z);
		void setRotation(Vec3f rotation);


		virtual void execute() override;
		virtual std::any getProperty(std::string name) override;
		virtual std::any getProperty(int name) override;
		virtual int getPropertyCount() override;

	};
}