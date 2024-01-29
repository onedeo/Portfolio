#pragma once

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

#define SYNTHESIZE(varType, varName, funName) \
         protected : varType varName; \
         public: inline varType Get##funName(void) const { return varName; } \
            public : inline void Set##funName(varType var) {varName = var; } 

#define SYNTHESIZE_PASS_BY_REF (varType, varName, funName)							\
					protected : varType varName;																	\
					public: inline varType& Get##funName	(void) {return varName;}			\
					public: inline void Set##funName(varName var) { varName = var; }	
	//##하면 함수 이름이 funName으로 된다
