#pragma once

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

#define SYNTHESIZE(varType, varName, funName) \
         protected : varType varName; \
         public: inline varType Get##funName(void) const { return varName; } \
            public : inline void Set##funName(varType var) {varName = var; } 

#define SYNTHESIZE_PASS_BY_REF (varType, varName, funName)							\
					protected : varType varName;																	\
					public: inline varType& Get##funName	(void) {return varName;}			\
					public: inline void Set##funName(varName var) { varName = var; }	
	//##�ϸ� �Լ� �̸��� funName���� �ȴ�
