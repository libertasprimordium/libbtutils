#ifndef __ENDIAN_UTILS_H__
#define __ENDIAN_UTILS_H__

#include <string.h> // for memcpy

inline uint64 ReadBE64(const void *p)
{
	byte *pp = (byte*)p;
	uint64 ret = 0;
	for (int i = 0; i < sizeof(uint64); ++i, ++pp) {
		ret <<= 8;
		ret |= *pp;
	}
	return ret;
}

inline void WriteBE64(void *p, uint64 x)
{
	byte *pp = (byte*)p;
	for (int i = (sizeof(uint64)-1)*8; i >= 0 ; i -= 8, ++pp) {
		*pp = (x >> i) & 0xff;
	}
}

#if !defined(STRICT_ALIGN) && !BT_LITTLE_ENDIAN
inline uint32 ReadBE32(const void *p) { return *(uint32*)p; }
inline uint16 ReadBE16(const void *p) { return *(uint16*)p; }
inline float ReadBEFloat(const void *p) { return *(float*)p; }
inline void WriteBE32(void *p, uint32 x) { *(uint32*)p = x; }
inline void WriteBE16(void *p, uint16 x) { *(uint16*)p = x; }
inline void WriteBEFloat(void *p, float x) { *(float*)p = x; }
#else

#if BT_LITTLE_ENDIAN

inline float ReadBEFloat(const void *p)
{
	byte *src = (byte*)p;
	float ret;
	byte* dst = (byte*)&ret;
	dst[0] = src[3];
	dst[1] = src[2];
	dst[2] = src[1];
	dst[3] = src[0];
	return ret;
}

inline void WriteBEFloat(const void *p, float v)
{
	byte *dst = (byte*)p;
	byte* src = (byte*)&v;
	dst[0] = src[3];
	dst[1] = src[2];
	dst[2] = src[1];
	dst[3] = src[0];
}
#else

inline float ReadBEFloat(const void *p)
{
	byte *src = (byte*)p;
	float ret;
	byte* dst = (byte*)&ret;
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = src[3];
	return ret;
}

inline void WriteBEFloat(const void *p, float v)
{
	byte *dst = (byte*)p;
	byte* src = (byte*)&v;
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = src[3];
}

#endif

inline uint32 ReadBE32(const void *p)
{
	byte *pp = (byte*)p;
	return (pp[0] << 24) | (pp[1] << 16) | (pp[2] << 8) | (pp[3] << 0);
}

inline uint16 ReadBE16(const void *p)
{
	byte *pp = (byte*)p;
	return (pp[0] << 8) | (pp[1] << 0);
}

inline void WriteBE32(void *p, uint32 x)
{
	byte *pp = (byte*)p;
	pp[0] = (byte)(x >> 24);
	pp[1] = (byte)(x >> 16);
	pp[2] = (byte)(x >> 8);
	pp[3] = (byte)(x >> 0);
}

inline void WriteBE16(void *p, uint16 x)
{
	byte *pp = (byte*)p;
	pp[0] = (byte)(x >> 8);
	pp[1] = (byte)(x >> 0);
}
#endif

#if !defined(STRICT_ALIGN) && BT_LITTLE_ENDIAN
inline uint32 ReadLE32(const void *p) { return *(uint32*)p; }
inline uint16 ReadLE16(const void *p) { return *(uint16*)p; }
inline void WriteLE32(void *p, uint32 x) { *(uint32*)p = x; }
inline void WriteLE16(void *p, uint16 x) { *(uint16*)p = x; }
#else
inline uint32 ReadLE32(const void *p)
{
	byte *pp = (byte*)p;
	return (pp[3] << 24) | (pp[2] << 16) | (pp[1] << 8) | (pp[0] << 0);

}

inline uint16 ReadLE16(const void *p)
{
	byte *pp = (byte*)p;
	return (pp[1] << 8) | (pp[0] << 0);
}

inline void WriteLE32(void *p, uint32 x)
{
	byte *pp = (byte*)p;
	pp[3] = (byte)(x >> 24);
	pp[2] = (byte)(x >> 16);
	pp[1] = (byte)(x >> 8);
	pp[0] = (byte)(x >> 0);
}

inline void WriteLE16(void *p, uint16 x)
{
	byte *pp = (byte*)p;
	pp[1] = (byte)(x >> 8);
	pp[0] = (byte)(x >> 0);
}
#endif

#ifdef STRICT_ALIGN
inline uint32 Read32(const void *p)
{
	uint32 tmp;
	memcpy(&tmp, p, sizeof tmp);
	return tmp;
}

inline uint16 Read16(const void *p)
{
	uint16 tmp;
	memcpy(&tmp, p, sizeof tmp);
	return tmp;
}
#else
inline uint32 Read32(const void *p) { return *(uint32*)p; }
inline uint16 Read16(const void *p) { return *(uint16*)p; }
#endif

inline void Write32(void *p, uint32 x) { memcpy(p, &x, 4); }
inline void Write16(void *p, uint16 x) { memcpy(p, &x, sizeof x); }

#endif //__ENDIAN_UTILS_H__
