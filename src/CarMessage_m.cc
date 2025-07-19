//
// Generated file, do not edit! Created by opp_msgtool 6.0 from CarMessage.msg.
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
#include "CarMessage_m.h"

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

Register_Class(CarMessage)

CarMessage::CarMessage(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

CarMessage::CarMessage(const CarMessage& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

CarMessage::~CarMessage()
{
}

CarMessage& CarMessage::operator=(const CarMessage& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void CarMessage::copy(const CarMessage& other)
{
    this->ID = other.ID;
    this->V = other.V;
    this->C = other.C;
    this->arrivalTime = other.arrivalTime;
    this->departureTime = other.departureTime;
    this->waitingTime = other.waitingTime;
    this->isStopped_ = other.isStopped_;
    this->arrivalRoadTime = other.arrivalRoadTime;
}

void CarMessage::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->ID);
    doParsimPacking(b,this->V);
    doParsimPacking(b,this->C);
    doParsimPacking(b,this->arrivalTime);
    doParsimPacking(b,this->departureTime);
    doParsimPacking(b,this->waitingTime);
    doParsimPacking(b,this->isStopped_);
    doParsimPacking(b,this->arrivalRoadTime);
}

void CarMessage::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->ID);
    doParsimUnpacking(b,this->V);
    doParsimUnpacking(b,this->C);
    doParsimUnpacking(b,this->arrivalTime);
    doParsimUnpacking(b,this->departureTime);
    doParsimUnpacking(b,this->waitingTime);
    doParsimUnpacking(b,this->isStopped_);
    doParsimUnpacking(b,this->arrivalRoadTime);
}

int CarMessage::getID() const
{
    return this->ID;
}

void CarMessage::setID(int ID)
{
    this->ID = ID;
}

double CarMessage::getV() const
{
    return this->V;
}

void CarMessage::setV(double V)
{
    this->V = V;
}

double CarMessage::getC() const
{
    return this->C;
}

void CarMessage::setC(double C)
{
    this->C = C;
}

double CarMessage::getArrivalTime() const
{
    return this->arrivalTime;
}

void CarMessage::setArrivalTime(double arrivalTime)
{
    this->arrivalTime = arrivalTime;
}

double CarMessage::getDepartureTime() const
{
    return this->departureTime;
}

void CarMessage::setDepartureTime(double departureTime)
{
    this->departureTime = departureTime;
}

double CarMessage::getWaitingTime() const
{
    return this->waitingTime;
}

void CarMessage::setWaitingTime(double waitingTime)
{
    this->waitingTime = waitingTime;
}

bool CarMessage::isStopped() const
{
    return this->isStopped_;
}

void CarMessage::setIsStopped(bool isStopped)
{
    this->isStopped_ = isStopped;
}

double CarMessage::getArrivalRoadTime() const
{
    return this->arrivalRoadTime;
}

void CarMessage::setArrivalRoadTime(double arrivalRoadTime)
{
    this->arrivalRoadTime = arrivalRoadTime;
}

class CarMessageDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_ID,
        FIELD_V,
        FIELD_C,
        FIELD_arrivalTime,
        FIELD_departureTime,
        FIELD_waitingTime,
        FIELD_isStopped,
        FIELD_arrivalRoadTime,
    };
  public:
    CarMessageDescriptor();
    virtual ~CarMessageDescriptor();

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

Register_ClassDescriptor(CarMessageDescriptor)

CarMessageDescriptor::CarMessageDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(CarMessage)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

CarMessageDescriptor::~CarMessageDescriptor()
{
    delete[] propertyNames;
}

bool CarMessageDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CarMessage *>(obj)!=nullptr;
}

