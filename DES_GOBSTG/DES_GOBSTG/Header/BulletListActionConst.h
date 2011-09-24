#ifndef _BULLETLISTACTIONCONST_H
#define _BULLETLISTACTIONCONST_H


#define THEN -1000000

#define BULA_CONDITIONSTART	0x0000

#define BULAC_FILTER	0xf0

#define BULAC_OTHER		0x00

#define	SECTIONEND		0x0

#define	EVERY			0x1
#define	EVERYMOD		0x2

#define BULAC_TIMER		0x10

#define	TIMERGREAT		0x11
#define	TIMEREQUAL		0x12
#define	TIMERLESS		0x13
#define	TIMERRANGE		0x14

#define BULAC_TYPE		0x20

#define	TYPEEQUAL		0x21

#define BULAC_COLOR		0x30

#define	COLOREQUAL		0x31

#define BULAC_ANGLE		0x40

#define	ANGLEGREAT		0x41
#define	ANGLEEQUAL		0x42
#define	ANGLELESS		0x43
#define	ANGLERANGE		0x44

#define BULAC_POS		0x50

#define	XGREAT			0x51
#define	XLESS			0x52
#define	XRANGE			0x53
#define	YGREAT			0x58
#define	YLESS			0x59
#define	YRANGE			0x5A

#define BULAC_VAL		0x60

#define VALGREAT		0x61
#define VALEQUAL		0x62
#define VALLESS			0x63
#define VALRANGE		0x64

#define BULAC_SPEED		0x70

#define	SPEEDGREAT		0x71
#define	SPEEDEQUAL		0x72
#define	SPEEDLESS		0x73
#define	SPEEDRANGE		0x74

#define BULAC_INDEX		0x80

#define INDEXMODGREAT	0x81
#define INDEXMODEQUAL	0x82
#define INDEXMODLESS	0x83
#define INDEXMODRANGE	0x84

#define BULAC_BOUNCE	0x90

#define BOUNCEGREAT		0x91
#define BOUNCEEQUAL		0x92
#define BOUNCELESS		0x93
#define BOUNCERANGE		0x94

#define BULA_EXECUTESTART	0x1000

#define BULAE_FILTER	0xf000

#define BULAE_TYPE		0x1000

#define	TYPESET			0x1100

#define BULAE_COLOR		0x2000

#define	COLORSET		0x2100

#define BULAE_ANGLE		0x3000

#define	ANGLESET		0x3100
#define ANGLESETADD		0x3200
#define	ANGLEADJUST		0x3300
#define	ANGLESETRMA		0x3400
#define	ANGLESETRMAP	0x3500
#define ANGLESETRMAT	0x3600
#define	ANGLESETAMA		0x3700
#define	ANGLESETAMAP	0x3800
#define ANGLESETAMAT	0x3900
#define ANGLESETRAND	0x3A00
#define ANGLESETADDRAND	0x3B00

#define BULAE_HEADANGLE	0x4000

#define	HEADANGLESET	0x4100
#define	HEADANGLESETADD	0x4200

#define BULAE_POS		0x5000

#define	XSET			0x5100
#define	YSET			0x5200
#define XSETADD			0x5300
#define	YSETADD			0x5400
#define	XSETACCADD		0x5500
#define	YSETACCADD		0x5600

#define BULAE_VAL		0x6000

#define VALSET			0x6100
#define VALSETADD		0x6200

#define BULAE_SPEED		0x7000

#define	SPEEDSET		0x7100
#define	SPEEDSETADD		0x7200
#define	SPEEDSETMUL		0x7300

#define BULAE_OTHER		0x8000

#define CALLEVENT		0x8100
#define CHASE			0x8200
#define	REMAIN			0x8300
#define DECANCEL		0x8400
#define FADEOUT			0x8500
#define BOUNCE			0x8800
#define BOUNCELR		0x8900
#define BOUNCETB		0x8A00

#define BULA_SPECIALSTART	0x00

#define	AND				-0x01
#define	OR				-0x02
#define	NOT				-0x03
#define CONDITIONBYVAL		-0x04
#define CONDITIONBYINDEX	-0x05
#define EXECUTEBYVAL		-0x06
#define EXECUTEBYINDEX		-0x07


#endif