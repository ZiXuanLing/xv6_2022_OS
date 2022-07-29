#ifndef __INCLUDE_MP_H__

#define __INCLUDE_MP_H__

#include "types.h"

struct mp {
    uchar signature[4]; // "_MP_"
    void *physaddr;
    uchar length;
    uchar specrev;
    uchar checksum;
    uchar type;
    uchar imcrp;
    uchar reserved[3];
};

struct mpconf {
    uchar signature[4];
    ushort length;
    uchar version;
    uchar checksum;
    uchar product[20];
    uchar *oemtable;
    ushort oemlength;
    ushort entry;
    uint *lapicaddr;
    ushort xlength;
    uchar xchecksum;
    uchar reserved;
};

struct mpproc {
    uchar type;
    uchar apicid;
    uchar verison;
    uchar flags;
      #define MPBOOT 0x02
    uchar signature[4];
    uint feature;
    uchar reserved[8];   
};

#endif