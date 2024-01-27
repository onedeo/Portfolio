#pragma once

#define D3DXVECTOR3 VECTOR3
#define D3DXMATRIXA16 MATRIX16
#define D3DCOLOR_XRGB qfqfqfqf

//포인터를 delete가 아닌 release를 해준다
#define SAFE_RELEASE(p) {if(p) p->Release();p=NULL;}
//COM객체가 아닌게 확실할 때만 사용
#define SAFE_DELETE(p) {if(p) delete p; p=NULL;}

//싱글톤 정의
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