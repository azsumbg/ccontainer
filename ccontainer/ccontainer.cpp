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

// FUNCTIONS **************************

float contlib::Distance(D2D1_POINT_2F init_point, D2D1_POINT_2F ref)
{
	float a = (float)(pow(abs(ref.x - init_point.x), 2));
	float b = (float)(pow(abs(ref.y - init_point.y), 2));

	return (float)(sqrt(a + b));
}

int contlib::SortBag(BAG<D2D1_POINT_2F>& bag, D2D1_POINT_2F ref, bool ascending)
{
	if (bag.empty())return BAD_PARAM;
	else
	{
		if (bag.size() < 2)return CONT_OK;

		if (ascending)
		{
			bool ok = false;

			while (!ok)
			{
				ok = true;

				for (int i = 0; i < bag.size() - 1; ++i)
				{
					if (Distance(bag[i], ref) > Distance(bag[i + 1], ref))
					{
						ok = false;

						D2D1_POINT_2F temp = bag[i];
						bag[i] = bag[i + 1];
						bag[i + 1] = temp;
					}
				}
			}
		}
		else
		{
			bool ok = false;

			while (!ok)
			{
				ok = true;

				for (int i = 0; i < bag.size() - 1; ++i)
				{
					if (Distance(bag[i], ref) < Distance(bag[i + 1], ref))
					{
						ok = false;

						D2D1_POINT_2F temp = bag[i];
						bag[i] = bag[i + 1];
						bag[i + 1] = temp;
					}
				}
			}
		}
	}

	return CONT_OK;
}

int contlib::SortBag(BAG<D2D1_POINT_2F>& bag, D2D1_RECT_F ref_rect, bool ascending)
{
	D2D1_POINT_2F ref{};

	ref.x = ref_rect.left + (ref_rect.right - ref_rect.left) / 2.0f;
	ref.y = ref_rect.top + (ref_rect.bottom - ref_rect.top) / 2.0f;

	if (bag.empty())return BAD_PARAM;
	else
	{
		if (bag.size() < 2)return CONT_OK;

		if (ascending)
		{
			bool ok = false;

			while (!ok)
			{
				ok = true;

				for (int i = 0; i < bag.size() - 1; ++i)
				{
					if (Distance(bag[i], ref) > Distance(bag[i + 1], ref))
					{
						ok = false;

						D2D1_POINT_2F temp = bag[i];
						bag[i] = bag[i + 1];
						bag[i + 1] = temp;
					}
				}
			}
		}
		else
		{
			bool ok = false;

			while (!ok)
			{
				ok = true;

				for (int i = 0; i < bag.size() - 1; ++i)
				{
					if (Distance(bag[i], ref) < Distance(bag[i + 1], ref))
					{
						ok = false;

						D2D1_POINT_2F temp = bag[i];
						bag[i] = bag[i + 1];
						bag[i + 1] = temp;
					}
				}
			}
		}
	}

	return CONT_OK;
}