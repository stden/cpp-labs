#include "PoiskDLL.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  CRC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
unsigned  table [] = {
0x00000000, 0x77073096, 0xEE0E612C, 0x990951BA,
0x076DC419, 0x706AF48F, 0xE963A535, 0x9E6495A3,
0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988,
0x09B64C2B, 0x7EB17CBD, 0xE7B82D07, 0x90BF1D91,

0x1DB71064, 0x6AB020F2, 0xF3B97148, 0x84BE41DE,
0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7,
0x136C9856, 0x646BA8C0, 0xFD62F97A, 0x8A65C9EC,
0x14015C4F, 0x63066CD9, 0xFA0F3D63, 0x8D080DF5,

0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172,
0x3C03E4D1, 0x4B04D447, 0xD20D85FD, 0xA50AB56B,
0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 0xACBCF940,
0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59,

0x26D930AC, 0x51DE003A, 0xC8D75180, 0xBFD06116,
0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 0xB8BDA50F,
0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924,
0x2F6F7C87, 0x58684C11, 0xC1611DAB, 0xB6662D3D,

0x76DC4190, 0x01DB7106, 0x98D220BC, 0xEFD5102A,
0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433,
0x7807C9A2, 0x0F00F934, 0x9609A88E, 0xE10E9818,
0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 0xE6635C01,

0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E,
0x6C0695ED, 0x1B01A57B, 0x8208F4C1, 0xF50FC457,
0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 0xFCB9887C,
0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65,

0x4DB26158, 0x3AB551CE, 0xA3BC0074, 0xD4BB30E2,
0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 0xD3D6F4FB,
0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0,
0x44042D73, 0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9,

0x5005713C, 0x270241AA, 0xBE0B1010, 0xC90C2086,
0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F,
0x5EDEF90E, 0x29D9C998, 0xB0D09822, 0xC7D7A8B4,
0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 0xC0BA6CAD,

0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A,
0xEAD54739, 0x9DD277AF, 0x04DB2615, 0x73DC1683,
0xE3630B12, 0x94643B84, 0x0D6D6A3E, 0x7A6A5AA8,
0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1,

0xF00F9344, 0x8708A3D2, 0x1E01F268, 0x6906C2FE,
0xF762575D, 0x806567CB, 0x196C3671, 0x6E6B06E7,
0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC,
0xF9B9DF6F, 0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5,

0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 0x4FDFF252,
0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B,
0xD80D2BDA, 0xAF0A1B4C, 0x36034AF6, 0x41047A60,
0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 0x4669BE79,

0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236,
0xCC0C7795, 0xBB0B4703, 0x220216B9, 0x5505262F,
0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 0x5CB36A04,
0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D,

0x9B64C2B0, 0xEC63F226, 0x756AA39C, 0x026D930A,
0x9C0906A9, 0xEB0E363F, 0x72076785, 0x05005713,
0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38,
0x92D28E9B, 0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21,

0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 0x1FDA836E,
0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777,
0x88085AE6, 0xFF0F6A70, 0x66063BCA, 0x11010B5C,
0x8F659EFF, 0xF862AE69, 0x616BFFD3, 0x166CCF45,

0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2,
0xA7672661, 0xD06016F7, 0x4969474D, 0x3E6E77DB,
0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 0x37D83BF0,
0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9,

0xBDBDF21C, 0xCABAC28A, 0x53B39330, 0x24B4A3A6,
0xBAD03605, 0xCDD70693, 0x54DE5729, 0x23D967BF,
0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94,
0xB40BBE37, 0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D
};

unsigned ProcCRC32(void* pData,int nLen, unsigned uns)
{
	const unsigned CRC_MASK = 0xD202EF8D;

    unsigned char* pdata = reinterpret_cast<unsigned char*>(pData);
	unsigned  crc = uns;

	while (nLen--)
	{
		crc = table[(unsigned  char)crc ^ *pdata++] ^ crc >> 8;
		crc ^= CRC_MASK;
	}
	uns = crc;
	return uns;
}

