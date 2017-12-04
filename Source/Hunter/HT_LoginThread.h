#include "HT_GameInstance.h"
#include "Runtime/Core/Public/HAL/Runnable.h"

class HUNTER_API FHT_LoginThread : public FRunnable
{
private:
	static FHT_LoginThread* Runnable;
	FRunnableThread* Thread;

	FThreadSafeCounter StopTaskCounter;
	class UHT_GameInstance* GameInstance;

private:
	MemberInfo LoginInfo;

public:
	bool IsComplete = false;
	bool IsInit = false;
	bool IsSuccess = false;

public:
	FHT_LoginThread();
	virtual ~FHT_LoginThread();

public:
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;

	void EnsureCompletion();

public:
	HRESULT JoyInit(MemberInfo Info, UHT_GameInstance* Game_Instance);
	void Shutdown();

	static FHT_LoginThread* GetInstance();
};
