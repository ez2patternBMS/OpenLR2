#pragma once

#include "LR2_customir_api.h"

#include <array>
#include <filesystem>
#include <future>
#include <memory>
#include <string>
#include <type_traits>

#include <wtypes.h>

struct game;
struct sqlite3;

class CustomIR {
public:
	CustomIR() = delete;
	CustomIR(const std::filesystem::path& directory);
	bool Initialize();
	bool Login();
	SendScoreStatus SendScore(const IRScoreV1& score);

	[[nodiscard]] const std::string& Name() const { return mName; };
private:
	struct ModuleDeleter {
		void operator()(std::remove_pointer_t<HMODULE>* handle);
	};
	std::unique_ptr<std::remove_pointer_t<HMODULE>, ModuleDeleter> mDllHandle;
	std::string mName;
	MethodTable mMethods;
};

class CUSTOMIR_MANAGER {
public:
	CUSTOMIR_MANAGER() = default;
	CUSTOMIR_MANAGER operator=(const CUSTOMIR_MANAGER&) = delete;
	CUSTOMIR_MANAGER(const CUSTOMIR_MANAGER&) = delete;
	CUSTOMIR_MANAGER operator=(CUSTOMIR_MANAGER&&) = delete;
	CUSTOMIR_MANAGER(CUSTOMIR_MANAGER&&) = delete;
	~CUSTOMIR_MANAGER();
	void Initialize(const std::filesystem::path& directory);
	void Login();
	void SendScore(game& game, sqlite3* sql, int player);
private:
	std::vector<std::shared_ptr<CustomIR>> mModules;
	std::vector<std::future<void>> mSendThreads;
};
