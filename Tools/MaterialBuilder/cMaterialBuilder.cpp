#include "cMaterialBuilder.h"
#include "Tools/AssetBuildLibrary/Functions.h"
#include <External/Lua/Includes.h>

namespace
{
	std::string m_EffectLocation;
	uint8_t m_ConstantType;
	std::string m_ConstantName;
	std::vector<uint8_t> m_ConstantData;
	std::string m_TextureLocation;
}


eae6320::cResult LoadTableValues(lua_State& i_LuaState)
{
	auto result = eae6320::Results::Success;
	const auto* const key = "Effect";
	lua_pushstring(&i_LuaState, key);
	lua_gettable(&i_LuaState, -2);
	if (lua_istable(&i_LuaState, -1))
	{
		auto* key2 = "EffectLocation";
		lua_pushstring(&i_LuaState, key2);
		lua_gettable(&i_LuaState, -2);
		if (lua_isstring(&i_LuaState, -1))
		{
			m_EffectLocation = lua_tostring(&i_LuaState, -1);
		}
		lua_pop(&i_LuaState, -1);

		key2 = "ConstantType";
		lua_pushstring(&i_LuaState, key2);
		lua_gettable(&i_LuaState, -2);
		if (lua_isstring(&i_LuaState, -1))
		{
			std::string tempConstType = lua_tostring(&i_LuaState, -1);
			if (tempConstType == "float")
			{
				m_ConstantType = 0;
			}
			else if (tempConstType == "float2")
			{
				m_ConstantType = 1;
			}
			else if(tempConstType == "float3")
			{
				m_ConstantType = 2;
			}
			else if(tempConstType == "float4")
			{
				m_ConstantType = 3;
			}
			else if(tempConstType =="float4x4")
			{
				m_ConstantType = 4;
			}
		}
		lua_pop(&i_LuaState, -1);

		key2 = "ConstantName";
		lua_pushstring(&i_LuaState, key2);
		lua_gettable(&i_LuaState, -2);
		if (lua_isstring(&i_LuaState, -1))
		{
			m_ConstantName = lua_tostring(&i_LuaState, -1);
		}
		lua_pop(&i_LuaState, -1);

		key2 = "ConstantValue";
		lua_pushstring(&i_LuaState, key2);
		lua_gettable(&i_LuaState, -2);
		if (lua_istable(&i_LuaState, -1))
		{
			lua_pushnil(&i_LuaState);
			while (lua_next(&i_LuaState, -2))
			{
				m_ConstantData.push_back(lua_tonumber(&i_LuaState, -1));
			}
			lua_pop(&i_LuaState, -1);
		}
		lua_pop(&i_LuaState, -1);

		key2 = "TextureLocation";
		lua_pushstring(&i_LuaState, key2);
		lua_gettable(&i_LuaState, -2);
		if (lua_isstring(&i_LuaState, -1))
		{
			m_TextureLocation = lua_tostring(&i_LuaState, -1);
		}
		lua_pop(&i_LuaState, -1);
		lua_pop(&i_LuaState, -1);
	}
	return result;
}

eae6320::cResult LoadFile(const char* const i_FileName)
{
	eae6320::cResult result = eae6320::Results::Success;

	lua_State* luaState = nullptr;
	{
		luaState = luaL_newstate();
		if (!luaState)
		{
			return result = eae6320::Results::OutOfMemory;
		}
	}

	const auto stackTopBeforeLoad = lua_gettop(luaState);
	{
		const auto luaResult = luaL_loadfile(luaState, i_FileName);
		if (luaResult != LUA_OK)
		{
			result = eae6320::Results::Failure;
			// Pop the error message
			lua_pop(luaState, 1);
			return result;
		}
	}

	{
		constexpr int argumentCount = 0;
		constexpr int returnValueCount = LUA_MULTRET;	// Return _everything_ that the file returns
		constexpr int noMessageHandler = 0;
		const auto luaResult = lua_pcall(luaState, argumentCount, returnValueCount, noMessageHandler);
		if (luaResult == LUA_OK)
		{
			// A well-behaved asset file will only return a single value
			const auto returnedValueCount = lua_gettop(luaState) - stackTopBeforeLoad;
			if (returnedValueCount == 1)
			{
				// A correct asset file _must_ return a table
				if (!lua_istable(luaState, -1))
				{
					result = eae6320::Results::InvalidFile;
					// Pop the returned non-table value
					lua_pop(luaState, 1);
				}
			}
			else
			{
				result = eae6320::Results::InvalidFile;
				std::string err = "Asset files must return a single table (instead of " + returnedValueCount;
				eae6320::Assets::OutputErrorMessage(err.c_str());
				// Pop every value that was returned
				lua_pop(luaState, returnedValueCount);
			}
		}
		else
		{
			result = eae6320::Results::InvalidFile;
			eae6320::Assets::OutputErrorMessage(lua_tostring(luaState, -1));
			// Pop the error message
			lua_pop(luaState, 1);
		}
	}

	result = LoadTableValues(*luaState);
	return result;

}


eae6320::cResult eae6320::Assets::cMaterialBuilder::Build(const std::vector<std::string>& i_arguments)
{
	cResult result = Results::Success;
	std::string m_errorString;
	result = LoadFile(m_path_source);

	if (!result) { OutputErrorMessageWithFileInfo(m_path_source, "Error Reading file"); }
	//Writing to file
	FILE * fptr;
	fptr = fopen(m_path_target, "w+b");
	fclose(fptr);
	return result;
}