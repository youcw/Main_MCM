/*************************************************************/
/*                   FAT操作函数库                                      */
/*************************************************************/

struct bootsector710 {
	BYTE	bsJump[3];					// jump inst E9xxxx or EBxx90
	char	bsOemName[8];				// OEM name and version
	char	bsBPB[53];					// BIOS parameter block
	char	bsExt[26];					// Bootsector Extension
	char	bsBootCode[418];			// pad so structure is 512b
	BYTE	bsBootSectSig2;				// boot sector signature byte 0x00 
	BYTE	bsBootSectSig3;				// boot sector signature byte 0x00
	BYTE	bsBootSectSig0;				// boot sector signature byte 0x55 
	BYTE	bsBootSectSig1;				// boot sector signature byte 0xAA
#define BOOTSIG0        0x55
#define BOOTSIG1        0xaa
#define BOOTSIG2        0x00
#define BOOTSIG3        0x00
};

	
struct bpb710{
		WORD	bpbBytesPerSec;	// bytes per sector
		BYTE	bpbSecPerClust;	// sectors per cluster
		WORD	bpbResSectors;	// number of reserved sectors
		BYTE	bpbFATs;		// number of FATs
		WORD	bpbRootDirEnts;	// number of root directory entries
		WORD	bpbSectors;		// total number of sectors
		BYTE	bpbMedia;		// media descriptor
		WORD	bpbFATsecs;		// number of sectors per FAT
		WORD	bpbSecPerTrack;	// sectors per track
		WORD	bpbHeads;		// number of heads
		DWORD	bpbHiddenSecs;	// # of hidden sectors
// 3.3 compat ends here
		DWORD	bpbHugeSectors;	// # of sectors if bpbSectors == 0
// 5.0 compat ends here
		DWORD     bpbBigFATsecs;// like bpbFATsecs for FAT32
		WORD      bpbExtFlags;	// extended flags:
#define FATNUM    0xf			// mask for numbering active FAT
#define FATMIRROR 0x80			// FAT is mirrored (like it always was)
		WORD      bpbFSVers;	// filesystem version
#define FSVERS    0				// currently only 0 is understood
		DWORD     bpbRootClust;	// start cluster for root directory
		WORD      bpbFSInfo;	// filesystem info structure sector
		WORD      bpbBackup;	// backup boot sector
		// There is a 12 byte filler here, but we ignore it
} __attribute__((__packed__))   ;

struct   partrecord// length 16 bytes
{			
	BYTE	prIsActive;					// 0x80 indicates active partition
	BYTE	prStartHead;				// starting head for partition
	WORD	prStartCylSect;				// starting cylinder and sector
	BYTE	prPartType;					// partition type (see above)
	BYTE	prEndHead;					// ending head for this partition
	WORD	prEndCylSect;				// ending cylinder and sector
	DWORD	prStartLBA;					// first LBA sector for this partition
	DWORD	prSize;						// size of this partition (bytes or sectors ?)
} __attribute__((__packed__)) ;

struct partsector
{
	char	psPartCode[446];		// pad so struct is 512b
	BYTE	psPart[64];					// four partition records (64 bytes)
	BYTE	psBootSectSig0;				// two signature bytes (2 bytes)
	BYTE	psBootSectSig1;
#define BOOTSIG0        0x55
#define BOOTSIG1        0xaa
};

struct FileInfoStruct
{
	DWORD StartCluster;			//< file starting cluster for last file accessed
	DWORD Size;					//< file size for last file accessed
	DWORD Attr;					//< file attr for last file accessed
	//unsigned short CreateTime;			//< file creation time for last file accessed
	//unsigned short CreateDate;			//< file creation date for last file accessed
	DWORD Sector;				//<file record place
	DWORD Offset;				//<file record offset
};

