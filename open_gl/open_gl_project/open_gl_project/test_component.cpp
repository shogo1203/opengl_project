#include "test_component.h"

void TestComponent::Initialize()
{
	std::cout << BOOST_VERSION << std::endl;
}

void TestComponent::Update()
{
	std::cout << "update" << std::endl;
}
