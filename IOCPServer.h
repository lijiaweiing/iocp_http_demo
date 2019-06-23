#include <winsock2.h>
#include <MSWSock.h>
#include<Windows.h>
#include<vector>
#pragma comment(lib,"ws2_32.lib")
typedef enum _OPERATION_TYPE
{
	ACCEPT_POSTED,                     // ��־Ͷ�ݵ�Accept����
	SEND_POSTED,                       // ��־Ͷ�ݵ��Ƿ��Ͳ���
	RECV_POSTED,                       // ��־Ͷ�ݵ��ǽ��ղ���
	NULL_POSTED                        // ���ڳ�ʼ����������

}OPERATION_TYPE;
typedef struct _PER_IO_CONTEXT
{
	// ÿһ���ص�����������ص��ṹ(���ÿһ��Socket��ÿһ����������Ҫ��һ��)              
	OVERLAPPED     m_Overlapped;
	// ������������ʹ�õ�Socket
	SOCKET         m_sockAccept;
	// WSA���͵Ļ����������ڸ��ص�������������
	WSABUF         m_wsaBuf;
	// �����WSABUF�������ַ��Ļ�����
	//char           m_szBuffer[MAX_BUFFER_LEN];
	// ��ʶ�������������(��Ӧ�����ö��)
	OPERATION_TYPE m_OpType;
};

typedef struct _PER_SOCKET_CONTEXT
{
	// ÿһ���ͻ������ӵ�Socket
	SOCKET      m_Socket;
	// �ͻ��˵ĵ�ַ
	SOCKADDR_IN m_ClientAddr;
};
class Server {
private:
	HANDLE* m_phWorkerThreads;             // �������̵߳ľ��ָ��
	int		m_nThreads;                    // ���ɵ��߳�����
	HANDLE m_hIOCompletionPort;
	_PER_SOCKET_CONTEXT *listensocket;
private:
	bool _InitializeListenSocket();
	bool _InitializeIOCP();
public:
	void start();
};