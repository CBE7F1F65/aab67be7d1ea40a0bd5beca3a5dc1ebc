#include "hge_impl.h"

/************************************************************************/
/* These functions are added by h5nc (h5nc@yahoo.com.cn)                */
/************************************************************************/
// begin

float CALL HGE_Impl::Math_Transform3DPoint(float &x, float &y, float &z, hge3DPoint *ptfar)
{
	if (!ptfar || ptfar->z == 0.0f)
	{
		return 1.0f;
	}
	float scale = (ptfar->z - z) / ptfar->z;
	x = (x - ptfar->x) * scale + ptfar->x;
	y = (y - ptfar->y) * scale + ptfar->y;
	z = 0;
	return scale;
}
// end

D3DXMATRIX * CALL HGE_Impl::Math_MatrixIdentity(D3DXMATRIX * pOut)
{
	if (!pOut)
	{
		return NULL;
	}
#ifdef __WIN32
	D3DXMatrixIdentity(pOut);
#else

	ZeroMemory(pOut, sizeof(D3DXMATRIX));
	pOut->_11 = 1.0f;
	pOut->_22 = 1.0f;
	pOut->_33 = 1.0f;
	pOut->_44 = 1.0f;

#endif // __WIN32
	return pOut;
}

D3DXMATRIX * CALL HGE_Impl::Math_MatrixTranslation( D3DXMATRIX *pOut, float x, float y, float z )
{
	if (!pOut)
	{
		return NULL;
	}
#ifdef __WIN32
	D3DXMatrixTranslation(pOut, x, y, z);
#else

	D3DXMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._41 = x;
	mul._42 = y;
	mul._43 = z;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

D3DXMATRIX * CALL HGE_Impl::Math_MatrixRotationX( D3DXMATRIX *pOut, float angle )
{
	if (!pOut)
	{
		return NULL;
	}
#ifdef __WIN32
	D3DXMatrixRotationX(pOut, angle);
#else
	
	float sinval=sinf(angle);
	float cosval=cosf(angle);

	D3DXMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._22 = cosval;
	mul._23 = sinval;
	mul._32 = -sinval;
	mul._33 = cosval;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

D3DXMATRIX * CALL HGE_Impl::Math_MatrixRotationY( D3DXMATRIX *pOut, float angle )
{
	if (!pOut)
	{
		return NULL;
	}
#ifdef __WIN32
	D3DXMatrixRotationY(pOut, angle);
#else

	float sinval=sinf(angle);
	float cosval=cosf(angle);

	D3DXMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._11 = cosval;
	mul._13 = -sinval;
	mul._31 = sinval;
	mul._33 = cosval;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

D3DXMATRIX * CALL HGE_Impl::Math_MatrixRotationZ( D3DXMATRIX *pOut, float angle )
{
	if (!pOut)
	{
		return NULL;
	}
#ifdef __WIN32
	D3DXMatrixRotationZ(pOut, angle);
#else

	float sinval=sinf(angle);
	float cosval=cosf(angle);

	D3DXMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._11 = cosval;
	mul._12 = sinval;
	mul._21 = -sinval;
	mul._22 = cosval;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

D3DXMATRIX * CALL HGE_Impl::Math_MatrixScaling( D3DXMATRIX *pOut, float sx, float sy, float sz )
{
	if (!pOut)
	{
		return NULL;
	}
#ifdef __WIN32
	D3DXMatrixScaling(pOut, sx, sy, sz);
#else

	D3DXMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._11 = sx;
	mul._22 = sy;
	mul._33 = sz;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

D3DXMATRIX * CALL HGE_Impl::Math_MatrixMultiply( D3DXMATRIX *pOut, const D3DXMATRIX *pM1, const D3DXMATRIX *pM2 )
{
	if (!pOut || !pM1 || ! pM2)
	{
		return NULL;
	}
#ifdef __WIN32
	D3DXMatrixMultiply(pOut, pM1, pM2);
#else

	D3DXMATRIX outmat;
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			outmat.m[i][j] = 0.0f;
			for (int k=0; k<4; k++)
			{
				outmat.m[i][j] += pM1->m[i][k] * pM2->m[k][j];
			}
		}
	}
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			pOut->m[i][j] = outmat.m[i][j];
		}
	}

#endif // __WIN32
	return pOut;
}

D3DXMATRIX*	CALL HGE_Impl::Math_MatrixOrthoOffCenterLH(D3DXMATRIX *pOut, float l, float r, float b, float t, float zn, float zf)
{
	if (!pOut)
	{
		return NULL;
	}
#ifdef __WIN32
	D3DXMatrixOrthoOffCenterLH(pOut, l, r, b, t, zn, zf);
#else

	D3DXMATRIX mul;
	Math_MatrixIdentity(&mul);
	if (r != l && t != b && zf != zn)
	{
		mul._11 = 2/(r-l);
		mul._22 = 2/(t-b);
		mul._33 = 1/(zf-zn);
		mul._41 = (l+r)/(l-r);
		mul._42 = (t+b)/(b-t);
		mul._43 = zn/(zn-zf);
	}
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

char * CALL HGE_Impl::Math_itoa(int ival, char * buffer)
{
	if (!buffer)
	{
		return NULL;
	}
	sprintf(buffer, "%d", ival);
	return buffer;
}

int CALL HGE_Impl::Math_atoi(const char * buffer)
{
	return atoi(buffer);
}

char * CALL HGE_Impl::Math_ftoa(float fval, char * buffer)
{
	if (!buffer)
	{
		return NULL;
	}
	sprintf(buffer, "%f", fval);
	return buffer;
}

float CALL HGE_Impl::Math_atof(const char * buffer)
{
	return atof(buffer);
}

LONGLONG CALL HGE_Impl::Math_atoll(const char *buffer)
{
#ifdef __WIN32
	return _atoi64(buffer);
#else

	LONGLONG llret = 0;
	int mul = 10;
	if (strlen(buffer) >= 2)
	{
		if (buffer[0] == '0' && buffer[1] != 'x' && buffer[1] != 'X')
		{
			mul = 8;
		}
		else if (buffer[0] == 'x' || buffer[1] == 'x' || buffer[0] == 'X' || buffer[1] == 'X')
		{
			mul = 16;
		}
	}
	int nowbit = 0;
	for (int i=strlen(buffer)-1; i>=0; i--, nowbit++)
	{
		LONGLONG val = buffer[i] - '0';
		if (mul == 16)
		{
			if (buffer[i] > 'a' && buffer[i] <= 'f')
			{
				val += '9' - 'a' + 1;
			}
			if (buffer[i] > 'A' && buffer[i] <= 'F')
			{
				val += '9' - 'A' + 1;
			}
		}
		if (val < 0 || val > mul)
		{
			break;
		}
		for (int j=0; j<nowbit; j++)
		{
			val = val * mul;
		}
		llret += val;
	}
	return llret;

#endif // __WIN32
}