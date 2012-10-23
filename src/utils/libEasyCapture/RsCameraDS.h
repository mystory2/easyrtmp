#ifndef ROSOO_DIRECTSHOW_CAMERA_H
#define ROSOO_DIRECTSHOW_CAMERA_H

#define WIN32_LEAN_AND_MEAN

#include <atlbase.h>
#include "qedit.h"
#include "dshow.h"
#include <windows.h>

#include <rscommon.h>

#ifdef _JACKY_USING_OPENCV_
#include <cxcore.h>
#endif

#define MYFREEMEDIATYPE(mt)	{if ((mt).cbFormat != 0)		\
					{CoTaskMemFree((PVOID)(mt).pbFormat);	\
					(mt).cbFormat = 0;						\
					(mt).pbFormat = NULL;					\
				}											\
				if ((mt).pUnk != NULL)						\
				{											\
					(mt).pUnk->Release();					\
					(mt).pUnk = NULL;						\
				}}									

/*
#ifdef LIBEASYCAPTURE_EXPORTS
#	define LIBEASYCAPTURE_API __declspec(dllexport)
#else
#	define LIBEASYCAPTURE_API __declspec(dllimport)
#endif
*/

class CRsCameraDS
{
private:
#ifdef _JACKY_USING_OPENCV_
	IplImage * m_pFrame;
#else
	BYTE*		m_pFrame;
#endif
	BOOL_ m_bConnected;
	int m_nWidth;
	int m_nHeight;
	BOOL_ m_bLock;
	BOOL_ m_bChanged;
	long m_nBufferSize;

	CComPtr<IGraphBuilder> m_pGraph;
	CComPtr<IBaseFilter> m_pDeviceFilter;
	CComPtr<IMediaControl> m_pMediaControl;
	CComPtr<IBaseFilter> m_pSampleGrabberFilter;
	CComPtr<ISampleGrabber> m_pSampleGrabber;
	CComPtr<IPin> m_pGrabberInput;
	CComPtr<IPin> m_pGrabberOutput;
	CComPtr<IPin> m_pCameraOutput;
	CComPtr<IMediaEvent> m_pMediaEvent;
	CComPtr<IBaseFilter> m_pNullFilter;
	CComPtr<IPin> m_pNullInputPin;

private:
	BOOL_ BindFilter(int nCamIDX, IBaseFilter **pFilter);
	void SetCrossBar();

public:
	CRsCameraDS();
	virtual ~CRsCameraDS();

	//������ͷ��nCamIDָ�����ĸ�����ͷ��ȡֵ����Ϊ0,1,2,...
	//bDisplayPropertiesָʾ�Ƿ��Զ���������ͷ����ҳ
	//nWidth��nHeight���õ�����ͷ�Ŀ�͸ߣ��������ͷ��֧�����趨�Ŀ�Ⱥ͸߶ȣ��򷵻�FALSE_
	BOOL_ CRsCameraDS::OpenCamera(int nCamID, int nWidth, int nHeight, int nFPS, BOOL_ bDisplayProperties);

	//�ر�����ͷ�������������Զ������������
	void CloseCamera();

	//��������ͷ����Ŀ
	//���Բ��ô���CRsCameraDSʵ��������int c=CRsCameraDS::CameraCount();�õ������
	static int CameraCount(); 

	//��������ͷ�ı�ŷ�������ͷ������
	//nCamID: ����ͷ���
	//sName: ���ڴ������ͷ���ֵ�����
	//nBufferSize: sName�Ĵ�С
	//���Բ��ô���CRsCameraDSʵ��������CRsCameraDS::CameraName();�õ������
	static int CRsCameraDS::CameraName(int nCamID, char* sName, int nBufferSize);

	//����ͼ����
	int GetWidth(){return m_nWidth;} 

	//����ͼ��߶�
	int GetHeight(){return m_nHeight;}

	//ץȡһ֡�����ص�IplImage�����ֶ��ͷţ�
	//����ͼ�����ݵ�ΪRGBģʽ��Top-down(��һ���ֽ�Ϊ���Ͻ�����)����IplImage::origin=0(IPL_ORIGIN_TL)
#ifdef _JACKY_USING_OPENCV_
	IplImage * QueryFrame();
#else
	BYTE* QueryFrame();
#endif
};

#endif //ROSOO_DIRECTSHOW_CAMERA_H