unsigned pathCRC(char* path1)
{
	HANDLE hfile = CreateFile(path1, GENERIC_READ, FILE_SHARE_READ,	NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if (hfile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	char data[512];
	DWORD len;
	unsigned uns = 0;

	while(ReadFile(hfile, data, 512, &len, NULL) && len)
			uns = ProcCRC32(data, len, uns);

	CloseHandle(hfile);

	return uns;
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!  CRC !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SHA-256
ULONG reversebytes(ULONG x) { // �� little-endian � big-endian -- TODO: ���������� BSWAP!!!
	return (x >> 24) | (x >> 8) & 0xFF00 | (x << 8) & 0xFF0000 | (x << 24) & 0xFF000000;
}

const ULONG h0 = 0x6a09e667, h1 = 0xbb67ae85, h2 = 0x3c6ef372, h3 = 0xa54ff53a;
const ULONG h4 = 0x510e527f, h5 = 0x9b05688c, h6 = 0x1f83d9ab, h7 = 0x5be0cd19;
const ULONG k[] = {
   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

ULONG inline ror(ULONG x, ULONG z) 
{

	x = x>>z | x<<(32-z);
	return x;
}

inline void SHA256(UCHAR *t, DWORD len, DWORD len2, ULONG& A, ULONG& B, ULONG& C, ULONG& D, ULONG& E, ULONG& F, ULONG& G, ULONG& H) { // �������� ��������� ���������� ����
	A = h0, B = h1, C = h2, D = h3, E = h4, F = h5, G = h6, H = h7;
	*(ULONG*)(t + len2 - 8) = reversebytes(len >> (32-3)); // ���������� ����� � ��������� 64 ����
	*(ULONG*)(t + len2 - 4) = reversebytes(len << 3);
	*(UCHAR*)(t + len) = 0x80; // ���������� �������� � ������
	memset(t + len + 1, '\0', len2 - 8 - len - 1);
	for(ULONG* m = (ULONG*)t; m < (ULONG*)(t + len2); m += 16){
		ULONG a = A, b = B, c = C, d = D, e = E, f = F, g = G, h = H;
		ULONG w[64];
		for(int i = 0; i < 16; ++i) {
			ULONG s0, m0, t0, s1, m1, t1;
			__asm{
				mov eax, a
				mov ebx, eax
				ror eax, 2
				mov ecx, ebx
				ror ebx, 13
				xor eax, ebx
				ror ecx, 22
				xor eax, ecx
				mov s0, eax
			}
			m0 = (a & b) | (c & (a | b));
			t0 = s0 + m0;
			__asm{
				mov eax, e
				mov ebx, eax
				ror eax, 6
				mov ecx, ebx
				ror ebx, 11
				xor eax, ebx
				ror ecx, 25
				xor eax, ecx
				mov s1, eax
			}
			s1 = ror(e, 6) ^ ror(e, 11) ^ ror(e, 25);
			m1 = g ^ (e & (f ^ g));
			w[i] = reversebytes(*(m+i));
			t1 = h + s1 + m1 + k[i] + w[i];
		
			h = g, g = f, f = e, e = d + t1, d = c, c = b, b = a, a = t0 + t1;
		}
		for(int i = 16; i < 64; ++i) {
			ULONG s0, m0, t0, s1, m1, t1, v1, v2;
			__asm{
				mov eax, a
				mov ebx, eax
				ror eax, 2
				mov ecx, ebx
				ror ebx, 13
				xor eax, ebx
				ror ecx, 22
				xor eax, ecx
				mov s0, eax
			}
			m0 = (a & b) | (c & (a | b));
			t0 = s0 + m0;
			__asm{
				mov eax, e
				mov ebx, eax
				ror eax, 6
				mov ecx, ebx
				ror ebx, 11
				xor eax, ebx
				ror ecx, 25
				xor eax, ecx
				mov s1, eax
			}
			m1 = g ^ (e & (f ^ g));

			// ��������� 16 ���� � 64 �����, �������� �������������� 48 ����
			ULONG g1 = w[i-15], g2 = w[i-2];
			__asm{
				mov eax, g1
				mov ebx, eax
				ror eax, 7
				mov ecx, ebx
				ror ebx, 18
				xor eax, ebx
				shr ecx, 3
				xor eax, ecx
				mov v1, eax

				mov eax, g2
				mov ebx, eax
				ror eax, 17
				mov ecx, ebx
				ror ebx, 19
				xor eax, ebx
				shr ecx, 10
				xor eax, ecx
				mov v2, eax
			}
			w[i] = w[i-16] + v1 + w[i-7] + v2;
			t1 = h + s1 + m1 + k[i] + w[i];
		
			h = g, g = f, f = e, e = d + t1, d = c, c = b, b = a, a = t0 + t1;
		}
		A += a, B += b, C += c, D += d, E += e, F += f, G += g, H += h;
	}
}

void pathSHA256(char* path1, char* out2)
{
     ULONG A, B, C, D, E, F, G, H; ULONG len, len2; char* s; 
	// char out[64+9];
	 HANDLE hFile = CreateFile(path1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	 if(INVALID_HANDLE_VALUE == hFile) 
				return;

	 len = GetFileSize(hFile, NULL);
	 len2 = ((len + 8 + 1) + 63) & -64; // ���������� �����
	 s = (char*)malloc(len2);
	 ReadFile(hFile, s, len, &len, NULL);
	
	 SHA256((UCHAR*)s, len, len2, A, B, C, D, E, F, G, H);
	 wsprintf(out2, "%08x %08x %08x %08x %08x %08x %08x %08x", A, B, C, D, E, F, G, H);

	 CloseHandle(hFile);
	 free(s);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! SHA-256
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! MD5 !!!!!!!!!!!!!!!!!!! 

const ULONG _F[] = { // ��������� t, ������������ �� ������ ����� � ������ �� ��������
	0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
	0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
	0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
	0x6b901122,0xfd987193,0xa679438e,0x49b40821},
_G[] = {
	0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
	0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
	0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
	0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a},
_H[] = {
	0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
	0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
	0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
	0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665},
_I[] = {
	0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
	0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
	0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
	0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391};

// ������� ������������� ��������� �� 2-�, 3-�, 4-� �����
const UINT _g[] = {1, 6, 11, 0, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12},
		   _h[] = {5, 8, 11, 14, 1, 4, 7, 10, 13, 0, 3, 6, 9, 12, 15, 2},
		   _i[] = {0, 7, 14, 5, 12, 3, 10, 1, 8, 15, 6, 13, 4, 11, 2, 9};

typedef ULONG (*NLF)(ULONG, ULONG, ULONG); // ���������� ���� ���������� �������
// ���������� �������, ������������ � �������� MD5
ULONG inline F(ULONG X, ULONG Y, ULONG Z) {
	return (Z ^ (X & (Y ^ Z)));
}

ULONG inline G(ULONG X, ULONG Y, ULONG Z) {
	return F(Z, X, Y);
}

ULONG inline H(ULONG X, ULONG Y, ULONG Z) {
	return X ^ Y ^ Z;
}

ULONG inline I(ULONG X, ULONG Y, ULONG Z) {
	return Y ^ (X | (~Z));
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#define ROLIT(xx) case xx: __asm{rol z, xx} break;
// ���� �������� �����������
template <NLF func, ULONG s> void inline Operation(ULONG& a, ULONG b, ULONG c, ULONG d, ULONG M, ULONG t) {
	ULONG z;
	z = a + func(b, c, d) + M + t;

	switch (s) { // ������ ���� ��� ����������� MSVC++
		ROLIT(7) ROLIT(12) ROLIT(17) ROLIT(22)
		ROLIT(5) ROLIT(9) ROLIT(14) ROLIT(20)
		ROLIT(4) ROLIT(11) ROLIT(16) ROLIT(23)
		ROLIT(6) ROLIT(10) ROLIT(15) ROLIT(21)
	}

	a = b + z;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void inline MD5(char* s, ULONG len, ULONG len2, ULONG& A, ULONG& B, ULONG& C, ULONG& D) {
	*(ULONG*)(s + len2 - 8) = len * 8; // ���������� ����� � ��������� 64 ����
	*(ULONG*)(s + len2 - 4) = 0;
	*(UCHAR*)(s + len) = 0x80; // ���������� �������� � ������
	memset(s + len + 1, '\0', len2 - 8 - len - 1);
	A = 0x67452301, B = 0xefcdab89, C = 0x98badcfe, D = 0x10325476;
	for(ULONG* m = (ULONG*)s; m < (ULONG*)(s + len2); m += 16) { // �������� ����
		ULONG a = A, b = B, c = C, d = D;
		for(int i = 0; i < 16; i+=4) { // 16 �������� �� ������ �����
			Operation<F, 7>(a, b, c, d, *(m+i+0), _F[i+0]); // 1-� ����
			Operation<F, 12>(d, a, b, c, *(m+i+1),_F[i+1]);
			Operation<F, 17>(c, d, a, b, *(m+i+2),_F[i+2]);
			Operation<F, 22>(b, c, d, a, *(m+i+3),_F[i+3]);
		}
		for(int i = 0; i < 16; i+=4) { // 16 �������� �� ������ �����
			Operation<G, 5>(a, b, c, d, *(m+_g[i+0]),  _G[i+0]);
			Operation<G, 9>(d, a, b, c, *(m+_g[i+1]),  _G[i+1]);
			Operation<G, 14>(c, d, a, b, *(m+_g[i+2]), _G[i+2]);
			Operation<G, 20>(b, c, d, a, *(m+_g[i+3]), _G[i+3]);
		}
		for(int i = 0; i < 16; i+=4) { // 16 �������� �� ������� �����
			Operation<H, 4>(a, b, c, d, *(m+_h[i+0]),  _H[i+0]);
			Operation<H, 11>(d, a, b, c, *(m+_h[i+1]), _H[i+1]);
			Operation<H, 16>(c, d, a, b, *(m+_h[i+2]), _H[i+2]);
			Operation<H, 23>(b, c, d, a, *(m+_h[i+3]), _H[i+3]);
		}
		for(int i = 0; i < 16; i+=4) { // 16 �������� �� ��������� �����
			Operation<I, 6>(a, b, c, d, *(m+_i[i+0]),  _I[i+0]);
			Operation<I, 10>(d, a, b, c, *(m+_i[i+1]), _I[i+1]);
			Operation<I, 15>(c, d, a, b, *(m+_i[i+2]), _I[i+2]);
			Operation<I, 21>(b, c, d, a, *(m+_i[i+3]), _I[i+3]);
		}
		A += a, B += b, C += c, D += d;
	}
}


void pathMD5(char* path1,  char *out2)
{
     ULONG A, B, C, D, E, F, G, H; ULONG len, len2; char* s; 
	 //char out[64+9];
	 HANDLE hFile = CreateFile(path1, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	 if(INVALID_HANDLE_VALUE == hFile) 
				return;

	 len = GetFileSize(hFile, NULL);
	 len2 = ((len + 8 + 1) + 63) & -64; // ���������� �����
	 s = (char*)malloc(len2);
	 ReadFile(hFile, s, len, &len, NULL);
	 MD5(s, len, len2, A, B, C, D);
	 A = reversebytes(A), B = reversebytes(B),
	 C = reversebytes(C), D = reversebytes(D);
	 wsprintf(out2, TEXT("%08x%08x%08x%08x"), A, B, C, D);

	 CloseHandle(hFile);
	 free(s);
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ������� ���������
bool pathBITsr(void* pData1,void* pData2, int nLen)
{
	unsigned char* pdata1 = reinterpret_cast<unsigned char*>(pData1);
	unsigned char* pdata2 = reinterpret_cast<unsigned char*>(pData2);

	while (nLen--)
		if (*pdata1++ ^ *pdata2++)
			return false;
	
	return true;
}


bool pathBIT(char* path1, char* path2)
{
	HANDLE hfile1 = CreateFile(path1, GENERIC_READ, FILE_SHARE_READ,	NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	HANDLE hfile2 = CreateFile(path2, GENERIC_READ, FILE_SHARE_READ,	NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

	if ( (hfile1 == INVALID_HANDLE_VALUE) || (hfile2 == INVALID_HANDLE_VALUE) )
		return false;

	char data1[512];
	DWORD len1;
	char data2[512];
	DWORD len2;

	while(ReadFile(hfile1, data1, 512, &len1, NULL) && len1 && ReadFile(hfile2, data2, 512, &len2, NULL) && len2)
			if ( (len1!=len2) || !pathBITsr(data1,data2,len1))
				return false;

	CloseHandle(hfile1);
	CloseHandle(hfile2);
	return true;
}
