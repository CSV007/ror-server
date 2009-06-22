#ifndef SCRIPTENGINE_H__
#define SCRIPTENGINE_H__

#include <string>
#include "angelscript.h"

class ExampleFrameListener;
class GameScript;
class Beam;
class Sequencer;

class ScriptEngine
{
public:
	ScriptEngine(Sequencer *seq);
	~ScriptEngine();

	int loadScript(std::string scriptName);
	void executeString(std::string command);

	asIScriptEngine *getEngine() { return engine; };

protected:
    Sequencer *seq;
    asIScriptEngine *engine;                //!< instance of the scripting engine
	asIScriptContext *context;              //!< context in which all scripting happens
	int frameStepFunctionPtr;               //!< script function pointer to the frameStep function
	int eventCallbackFunctionPtr;           //!< script function pointer to the event callback function

	/**
	 * This function initialzies the engine and registeres all types
	 */
    void init();
    
	/**
	 * This is the callback function that gets called when script error occur.
	 * When the script crashes, this function will provide you with more detail
	 * @param msg arguments that contain details about the crash
	 * @param param unkown?
	 */
    void msgCallback(const asSMessageInfo *msg);

	/**
	 * This function reads a file into the provided string.
	 * @param filename filename of the file that should be loaded into the script string
	 * @param script reference to a string where the contents of the file is written to
	 * @return 0 on success, everything else on error
	 */
	int loadScriptFile(const char *fileName, std::string &script);

	// undocumented debugging functions below, not working.
	void ExceptionCallback(asIScriptContext *ctx, void *param);
	void PrintVariables(asIScriptContext *ctx, int stackLevel);
	void LineCallback(asIScriptContext *ctx, void *param);
};

#endif //SCRIPTENGINE_H__