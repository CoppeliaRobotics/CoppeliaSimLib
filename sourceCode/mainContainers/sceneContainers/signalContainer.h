#pragma once

class CSignalContainer
{
  public:
    CSignalContainer();
    virtual ~CSignalContainer();

    void simulationEnded();
    void announceScriptStateWillBeErased(int scriptHandle, bool simulationScript, bool sceneSwitchPersistentScript);

    void setIntegerSignal(const char *signalName, int value, int creatorHandle);
    bool getIntegerSignal(const char *signalName, int &value);
    bool getIntegerSignalNameAtIndex(int index, std::string &signalName);
    int clearIntegerSignal(const char *signalName);
    int clearAllIntegerSignals();

    void setFloatSignal(const char *signalName, double value, int creatorHandle);
    bool getFloatSignal(const char *signalName, double &value);
    bool getFloatSignalNameAtIndex(int index, std::string &signalName);
    int clearFloatSignal(const char *signalName);
    int clearAllFloatSignals();

    void setStringSignal(const char *signalName, const std::string &value, int creatorHandle);
    bool getStringSignal(const char *signalName, std::string &value);
    bool getStringSignalNameAtIndex(int index, std::string &signalName);
    int clearStringSignal(const char *signalName);
    int clearAllStringSignals();

    // Old, deprecated:
    void setDoubleSignal_old(const char *signalName, double value, int creatorHandle);
    bool getDoubleSignal_old(const char *signalName, double &value);
    bool getDoubleSignalNameAtIndex_old(int index, std::string &signalName);
    int clearDoubleSignal_old(const char *signalName);
    int clearAllDoubleSignals_old();

  protected:
    int _getIntegerSignalIndex(const char *signalName);
    int _getFloatSignalIndex(const char *signalName);
    int _getStringSignalIndex(const char *signalName);

    std::vector<std::string> _intSignalNames;
    std::vector<int> _intSignalValues;
    std::vector<int> _intSignalCreatorHandles;

    std::vector<std::string> _floatSignalNames;
    std::vector<double> _floatSignalValues;
    std::vector<int> _floatSignalCreatorHandles;

    std::vector<std::string> _stringSignalNames;
    std::vector<std::string> _stringSignalValues;
    std::vector<int> _stringSignalCreatorHandles;

    // Old, deprecated:
    int _getDoubleSignalIndex_old(const char *signalName);
    std::vector<std::string> _doubleSignalNames_old;
    std::vector<double> _doubleSignalValues_old;
    std::vector<int> _doubleSignalCreatorHandles_old;
};
