#pragma once

#define D3DXVECTOR3 VECTOR3
#define D3DXMATRIXA16 MATRIX16
#define D3DCOLOR_XRGB qfqfqfqf

//�����͸� delete�� �ƴ� release�� ���ش�
#define SAFE_RELEASE(p) {if(p) p->Release();p=NULL;}
//COM��ü�� �ƴѰ� Ȯ���� ���� ���
#define SAFE_DELETE(p) {if(p) delete p; p=NULL;}

//�̱��� ����
#define SINGLETON(class_name)								\
				private:															\
					class_name(void);										\
					~class_name(void);									\
				public :															\
					static class_name* GetInstance()				\
					{																\
						static class_name instance;					\
						return &instance;									\
					}