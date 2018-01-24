#ifndef STARTUP_HPP_
#define STARTUP_HPP_

#include "AModule.hpp"

class Startup : public AModule {

public:
    Startup();
    Startup(const Startup &obj);
    Startup &operator=(const Startup &obj);
    ~Startup();

    virtual void setup();
	virtual void update();
	virtual void uninstall();

    bool checkStartup() const;

private:
	BOOL _registerStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args);
	BOOL _unregisterStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args);
    BOOL _checkStartup(PCWSTR pszAppName) const;

};

#endif /* STARTUP_HPP_ */
