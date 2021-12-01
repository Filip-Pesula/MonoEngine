#pragma once
#include "Efector.h"
#include "MoveEfector.h"
namespace monoEngine {
	class GraphycsBodyEfector : public Efector
	{
		Vec3f position;
		MoveEfector& moveEfector;
		std::vector<std::unique_ptr<InputElement>> generateInputField();

	public:
		GraphycsBodyEfector(MoveEfector& moveEfector);


		virtual void execute() override;
		virtual std::any getProperty(std::string name) override;
		virtual std::any getProperty(int name) override;
		virtual int getPropertyCount() override;
	};
}

