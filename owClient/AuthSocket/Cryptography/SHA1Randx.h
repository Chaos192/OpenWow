#pragma once

#include "SHA1.h"

class SHA1Randx
{
public:
	SHA1Randx(uint8* buff, uint32 size)
	{
		uint32 halfSize = size / 2;

		sh.Initialize();
		sh.UpdateData(buff, halfSize);
		sh.Finalize();

		memcpy(o1, sh.GetDigest(), 20);

		sh.Initialize();
		sh.UpdateData(buff + halfSize, size - halfSize);
		sh.Finalize();

		memcpy(o2, sh.GetDigest(), 20);

		memset(o0, 0x00, 20);

		FillUp();
	}

	void Generate(uint8* buf, uint32 sz)
	{
		for (uint32 i = 0; i < sz; ++i)
		{
			if (taken == 20)
				FillUp();

			buf[i] = o0[taken];
			taken++;
		}
	}

private:
	void FillUp()
	{
		sh.Initialize();
		sh.UpdateData(o1, 20);
		sh.UpdateData(o0, 20);
		sh.UpdateData(o2, 20);
		sh.Finalize();

		memcpy(o0, sh.GetDigest(), 20);

		taken = 0;
	}

	SHA1Hash sh;
	uint32 taken;
	uint8 o0[20], o1[20], o2[20];
};