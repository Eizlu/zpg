#pragma once

class Light;

class LightObserver
{
public:
		virtual ~LightObserver() = default;
		virtual void onLightChanged(const Light& light) = 0;
};

//spojit s cameraObserver
//vytvorit subject, kterz bude vztvaret kameru i svetlo.
//pak bude mene kodu v camera a light tridach, budou dedit od subject a observer