#include "pch.h"
#include "ccontainer.h"

// EXCEPTION CLASS ***********************

contlib::EXCEPTION::EXCEPTION(int err)
{
	what = err;
}

const wchar_t* contlib::EXCEPTION::eGet()const
{
	switch (what)
	{
	case BAD_PTR:
		return L"Nullptr pointer passed in container method ! ";

	case BAD_INDEX:
		return L"Bad index passed in container method ! ";

	case BAD_PARAM:
		return L"Bad parameter passed in container method ! ";
	}

	return L"Unknown error occured in container ! ";
}

//////////////////////////////////////////

// RAND CLASS ***********************

contlib::RAND::RAND()
{
	std::random_device rd{};
	std::seed_seq sq{ rd(), rd(), rd(), rd(), rd(), rd(), rd() };

	twister = new std::mt19937(sq);
}
contlib::RAND::~RAND()
{
	if (twister)delete twister;
}

int contlib::RAND::operator()(int min, int max)
{
	if (max < min)return -1;

	std::uniform_int_distribution distr(min, max);

	return distr(*twister);
}
float contlib::RAND::operator()(float min, float max)
{
	if (max < min)return -1.0f;

	std::uniform_real_distribution<float> distr(min, max);

	return distr(*twister);
}

//////////////////////////////////////