#pragma once

class Light;

class LightObserver
{
public:
		virtual ~LightObserver() = default;
		virtual void onLightChanged(const Light& light) = 0;
};