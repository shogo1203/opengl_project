#include "test_component.h"

void TestComponent::Initialize()
{
	std::cout << "init" << std::endl;
}

void TestComponent::Update()
{
	std::cout << "update" << std::endl;
}

void TestComponent::OnEnable()
{
	std::cout << "enable" << std::endl;
}

void TestComponent::Awake()
{
	std::cout << "awake" << std::endl;
}