const char **CarMessageDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CarMessageDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CarMessageDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int CarMessageDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_ID
        FD_ISEDITABLE,    // FIELD_V
        FD_ISEDITABLE,    // FIELD_C
        FD_ISEDITABLE,    // FIELD_arrivalTime
        FD_ISEDITABLE,    // FIELD_departureTime
        FD_ISEDITABLE,    // FIELD_waitingTime
        FD_ISEDITABLE,    // FIELD_isStopped
        FD_ISEDITABLE,    // FIELD_arrivalRoadTime
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *CarMessageDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "ID",
        "V",
        "C",
        "arrivalTime",
        "departureTime",
        "waitingTime",
        "isStopped",
        "arrivalRoadTime",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int CarMessageDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "ID") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "V") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "C") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "arrivalTime") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "departureTime") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "waitingTime") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "isStopped") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "arrivalRoadTime") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *CarMessageDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_ID
        "double",    // FIELD_V
        "double",    // FIELD_C
        "double",    // FIELD_arrivalTime
        "double",    // FIELD_departureTime
        "double",    // FIELD_waitingTime
        "bool",    // FIELD_isStopped
        "double",    // FIELD_arrivalRoadTime
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **CarMessageDescriptor::getFieldPropertyNames(int field) const
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

const char *CarMessageDescriptor::getFieldProperty(int field, const char *propertyName) const
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

int CarMessageDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CarMessage *pp = omnetpp::fromAnyPtr<CarMessage>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CarMessageDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CarMessage *pp = omnetpp::fromAnyPtr<CarMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CarMessage'", field);
    }
}

const char *CarMessageDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CarMessage *pp = omnetpp::fromAnyPtr<CarMessage>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CarMessageDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CarMessage *pp = omnetpp::fromAnyPtr<CarMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ID: return long2string(pp->getID());
        case FIELD_V: return double2string(pp->getV());
        case FIELD_C: return double2string(pp->getC());
        case FIELD_arrivalTime: return double2string(pp->getArrivalTime());
        case FIELD_departureTime: return double2string(pp->getDepartureTime());
        case FIELD_waitingTime: return double2string(pp->getWaitingTime());
        case FIELD_isStopped: return bool2string(pp->isStopped());
        case FIELD_arrivalRoadTime: return double2string(pp->getArrivalRoadTime());
        default: return "";
    }
}

void CarMessageDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CarMessage *pp = omnetpp::fromAnyPtr<CarMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ID: pp->setID(string2long(value)); break;
        case FIELD_V: pp->setV(string2double(value)); break;
        case FIELD_C: pp->setC(string2double(value)); break;
        case FIELD_arrivalTime: pp->setArrivalTime(string2double(value)); break;
        case FIELD_departureTime: pp->setDepartureTime(string2double(value)); break;
        case FIELD_waitingTime: pp->setWaitingTime(string2double(value)); break;
        case FIELD_isStopped: pp->setIsStopped(string2bool(value)); break;
        case FIELD_arrivalRoadTime: pp->setArrivalRoadTime(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CarMessage'", field);
    }
}

omnetpp::cValue CarMessageDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CarMessage *pp = omnetpp::fromAnyPtr<CarMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ID: return pp->getID();
        case FIELD_V: return pp->getV();
        case FIELD_C: return pp->getC();
        case FIELD_arrivalTime: return pp->getArrivalTime();
        case FIELD_departureTime: return pp->getDepartureTime();
        case FIELD_waitingTime: return pp->getWaitingTime();
        case FIELD_isStopped: return pp->isStopped();
        case FIELD_arrivalRoadTime: return pp->getArrivalRoadTime();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CarMessage' as cValue -- field index out of range?", field);
    }
}

void CarMessageDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CarMessage *pp = omnetpp::fromAnyPtr<CarMessage>(object); (void)pp;
    switch (field) {
        case FIELD_ID: pp->setID(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_V: pp->setV(value.doubleValue()); break;
        case FIELD_C: pp->setC(value.doubleValue()); break;
        case FIELD_arrivalTime: pp->setArrivalTime(value.doubleValue()); break;
        case FIELD_departureTime: pp->setDepartureTime(value.doubleValue()); break;
        case FIELD_waitingTime: pp->setWaitingTime(value.doubleValue()); break;
        case FIELD_isStopped: pp->setIsStopped(value.boolValue()); break;
        case FIELD_arrivalRoadTime: pp->setArrivalRoadTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CarMessage'", field);
    }
}

const char *CarMessageDescriptor::getFieldStructName(int field) const
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

omnetpp::any_ptr CarMessageDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CarMessage *pp = omnetpp::fromAnyPtr<CarMessage>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CarMessageDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CarMessage *pp = omnetpp::fromAnyPtr<CarMessage>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CarMessage'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

