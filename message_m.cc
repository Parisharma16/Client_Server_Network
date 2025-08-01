//
// Generated file, do not edit! Created by opp_msgtool 6.1 from message.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "message_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(SubtaskRequest)

SubtaskRequest::SubtaskRequest(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SubtaskRequest::SubtaskRequest(const SubtaskRequest& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SubtaskRequest::~SubtaskRequest()
{
}

SubtaskRequest& SubtaskRequest::operator=(const SubtaskRequest& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SubtaskRequest::copy(const SubtaskRequest& other)
{
    this->subtaskID = other.subtaskID;
    this->subtaskArr = other.subtaskArr;
    this->serverID = other.serverID;
    this->isMalicious_ = other.isMalicious_;
}

void SubtaskRequest::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->subtaskID);
    doParsimPacking(b,this->subtaskArr);
    doParsimPacking(b,this->serverID);
    doParsimPacking(b,this->isMalicious_);
}

void SubtaskRequest::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->subtaskID);
    doParsimUnpacking(b,this->subtaskArr);
    doParsimUnpacking(b,this->serverID);
    doParsimUnpacking(b,this->isMalicious_);
}

int SubtaskRequest::getSubtaskID() const
{
    return this->subtaskID;
}

void SubtaskRequest::setSubtaskID(int subtaskID)
{
    this->subtaskID = subtaskID;
}

const char * SubtaskRequest::getSubtaskArr() const
{
    return this->subtaskArr.c_str();
}

void SubtaskRequest::setSubtaskArr(const char * subtaskArr)
{
    this->subtaskArr = subtaskArr;
}

int SubtaskRequest::getServerID() const
{
    return this->serverID;
}

void SubtaskRequest::setServerID(int serverID)
{
    this->serverID = serverID;
}

bool SubtaskRequest::isMalicious() const
{
    return this->isMalicious_;
}

void SubtaskRequest::setIsMalicious(bool isMalicious)
{
    this->isMalicious_ = isMalicious;
}

class SubtaskRequestDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_subtaskID,
        FIELD_subtaskArr,
        FIELD_serverID,
        FIELD_isMalicious,
    };
  public:
    SubtaskRequestDescriptor();
    virtual ~SubtaskRequestDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SubtaskRequestDescriptor)

SubtaskRequestDescriptor::SubtaskRequestDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SubtaskRequest)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SubtaskRequestDescriptor::~SubtaskRequestDescriptor()
{
    delete[] propertyNames;
}

bool SubtaskRequestDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SubtaskRequest *>(obj)!=nullptr;
}

const char **SubtaskRequestDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SubtaskRequestDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SubtaskRequestDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SubtaskRequestDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_subtaskID
        FD_ISEDITABLE,    // FIELD_subtaskArr
        FD_ISEDITABLE,    // FIELD_serverID
        FD_ISEDITABLE,    // FIELD_isMalicious
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SubtaskRequestDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "subtaskID",
        "subtaskArr",
        "serverID",
        "isMalicious",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SubtaskRequestDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "subtaskID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "subtaskArr") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "serverID") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "isMalicious") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SubtaskRequestDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_subtaskID
        "string",    // FIELD_subtaskArr
        "int",    // FIELD_serverID
        "bool",    // FIELD_isMalicious
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SubtaskRequestDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SubtaskRequestDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SubtaskRequestDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SubtaskRequest *pp = omnetpp::fromAnyPtr<SubtaskRequest>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SubtaskRequestDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskRequest *pp = omnetpp::fromAnyPtr<SubtaskRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SubtaskRequest'", field);
    }
}

const char *SubtaskRequestDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SubtaskRequest *pp = omnetpp::fromAnyPtr<SubtaskRequest>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SubtaskRequestDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SubtaskRequest *pp = omnetpp::fromAnyPtr<SubtaskRequest>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: return long2string(pp->getSubtaskID());
        case FIELD_subtaskArr: return oppstring2string(pp->getSubtaskArr());
        case FIELD_serverID: return long2string(pp->getServerID());
        case FIELD_isMalicious: return bool2string(pp->isMalicious());
        default: return "";
    }
}

void SubtaskRequestDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskRequest *pp = omnetpp::fromAnyPtr<SubtaskRequest>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: pp->setSubtaskID(string2long(value)); break;
        case FIELD_subtaskArr: pp->setSubtaskArr((value)); break;
        case FIELD_serverID: pp->setServerID(string2long(value)); break;
        case FIELD_isMalicious: pp->setIsMalicious(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SubtaskRequest'", field);
    }
}

omnetpp::cValue SubtaskRequestDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SubtaskRequest *pp = omnetpp::fromAnyPtr<SubtaskRequest>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: return pp->getSubtaskID();
        case FIELD_subtaskArr: return pp->getSubtaskArr();
        case FIELD_serverID: return pp->getServerID();
        case FIELD_isMalicious: return pp->isMalicious();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SubtaskRequest' as cValue -- field index out of range?", field);
    }
}

void SubtaskRequestDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskRequest *pp = omnetpp::fromAnyPtr<SubtaskRequest>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: pp->setSubtaskID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_subtaskArr: pp->setSubtaskArr(value.stringValue()); break;
        case FIELD_serverID: pp->setServerID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_isMalicious: pp->setIsMalicious(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SubtaskRequest'", field);
    }
}

const char *SubtaskRequestDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SubtaskRequestDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SubtaskRequest *pp = omnetpp::fromAnyPtr<SubtaskRequest>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SubtaskRequestDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskRequest *pp = omnetpp::fromAnyPtr<SubtaskRequest>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SubtaskRequest'", field);
    }
}

Register_Class(SubtaskReply)

SubtaskReply::SubtaskReply(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SubtaskReply::SubtaskReply(const SubtaskReply& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SubtaskReply::~SubtaskReply()
{
}

SubtaskReply& SubtaskReply::operator=(const SubtaskReply& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SubtaskReply::copy(const SubtaskReply& other)
{
    this->subtaskID = other.subtaskID;
    this->result = other.result;
    this->serverID = other.serverID;
}

void SubtaskReply::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->subtaskID);
    doParsimPacking(b,this->result);
    doParsimPacking(b,this->serverID);
}

void SubtaskReply::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->subtaskID);
    doParsimUnpacking(b,this->result);
    doParsimUnpacking(b,this->serverID);
}

int SubtaskReply::getSubtaskID() const
{
    return this->subtaskID;
}

void SubtaskReply::setSubtaskID(int subtaskID)
{
    this->subtaskID = subtaskID;
}

int SubtaskReply::getResult() const
{
    return this->result;
}

void SubtaskReply::setResult(int result)
{
    this->result = result;
}

int SubtaskReply::getServerID() const
{
    return this->serverID;
}

void SubtaskReply::setServerID(int serverID)
{
    this->serverID = serverID;
}

class SubtaskReplyDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_subtaskID,
        FIELD_result,
        FIELD_serverID,
    };
  public:
    SubtaskReplyDescriptor();
    virtual ~SubtaskReplyDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SubtaskReplyDescriptor)

SubtaskReplyDescriptor::SubtaskReplyDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SubtaskReply)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SubtaskReplyDescriptor::~SubtaskReplyDescriptor()
{
    delete[] propertyNames;
}

bool SubtaskReplyDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SubtaskReply *>(obj)!=nullptr;
}

const char **SubtaskReplyDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SubtaskReplyDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SubtaskReplyDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int SubtaskReplyDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_subtaskID
        FD_ISEDITABLE,    // FIELD_result
        FD_ISEDITABLE,    // FIELD_serverID
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *SubtaskReplyDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "subtaskID",
        "result",
        "serverID",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int SubtaskReplyDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "subtaskID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "result") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "serverID") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *SubtaskReplyDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_subtaskID
        "int",    // FIELD_result
        "int",    // FIELD_serverID
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **SubtaskReplyDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SubtaskReplyDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SubtaskReplyDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SubtaskReply *pp = omnetpp::fromAnyPtr<SubtaskReply>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SubtaskReplyDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskReply *pp = omnetpp::fromAnyPtr<SubtaskReply>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SubtaskReply'", field);
    }
}

