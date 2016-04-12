#ifndef ISERVERPACKET_H_
# define ISERVERPACKET_H_

# include "NetworkDefines.h"
# include "ObjectInfo.hpp"
# pragma pack (1)

typedef struct
{
  uint32_t			magic;
  ServerTCPResponse		command;
  uint32_t			size;
}				ServerTCPHeader;

typedef struct
{
  uint32_t			magic;
  ServerUDPResponse		command;
  uint32_t			size;
  uint32_t			idx;
}				ServerUDPHeader;

typedef struct
{
  uint32_t			data;
  uint32_t			magic;
}				integerData;

typedef struct
{
  Bool				success;
  uint32_t			magic;
}				AuthTCPData;

typedef struct
{
  char				ip[256];
  uint32_t			port;
  uint32_t			magic;
}			 	GameInfoData;

typedef struct
{
  uint32_t			id;
  char				gameName[256];
  char				players[256];
  uint32_t			magic;
}				DesGameData;

typedef struct
{
  Bool				success;
  float				timestamp;
  uint32_t			magic;
}				AuthUDPData;

typedef struct
{
  int				id;
  float				x;
  float				y;
  uint32_t			magic;
}				CrePlayData;

typedef struct
{
  int				id;
  float				speed;
  ObjectInfo::WaveType		type;
  float				x;
  float				y;
  uint32_t			magic;
}				BonusData;

typedef struct
{
  int				id;
  float				x;
  float				y;
  uint32_t			score;
  uint32_t			magic;
}				MoveData;

typedef struct
{
  int				id;
  float				x;
  float				y;
  float				speedX;
  float				speedY;
  ObjectInfo::ShotType		type;
  uint32_t			magic;
}				CreObjData;

typedef struct
{
  int				id;
  float				x;
  float				y;
  float				speed;
  float				coeff;
  enum ObjectInfo::WaveType	iatype;
  uint32_t			magic;
}				CreIAData;


typedef integerData		GameOverData;
typedef integerData		GameListData;
typedef integerData		DelItemData;
typedef integerData		NextLvlData;

template <typename T>
class				IServerPacket
{
public:
  virtual ~IServerPacket() {};

public:
  virtual char*			deserialize() = 0;
  virtual bool			checkHeader() = 0;
  virtual void			setRawData(char *) = 0;
  virtual T			getCommandType() const = 0;
  virtual size_t		getPacketSize() const = 0;
};

# pragma pack ()

#endif
