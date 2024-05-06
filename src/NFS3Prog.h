#ifndef _NFS3PROG_H_
#define _NFS3PROG_H_

#include "RPCProg.h"
#include <string>
#include <windows.h>
#include <unordered_map>

typedef unsigned __int64 uint64;
typedef unsigned long uint32;
typedef long int32;
typedef uint32 uid3_32;
typedef uint32 gid3_32;
typedef uint32 mode3_32;
typedef uint32 count3_32;
typedef uint32 nfsstat3_32;
typedef uint32 ftype3_32;
typedef uint32 stable_how_32;
typedef uint32 time_how_32;
typedef uint32 createmode3_32;

typedef uint64 fileid3_64;
typedef uint64 cookie3_64;
typedef uint64 size3_64;
typedef uint64 offset3_64;
typedef uint64 cookieverf3_64;
typedef uint64 createverf3_64;
typedef uint64 writeverf3_64;

class opaque
{
public:
	uint32 length;
	unsigned char* contents;

	opaque();
	opaque(uint32 len);
	virtual ~opaque();
	virtual void SetSize(uint32 len);
};

class nfs_fh3 : public opaque
{
public:
	nfs_fh3();
	~nfs_fh3();
};

class filename3 : public opaque
{
public:
	char* name;

	filename3();
	~filename3();
	void SetSize(uint32 len);
	void Set(char* str);
};

class nfspath3 : public opaque
{
public:
	char* path;

	nfspath3();
	~nfspath3();
	void SetSize(uint32 len);
	void Set(char* str);
};

struct specdata3
{
	uint32 specdata1;
	uint32 specdata2;
};

struct nfstime3
{
	uint32 seconds;
	uint32 nseconds;
};

struct sattrguard3
{
	bool check;
	nfstime3 obj_ctime;
};

struct fattr3
{
	ftype3_32 type;
	mode3_32 mode;
	uint32 nlink;
	uid3_32 uid;
	gid3_32 gid;
	size3_64 size;
	size3_64 used;
	specdata3 rdev;
	uint64 fsid;
	fileid3_64 fileid;
	nfstime3 atime;
	nfstime3 mtime;
	nfstime3 ctime;
};

struct post_op_attr
{
	bool attributes_follow;
	fattr3 attributes;
};

struct wcc_attr
{
	size3_64 size;
	nfstime3 mtime;
	nfstime3 ctime;
};

struct pre_op_attr
{
	bool attributes_follow;
	wcc_attr attributes;
};

struct wcc_data
{
	pre_op_attr before;
	post_op_attr after;
};

struct post_op_fh3
{
	bool handle_follows;
	nfs_fh3 handle;
};

struct set_mode3
{
	bool set_it;
	mode3_32 mode;
};

struct set_uid3
{
	bool set_it;
	uid3_32 uid;
};

struct set_gid3
{
	bool set_it;
	gid3_32 gid;
};

struct set_size3
{
	bool set_it;
	size3_64 size;
};

struct set_atime
{
	time_how_32 set_it;
	nfstime3 atime;
};

struct set_mtime
{
	time_how_32 set_it;
	nfstime3 mtime;
};

struct sattr3
{
	set_mode3 mode;
	set_uid3 uid;
	set_gid3 gid;
	set_size3 size;
	set_atime atime;
	set_mtime mtime;
};

struct diropargs3
{
	nfs_fh3 dir;
	filename3 name;
};

struct createhow3
{
	createmode3_32 mode;
	sattr3 obj_attributes;
	createverf3_64 verf;
};

struct symlinkdata3
{
	sattr3 symlink_attributes;
	nfspath3 symlink_data;
};