const char *SubtaskReplyDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SubtaskReply *pp = omnetpp::fromAnyPtr<SubtaskReply>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SubtaskReplyDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SubtaskReply *pp = omnetpp::fromAnyPtr<SubtaskReply>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: return long2string(pp->getSubtaskID());
        case FIELD_result: return long2string(pp->getResult());
        case FIELD_serverID: return long2string(pp->getServerID());
        default: return "";
    }
}

void SubtaskReplyDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskReply *pp = omnetpp::fromAnyPtr<SubtaskReply>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: pp->setSubtaskID(string2long(value)); break;
        case FIELD_result: pp->setResult(string2long(value)); break;
        case FIELD_serverID: pp->setServerID(string2long(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SubtaskReply'", field);
    }
}

omnetpp::cValue SubtaskReplyDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SubtaskReply *pp = omnetpp::fromAnyPtr<SubtaskReply>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: return pp->getSubtaskID();
        case FIELD_result: return pp->getResult();
        case FIELD_serverID: return pp->getServerID();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SubtaskReply' as cValue -- field index out of range?", field);
    }
}

void SubtaskReplyDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskReply *pp = omnetpp::fromAnyPtr<SubtaskReply>(object); (void)pp;
    switch (field) {
        case FIELD_subtaskID: pp->setSubtaskID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_result: pp->setResult(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_serverID: pp->setServerID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SubtaskReply'", field);
    }
}

const char *SubtaskReplyDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SubtaskReplyDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SubtaskReply *pp = omnetpp::fromAnyPtr<SubtaskReply>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SubtaskReplyDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SubtaskReply *pp = omnetpp::fromAnyPtr<SubtaskReply>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SubtaskReply'", field);
    }
}

Register_Class(GossipMessage)

GossipMessage::GossipMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

GossipMessage::GossipMessage(const GossipMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

GossipMessage::~GossipMessage()
{
}

GossipMessage& GossipMessage::operator=(const GossipMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void GossipMessage::copy(const GossipMessage& other)
{
    this->content = other.content;
}

void GossipMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->content);
}

void GossipMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->content);
}

const char * GossipMessage::getContent() const
{
    return this->content.c_str();
}

void GossipMessage::setContent(const char * content)
{
    this->content = content;
}

class GossipMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_content,
    };
  public:
    GossipMessageDescriptor();
    virtual ~GossipMessageDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(GossipMessageDescriptor)

GossipMessageDescriptor::GossipMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(GossipMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

GossipMessageDescriptor::~GossipMessageDescriptor()
{
    delete[] propertyNames;
}

bool GossipMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<GossipMessage *>(obj)!=nullptr;
}

const char **GossipMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *GossipMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int GossipMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 1+base->getFieldCount() : 1;
}

unsigned int GossipMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_content
    };
    return (field >= 0 && field < 1) ? fieldTypeFlags[field] : 0;
}

const char *GossipMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "content",
    };
    return (field >= 0 && field < 1) ? fieldNames[field] : nullptr;
}

int GossipMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "content") == 0) return baseIndex + 0;
    return base ? base->findField(fieldName) : -1;
}

const char *GossipMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_content
    };
    return (field >= 0 && field < 1) ? fieldTypeStrings[field] : nullptr;
}

const char **GossipMessageDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *GossipMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int GossipMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void GossipMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'GossipMessage'", field);
    }
}

const char *GossipMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string GossipMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        case FIELD_content: return oppstring2string(pp->getContent());
        default: return "";
    }
}

void GossipMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        case FIELD_content: pp->setContent((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GossipMessage'", field);
    }
}

omnetpp::cValue GossipMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        case FIELD_content: return pp->getContent();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'GossipMessage' as cValue -- field index out of range?", field);
    }
}

void GossipMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        case FIELD_content: pp->setContent(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GossipMessage'", field);
    }
}

const char *GossipMessageDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr GossipMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void GossipMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    GossipMessage *pp = omnetpp::fromAnyPtr<GossipMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'GossipMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

