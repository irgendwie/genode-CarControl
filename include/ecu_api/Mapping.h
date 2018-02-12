#ifndef __MAPPING__
#define __MAPPING__

typedef unsigned char   __u8;
class Mapping{
  public:
    __u8 GetReadMapping(int cmd);
    __u8 GetWriteMapping(int cmd);
    Mapping();
    ~Mapping();
};

#endif