// Structure of a dos directory entry.
struct direntry {
		BYTE		deName[8];      	// filename, blank filled
#define SLOT_EMPTY      0x00            // slot has never been used
#define SLOT_E5         0x05            // the real value is 0xE5
#define SLOT_DELETED    0xE5            // file in this slot deleted
#define SLOT_DIR		0x2E			// a directorymmm
		BYTE		deExtension[3]; 	// extension, blank filled
		BYTE		deAttributes;   	// file attributes
#define ATTR_NORMAL     0x00            // normal file
#define ATTR_READONLY   0x01            // file is readonly
#define ATTR_HIDDEN     0x02            // file is hidden
#define ATTR_SYSTEM     0x04            // file is a system file
#define ATTR_VOLUME     0x08            // entry is a volume label
#define ATTR_LONG_FILENAME	0x0F		// this is a long filename entry			    
#define ATTR_DIRECTORY  0x10            // entry is a directory name
#define ATTR_ARCHIVE    0x20            // file is new or modified
		BYTE        deLowerCase;    	// NT VFAT lower case flags  (set to zero)
#define LCASE_BASE      0x08            // filename base in lower case
#define LCASE_EXT       0x10            // filename extension in lower case
		BYTE        deCHundredth;   	// hundredth of seconds in CTime
		BYTE        deCTime[2];     	// create time
		BYTE        deCDate[2];     	// create date
		BYTE        deADate[2];     	// access date
		WORD        deHighClust; 		// high bytes of cluster number
		BYTE        deMTime[2];     	// last update time
		BYTE        deMDate[2];     	// last update date
		WORD        deStartCluster; 	// starting cluster of file
		DWORD       deFileSize;  		// size of file in bytes
};


extern DWORD MMC_SD_ReadCapacity();

extern U8 Rd_Block(U32 addr,U8* buffer);

extern BYTE FAT_LoadPartCluster(DWORD cluster,unsigned part,BYTE * buffer);//加载文件
//extern DWORD FAT_NextCluster_NEW(DWORD cluster);//fit system which has large ram
//FAT原有的函数
extern unsigned char FAT_Init(void);//初始化
extern DWORD FAT_NextCluster(DWORD cluster);//查找下一簇号
extern unsigned long FAT_FindFreeCluster(void);//查找空簇
extern unsigned char FAT_DisDir(BYTE *dir);//显示目录内容
extern WORD FAT_FindItem(DWORD cluster, BYTE *name, struct FileInfoStruct *FileInfo);//查找文件
extern DWORD FAT_Open(BYTE * dir);//打开文件
extern DWORD FAT_OpenDir(BYTE * dir);//打开目录
extern unsigned char FAT_Read(DWORD pointer, DWORD size);//读文件，size=0代表整个文件
extern unsigned char FAT_Rename(BYTE *dir,BYTE *newname);//重命名
extern unsigned char FAT_ModifyFAT(DWORD cluster,DWORD val);//修改FAT项
extern unsigned char FAT_Delete(BYTE *dir);//删除文件
extern unsigned char FAT_DelItem(struct FileInfoStruct *FileInfo);//删除记录项
extern WORD FAT_FindFreeItem(DWORD cluster, struct FileInfoStruct *FileInfo);//查找空余项
extern unsigned char FAT_MkDir(BYTE * dir);//建目录
extern unsigned char FAT_Write(DWORD cluster,unsigned char *data,DWORD size);//写文件
extern DWORD FAT_Create(BYTE * dir,DWORD size);//建文件，必须指定文件大小
extern unsigned char FAT_RmDir(BYTE * dir);//删除目录
extern WORD FAT_Close(DWORD * p);//关闭文件
extern unsigned char FAT_GetFile(BYTE *dir,struct FileInfoStruct *FileInfo);//获取指定目录下的文件信息
extern DWORD FAT_OpenFile(char *dir,struct FileInfoStruct *File_Info);//1=失败.//打开指定路径的文件,输出文件信息并返回文件的首簇.
extern BYTE FAT_DirLoadFile(char *dir,BYTE *Buf); //0=失败;1=成功.//通过目录加载文件到缓冲
extern BYTE FAT_ClusterLoadFile(DWORD cluster,BYTE *Buf);//0=失败;1=成功.//通过簇加载整个文件到Buf.
extern int FAT_RunFile(char *ini_dir); 
