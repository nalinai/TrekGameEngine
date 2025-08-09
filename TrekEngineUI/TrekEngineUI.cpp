#include "TrekEngineUI.h"
#include "TrekEngine.h"


class TrekEngineUI : public TrekEngine::Application
{
public:
	TrekEngineUI()
	{
		// Initialization code for the TrekEngine UI application
	}
	~TrekEngineUI()
	{

	}
};

TrekEngine::Application* TrekEngine::CreateApplication()
{
	return new TrekEngineUI();
}