typedef struct _REPARSE_DATA_BUFFER {
	ULONG  ReparseTag;
	USHORT ReparseDataLength;
	USHORT Reserved;
	union {
		struct {
			USHORT SubstituteNameOffset;
			USHORT SubstituteNameLength;
			USHORT PrintNameOffset;
			USHORT PrintNameLength;
			ULONG  Flags;
			WCHAR  PathBuffer[1];
		} SymbolicLinkReparseBuffer;
		struct {
			USHORT SubstituteNameOffset;
			USHORT SubstituteNameLength;
			USHORT PrintNameOffset;
			USHORT PrintNameLength;
			WCHAR  PathBuffer[1];
		} MountPointReparseBuffer;
		struct {
			UCHAR DataBuffer[1];
		} GenericReparseBuffer;
	};
} REPARSE_DATA_BUFFER, * PREPARSE_DATA_BUFFER;

class CNFS3Prog : public CRPCProg
{
public:
	CNFS3Prog();
	~CNFS3Prog();
	void SetUserID(unsigned int nUID, unsigned int nGID);
	int Process(IInputStream* pInStream, IOutputStream* pOutStream, ProcessParam* pParam);

protected:
	unsigned long m_nUID, m_nGID;
	IInputStream* m_pInStream;
	IOutputStream* m_pOutStream;
	ProcessParam* m_pParam;

	nfsstat3_32 ProcedureNULL(void);
	nfsstat3_32 ProcedureGETATTR(void);
	nfsstat3_32 ProcedureSETATTR(void);
	nfsstat3_32 ProcedureLOOKUP(void);
	nfsstat3_32 ProcedureACCESS(void);
	nfsstat3_32 ProcedureREADLINK(void);
	nfsstat3_32 ProcedureREAD(void);
	nfsstat3_32 ProcedureWRITE(void);
	nfsstat3_32 ProcedureCREATE(void);
	nfsstat3_32 ProcedureMKDIR(void);
	nfsstat3_32 ProcedureSYMLINK(void);
	nfsstat3_32 ProcedureMKNOD(void);
	nfsstat3_32 ProcedureREMOVE(void);
	nfsstat3_32 ProcedureRMDIR(void);
	nfsstat3_32 ProcedureRENAME(void);
	nfsstat3_32 ProcedureLINK(void);
	nfsstat3_32 ProcedureREADDIR(void);
	nfsstat3_32 ProcedureREADDIRPLUS(void);
	nfsstat3_32 ProcedureFSSTAT(void);
	nfsstat3_32 ProcedureFSINFO(void);
	nfsstat3_32 ProcedurePATHCONF(void);
	nfsstat3_32 ProcedureCOMMIT(void);
	nfsstat3_32 ProcedureNOIMP(void);

	void Read(bool* pBool);
	void Read(uint32* pUint32);
	void Read(uint64* pUint64);
	void Read(sattr3* pAttr);
	void Read(sattrguard3* pGuard);
	void Read(diropargs3* pDir);
	void Read(opaque* pOpaque);
	void Read(nfstime3* pTime);
	void Read(createhow3* pHow);
	void Read(symlinkdata3* pSymlink);
	void Write(bool* pBool);
	void Write(uint32* pUint32);
	void Write(uint64* pUint64);
	void Write(fattr3* pAttr);
	void Write(opaque* pOpaque);
	void Write(wcc_data* pWcc);
	void Write(post_op_attr* pAttr);
	void Write(pre_op_attr* pAttr);
	void Write(post_op_fh3* pObj);
	void Write(nfstime3* pTime);
	void Write(specdata3* pSpec);
	void Write(wcc_attr* pAttr);

private:
	int m_nResult;

	bool GetPath(std::string& path);
	bool ReadDirectory(std::string& dirName, std::string& fileName);
	char* GetFullPath(std::string& dirName, std::string& fileName);
	nfsstat3_32 CheckFile(const char* fullPath);
	nfsstat3_32 CheckFile(const char* directory, const char* fullPath);
	bool GetFileHandle(const char* path, nfs_fh3* pObject);
	bool GetFileAttributesForNFS(const char* path, wcc_attr* pAttr);
	bool GetFileAttributesForNFS(const char* path, fattr3* pAttr);
	UINT32 FileTimeToPOSIX(FILETIME ft);
	std::unordered_map<int, FILE*> unstableStorageFile;
};

#endif
