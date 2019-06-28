#include "IOCPServer.h"



bool Server::_PostAccept()
{
	return false;
}

// ��ʼ��Socket
bool Server::_InitializeListenSocket()
{
	// AcceptEx �� GetAcceptExSockaddrs ��GUID�����ڵ�������ָ��
	GUID GuidAcceptEx = WSAID_ACCEPTEX;
	GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;
	// ��������ַ��Ϣ�����ڰ�Socket
	struct sockaddr_in ServerAddress;

	// �������ڼ�����Socket����Ϣ
	listensocket = new _PER_SOCKET_CONTEXT;
	listensocket->m_Socket = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	// ����ַ��Ϣ
	ZeroMemory((char*)& ServerAddress, sizeof(ServerAddress));
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(9999);
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	if (NULL == CreateIoCompletionPort((HANDLE)listensocket->m_Socket, m_hIOCompletionPort, listensocket->m_Socket, 0)) {
		printf("");
	}
	//��һ���˿�
	bind(listensocket->m_Socket, (struct sockaddr*) & ServerAddress, sizeof(ServerAddress));
	//���м���
	listen(listensocket->m_Socket, SOMAXCONN);
	//����10��socket 
	for (int i = 0; i < 10; i++) {
		DWORD dwBytes = 0;
		_PER_IO_CONTEXT* pAccpectIoContext = new _PER_IO_CONTEXT;
		pAccpectIoContext->m_OpType = ACCEPT_POSTED;
		OVERLAPPED* p_ol = &pAccpectIoContext->m_Overlapped;
		WSABUF* p_wbuf = &pAccpectIoContext->m_wsaBuf;
		pAccpectIoContext->m_sockAccept = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (FALSE == AcceptEx(listensocket->m_Socket, pAccpectIoContext->m_sockAccept, p_wbuf->buf, p_wbuf->len - ((sizeof(SOCKADDR_IN) + 16) * 2),
			sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, &dwBytes, p_ol)) {


		}
		
	}
	return true;
}

bool Server::_InitializeIOCP()
{
	m_hIOCompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (NULL == m_hIOCompletionPort) {
		return false;
	}

	return true;
}

void Server::start()
{
	if (_InitializeIOCP() == FALSE) {

	}
	if (_InitializeListenSocket() == FALSE) {

	}
	while (  WAIT_OBJECT_0 != WaitForSingleObject(m_hShutdownEvent ,0 ))
	{
		DWORD dwNumberofBytes;
		ULONG_PTR completion_KEY;
		_PER_IO_CONTEXT*ol;
		BOOL beReturn = GetQueuedCompletionStatus(
			m_hIOCompletionPort , &dwNumberofBytes , &completion_KEY , (LPOVERLAPPED*)&ol , 10
		);
		if (beReturn){
			if (completion_KEY) {
				if (ol->m_OpType == ACCEPT_POSTED) {
					GetAcceptExSockaddrs();
				}else if (ol->m_OpType == RECV_POSTED ){

				}
			}
		}
		else {
			printf("error");
		}
	}

}
