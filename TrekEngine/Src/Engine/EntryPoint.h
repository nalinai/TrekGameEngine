#pragma once

extern TrekEngine::Application* TrekEngine::CreateApplication();

int main(int agrc, char** argv)
{
	// Run the application
	auto app = TrekEngine::CreateApplication();
	app->Run();
	delete app;
}