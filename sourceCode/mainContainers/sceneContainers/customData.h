#pragma once

#include <ser.h>
#include <cbor.h>

struct SCustomData
{
    std::string tag;
    std::string data;
};

class CCustomData
{
  public:
    CCustomData();
    virtual ~CCustomData();

    bool setData(const char *tag, const char *data, size_t dataLen);
    std::string getData(const char *tag) const;
    void getDataEvents(std::map<std::string, bool> &dataEvents); // different from below cbor events
    void clearDataEvents(); // different from below cbor events
    std::string getAllTags(size_t *cnt) const;
    size_t getDataCount() const;
    void copyYourselfInto(CCustomData &theCopy) const;
    void serializeData(CSer &ar, const char *objectName);
    void appendEventData(CCbor *ev) const;

  protected:
    std::vector<SCustomData> _data;
    std::map<std::string, bool> _dataEvents; // tag, true=present, false=absent. Different from above cbor events
};
